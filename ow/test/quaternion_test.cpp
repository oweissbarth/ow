#include "ow/math/quaternion.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace ow;

// Test for quaternion multiplication
TEST_CASE("union quaternion multiplication", "[Quaternion]"){
    math::Quaternion<double> quat1(1.0, 2.0, 3.0, 4.0);
    math::Quaternion<double> quat2(5.0, 6.0, 7.0, 8.0);

    math::Quaternion<double> quat3 = quat1 * quat2;

    REQUIRE(Catch::Approx(quat3.norm()).margin(1e-6) == 1.0);

    /*REQUIRE(Catch::Approx(quat3.w).margin(1e-6) == -60.0);
    REQUIRE(Catch::Approx(quat3.x).margin(1e-6) == 12.0);
    REQUIRE(Catch::Approx(quat3.y).margin(1e-6) == 30.0);
    REQUIRE(Catch::Approx(quat3.z).margin(1e-6) == 24.0);*/
}


// Test for unit quaternion to matrix conversion
TEST_CASE("Unit quaternion to matrix conversion", "[Quaternion]"){
    math::Quaternion<double> quat1(1.0, 2.0, 3.0, 4.0);

    REQUIRE(Catch::Approx(quat1.norm()).margin(1e-6) == 1.0);

    REQUIRE(Catch::Approx(quat1.x).margin(1e-6) == 0.3651484);
    REQUIRE(Catch::Approx(quat1.y).margin(1e-6) == 0.5477226);
    REQUIRE(Catch::Approx(quat1.z).margin(1e-6) == 0.7302967);
    REQUIRE(Catch::Approx(quat1.w).margin(1e-6) == 0.1825742);

    math::Mat3<double> mat1 = quat1.toMat3();

    REQUIRE(Catch::Approx(mat1(0,0)).margin(1e-6) == -0.6666666666666666);
    REQUIRE(Catch::Approx(mat1(1,0)).margin(1e-6) ==  0.1333333333333333);
    REQUIRE(Catch::Approx(mat1(2,0)).margin(1e-6) ==  0.7333333333333333);
    REQUIRE(Catch::Approx(mat1(0,1)).margin(1e-6) ==  0.6666666666666666);
    REQUIRE(Catch::Approx(mat1(1,1)).margin(1e-6) == -0.3333333333333333);
    REQUIRE(Catch::Approx(mat1(2,1)).margin(1e-6) ==  0.6666666666666666);
    REQUIRE(Catch::Approx(mat1(0,2)).margin(1e-6) ==  0.3333333333333333);
    REQUIRE(Catch::Approx(mat1(1,2)).margin(1e-6) ==  0.9333333333333333);
    REQUIRE(Catch::Approx(mat1(2,2)).margin(1e-6) ==  0.1333333333333333);
}

// Test for quaternion to mat4 conversion
TEST_CASE("Quaternion to mat4 conversion", "[Quaternion]"){
    math::Quaternion<double> quat1(1.0, 2.0, 3.0, 4.0);

    REQUIRE(Catch::Approx(quat1.norm()).margin(1e-6) == 1.0);

    REQUIRE(Catch::Approx(quat1.x).margin(1e-6) == 0.3651484);
    REQUIRE(Catch::Approx(quat1.y).margin(1e-6) == 0.5477226);
    REQUIRE(Catch::Approx(quat1.z).margin(1e-6) == 0.7302967);
    REQUIRE(Catch::Approx(quat1.w).margin(1e-6) == 0.1825742);

    math::Mat4<double> mat1 = quat1.toMat4();

    REQUIRE(Catch::Approx(mat1(0, 0)).margin(1e-6) == -0.6666666666666666);
    REQUIRE(Catch::Approx(mat1(1, 0)).margin(1e-6) ==  0.1333333333333333);
    REQUIRE(Catch::Approx(mat1(2, 0)).margin(1e-6) ==  0.7333333333333333);
    REQUIRE(Catch::Approx(mat1(3, 0)).margin(1e-6) ==  0.0);
    REQUIRE(Catch::Approx(mat1(0, 1)).margin(1e-6) ==  0.6666666666666666);
    REQUIRE(Catch::Approx(mat1(1, 1)).margin(1e-6) == -0.3333333333333333);
    REQUIRE(Catch::Approx(mat1(2, 1)).margin(1e-6) ==  0.6666666666666666);
    REQUIRE(Catch::Approx(mat1(3, 1)).margin(1e-6) ==  0.0);
    REQUIRE(Catch::Approx(mat1(0, 2)).margin(1e-6) ==  0.3333333333333333);
    REQUIRE(Catch::Approx(mat1(1, 2)).margin(1e-6) ==  0.9333333333333333);
    REQUIRE(Catch::Approx(mat1(2, 2)).margin(1e-6) ==  0.1333333333333333);
    REQUIRE(Catch::Approx(mat1(3, 2)).margin(1e-6) ==  0.0);
    REQUIRE(Catch::Approx(mat1(0, 3)).margin(1e-6) ==  0.0);
    REQUIRE(Catch::Approx(mat1(1, 3)).margin(1e-6) ==  0.0);
    REQUIRE(Catch::Approx(mat1(2, 3)).margin(1e-6) ==  0.0);
    REQUIRE(Catch::Approx(mat1(3, 3)).margin(1e-6) ==  1.0);
}