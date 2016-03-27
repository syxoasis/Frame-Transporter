#include <stdlib.h>
#include <check.h>
#include <unistd.h>
#include <time.h>

/* Use:

CK_RUN_CASE="base32-core" make test
CK_RUN_SUITE="base32" make test

*/

Suite * base32_tsuite(void);
Suite * fd_tsuite(void);
Suite * boolean_tsuite(void);
Suite * config_tsuite(void);
Suite * log_tsuite(void);
Suite * daemon_tsuite(void);

///

Suite * sanity_tsuite(void)
{
	Suite *s = suite_create("sanity");
	return s;
}

int main()
{
	int number_failed;
	
	srand(time(NULL) + getpid());
	SRunner *sr = srunner_create(sanity_tsuite());

	srunner_add_suite(sr, config_tsuite());
	srunner_add_suite(sr, base32_tsuite());
	srunner_add_suite(sr, fd_tsuite());
	srunner_add_suite(sr, boolean_tsuite());
	srunner_add_suite(sr, log_tsuite());
	srunner_add_suite(sr, daemon_tsuite());

	srunner_run_all(sr, CK_VERBOSE /*CK_NORMAL*/);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}