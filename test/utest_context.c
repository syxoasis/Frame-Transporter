#include "testutils.h"

//TODO: unit test of flag.running
//TODO: unit test of started_at
//TODO: unit test of shutdown_at
//TODO: unit test of forceful shutdown

///

START_TEST(ft_context_empty_utest)
{
	bool ok;

	struct ft_context context;
	ok = ft_context_init(&context);
	ck_assert_int_eq(ok, true);

	// Will immediately stop since there is nothing to do (no watcher is active)
	ft_context_run(&context);

	ft_context_fini(&context);

	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
}
END_TEST

///

void ft_context_at_termination_utest_callback(struct ft_context * context, void * data)
{
	ck_assert_ptr_eq(data, (void*)33);

	// This is cause event loop to terminate
	ev_unref(context->ev_loop);
}

START_TEST(ft_context_at_termination_utest)
{
	bool ok;

	struct ft_context context;
	ok = ft_context_init(&context);
	ck_assert_int_eq(ok, true);

	// Add a first callback
	ok = ft_context_at_termination(&context, ft_context_at_termination_utest_callback, (void*)33);
	ck_assert_int_eq(ok, true);

	// Add a second one too
	ok = ft_context_at_termination(&context, ft_context_at_termination_utest_callback, (void*)33);
	ck_assert_int_eq(ok, true);

	int rc = raise(SIGTERM);
	ck_assert_int_eq(rc, 0);

	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);

	ft_context_run(&context);

	ft_context_fini(&context);
}
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);

END_TEST

///

void ft_context_at_heartbeat_utest_callback(struct ft_context * context, void * data)
{
	ck_assert_ptr_eq(data, (void*)33);

	// This is cause event loop to terminate
	ev_unref(context->ev_loop);
}

START_TEST(ft_context_at_heartbeat_utest)
{
	bool ok;

	ft_config.heartbeat_interval = 0.01;

	struct ft_context context;
	ok = ft_context_init(&context);
	ck_assert_int_eq(ok, true);

	// Add a heartbeat callback
	ok = ft_context_at_heartbeat(&context, ft_context_at_heartbeat_utest_callback, (void*)33);
	ck_assert_int_eq(ok, true);

	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);
	ev_ref(context.ev_loop);

	ft_context_run(&context);

	ft_context_fini(&context);

	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
}
END_TEST

///

Suite * ft_context_tsuite(void)
{
	TCase *tc;
	Suite *s = suite_create("ft_context");

	tc = tcase_create("context_evloop");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, ft_context_empty_utest);
	tcase_add_test(tc, ft_context_at_termination_utest);
	tcase_add_test(tc, ft_context_at_heartbeat_utest);

	return s;
}
