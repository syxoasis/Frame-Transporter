#include "testutils.h"

////

START_TEST(log_normal_debug_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));

	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_DEBUG("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	FT_DEBUG_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ck_assert_int_eq(ft_log_stats.debug_count, 2);

	ft_log_verbose(false);
	FT_DEBUG("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	FT_DEBUG_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 2);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_normal_info_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_INFO("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_INFO_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 2);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_normal_warn_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_WARN("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_WARN_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 2);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST


START_TEST(log_normal_error_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_ERROR("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_ERROR_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 2);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_normal_fatal_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_FATAL("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_FATAL_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 2);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_normal_audit_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_AUDIT("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_AUDIT_P("Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 2);
}
END_TEST

//

START_TEST(log_errno_info_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_INFO_ERRNO(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_INFO_ERRNO_P(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 2);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_errno_warn_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_WARN_ERRNO(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_WARN_ERRNO_P(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 2);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);	
}
END_TEST

START_TEST(log_errno_error_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_ERROR_ERRNO(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_ERROR_ERRNO_P(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 2);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_errno_fatal_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_FATAL_ERRNO(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_FATAL_ERRNO_P(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 2);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST


START_TEST(log_errno_audit_utest)
{
	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ft_log_verbose(true);
	FT_AUDIT_ERRNO(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	ft_log_verbose(false);
	FT_AUDIT_ERRNO_P(EAGAIN, "Log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 2);
}
END_TEST

///

START_TEST(log_reopen_nofile_utest)
{
	ck_assert_ptr_eq(ft_config.log_file.file, NULL);
	ck_assert_ptr_eq(ft_config.log_file.filename, NULL);

	bool ok = ft_log_file_reopen();
	ck_assert_int_eq(ok, true);

	ck_assert_ptr_eq(ft_config.log_file.file, NULL);
	ck_assert_ptr_eq(ft_config.log_file.filename, NULL);

	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
}
END_TEST


START_TEST(log_reopen_wfile_utest)
{
	ck_assert_ptr_eq(ft_config.log_file.file, NULL);
	ck_assert_ptr_eq(ft_config.log_file.filename, NULL);

	bool ok = ft_log_file_set("./log.txt");
	ck_assert_int_eq(ok, true);
	ck_assert_ptr_ne(ft_config.log_file.file, NULL);
	ck_assert_ptr_ne(ft_config.log_file.filename, NULL);

	FT_INFO_ERRNO(EAGAIN, "Log message test!");

	ok = ft_log_file_reopen();
	ck_assert_int_eq(ok, true);

	ok = ft_log_file_set(NULL);
	ck_assert_int_eq(ok, true);
	ck_assert_ptr_eq(ft_config.log_file.file, NULL);
	ck_assert_ptr_eq(ft_config.log_file.filename, NULL);

	int rc = unlink("./log.txt");
	ck_assert_int_eq(rc, 0);

	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
}
END_TEST


START_TEST(log_reopen_sighup_utest)
{
	ck_assert_ptr_eq(ft_config.log_file.file, NULL);
	ck_assert_ptr_eq(ft_config.log_file.filename, NULL);

	bool ok = ft_log_file_set("./log.txt");
	ck_assert_int_eq(ok, true);
	ck_assert_ptr_ne(ft_config.log_file.file, NULL);
	ck_assert_str_eq(ft_config.log_file.filename, "./log.txt");

	FT_INFO("Log message test!");

	struct ft_context context;
	ok = ft_context_init(&context);
	ck_assert_int_eq(ok, true);

	ft_log_handle_sighup(&context);

	ev_feed_signal(SIGHUP);
	ev_run(context.ev_loop, EVBREAK_ONE);

	FT_INFO("Log message test!");

	ev_feed_signal(SIGHUP);
	ev_run(context.ev_loop, EVBREAK_ONE);

	int rc = system("grep \"Log file is reopen\" ./log.txt");
	ck_assert_int_eq(rc, 0);

	rc = unlink("./log.txt");
	ck_assert_int_eq(rc, 0);

	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);

	ft_log_handle_sighup(&context);

	ck_assert_int_eq(ft_log_stats.warn_count, 1);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
}
END_TEST

///

START_TEST(log_openssl_info_utest)
{
	unsigned long code;

	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,3,__FILE__,__LINE__);
	ERR_put_error(1,2,4,__FILE__,__LINE__);
	ERR_put_error(1,2,5,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002003);

	ft_log_verbose(true);
	FT_INFO_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,6,__FILE__,__LINE__);
	ERR_put_error(1,2,7,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002006);

	ft_log_verbose(false);
	FT_INFO_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	FT_INFO_OPENSSL_P("OpenSSL log message test (no SSL error)!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 3);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 3);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_openssl_warn_utest)
{
	unsigned long code;

	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,3,__FILE__,__LINE__);
	ERR_put_error(1,2,4,__FILE__,__LINE__);
	ERR_put_error(1,2,5,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002003);

	ft_log_verbose(true);
	FT_WARN_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,6,__FILE__,__LINE__);
	ERR_put_error(1,2,7,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002006);

	ft_log_verbose(false);
	FT_WARN_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	FT_WARN_OPENSSL_P("OpenSSL log message test (no SSL error)!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 3);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 3);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_openssl_error_utest)
{
	unsigned long code;

	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,3,__FILE__,__LINE__);
	ERR_put_error(1,2,4,__FILE__,__LINE__);
	ERR_put_error(1,2,5,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002003);

	ft_log_verbose(true);
	FT_ERROR_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,6,__FILE__,__LINE__);
	ERR_put_error(1,2,7,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002006);

	ft_log_verbose(false);
	FT_ERROR_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	FT_ERROR_OPENSSL_P("OpenSSL log message test (no SSL error)!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 3);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 3);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_openssl_fatal_utest)
{
	unsigned long code;

	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,3,__FILE__,__LINE__);
	ERR_put_error(1,2,4,__FILE__,__LINE__);
	ERR_put_error(1,2,5,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002003);

	ft_log_verbose(true);
	FT_FATAL_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,6,__FILE__,__LINE__);
	ERR_put_error(1,2,7,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002006);

	ft_log_verbose(false);
	FT_FATAL_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	FT_FATAL_OPENSSL_P("OpenSSL log message test (no SSL error)!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 3);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 3);
	ck_assert_int_eq(ft_log_stats.audit_count, 0);
}
END_TEST

START_TEST(log_openssl_audit_utest)
{
	unsigned long code;

	ft_config.log_file.flush_counter_max = 1;
	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,3,__FILE__,__LINE__);
	ERR_put_error(1,2,4,__FILE__,__LINE__);
	ERR_put_error(1,2,5,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002003);

	ft_log_verbose(true);
	FT_AUDIT_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 1);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ERR_put_error(1,2,6,__FILE__,__LINE__);
	ERR_put_error(1,2,7,__FILE__,__LINE__);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0x1002006);

	ft_log_verbose(false);
	FT_AUDIT_OPENSSL("OpenSSL log message test!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 2);

	FT_AUDIT_OPENSSL_P("OpenSSL log message test (no SSL error)!");
	ck_assert_int_eq(ft_config.log_file.flush_counter, 3);

	code = ERR_peek_error();
	ck_assert_int_eq(code, 0);

	ft_log_file_flush(ft_safe_now(NULL));
	ck_assert_int_eq(ft_config.log_file.flush_counter, 0);

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 0);
	ck_assert_int_eq(ft_log_stats.warn_count, 0);
	ck_assert_int_eq(ft_log_stats.error_count, 0);
	ck_assert_int_eq(ft_log_stats.fatal_count, 0);
	ck_assert_int_eq(ft_log_stats.audit_count, 3);
}
END_TEST


START_TEST(log_if_else_block_utest)
{
	ft_config.log_verbose = false;

	if (true) FT_TRACE(0, "Test");
	else FT_INFO_P("Test");

	if (true) FT_INFO("Test begin --!!--");
	else FT_TRACE(0, "Test");

	//

	if (true) FT_DEBUG("Test");
	else FT_DEBUG_P("Test");

	if (true) FT_INFO("Test");
	else FT_INFO_P("Test");

	if (true) FT_WARN("Test");
	else FT_WARN_P("Test");

	if (true) FT_ERROR("Test");
	else FT_ERROR_P("Test");

	if (true) FT_FATAL("Test");
	else FT_FATAL_P("Test");

	if (true) FT_AUDIT("Test");
	else FT_AUDIT_P("Test");

	//

	if (true) FT_DEBUG_P("Test");
	else FT_DEBUG("Test");

	if (true) FT_INFO_P("Test");
	else FT_INFO("Test");

	if (true) FT_WARN_P("Test");
	else FT_WARN("Test");

	if (true) FT_ERROR_P("Test");
	else FT_ERROR("Test");

	if (true) FT_FATAL_P("Test");
	else FT_FATAL("Test");

	if (true) FT_AUDIT_P("Test");
	else FT_AUDIT("Test");

	//

	if (true) FT_DEBUG_ERRNO(1, "Test");
	else FT_DEBUG_ERRNO_P(1, "Test");

	if (true) FT_INFO_ERRNO(1, "Test");
	else FT_INFO_ERRNO_P(1, "Test");

	if (true) FT_WARN_ERRNO(1, "Test");
	else FT_WARN_ERRNO_P(1, "Test");

	if (true) FT_ERROR_ERRNO(1, "Test");
	else FT_ERROR_ERRNO_P(1, "Test");

	if (true) FT_FATAL_ERRNO(1, "Test");
	else FT_FATAL_ERRNO_P(1, "Test");

	if (true) FT_AUDIT_ERRNO(1, "Test");
	else FT_AUDIT_ERRNO_P(1, "Test");

	//

	if (true) FT_DEBUG_ERRNO_P(1, "Test");
	else FT_DEBUG_ERRNO(1, "Test");

	if (true) FT_INFO_ERRNO_P(1, "Test");
	else FT_INFO_ERRNO(1, "Test");

	if (true) FT_WARN_ERRNO_P(1, "Test");
	else FT_WARN_ERRNO(1, "Test");

	if (true) FT_ERROR_ERRNO_P(1, "Test");
	else FT_ERROR_ERRNO(1, "Test");

	if (true) FT_FATAL_ERRNO_P(1, "Test");
	else FT_FATAL_ERRNO(1, "Test");

	if (true) FT_AUDIT_ERRNO_P(1, "Test");
	else FT_AUDIT_ERRNO(1, "Test");

	//

	if (true) FT_DEBUG_OPENSSL("Test");
	else FT_DEBUG_OPENSSL_P("Test");

	if (true) FT_INFO_OPENSSL("Test");
	else FT_INFO_OPENSSL_P("Test");

	if (true) FT_WARN_OPENSSL("Test");
	else FT_WARN_OPENSSL_P("Test");

	if (true) FT_ERROR_OPENSSL("Test");
	else FT_ERROR_OPENSSL_P("Test");

	if (true) FT_FATAL_OPENSSL("Test");
	else FT_FATAL_OPENSSL_P("Test");

	if (true) FT_AUDIT_OPENSSL("Test");
	else FT_AUDIT_OPENSSL_P("Test");

	//

	if (true) FT_DEBUG_OPENSSL_P("Test");
	else FT_DEBUG_OPENSSL("Test");

	if (true) FT_INFO_OPENSSL_P("Test");
	else FT_INFO_OPENSSL("Test");

	if (true) FT_WARN_OPENSSL_P("Test");
	else FT_WARN_OPENSSL("Test");

	if (true) FT_ERROR_OPENSSL_P("Test");
	else FT_ERROR_OPENSSL("Test");

	if (true) FT_FATAL_OPENSSL_P("Test");
	else FT_FATAL_OPENSSL("Test");

	if (true) FT_AUDIT_OPENSSL_P("Test");
	else FT_AUDIT_OPENSSL("Test");

	ck_assert_int_eq(ft_log_stats.debug_count, 0);
	ck_assert_int_eq(ft_log_stats.info_count, 7);
	ck_assert_int_eq(ft_log_stats.warn_count, 6);
	ck_assert_int_eq(ft_log_stats.error_count, 6);
	ck_assert_int_eq(ft_log_stats.fatal_count, 6);
	ck_assert_int_eq(ft_log_stats.audit_count, 6);

	//
	ft_config.log_verbose = true;

	if (true) FT_DEBUG("Test");
	else FT_DEBUG_P("Test");

	if (true) FT_DEBUG_P("Test");
	else FT_DEBUG("Test");

	if (true) FT_DEBUG_ERRNO(1, "Test");
	else FT_DEBUG_ERRNO_P(1, "Test");

	if (true) FT_DEBUG_ERRNO_P(1, "Test");
	else FT_DEBUG_ERRNO(1, "Test");

	if (true) FT_DEBUG_OPENSSL("Test");
	else FT_DEBUG_OPENSSL_P("Test");

	if (true) FT_DEBUG_OPENSSL_P("Test");
	else FT_DEBUG_OPENSSL("Test");

	ck_assert_int_eq(ft_log_stats.debug_count, 6);
	ck_assert_int_eq(ft_log_stats.info_count, 7);
	ck_assert_int_eq(ft_log_stats.warn_count, 6);
	ck_assert_int_eq(ft_log_stats.error_count, 6);
	ck_assert_int_eq(ft_log_stats.fatal_count, 6);
	ck_assert_int_eq(ft_log_stats.audit_count, 6);
}
END_TEST

///

Suite * log_tsuite(void)
{
	TCase *tc;
	Suite *s = suite_create("log");

	tc = tcase_create("log-normal");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, log_normal_debug_utest);
	tcase_add_test(tc, log_normal_info_utest);
	tcase_add_test(tc, log_normal_warn_utest);
	tcase_add_test(tc, log_normal_error_utest);
	tcase_add_test(tc, log_normal_fatal_utest);
	tcase_add_test(tc, log_normal_audit_utest);

	tc = tcase_create("log-errno");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, log_errno_info_utest);
	tcase_add_test(tc, log_errno_warn_utest);
	tcase_add_test(tc, log_errno_error_utest);
	tcase_add_test(tc, log_errno_fatal_utest);
	tcase_add_test(tc, log_errno_audit_utest);

	tc = tcase_create("log-openssl");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, log_openssl_info_utest);
	tcase_add_test(tc, log_openssl_warn_utest);
	tcase_add_test(tc, log_openssl_error_utest);
	tcase_add_test(tc, log_openssl_fatal_utest);
	tcase_add_test(tc, log_openssl_audit_utest);

	tc = tcase_create("log-reopen");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, log_reopen_nofile_utest);
	tcase_add_test(tc, log_reopen_wfile_utest);
	tcase_add_test(tc, log_reopen_sighup_utest);

	tc = tcase_create("log-misc");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, log_if_else_block_utest);

	return s;
}
