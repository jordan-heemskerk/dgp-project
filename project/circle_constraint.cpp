#include <csc486a/circle_constraint.hpp>

#define DIM (3)

namespace csc486a {

    circle_constraint::circle_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : circle_sphere_constraint_base(mesh, std::move(vs), w, type::circle) { }

    circle_constraint::points_type circle_constraint::project (points_type ps) const {
        //just in case
        ps.clear();

        //number of points in this constraint
        auto N = vs_.size();

        Eigen::MatrixXf X(N,DIM);
        std::size_t row_x(0);
        for(auto && v : vs_){
            X.row(row_x) = vpoints_[v];
            row_x++;
        }

        std::cout << X << std::endl;

        //calculate all sums needed in further calculations
        float sumX = X.col(0).array().sum();
        float sumXSq = (X.col(0).array()*X.col(0).array()).sum();
        float sumXCube = ((X.col(0).array()*X.col(0).array())*X.col(0).array()).sum();

        float sumY = X.col(1).array().sum();
        float sumYSq = (X.col(1).array()*X.col(1).array()).sum();
        float sumYCube = ((X.col(1).array()*X.col(1).array())*X.col(1).array()).sum();

        float sumZ = X.col(2).array().sum();
        float sumZSq = (X.col(2).array()*X.col(2).array()).sum();
        float sumZCube = ((X.col(2).array()*X.col(2).array())*X.col(2).array()).sum();

        float sumXY = (X.col(0).array()*X.col(1).array()).sum();
        float sumXZ = (X.col(0).array()*X.col(2).array()).sum();
        float sumYZ = (X.col(1).array()*X.col(2).array()).sum();

        float sumXSqY = ((X.col(0).array()*X.col(0).array())*X.col(1).array()).sum();
        float sumXYSq = (X.col(0).array()*(X.col(1).array()*X.col(1).array())).sum();
        float sumXZSq = (X.col(0).array()*(X.col(2).array()*X.col(2).array())).sum();
        float sumYZSq = (X.col(1).array()*(X.col(2).array()*X.col(2).array())).sum();
        float sumYSqZ = ((X.col(1).array()*X.col(1).array())*X.col(2).array()).sum();
        float sumXSqZ = ((X.col(0).array()*X.col(0).array())*X.col(2).array()).sum();

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

        Eigen::Vector3f Y = A.inverse()*B;

        //calculate
        float xBar = Y(0);
        float yBar = Y(1);
        float zBar = Y(2);

        std::cout << "A: " << std::endl;
        std::cout << A << std::endl;
        std::cout << "B: " << std::endl;
        std::cout << B << std::endl;
        std::cout << "xBar: " << xBar << std::endl;
        std::cout << "yBar: " << yBar << std::endl;
        std::cout << "zBar: " << zBar << std::endl;

        float radius = std::sqrt((1/(float)N)*(sumXSq - 2*sumX*xBar + N*xBar*xBar + sumYSq - 2*sumY*yBar + N*yBar*yBar + sumZSq - 2*sumZ*zBar + N*zBar*zBar));

        std::cout << "radius: " << radius << std::endl;

        Eigen::Vector3f c(xBar,yBar,zBar);
        //point minus center
        for(auto && v : vs_){
            auto c2p = vpoints_[v] - c;
            ps.emplace_back(c + c2p.normalized()*radius);
        }

        return ps;
    }

}
