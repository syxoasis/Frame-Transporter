#include "_ft_internal.h"

///

struct ft_log_stats ft_log_stats = {
	.trace_count = 0,
	.debug_count = 0,
	.info_count = 0,
	.warn_count = 0,
	.error_count = 0,
	.fatal_count = 0,
	.audit_count = 0,
};

static struct ft_context * _ft_log_context = NULL;

///

static inline int _ft_logrecord_build(struct ft_logrecord * le, char level,const char * format, va_list args)
{
	le->timestamp = ft_safe_now(_ft_log_context);
	le->pid = getpid();
	le->level = level;

	if (format != NULL) return vsnprintf(le->message, sizeof(le->message), format, args);

	le->message[0] = '\0';
	return 0;
}

///

void _ft_log_v(const char level, const char * format, va_list args)
{
	static __thread struct ft_logrecord le;
	int le_message_length = _ft_logrecord_build(&le, level, format, args);
	ft_logrecord_process(&le, le_message_length);
}

void _ft_log_errno_v(int errnum, const char level, const char * format, va_list args)
{
	static __thread struct ft_logrecord le;
	int le_message_length = _ft_logrecord_build(&le, level, format, args);

	if (le_message_length > 0)
	{
		le.message[le_message_length++] = ':';
		le.message[le_message_length++] = ' ';
	}
	le.message[le_message_length] = '\0';

#ifdef _GNU_SOURCE
	// The GNU-specific strerror_r() is in use ...
	char * im = strerror_r(errnum, le.message + le_message_length, sizeof(le.message)-le_message_length);
	int len = strlen(im);
	if (len > sizeof(le.message)-le_message_length) len = sizeof(le.message)-le_message_length;
	if (im != (le.message + le_message_length)) strncpy(le.message + le_message_length, im, len);
	le_message_length += len;
#else
	strerror_r(errnum, le.message + le_message_length, sizeof(le.message)-le_message_length);
	le_message_length += strlen(le.message + le_message_length);
#endif

	le_message_length += snprintf(le.message + le_message_length, sizeof(le.message)-le_message_length, " (%d)", errnum);

	ft_logrecord_process(&le, le_message_length);
}

void _ft_log_openssl_err_v(const char level, const char * format, va_list args)
{
	static __thread struct ft_logrecord le;
	int le_message_length = _ft_logrecord_build(&le, level, format, args);

	unsigned long es = CRYPTO_thread_id();
	while (true)
	{
		const char * file;
		int line;
		const char * data;
		int flags;
		unsigned long code = ERR_get_error_line_data(&file, &line, &data, &flags);
		if (code == 0) break;

		char buf[256];
		ERR_error_string_n(code, buf, sizeof(buf));

		int len = snprintf(le.message+le_message_length, sizeof(le.message) - (le_message_length+1), 
			"\n                                       SSL: %lu:%s:%s:%d:%s",
			es, buf, file, line, (flags & ERR_TXT_STRING) ? data : ""
		);
		le_message_length += len;
	}

	ft_logrecord_process(&le, le_message_length);
}


static void _ft_log_libev_on_syserr(const char * msg)
{
	// See ERROR HANDLING in libev
	FT_FATAL("%s", msg);
	abort();
}

///

void ft_log_initialise_()
{
	ev_set_syserr_cb(_ft_log_libev_on_syserr);
}

void ft_log_finalise()
{
	if ((ft_config.log_backend != NULL) && (ft_config.log_backend->fini != NULL))
		ft_config.log_backend->fini();

	fflush(stderr);
}

void ft_log_context(struct ft_context * context)
{
	if (context == NULL)
	{
		assert(_ft_log_context != NULL);
		_ft_log_context = NULL;
		return;
	}

	assert(_ft_log_context == NULL);
	_ft_log_context = context;
}


void ft_log_backend_switch(struct ft_log_backend * backend)
{
	if ((ft_config.log_backend != NULL) && (ft_config.log_backend->fini != NULL))
		ft_config.log_backend->fini();

	ft_config.log_backend = backend;
}


void ft_logrecord_process(struct ft_logrecord * le, int le_message_length)
{
#ifndef RELEASE
	if ((ft_config.log_backend == NULL) || (ft_config.log_backend->process == NULL))
	{
		fprintf(stderr, "Log config backend is not configued!\n");
		return;
	}
#endif
	ft_config.log_backend->process(le, le_message_length);
}
