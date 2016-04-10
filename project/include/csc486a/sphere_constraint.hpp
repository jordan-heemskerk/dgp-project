/**
 *  \file
 */


#pragma once


#include <csc486a/circle_sphere_constraint_base.hpp>


namespace csc486a {


    class sphere_constraint : public circle_sphere_constraint_base {


        public:


        sphere_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type);


    };


}
