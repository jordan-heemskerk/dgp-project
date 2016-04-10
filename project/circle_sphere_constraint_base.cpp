#include <csc486a/circle_sphere_constraint_base.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <OpenGP/MLogger.h> /// mDebug() <<
#include <cmath>

namespace csc486a{

    circle_sphere_constraint_base::circle_sphere_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t) : vertices_constraint_base(mesh,std::move(vs),w), t_(t) { }

    circle_sphere_constraint_base::points_type circle_sphere_constraint_base::project (points_type ps) const {

        //just in case
        ps.clear();

        //number of points in this constraint
        auto N = vs_.size();

        if(t_ == type::circle){

        }



        return ps;
    }
}
