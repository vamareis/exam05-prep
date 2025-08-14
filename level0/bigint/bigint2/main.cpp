#include "bigint.hpp"
#include <iostream>
#include <string>

static void check(const std::string &label, const bigint &got, const std::string &expected)
{
    if (got.getValue() == expected)
        std::cout << "[PASS] " << label << " => " << got << std::endl;
    else
        std::cout << "[FAIL] " << label << " => got: " << got << " expected: " << expected << std::endl;
}

static void checkBool(const std::string &label, bool got, bool expected)
{
    if (got == expected)
        std::cout << "[PASS] " << label << " => " << (got ? "true" : "false") << std::endl;
    else
        std::cout << "[FAIL] " << label << " => got: " << (got ? "true" : "false")
                  << " expected: " << (expected ? "true" : "false") << std::endl;
}

int main()
{
    // --- ADDITION (carry & different lengths) ---
    check("999 + 1", bigint("999") + bigint("1"), "1000");
    check("1 + 9999", bigint("1") + bigint("9999"), "10000");
    check("12345678901234567890 + 9",
          bigint("12345678901234567890") + bigint("9"),
          "12345678901234567899");
    check("999999 + 1", bigint("999999") + bigint("1"), "1000000");
    check("0 + 0", bigint("0") + bigint("0"), "0");

    // --- SUBTRACTION (normalization & chained borrows) ---
    // classic chained borrow cases
    check("1000 - 1", bigint("1000") - bigint("1"), "999");
    check("1010 - 11", bigint("1010") - bigint("11"), "999");
    check("10000 - 9999", bigint("10000") - bigint("9999"), "1");
    // equal values -> 0
    check("123456 - 123456", bigint("123456") - bigint("123456"), "0");
    // subtract zero -> unchanged
    check("1000 - 0", bigint("1000") - bigint("0"), "1000");
    // inputs with leading zeros, result should be normalized
    check("01000 - 00001", bigint("01000") - bigint("00001"), "999");
    // clamp-at-zero policy for negatives (if your bigint is unsigned-only)
    check("1 - 2 (clamped)", bigint("1") - bigint("2"), "0");
    check("0 - 1 (clamped)", bigint("0") - bigint("1"), "0");
    // big differences and borrows deep in the number
    check("1000000 - 1", bigint("1000000") - bigint("1"), "999999");
    check("100000 - 99999", bigint("100000") - bigint("99999"), "1");

    // --- SHIFTS (decimal semantics) ---
    check("123 << 0", bigint("123") << 0, "123");
    check("123 >> 0", bigint("123") >> 0, "123");
    check("7 << 12", bigint("7") << 12, "7000000000000");
    check("12345 >> 5", bigint("12345") >> 5, "0");      // dropping all digits
    check("1337 << 4", (bigint("1337") << 4), "13370000");
    check("13370000 >> 2", (bigint("13370000") >> 2), "133700");

    // --- COMPARISONS (normalization & ordering) ---
    bigint n1("00042"), n2("42"), n3("133700"), n4("100"), n5("100");
    checkBool("00042 == 42", (n1 == n2), true);
    checkBool("42 < 133700", (n2 < n3), true);
    checkBool("133700 > 42", (n3 > n2), true);
    checkBool("100 == 100", (n4 == n5), true);
    checkBool("100 <= 100", (n4 <= n5), true);
    checkBool("100 >= 100", (n4 >= n5), true);
    checkBool("42 > 42", (n2 > n2), false);
    checkBool("42 < 42", (n2 < n2), false);

    // --- INCREMENT / PLUS-EQUAL ---
    bigint inc("0");
    inc += bigint("0");
    check("inc += 0", inc, "0");
    ++inc; // 1
    check("++inc from 0", inc, "1");
    inc++; // prints 1, then becomes 2 (we just check value afterward)
    check("inc++ now", inc, "2");

    return 0;
}

