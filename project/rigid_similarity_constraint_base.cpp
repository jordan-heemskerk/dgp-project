#include <csc486a/rigid_similarity_constraint_base.hpp>
#include <utility>


#define DIM (3)
#define EPSILON 0.00001f

namespace csc486a {
    
    
    static bool floateq (float a, float b) {
        return std::abs(a-b) < EPSILON;
    }
    
    static float variance(Eigen::MatrixXf A) {
        auto u_x = A.colwise().mean();
        auto A_temp = A;
        A_temp.rowwise() -= u_x;
        auto normed = A_temp.rowwise().squaredNorm();
        auto var = normed.sum()/float(A.rows());
        return var;
    }
    
    
    rigid_similarity_constraint_base::rigid_similarity_constraint_base (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, rigid_similarity_constraint_base::type t, float clamp) : vertices_constraint_base(mesh, std::move(vs), w), original_(std::move(original)), t_(t), clamp_(clamp) { }
    
    rigid_similarity_constraint_base::points_type rigid_similarity_constraint_base::project(points_type ps) const {
        
        // Just in case
        ps.clear();
        
        // number of points in this constraint
        auto n_pts = vs_.size();
        
        auto dvpoints = original_.get_vertex_property<Eigen::Vector3f>("v:point");
        
        // load points from std::vector to matrix of positions
        Eigen::MatrixXf X(n_pts, DIM);
        Eigen::MatrixXf Y(n_pts, DIM);
        std::size_t row_x(0);
        for (auto && v : vs_) {
            Y.row(row_x) = vpoints_[v];
            X.row(row_x) = dvpoints[v];
            row_x++;
        }
        
        // calculate means, variances and covariances
        Eigen::VectorXf u_x(DIM);
        Eigen::VectorXf u_y(DIM);
        u_x = X.colwise().mean();
        u_y = Y.colwise().mean();
        auto s_x = variance(X);
        auto s_y = variance(Y);
        auto centered_y = Y.rowwise() - Y.colwise().mean();
        auto centered_x = X.rowwise() - X.colwise().mean();
        Eigen::Matrix3f S_xy = (centered_y.adjoint() * centered_x)/float(Y.rows());
        
        // SVD
        Eigen::JacobiSVD<Eigen::MatrixXf> svd(S_xy, Eigen::ComputeThinU | Eigen::ComputeThinV);
        Eigen::Matrix3f U = svd.matrixU();
        Eigen::Matrix3f D = svd.singularValues().asDiagonal(); //these should be sorted
        Eigen::Matrix3f V = svd.matrixV();
        
        // determinant and rank for cases
        auto det = S_xy.determinant();
        auto rank = svd.rank();
        
        if (rank < DIM-1) throw std::logic_error("Rank does not match dimensions");
        
        Eigen::Matrix3f S = Eigen::Matrix3f::Identity();
        
        if (det < 0) {
            S(DIM-1,DIM-1) = -1;
        }
        
        if (rank == DIM-1) {
            S = Eigen::Matrix3f::Identity();
            auto det_cond = U.determinant() * V.determinant();
            
            if (floateq(det_cond, 1)) {
                //all good
            } else if (floateq(det_cond, -1)) {
                S(DIM-1,DIM-1) = -1;
            } else {
                throw std::logic_error("det_cond is not 1 or -1");
            }
        }
        
        // compute R, c, t
        Eigen::Matrix3f R = U * S * V.transpose();
        float c = (D*S).trace()/s_x;
        Eigen::Vector3f t = u_y - c*R*u_x;
        
        
        // force scale to be in specified range
        if (std::abs(c-1) > clamp_) {
            if ((c-1) > 0) c = 1 + clamp_;
            if ((c-1) < 0) c = 1 - clamp_;
        }
        
        // load up result to global projections
        for (unsigned int i = 0; i < n_pts; i++) {
            auto test = (c*R*X.row(i).transpose() +t).eval();
            ps.emplace_back(test*w_);
        }
        
        return ps;

        
        
    }
}