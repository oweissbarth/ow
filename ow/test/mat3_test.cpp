#include "ow/math/mat3.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <glm/fwd.hpp>

using namespace ow;

// Define a Catch2 test case for the inverse() function
TEST_CASE("Mat3 inverse", "[Mat3]") {
    // Test case 1: Invertible matrix
    math::Mat3<double> mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    math::Mat3<double> inv1 = mat1.inverse();
    math::Mat3<double> identity1 = mat1 * inv1;

    // Check that the resulting matrix times the original matrix is close to the identity matrix
    REQUIRE(Catch::Approx(identity1.data()[0]).margin(1e-6) == 1.0);
    REQUIRE(Catch::Approx(identity1.data()[1]).margin(1e-6) == 0.0);
    REQUIRE(Catch::Approx(identity1.data()[2]).margin(1e-6) == 0.0);
    REQUIRE(Catch::Approx(identity1.data()[3]).margin(1e-6) == 0.0);
    REQUIRE(Catch::Approx(identity1.data()[4]).margin(1e-6) == 1.0);
    REQUIRE(Catch::Approx(identity1.data()[5]).margin(1e-6) == 0.0);
    REQUIRE(Catch::Approx(identity1.data()[6]).margin(1e-6) == 0.0);
    REQUIRE(Catch::Approx(identity1.data()[7]).margin(1e-6) == 0.0);
    REQUIRE(Catch::Approx(identity1.data()[8]).margin(1e-6) == 1.0);


    // Test case 2: Non-invertible matrix
    math::Mat3<double> mat2(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    // Attempt to calculate the inverse of a non-invertible matrix
    // The function should trigger an assertion (if using assert(det != 0);) or handle this case in a desired manner.
    //CHECK_THROWS(mat2.inverse());

}

// Test for mat3 determinant
TEST_CASE("Mat3 determinant", "[Mat3]"){
    // Test case 1: Invertible matrix
    math::Mat3<double> mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    double det1 = mat1.determinant();
    REQUIRE(Catch::Approx(det1).margin(1e-6) == 1.0);

    // Test case 2: Non-invertible matrix
    math::Mat3<double> mat2(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    double det2 = mat2.determinant();
    REQUIRE(Catch::Approx(det2).margin(1e-6) == 0.0);
}

// Test for mat3 multiplication
TEST_CASE("Mat3 multiplication", "[Mat3]"){
    // Test case 1: Invertible matrix
    math::Mat3<double> mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    math::Mat3<double> mat2(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    math::Mat3<double> mat3 = mat1 * mat2;

    REQUIRE(Catch::Approx(mat3.data()[0]).margin(1e-6) == 16.0);
    REQUIRE(Catch::Approx(mat3.data()[1]).margin(1e-6) == 22.0);
    REQUIRE(Catch::Approx(mat3.data()[2]).margin(1e-6) == 11.0);
    REQUIRE(Catch::Approx(mat3.data()[3]).margin(1e-6) == 20.0);
    REQUIRE(Catch::Approx(mat3.data()[4]).margin(1e-6) == 25.0);
    REQUIRE(Catch::Approx(mat3.data()[5]).margin(1e-6) == 4.0);
    REQUIRE(Catch::Approx(mat3.data()[6]).margin(1e-6) == 5.0);
    REQUIRE(Catch::Approx(mat3.data()[7]).margin(1e-6) == 16.0);
    REQUIRE(Catch::Approx(mat3.data()[8]).margin(1e-6) == 39.0);
}

TEST_CASE("Mat3 Matrix Multiplication Test", "[matrix]") {
    // Test matrices
    math::Mat3<float> mat1{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    math::Mat3<float> mat2{
        9, 8, 7,
        6, 5, 4,
        3, 2, 1
    };
    math::Mat3<float> identityMat = math::Mat3<float>::identity();

    SECTION("Matrix Multiplication with Identity Matrix") {
        math::Mat3<float> result = mat1 * identityMat;
        REQUIRE(result == mat1); // Multiplying with an identity matrix should return the same matrix
    }

    SECTION("Matrix Multiplication Order Test") {
        math::Mat3<float> result1 = mat1 * mat2;
        math::Mat3<float> result2 = mat2 * mat1;
        REQUIRE(result1 != result2); // Multiplication order matters for non-commutative matrices
    }

    SECTION("Associative Property Test") {
        math::Mat3<float> result1 = (mat1 * mat2) * mat1;
        math::Mat3<float> result2 = mat1 * (mat2 * mat1);
        REQUIRE(result1 == result2); // Matrix multiplication should satisfy the associative property
    }
}

TEST_CASE("Mat3 Matrix transpose", "[matrix]") {
    // Test matrices
    math::Mat3<float> mat1{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    math::Mat3<float> mat1_transposed = mat1.transpose();

    REQUIRE(Catch::Approx(mat1(0, 0)).margin(1e-6) == mat1_transposed(0, 0));
    REQUIRE(Catch::Approx(mat1(0, 1)).margin(1e-6) == mat1_transposed(1, 0));
    REQUIRE(Catch::Approx(mat1(0, 2)).margin(1e-6) == mat1_transposed(2, 0));
    REQUIRE(Catch::Approx(mat1(1, 0)).margin(1e-6) == mat1_transposed(0, 1));
    REQUIRE(Catch::Approx(mat1(1, 1)).margin(1e-6) == mat1_transposed(1, 1));
    REQUIRE(Catch::Approx(mat1(1, 2)).margin(1e-6) == mat1_transposed(2, 1));
    REQUIRE(Catch::Approx(mat1(2, 0)).margin(1e-6) == mat1_transposed(0, 2));
    REQUIRE(Catch::Approx(mat1(2, 1)).margin(1e-6) == mat1_transposed(1, 2));
    REQUIRE(Catch::Approx(mat1(2, 2)).margin(1e-6) == mat1_transposed(2, 2));

}
