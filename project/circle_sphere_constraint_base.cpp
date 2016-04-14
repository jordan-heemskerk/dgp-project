#include <csc486a/circle_sphere_constraint_base.hpp>
#include <csc486a/sphere_constraint.hpp>
#include <csc486a/circle_constraint.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <OpenGP/MLogger.h> /// mDebug() <<
#include <cmath>
#include <utility>

namespace csc486a{

    circle_sphere_constraint_base::circle_sphere_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t) : vertices_constraint_base(mesh,std::move(vs),w), t_(t) { }

    circle_sphere_constraint_base::points_type circle_sphere_constraint_base::project (points_type ps) const {
        if(t_ == csc486a::circle_sphere_constraint_base::type::circle){
            std::cout << "Circle" << std::endl;
            circle_constraint cc(mesh_, vs_, 0.0f);
            return cc.project(ps);
        }else{
            std::cout << "Sphere" << std::endl;
            sphere_constraint sc(mesh_,vs_,0.0f);
            return sc.project(ps);
         }
    }
}
