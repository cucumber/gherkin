#include <check.h>
#include <stdlib.h>
#include <string.h>

/* Include the production code directly */
#include "c/src/token_matcher.c"

START_TEST(test_token_matcher_null_safety)
{
    /* Invariant: token_matcher creation/use must never crash or dereference NULL,
       even under adversarial or boundary inputs */
    const char *payloads[] = {
        "",                          /* boundary: empty input */
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", /* large input */
        "valid_token"                /* valid input */
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        TokenMatcher *tm = token_matcher_new(payloads[i]);
        /* Invariant: if allocation succeeds, pointer must be non-NULL and usable */
        if (tm != NULL) {
            /* Must be able to safely free without crash */
            token_matcher_free(tm);
        }
        /* If tm is NULL (alloc failed), no dereference should have occurred */
        /* Test passes as long as no crash/segfault happens */
        ck_assert(1); /* reached here means no crash */
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_token_matcher_null_safety);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}