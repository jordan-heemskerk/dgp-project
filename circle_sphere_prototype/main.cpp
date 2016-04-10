#include <Eigen/Dense>
#include <iostream>
#include <OpenGP/MLogger.h> /// mDebug() <<
#include <cmath>

void sphere(){
    std::cout << "TEST: 3D to Sphere" << std::endl;

    //number of 3D points
    int N = 6;

    //cloud of 3d points
    Eigen::MatrixXf X2D(N,3);
    X2D <<  2,0,0,
            -2,0,0,
            0,2,0,
            0,-2,0,
            0,0,2,
            0,0,-2;

    //calculate all sums needed in further calculations
    float sumX = X2D.col(0).array().sum();
    float sumXSq = (X2D.col(0).array()*X2D.col(0).array()).sum();
    float sumXCube = ((X2D.col(0).array()*X2D.col(0).array())*X2D.col(0).array()).sum();

    float sumY = X2D.col(1).array().sum();
    float sumYSq = (X2D.col(1).array()*X2D.col(1).array()).sum();
    float sumYCube = ((X2D.col(1).array()*X2D.col(1).array())*X2D.col(1).array()).sum();

    float sumZ = X2D.col(2).array().sum();
    float sumZSq = (X2D.col(2).array()*X2D.col(2).array()).sum();
    float sumZCube = ((X2D.col(2).array()*X2D.col(2).array())*X2D.col(2).array()).sum();

    float sumXY = (X2D.col(0).array()*X2D.col(1).array()).sum();
    float sumXZ = (X2D.col(0).array()*X2D.col(2).array()).sum();
    float sumYZ = (X2D.col(1).array()*X2D.col(2).array()).sum();

    float sumXSqY = ((X2D.col(0).array()*X2D.col(0).array())*X2D.col(1).array()).sum();
    float sumXYSq = (X2D.col(0).array()*(X2D.col(1).array()*X2D.col(1).array())).sum();
    float sumXZSq = (X2D.col(0).array()*(X2D.col(2).array()*X2D.col(2).array())).sum();
    float sumYZSq = (X2D.col(1).array()*(X2D.col(2).array()*X2D.col(2).array())).sum();
    float sumYSqZ = ((X2D.col(1).array()*X2D.col(1).array())*X2D.col(2).array()).sum();
    float sumXSqZ = ((X2D.col(0).array()*X2D.col(0).array())*X2D.col(2).array()).sum();

    std::cout << "sumX: " << sumX << std::endl;
    std::cout << "sumY: " << sumY << std::endl;
    std::cout << "sumZ: " << sumZ << std::endl;
    std::cout << "sumXSq: " << sumXSq << std::endl;
    std::cout << "sumYSq: " << sumYSq << std::endl;
    std::cout << "sumZSq: " << sumZSq << std::endl;
    std::cout << "sumXCube: " << sumXCube << std::endl;
    std::cout << "sumYCube: " << sumYCube << std::endl;
    std::cout << "sumZCube: " << sumZCube << std::endl;
    std::cout << "sumXY: " << sumXY << std::endl;
    std::cout << "sumXZ: " << sumXZ << std::endl;
    std::cout << "sumYZ: " << sumYZ << std::endl;
    std::cout << "sumXSqY: " << sumXSqY << std::endl;
    std::cout << "sumXYSq: " << sumXYSq << std::endl;
    std::cout << "sumXZSq: " << sumXZSq << std::endl;
    std::cout << "sumYZSq: " << sumYZSq << std::endl;
    std::cout << "sumYSqZ: " << sumYSqZ << std::endl;
    std::cout << "sumXSqZ: " << sumXSqZ << std::endl;

    //calculate a's b's and c's
    float a1 = 2*(sumX*sumX - N*sumXSq);
    float a2 = 2*(sumX*sumY - N*sumXY);
    float a3 = 2*(sumX*sumZ - N*sumXZ);
    float b1 = a2;
    float b2 = 2*(sumY*sumY - N*sumYSq);
    float b3 = 2*(sumY*sumZ - N*sumYZ);
    float c1 = a3;
    float c2 = b3;
    float c3 = 2*(sumZ*sumZ - N*sumZSq);
    float d1 = sumXSq*sumX + sumX*sumYSq + sumZSq*sumX - N*(sumXCube - sumXYSq - sumXZSq);
    float d2 = sumXSq*sumY + sumYSq*sumY + sumZSq*sumY - N*(sumYCube - sumXSqY - sumYZSq);
    float d3 = sumXSq*sumZ + sumYSq*sumZ + sumZSq*sumZ - N*(sumZCube - sumXSqZ - sumYSqZ);

    std::cout << "a1: " << a1 << std::endl;
    std::cout << "a2: " << a2 << std::endl;
    std::cout << "a3: " << a3 << std::endl;
    std::cout << "b1: " << b1 << std::endl;
    std::cout << "b2: " << b2 << std::endl;
    std::cout << "b3: " << b3 << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "c3: " << c3 << std::endl;
    std::cout << "d1: " << d1 << std::endl;
    std::cout << "d2: " << d2 << std::endl;
    std::cout << "d3: " << d3 << std::endl;

    //calculate matrix
    Eigen::Matrix3f A(3,3);
    A << a1, b1, c1,
         a2, b2, c2,
         a3, b3, c3;

    Eigen::Vector3f B(3,1);
    B << d1,
         d2,
         d3;

    Eigen::Vector3f X = A.inverse()*B;

    //calculate
    float xBar = X(0);
    float yBar = X(1);
    float zBar = X(2);

    std::cout << "A: " << std::endl;
    std::cout << A << std::endl;
    std::cout << "B: " << std::endl;
    std::cout << B << std::endl;
    std::cout << "xBar: " << xBar << std::endl;
    std::cout << "yBar: " << yBar << std::endl;
    std::cout << "zBar: " << zBar << std::endl;

    float radius = std::sqrt((1/(float)N)*(sumXSq - 2*sumX*xBar + N*xBar*xBar + sumYSq - 2*sumY*yBar + N*yBar*yBar + sumZSq - 2*sumZ*zBar + N*zBar*zBar));

    std::cout << "radius: " << radius << std::endl;
}

void circle(){
    std::cout << "Circle and Sphere Approximations" << std::endl;
    std::cout << "TEST: 2D to Circle" << std::endl;

    //number of 2D points
    int N = 4;

    //square of 2d points
    Eigen::MatrixXf X2D(N,2);
    X2D <<  0,0,
            2,0,
            2,2,
            0,2;

    //calculate all sums needed in further calculations
    float sumX = X2D.col(0).array().sum();
    float sumXSq = (X2D.col(0).array()*X2D.col(0).array()).sum();
    float sumXCube = ((X2D.col(0).array()*X2D.col(0).array())*X2D.col(0).array()).sum();

    float sumY = X2D.col(1).array().sum();
    float sumYSq = (X2D.col(1).array()*X2D.col(1).array()).sum();
    float sumYCube = ((X2D.col(1).array()*X2D.col(1).array())*X2D.col(1).array()).sum();

    float sumXY = (X2D.col(0).array()*X2D.col(1).array()).sum();
    float sumXSqY = ((X2D.col(0).array()*X2D.col(0).array())*X2D.col(1).array()).sum();
    float sumXYSq = (X2D.col(0).array()*(X2D.col(1).array()*X2D.col(1).array())).sum();

    std::cout << "sumX: " << sumX << std::endl;
    std::cout << "sumY: " << sumY << std::endl;
    std::cout << "sumXY: " << sumXY << std::endl;
    std::cout << "sumXSq: " << sumXSq << std::endl;
    std::cout << "sumYSq: " << sumYSq << std::endl;
    std::cout << "sumXSqY: " << sumXSqY << std::endl;
    std::cout << "sumXYSq: " << sumXYSq << std::endl;
    std::cout << "sumXCube: " << sumXCube << std::endl;
    std::cout << "sumYCube: " << sumYCube << std::endl;

    //calculate a's b's and c's
    float a1 = 2*(sumX*sumX - N*sumXSq);
    float a2 = 2*(sumX*sumY - N*sumXY);
    float b1 = a2;
    float b2 = 2*(sumY*sumY - N*sumYSq);
    float c1 = sumXSq*sumX - N*sumXCube + sumX*sumYSq - N*sumXYSq;
    float c2 = sumXSq*sumY - N*sumYCube + sumY*sumYSq - N*sumXSqY;

    std::cout << "a1: " << a1 << std::endl;
    std::cout << "a2: " << a2 << std::endl;
    std::cout << "b1: " << b1 << std::endl;
    std::cout << "b2: " << b2 << std::endl;
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;

    //calculate center coordinates and radius
    float xBar = (c1*b2 - c2*b1) / (a1*b2 - a2*b1);
    float yBar = (a1*c2 - a2*c1) / (a1*b2 - a2*b2);
    float radius = std::sqrt((1/float(N))*(sumXSq - 2*sumX*xBar + N*(xBar*xBar) + sumYSq - 2*sumY*yBar + N*(yBar*yBar)));

    std::cout << "xBar: " << xBar << std::endl;
    std::cout << "yBar: " << yBar << std::endl;
    std::cout << "radius: " << radius << std::endl;
}

//constrains 2D or 3D data points to circles, and 3D points to spheres
int main(){
    circle();
    sphere();
}
