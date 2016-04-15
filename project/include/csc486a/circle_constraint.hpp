/**
 *  \file
 */


#pragma once


#include <csc486a/circle_sphere_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {


    class circle_constraint : public circle_sphere_constraint_base {


        public:


        circle_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);


    };


}
