#include "ow/math/mat4.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace ow;

TEST_CASE("Mat4 Matrix Multiplication Test", "[matrix]") {
    // Test matrices
    math::Mat4<float> mat1{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };
    math::Mat4<float> mat2{
        16, 15, 14, 13,
        12, 11, 10, 9,
        8, 7, 6, 5,
        4, 3, 2, 1
    };
    math::Mat4<float> identityMat = math::Mat4<float>::identity();

    SECTION("Matrix Multiplication with Identity Matrix") {
        math::Mat4<float> result = mat1 * identityMat;
        REQUIRE(result == mat1); // Multiplying with an identity matrix should return the same matrix
    }

    SECTION("Matrix Multiplication Order Test") {
        math::Mat4<float> result1 = mat1 * mat2;
        math::Mat4<float> result2 = mat2 * mat1;
        REQUIRE(result1 != result2); // Multiplication order matters for non-commutative matrices
    }

    SECTION("Associative Property Test") {
        math::Mat4<float> result1 = (mat1 * mat2) * mat1;
        math::Mat4<float> result2 = mat1 * (mat2 * mat1);
        REQUIRE(result1 == result2); // Matrix multiplication should satisfy the associative property
    }
}