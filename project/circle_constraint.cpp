#include <csc486a/circle_constraint.hpp>
#define DIM (2)

namespace csc486a {

    circle_constraint::circle_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : circle_sphere_constraint_base(mesh, std::move(vs), w, type::circle) { }

    circle_constraint::points_type circle_constraint::project (points_type ps) const {
        //just in case
        ps.clear();

        auto h=vs_.size();
        Eigen::Matrix3Xf obs(3,h);
        std::size_t row(0);
        for (auto && v : vs_) obs.col(row++)=vpoints_[v];

        auto c=(obs.colwise()-obs.rowwise().mean()).eval();

        Eigen::JacobiSVD<Eigen::Matrix3Xf> jsvd(c,Eigen::ComputeFullU);
        auto u=jsvd.matrixU().eval();
        c=u.transpose()*c;
        auto z=Eigen::Matrix<float,1,Eigen::Dynamic>::Constant(c.cols(),0.0f);

        c.row(2)=z;
        std::cout << "C: "<< c << std::endl;
        auto result=(u*c).eval();

        std::size_t num(vs_.size());
//        for (std::size_t i=0;i<num;++i) ps.emplace_back(result.col(i)*w_);

        //get two vectors in the plane of the surface and dot and cross them
        auto v1 = (result.col(0) - result.col(1)).normalized();
        auto v2 = (result.col(0) - result.col(2)).normalized();
        auto a = (v1.cross(v2)).normalized();
        Eigen::Vector3f b(0,0,1);

        std::cout << "v1: " << v1 << std::endl;
        std::cout << "v2: " << v2 << std::endl;
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;

        auto aXb = a.cross(b);
        auto aDotb = a.dot(b);

        std::cout << "aXb: " << aXb << std::endl;
        std::cout << "aDotb: " << aDotb << std::endl;

        Eigen::MatrixXf GG(3,3);
        GG << aDotb, -aXb.norm(), 0,
              aXb.norm(), aDotb, 0,
              0,0,1;
        std::cout << "GG: " << GG << std::endl;

        Eigen::Matrix3f FF;
        FF.col(0) = a;
        FF.col(1) = (b-aDotb*a)/((b-aDotb*a).norm());
        FF.col(2) = aXb;

        std::cout << "FF: " << FF <<std::endl;

        auto R = FF*GG*FF.inverse();
        auto Rinv = R.inverse();


        std::cout << "R: " << R << std::endl;
        std::cout << "Rinveerse: \n" << R.inverse() << std::endl;

        //rotate all points
        for(int i = 0; i < result.cols(); i++){
            std::cout << "Result before: \n" << result.col(i) << std::endl;
            result.col(i) = R*result.col(i);
            std::cout << "Result after: \n" << result.col(i) << std::endl;
        }

        //number of points in this constraint
        auto N = result.size();
        std::cout << "N: \n" << N << std::endl;
        Eigen::MatrixXf X(result.cols(),2);
        X.col(0) = result.transpose().col(0);
        X.col(1) = result.transpose().col(1);

//        Eigen::MatrixXf X(result.cols(),2);
//        std::size_t row_x = 0;
//        for(auto && v : vs_){
//            X.row(row_x) = vpoints_[v];
//            row_x++;
//        }

        std::cout << X << std::endl;

        //calculate all sums needed in further calculations
        float sumX = X.col(0).array().sum();
        float sumXSq = (X.col(0).array()*X.col(0).array()).sum();
        float sumXCube = ((X.col(0).array()*X.col(0).array())*X.col(0).array()).sum();

        float sumY = X.col(1).array().sum();
        float sumYSq = (X.col(1).array()*X.col(1).array()).sum();
        float sumYCube = ((X.col(1).array()*X.col(1).array())*X.col(1).array()).sum();

        float sumXY = (X.col(0).array()*X.col(1).array()).sum();
        float sumXSqY = ((X.col(0).array()*X.col(0).array())*X.col(1).array()).sum();
        float sumXYSq = (X.col(0).array()*(X.col(1).array()*X.col(1).array())).sum();

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

        Eigen::Vector3f res(xBar,yBar,0.0f);
        //point minus center
        for(int i = 0; i < result.cols(); i++){
            auto c2p = result.col(i) - res;
            auto proj = res + c2p.normalized()*radius;
            std::cout << "Proj: \n" << proj << std::endl;
            auto to_empl = Rinv * proj;
            std::cout << "To_empl: \n" << to_empl << std::endl;
            ps.emplace_back(to_empl);
        }

        return ps;
    }

}
