#include <stdbool.h>

#include <criterion/criterion.h>

Test(asserts, base) {
    cr_expect_eq(1, 1, "True 1");
    cr_expect(1 == 1, "True 2");

    cr_expect(false, "False 1");
    cr_expect(false, "False 2");
}