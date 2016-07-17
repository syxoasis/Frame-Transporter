#include "_ft_internal.h"

static void heartbeat_on_timer(struct ev_loop * loop, ev_timer * w, int revents);

///

void heartbeat_init(struct heartbeat * this, struct context * context)
{
	assert(this != NULL);
	assert(context != NULL);

	this->context = context;
	this->last_beat = 0.0;
	this->first_watcher = NULL;
	this->last_watcher = NULL;

	ev_timer_init(&this->timer_w, heartbeat_on_timer, 0.0, libsccmn_config.heartbeat_interval);
	ev_set_priority(&this->timer_w, -2);
	this->timer_w.data = this;
}

void heartbeat_start(struct heartbeat * this)
{
	assert(this != NULL);

	ev_timer_start(this->context->ev_loop, &this->timer_w);
	ev_unref(this->context->ev_loop);
}

void heartbeat_stop(struct heartbeat * this)
{
	assert(this != NULL);

	ev_ref(this->context->ev_loop);
	ev_timer_stop(this->context->ev_loop, &this->timer_w);
}


void heartbeat_add(struct heartbeat * this, struct heartbeat_watcher * watcher, heartbeat_cb cb)
{
	assert(this != NULL);
	assert(watcher != NULL);

	watcher->cb = cb;

	if (this->last_watcher == NULL)
	{
		assert(this->first_watcher == NULL);

		this->first_watcher = watcher;
		this->last_watcher = watcher;
		watcher->next = NULL;
		watcher->prev = NULL;
	}
	else
	{
		this->last_watcher->next = watcher;
		watcher->next = NULL;
		watcher->prev = this->last_watcher;
		this->last_watcher = watcher;
	}
}

void heartbeat_remove(struct heartbeat * this, struct heartbeat_watcher * watcher)
{
	assert(this != NULL);
	assert(watcher != NULL);

	if ((watcher->prev == NULL) && (watcher->next == NULL))
	{
		assert(this->first_watcher == watcher);
		assert(this->last_watcher == watcher);
		this->first_watcher = NULL;
		this->last_watcher = NULL;
		return;
	}

	assert((this->first_watcher != NULL) || (this->last_watcher != NULL));

	if (watcher->prev == NULL)
	{
		assert(this->first_watcher == watcher);
		this->first_watcher = watcher->next;
		if (this->first_watcher != NULL) this->first_watcher->prev = NULL;
	}
	else
	{
		watcher->prev->next = watcher->next;
	}

	if (watcher->next == NULL)
	{
		assert(this->last_watcher == watcher);
		this->last_watcher = watcher->prev;
		if (this->last_watcher != NULL) this->last_watcher->next = NULL;
	}
	else
	{
		watcher->next->prev = watcher->prev;
	}

	watcher->prev = NULL;
	watcher->next = NULL;
}


void heartbeat_on_timer(struct ev_loop * loop, ev_timer * w, int revents)
{
	ev_tstamp now = ev_now(loop);
	struct heartbeat * this = w->data;

	for (struct heartbeat_watcher * watcher = this->first_watcher; watcher != NULL; watcher = watcher->next)
	{
		if (watcher->cb == NULL) continue;
		watcher->cb(watcher, this, now);
	}

	// Flush logs
	ft_log_flush();

	//Lag detector
	if (this->last_beat > 0.0)
	{
		double delta = (now - this->last_beat) - w->repeat;
		if (delta > libsccmn_config.lag_detector_sensitivity)
		{
			FT_WARN("Lag (~ %.2lf sec.) detected", delta);
		}
	}
	this->last_beat = now;

}
