#include <stdlib.h>
#include <stdbool.h>

#include <ft.h>

///

SSL_CTX * ssl_ctx;
struct ft_context context;

struct ft_list streams;
struct ft_list listeners;

///

bool on_read(struct ft_stream * established_sock, struct ft_frame * frame)
{
//	ft_frame_fwrite(frame, stdout);
	ft_frame_flip(frame);
	bool ok = ft_stream_write(established_sock, frame);
	if (!ok)
	{
		FT_ERROR("Cannot write a frame!");
		ft_frame_return(frame);
	}

	return true;
}

struct ft_stream_delegate stream_delegate = 
{
	.read = on_read,
	.error = NULL,
};

static void streams_on_remove(struct ft_list * list, struct ft_list_node * node)
{
	struct ft_stream * stream = (struct ft_stream *)node->data;

	FT_INFO("Stats: Re:%u We:%u+%u Rb:%lu Wb:%lu",
		stream->stats.read_events,
		stream->stats.write_events,
		stream->stats.write_direct,
		stream->stats.read_bytes,
		stream->stats.write_bytes
	);

	ft_stream_fini(stream);
}

///

static bool on_accept_cb(struct ft_listener * listening_socket, int fd, const struct sockaddr * client_addr, socklen_t client_addr_len)
{
	bool ok;

	struct ft_list_node * new_node = ft_list_node_new(sizeof(struct ft_stream));
	if (new_node == NULL) return false;

	struct ft_stream * established_sock = (struct ft_stream *)&new_node->data;

	ok = ft_stream_accept(established_sock, &stream_delegate, listening_socket, fd, client_addr, client_addr_len);
	if (!ok)
	{
		ft_list_node_del(new_node);
		return false;
	}

	ft_stream_set_partial(established_sock, true);

	// Initiate SSL
	ok = ft_stream_enable_ssl(established_sock, ssl_ctx);
	if (!ok) return EXIT_FAILURE;


	ft_list_add(&streams, new_node);

	return true;
}

struct ft_listener_delegate listener_delegate =
{
	.accept = on_accept_cb,
};

///

static void on_termination_cb(struct ft_context * context, void * data)
{
	FT_LIST_FOR(&streams, node)
	{
		struct ft_stream * stream = (struct ft_stream *)node->data;
		ft_stream_cntl(stream, FT_STREAM_READ_STOP | FT_STREAM_WRITE_STOP);
	}

	ft_listener_list_cntl(&listeners, FT_LISTENER_STOP);
}


static void on_check_cb(struct ev_loop * loop, ev_prepare * check, int revents)
{
	size_t avail = ft_pool_count_available_frames(&context.frame_pool);
	bool throttle = avail < 8;

	if (throttle)
	{
		// We can still allocated new zone
		if (ft_pool_count_zones(&context.frame_pool) < 2) throttle = false;
	}

	// Check all established socket and remove closed ones
restart:
	FT_LIST_FOR(&streams, node)
	{
		struct ft_stream * sock = (struct ft_stream *)node->data;

		if (ft_stream_is_shutdown(sock))
		{
			ft_list_remove(&streams, node);
			goto restart;
		}

		if ((throttle) && (sock->flags.read_throttle == false))
		{
			ft_stream_cntl(sock, FT_STREAM_READ_PAUSE);
		}
		else if ((!throttle) && (sock->flags.read_throttle == true))
		{
			ft_stream_cntl(sock, FT_STREAM_READ_RESUME);
		}
	}
}

int main(int argc, char const *argv[])
{
	bool ok;
	int rc;

	//ft_log_verbose(true);
	//ft_config.log_trace_mask |= FT_TRACE_ID_STREAM | FT_TRACE_ID_EVENT_LOOP;

	ft_initialise();
	
	// Initializa context
	ok = ft_context_init(&context);
	if (!ok) return EXIT_FAILURE;

	ft_context_at_termination(&context, on_termination_cb, NULL);

	// Initialize OpenSSL context
	ssl_ctx = SSL_CTX_new(SSLv23_server_method());
	if (ssl_ctx == NULL) return EXIT_FAILURE;

	long ssloptions = SSL_OP_ALL | SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION | SSL_OP_NO_COMPRESSION
	| SSL_OP_CIPHER_SERVER_PREFERENCE | SSL_OP_SINGLE_DH_USE;
	SSL_CTX_set_options(ssl_ctx, ssloptions);

	rc = SSL_CTX_use_PrivateKey_file(ssl_ctx, "./key.pem", SSL_FILETYPE_PEM);
	if (rc != 1) return EXIT_FAILURE;

	rc = SSL_CTX_use_certificate_file(ssl_ctx, "./cert.pem", SSL_FILETYPE_PEM);
	if (rc != 1) return EXIT_FAILURE;

	ft_list_init(&streams, streams_on_remove);

	// Prepare listening socket(s)
	ft_listener_list_init(&listeners);

	rc = ft_listener_list_extend(&listeners, &listener_delegate, &context, AF_INET, SOCK_STREAM, "127.0.0.1", "12345");
	if (rc < 0) return EXIT_FAILURE;

	rc = ft_listener_list_extend(&listeners, &listener_delegate, &context, AF_UNIX, SOCK_STREAM, "/tmp/sctext.tmp", NULL);
	if (rc < 0) return EXIT_FAILURE;

	// Registed check handler
	ev_prepare prepare_w;
	ev_prepare_init(&prepare_w, on_check_cb);
	ev_prepare_start(context.ev_loop, &prepare_w);
	ev_unref(context.ev_loop);

	// Start listening
	ft_listener_list_cntl(&listeners, FT_LISTENER_START);

	// Enter event loop
	ft_context_run(&context);

	// Clean up
	ft_list_fini(&streams);
	ft_list_fini(&listeners);
	ft_context_fini(&context);

	return EXIT_SUCCESS;
}
