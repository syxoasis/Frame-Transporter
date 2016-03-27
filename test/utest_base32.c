#include <check.h>

#include <libsccmn.h>

////

START_TEST(base32_encode_utest)
{
	int rc;

	char result[100];
	size_t result_len = sizeof(result)-1;

	char input[] = "1234567890";
	size_t input_len = sizeof(input);

	rc = base32_encode(result, &result_len, input, input_len);

	ck_assert_int_eq(rc, 18);
	ck_assert_str_eq(result, "GEZDGNBVGY3TQOJQAA");
}
END_TEST

///

Suite * base32_tsuite(void)
{
	TCase *tc;
	Suite *s = suite_create("base32");

	tc = tcase_create("base32-core");
	suite_add_tcase(s, tc);
	tcase_add_test(tc, base32_encode_utest);

	return s;
}
