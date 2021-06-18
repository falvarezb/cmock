#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern struct tm* gettime();

time_t __wrap_time(time_t* t) {
    return mock_type(time_t);
}

void test_hour_21(void** state){
    will_return(__wrap_time, 1623620649); // 13 June 2021 21:44:09 Z
    struct tm *utctime = gettime();
    assert_int_equal(utctime->tm_hour, 21);
    assert_int_equal(utctime->tm_min, 44);
    assert_int_equal(utctime->tm_sec, 9);
}

void test_hour_22(void** state){
    will_return(__wrap_time, 1623624352); // 13 June 2021 22:45:52 Z
    struct tm *utctime = gettime();
    assert_int_equal(utctime->tm_hour, 22);
    assert_int_equal(utctime->tm_min, 45);
    assert_int_equal(utctime->tm_sec, 52);
}

int main(int argc, char const *argv[]) {
    (void)argc;
    (void)argv;

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_hour_21),
        cmocka_unit_test(test_hour_22)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}