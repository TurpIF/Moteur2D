#include "type.h"

#include <cstdlib>
#include <iostream>

// #define SHOW_SUCCESS

static std::size_t num_test = 0;

template <typename T, typename U>
static void test(T const &__val,
        U const & __expected,
        char const * __file = "\0",
        std::size_t __line = 0)
{
    num_test++;
    if(__val != __expected)
    {
        std::cerr << __file << ":" << __line
            << ": Test n°" << num_test
            << " failed: "
            << __expected << " expected but "
            << __val << " find"
            << std::endl;
        std::abort();
    }
#ifdef SHOW_SUCCESS
    else
    {
        std::cout << __file << ":" << __line
            << ": Test n°" << num_test
            << " valid"
            << std::endl;
    }
#endif
}

template <typename T, typename U, typename T::value_type>
static void test(T const &__val,
        U const & __expected,
        char const * __file = "\0",
        std::size_t __line = 0)
{
    num_test++;
    if(__val != __expected)
    {
        std::cerr << __file << ":" << __line
            << ": Test n°" << num_test
            << " failed: "
            << static_cast<typename T::value_type>(__expected) << " expected but "
            << static_cast<typename T::value_type>(__val) << " find"
            << std::endl;
        std::abort();
    }
#ifdef SHOW_SUCCESS
    else
    {
        std::cout << __file << ":" << __line
            << ": Test n°" << num_test
            << " valid"
            << std::endl;
    }
#endif
}

#define TEST(__val, __expected) test(__val, __expected, __FILE__, __LINE__)

int main() {
    for(int i = -1000 ; i < 1000 ; i++) {
        numeric<int> ni(i);
        TEST(ni, i);
    }

    {
        numeric<int> n(0);
        TEST(n, 0);
        n++;
        TEST(n, 1);
        ++n;
        TEST(n, 2);
        n--;
        TEST(n, 1);
        --n;
        TEST(n, 0);
    }

    {
        int i = -1000;
        for(numeric<int> n(i) ; n < 1000 ; n++, i++) {
            TEST(n, i);
        }
    }

    {
        numeric<int> n1(1);
        numeric<int> n2(n1);
        TEST(n1, n2);
        TEST(n1 + n2, 2);
        TEST(n1 * n2, 1);
        TEST(n1 - n2, 0);
        TEST(n1 / n2, 1);
    }

    for(int i = -1000 ; i < 1000 ; i++) {
        for(int j = -1000 ; j < 1000 ; j++) {
            numeric<int> ni(i);
            numeric<int> nj(j);
            TEST(ni + nj, i + j);
            TEST(ni - nj, i - j);
            TEST(ni * nj, i * j);
            TEST(ni == nj, i == j);
            TEST(ni != nj, i != j);
            TEST(ni <= nj, i <= j);
            TEST(ni >= nj, i >= j);
            TEST(ni < nj, i < j);
            TEST(ni > nj, i > j);

            if(nj != numeric<int>(0))
                TEST(ni / nj, i / j);
        }
    }

    return 0;
}
