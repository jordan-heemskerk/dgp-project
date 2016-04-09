#include <Eigen/Dense>
#include <iostream>
#include <OpenGP/MLogger.h> /// mDebug() <<
#include <cmath>

#define UNUSED(expr) (void)expr

#define DIM 3

#define EPSILON 0.00001f

static bool floateq (float a, float b) {
    return std::abs(a-b) < EPSILON;
}

float variance (Eigen::MatrixXf A) {

    //TODO: do this SMRT
    auto u_x = A.colwise().mean();
    auto A_temp = A;
    A_temp.rowwise() -= u_x;
    auto normed = A_temp.rowwise().squaredNorm();
    auto var = normed.sum()/3.0;
    return var;
}

int main() {
    // Quick documentation (for MATLAB users)
    // http://eigen.tuxfamily.org/dox/AsciiQuickReference.txt

    std::cout << "Rigid Similarity Prototype" << std::endl;

    Eigen::Matrix3f X;
    Eigen::Matrix3f Y;

    X << 0,0,0,
         1,0,0,
         0,2,0;

    Y << 0, 0, 0,
         -1, 0, 0,
         0, 2, 0;

    Eigen::Vector3f u_x = X.colwise().mean();
    float s_x = variance(X);

    Eigen::Vector3f u_y = Y.colwise().mean();
    float s_y = variance(Y);


    auto centered_y = Y.rowwise() - Y.colwise().mean();
    auto centered_x = X.rowwise() - X.colwise().mean();

    std::cout << "centered_x: \n" << centered_x << std::endl;
    std::cout << "centered_y: \n" << centered_y << std::endl;

    Eigen::Matrix3f S_xy = (centered_y.adjoint() * centered_x)/3.0;


    std::cout << "Matrix X:\n" << X << std::endl;
    std::cout << "Matrix Y:\n" << Y << std::endl;
    std::cout << "u_x: \n" << u_x << std::endl;
    std::cout << "u_y: \n" << u_y << std::endl;
    std::cout << "s_x: \n" << s_x << std::endl;
    std::cout << "s_y: \n" << s_y << std::endl;
    std::cout << "S_xy: \n" << S_xy << std::endl;


    Eigen::JacobiSVD<Eigen::MatrixXf> svd(S_xy, Eigen::ComputeThinU | Eigen::ComputeThinV);

    Eigen::Matrix3f U = svd.matrixU();
    Eigen::Matrix3f D = svd.singularValues().asDiagonal(); //these should be sorted
    Eigen::Matrix3f V = svd.matrixV();

    std::cout << "U:\n" << U << std::endl;
    std::cout << "D:\n" << D << std::endl;
    std::cout << "V:\n" << V << std::endl;


    auto det = S_xy.determinant();

    auto rank = svd.rank();


    std::cout << "Rank of S_xy = " << rank << std::endl;
    assert(rank >= DIM-1);

    Eigen::Matrix3f S = Eigen::Matrix3f::Identity();

    if (det < 0) {
        S(2,2) = -1;
    }

    if (rank == DIM-1) {
        S = Eigen::Matrix3f::Identity();

        auto det_cond = U.determinant() * V.determinant();
        std::cout << "det_cond: " << det_cond << std::endl;

        if (floateq(det_cond, 1)) {
            //all good
        } else if (floateq(det_cond, -1)) {
            S(2,2) = -1;
        } else {
            std::cout << "GARBAGE" << std::endl;
        }
    }


    std::cout << "S:\n" << S << std::endl;

    Eigen::Matrix3f R = U * S * V.transpose();
    float c = (D*S).trace()/s_x;
    Eigen::Vector3f t = u_y - c*R*u_x;

    Eigen::Matrix3f new_X;

    float clamp = 0.1;
    if (std::abs(c-1) > clamp) {
        if ((c-1) > 0) c = 1 + clamp;
        if ((c-1) < 0) c = 1 - clamp;
    }

    std::cout << "R:\n" << R << std::endl;
    std::cout << "c:" << c << std::endl;
    std::cout << "t:\n" << t << std::endl;

    for (int i = 0; i < 3; i ++) {
        auto test = c*R*X.row(i).transpose() +t;
        std::cout << "Point " << i << ": \n" << test << std::endl;
    }
    return 0;
}
