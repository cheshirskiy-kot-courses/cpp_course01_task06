#define BOOST_TEST_MODULE matrix_test_module

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

BOOST_AUTO_TEST_CASE(test_empty_matrix)
{
    Matrix<int, -1> matrix;
    BOOST_TEST(matrix.size() == 0);

    auto a = matrix(0, 0);
    BOOST_TEST(matrix.size() == 0);
    BOOST_TEST(a == -1);
}

BOOST_AUTO_TEST_CASE(test_set_element)
{
    Matrix<int, -1> matrix;
    matrix(100, 100) = 314;

    BOOST_TEST(matrix(100, 100) == 314);
    BOOST_TEST(matrix.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_3N_matrix)
{
    Matrix<int, -1, 3> matrix;
    matrix(100, 100, 10) = 314;

    BOOST_TEST(matrix(100, 100, 10) == 314);
    BOOST_TEST(matrix.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_out_of_range_exception)
{
    Matrix<int, -1, 2> matrix;
    try {
        matrix(-1, 0) = 314;
    }
    catch (std::out_of_range & e) {
    }
}

BOOST_AUTO_TEST_SUITE_END()
