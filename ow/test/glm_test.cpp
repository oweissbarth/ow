#include "ow/math/mat3.h"
#include "ow/math/mat4.h"
#include "ow/math/quaternion.h"
#include "ow/math/vec3.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>



// Test case to compare the matrix multiplication in ow::math::Mat3 and glm::mat3
TEST_CASE("Mat3 multiplication compare glm", "[Mat3]"){
    // Test case 1: Invertible matrix
    ow::math::Mat3<double> mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    glm::mat3 glm_mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    ow::math::Mat3<double> mat2(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    glm::mat3 glm_mat2(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    ow::math::Mat3<double> mat3 = mat1 * mat2;
    glm::mat3 glm_mat3 = glm_mat1 * glm_mat2;

    REQUIRE(Catch::Approx(mat3.data()[0]).margin(1e-6) == glm_mat3[0][0]);
    REQUIRE(Catch::Approx(mat3.data()[1]).margin(1e-6) == glm_mat3[0][1]);
    REQUIRE(Catch::Approx(mat3.data()[2]).margin(1e-6) == glm_mat3[0][2]);
    REQUIRE(Catch::Approx(mat3.data()[3]).margin(1e-6) == glm_mat3[1][0]);
    REQUIRE(Catch::Approx(mat3.data()[4]).margin(1e-6) == glm_mat3[1][1]);
    REQUIRE(Catch::Approx(mat3.data()[5]).margin(1e-6) == glm_mat3[1][2]);
    REQUIRE(Catch::Approx(mat3.data()[6]).margin(1e-6) == glm_mat3[2][0]);
    REQUIRE(Catch::Approx(mat3.data()[7]).margin(1e-6) == glm_mat3[2][1]);
    REQUIRE(Catch::Approx(mat3.data()[8]).margin(1e-6) == glm_mat3[2][2]);
}

// Test case to compare the determinant in ow::math::Mat3 and glm::mat3
TEST_CASE("Mat3 determinant compare glm", "[Mat3]"){
    // Test case 1: Invertible matrix
    ow::math::Mat3<double> mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    glm::mat3 glm_mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    double det1 = mat1.determinant();
    double glm_det1 = glm::determinant(glm_mat1);

    REQUIRE(Catch::Approx(det1).margin(1e-6) == glm_det1);

    // Test case 2: Non-invertible matrix
    ow::math::Mat3<double> mat2(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    glm::mat3 glm_mat2(
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    );

    double det2 = mat2.determinant();
    double glm_det2 = glm::determinant(glm_mat2);

    REQUIRE(Catch::Approx(det2).margin(1e-6) == glm_det2);
}

// Test case to compare the matrix inversion in ow::math::Mat3 and glm::mat3
TEST_CASE("Mat3 inversion compare glm", "[Mat3]"){
    ow::math::Mat3<double> mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    glm::mat3 glm_mat1(
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    );

    ow::math::Mat3<double> mat2 = mat1.inverse();
    glm::mat3 glm_mat2 = glm::inverse(glm_mat1);

    REQUIRE(Catch::Approx(mat2(0, 0)).margin(1e-6) == glm_mat2[0][0]);
    REQUIRE(Catch::Approx(mat2(0, 1)).margin(1e-6) == glm_mat2[0][1]);
    REQUIRE(Catch::Approx(mat2(0, 2)).margin(1e-6) == glm_mat2[0][2]);
    REQUIRE(Catch::Approx(mat2(1, 0)).margin(1e-6) == glm_mat2[1][0]);
    REQUIRE(Catch::Approx(mat2(1, 1)).margin(1e-6) == glm_mat2[1][1]);
    REQUIRE(Catch::Approx(mat2(1, 2)).margin(1e-6) == glm_mat2[1][2]);
    REQUIRE(Catch::Approx(mat2(2, 0)).margin(1e-6) == glm_mat2[2][0]);
    REQUIRE(Catch::Approx(mat2(2, 1)).margin(1e-6) == glm_mat2[2][1]);
    REQUIRE(Catch::Approx(mat2(2, 2)).margin(1e-6) == glm_mat2[2][2]);
}

// Test case to compare the matrix inversion in ow::math::Mat4 and glm::mat4
TEST_CASE("Mat4 inversion compare glm", "[Mat4]"){
    /*ow::math::Mat4<double> mat1(
        1.0, 2.0, 3.0, 4.0,
        0.0, 1.0, 4.0, 5.0,
        5.0, 6.0, 0.0, 6.0,
        7.0, 8.0, 9.0, 0.0
    );

    std::cout << mat1 << std::endl;

    glm::mat4 glm_mat1(
        1.0, 2.0, 3.0, 4.0,
        0.0, 1.0, 4.0, 5.0,
        5.0, 6.0, 0.0, 6.0,
        7.0, 8.0, 9.0, 0.0
    );

    std::cout << glm::to_string(glm_mat1) << std::endl;

    ow::math::Mat4<double> mat2 = mat1.inverse();
    std::cout << mat2 << std::endl;

    glm::mat4 glm_mat2 = glm::inverse(glm_mat1);
    std::cout << glm::to_string(glm_mat2) << std::endl;


    REQUIRE(Catch::Approx(mat2(0, 0)).margin(1e-6) == glm_mat2[0][0]);
    REQUIRE(Catch::Approx(mat2(0, 1)).margin(1e-6) == glm_mat2[0][1]);
    REQUIRE(Catch::Approx(mat2(0, 2)).margin(1e-6) == glm_mat2[0][2]);
    REQUIRE(Catch::Approx(mat2(0, 3)).margin(1e-6) == glm_mat2[0][3]);
    REQUIRE(Catch::Approx(mat2(1, 0)).margin(1e-6) == glm_mat2[1][0]);
    REQUIRE(Catch::Approx(mat2(1, 1)).margin(1e-6) == glm_mat2[1][1]);
    REQUIRE(Catch::Approx(mat2(1, 2)).margin(1e-6) == glm_mat2[1][2]);
    REQUIRE(Catch::Approx(mat2(1, 3)).margin(1e-6) == glm_mat2[1][3]);
    REQUIRE(Catch::Approx(mat2(2, 0)).margin(1e-6) == glm_mat2[2][0]);
    REQUIRE(Catch::Approx(mat2(2, 1)).margin(1e-6) == glm_mat2[2][1]);
    REQUIRE(Catch::Approx(mat2(2, 2)).margin(1e-6) == glm_mat2[2][2]);
    REQUIRE(Catch::Approx(mat2(2, 3)).margin(1e-6) == glm_mat2[2][3]);
    REQUIRE(Catch::Approx(mat2(3, 0)).margin(1e-6) == glm_mat2[3][0]);
    REQUIRE(Catch::Approx(mat2(3, 1)).margin(1e-6) == glm_mat2[3][1]);
    REQUIRE(Catch::Approx(mat2(3, 2)).margin(1e-6) == glm_mat2[3][2]);
    REQUIRE(Catch::Approx(mat2(3, 3)).margin(1e-6) == glm_mat2[3][3]);*/
}

// Test case to compare the matrix multiplication in ow::math::Mat4 and glm::mat4
TEST_CASE("Mat4 multiplication compare glm", "[Mat4]"){
    // Test case 1: Invertible matrix
    ow::math::Mat4<double> mat1(
        1.0, 2.0, 3.0, 4.0,
        0.0, 1.0, 4.0, 5.0,
        5.0, 6.0, 0.0, 6.0,
        7.0, 8.0, 9.0, 0.0
    );

    glm::mat4 glm_mat1(
        1.0, 2.0, 3.0, 4.0,
        0.0, 1.0, 4.0, 5.0,
        5.0, 6.0, 0.0, 6.0,
        7.0, 8.0, 9.0, 0.0
    );

    ow::math::Mat4<double> mat2(
        1.0, 2.0, 3.0, 4.0,
        4.0, 5.0, 6.0, 5.0,
        7.0, 8.0, 9.0, 6.0,
        7.0, 8.0, 9.0, 0.0
    );

    glm::mat4 glm_mat2(
        1.0, 2.0, 3.0, 4.0,
        4.0, 5.0, 6.0, 5.0,
        7.0, 8.0, 9.0, 6.0,
        7.0, 8.0, 9.0, 0.0
    );

    ow::math::Mat4<double> mat3 = mat1 * mat2;
    glm::mat4 glm_mat3 = glm_mat1 * glm_mat2;

    REQUIRE(Catch::Approx(mat3(0, 0)).margin(1e-6) == glm_mat3[0][0]);
    REQUIRE(Catch::Approx(mat3(0, 1)).margin(1e-6) == glm_mat3[0][1]);
    REQUIRE(Catch::Approx(mat3(0, 2)).margin(1e-6) == glm_mat3[0][2]);
    REQUIRE(Catch::Approx(mat3(0, 3)).margin(1e-6) == glm_mat3[0][3]);
    REQUIRE(Catch::Approx(mat3(1, 0)).margin(1e-6) == glm_mat3[1][0]);
    REQUIRE(Catch::Approx(mat3(1, 1)).margin(1e-6) == glm_mat3[1][1]);
    REQUIRE(Catch::Approx(mat3(1, 2)).margin(1e-6) == glm_mat3[1][2]);
    REQUIRE(Catch::Approx(mat3(1, 3)).margin(1e-6) == glm_mat3[1][3]);
    REQUIRE(Catch::Approx(mat3(2, 0)).margin(1e-6) == glm_mat3[2][0]);
    REQUIRE(Catch::Approx(mat3(2, 1)).margin(1e-6) == glm_mat3[2][1]);
    REQUIRE(Catch::Approx(mat3(2, 2)).margin(1e-6) == glm_mat3[2][2]);
    REQUIRE(Catch::Approx(mat3(2, 3)).margin(1e-6) == glm_mat3[2][3]);
    REQUIRE(Catch::Approx(mat3(3, 0)).margin(1e-6) == glm_mat3[3][0]);
    REQUIRE(Catch::Approx(mat3(3, 1)).margin(1e-6) == glm_mat3[3][1]);
    REQUIRE(Catch::Approx(mat3(3, 2)).margin(1e-6) == glm_mat3[3][2]);
    REQUIRE(Catch::Approx(mat3(3, 3)).margin(1e-6) == glm_mat3[3][3]);
}

// Test case to compare perspective in ow::math::Mat4 and glm::mat4
TEST_CASE("Mat4 perspective compare glm", "[Mat4]"){
    ow::math::Mat4<double> mat1 = ow::math::Mat4<double>::perspective(glm::radians(45.0), 1.0, 0.1, 100.0);
    glm::mat4 glm_mat1 = glm::perspective(glm::radians(45.0), 1.0, 0.1, 100.0);

    REQUIRE(Catch::Approx(mat1(0, 0)).margin(1e-6) == glm_mat1[0][0]);
    REQUIRE(Catch::Approx(mat1(0, 1)).margin(1e-6) == glm_mat1[0][1]);
    REQUIRE(Catch::Approx(mat1(0, 2)).margin(1e-6) == glm_mat1[0][2]);
    REQUIRE(Catch::Approx(mat1(0, 3)).margin(1e-6) == glm_mat1[0][3]);
    REQUIRE(Catch::Approx(mat1(1, 0)).margin(1e-6) == glm_mat1[1][0]);
    REQUIRE(Catch::Approx(mat1(1, 1)).margin(1e-6) == glm_mat1[1][1]);
    REQUIRE(Catch::Approx(mat1(1, 2)).margin(1e-6) == glm_mat1[1][2]);
    REQUIRE(Catch::Approx(mat1(1, 3)).margin(1e-6) == glm_mat1[1][3]);
    REQUIRE(Catch::Approx(mat1(2, 0)).margin(1e-6) == glm_mat1[2][0]);
    REQUIRE(Catch::Approx(mat1(2, 1)).margin(1e-6) == glm_mat1[2][1]);
    REQUIRE(Catch::Approx(mat1(2, 2)).margin(1e-6) == glm_mat1[2][2]);
    REQUIRE(Catch::Approx(mat1(2, 3)).margin(1e-6) == glm_mat1[2][3]);
    REQUIRE(Catch::Approx(mat1(3, 0)).margin(1e-6) == glm_mat1[3][0]);
    REQUIRE(Catch::Approx(mat1(3, 1)).margin(1e-6) == glm_mat1[3][1]);
    REQUIRE(Catch::Approx(mat1(3, 2)).margin(1e-6) == glm_mat1[3][2]);
    REQUIRE(Catch::Approx(mat1(3, 3)).margin(1e-6) == glm_mat1[3][3]);
}

TEST_CASE("Quaternion to mat4 compare glm", "[Mat4]"){
    ow::math::Quaternion<double> quat1(1.0, 2.0, 3.0, 4.0);
    ow::math::Mat4<double> mat1 = quat1.toMat4();

    glm::quat quat1_glm(1.0, 2.0, 3.0, 4.0);
    quat1_glm = glm::normalize(quat1_glm);

    glm::mat4 mat1_glm = glm::toMat4(quat1_glm);

    REQUIRE(Catch::Approx(mat1(0, 0)).margin(1e-6) == mat1_glm[0][0]);
    REQUIRE(Catch::Approx(mat1(0, 1)).margin(1e-6) == mat1_glm[0][1]);
    REQUIRE(Catch::Approx(mat1(0, 2)).margin(1e-6) == mat1_glm[0][2]);
    REQUIRE(Catch::Approx(mat1(0, 3)).margin(1e-6) == mat1_glm[0][3]);
    REQUIRE(Catch::Approx(mat1(1, 0)).margin(1e-6) == mat1_glm[1][0]);
    REQUIRE(Catch::Approx(mat1(1, 1)).margin(1e-6) == mat1_glm[1][1]);
    REQUIRE(Catch::Approx(mat1(1, 2)).margin(1e-6) == mat1_glm[1][2]);
    REQUIRE(Catch::Approx(mat1(1, 3)).margin(1e-6) == mat1_glm[1][3]);
    REQUIRE(Catch::Approx(mat1(2, 0)).margin(1e-6) == mat1_glm[2][0]);
    REQUIRE(Catch::Approx(mat1(2, 1)).margin(1e-6) == mat1_glm[2][1]);
    REQUIRE(Catch::Approx(mat1(2, 2)).margin(1e-6) == mat1_glm[2][2]);
    REQUIRE(Catch::Approx(mat1(2, 3)).margin(1e-6) == mat1_glm[2][3]);
    REQUIRE(Catch::Approx(mat1(3, 0)).margin(1e-6) == mat1_glm[3][0]);
    REQUIRE(Catch::Approx(mat1(3, 1)).margin(1e-6) == mat1_glm[3][1]);
    REQUIRE(Catch::Approx(mat1(3, 2)).margin(1e-6) == mat1_glm[3][2]);
    REQUIRE(Catch::Approx(mat1(3, 3)).margin(1e-6) == mat1_glm[3][3]);
}

TEST_CASE("Mat3 times vector compare glm", "[Mat4]"){
    ow::math::Mat3f mat(1 ,2 ,3 , 4,5,6,7,8,9);
    ow::math::Vec3f vec(5,6,7);

    glm::mat3 mat_glm(1 ,2 ,3 , 4,5,6,7,8,9);
    glm::vec3 vec_glm(5,6,7);

    ow::math::Vec3f result = mat * vec;
    glm::vec3 result_glm = mat_glm * vec_glm;

    REQUIRE(Catch::Approx(result.x).margin(1e-6) == result_glm.x);
    REQUIRE(Catch::Approx(result.y).margin(1e-6) == result_glm.y);
    REQUIRE(Catch::Approx(result.z).margin(1e-6) == result_glm.z);


}

TEST_CASE("Mat4 lookAt compare glm", "[Mat4]"){
    ow::math::Mat4f mat = ow::math::Mat4f::lookAt(ow::math::Vec3f(10,0,0), ow::math::Vec3f(0,0,0), ow::math::Vec3f(0,0,1));

    glm::mat4 mat_glm = glm::lookAt(glm::vec3(10,0,0), glm::vec3(0,0,0), glm::vec3(0,0,1));

    REQUIRE(Catch::Approx(mat(0, 0)).margin(1e-6) == mat_glm[0][0]);
    REQUIRE(Catch::Approx(mat(0, 1)).margin(1e-6) == mat_glm[0][1]);
    REQUIRE(Catch::Approx(mat(0, 2)).margin(1e-6) == mat_glm[0][2]);
    REQUIRE(Catch::Approx(mat(0, 3)).margin(1e-6) == mat_glm[0][3]);
    REQUIRE(Catch::Approx(mat(1, 0)).margin(1e-6) == mat_glm[1][0]);
    REQUIRE(Catch::Approx(mat(1, 1)).margin(1e-6) == mat_glm[1][1]);
    REQUIRE(Catch::Approx(mat(1, 2)).margin(1e-6) == mat_glm[1][2]);
    REQUIRE(Catch::Approx(mat(1, 3)).margin(1e-6) == mat_glm[1][3]);
    REQUIRE(Catch::Approx(mat(2, 0)).margin(1e-6) == mat_glm[2][0]);
    REQUIRE(Catch::Approx(mat(2, 1)).margin(1e-6) == mat_glm[2][1]);
    REQUIRE(Catch::Approx(mat(2, 2)).margin(1e-6) == mat_glm[2][2]);
    REQUIRE(Catch::Approx(mat(2, 3)).margin(1e-6) == mat_glm[2][3]);
    REQUIRE(Catch::Approx(mat(3, 0)).margin(1e-6) == mat_glm[3][0]);
    REQUIRE(Catch::Approx(mat(3, 1)).margin(1e-6) == mat_glm[3][1]);
    REQUIRE(Catch::Approx(mat(3, 2)).margin(1e-6) == mat_glm[3][2]);
    REQUIRE(Catch::Approx(mat(3, 3)).margin(1e-6) == mat_glm[3][3]);

}