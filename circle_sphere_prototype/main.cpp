#include <Eigen/Dense>
#include <iostream>
#include <OpenGP/MLogger.h> /// mDebug() <<
#include <cmath>

//constrains 2D or 3D data points to circles, and 3D points to spheres
int main(){
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

    //circle radius and center location (in case that we wish to specify these and not solve for them)
//    int rSpec = 5;
//    Eigen::Matrix2f cSpec;
//    cSpec << 0,0; //centered at origin

//    std::cout << "Radius" << rSpec << std::endl;
//    std::cout << "Center" << cSpec << std::endl;

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
