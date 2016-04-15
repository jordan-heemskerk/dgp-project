/**
 *  \file
 */


#pragma once


#include <csc486a/vertices_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {


    class circle_sphere_constraint_base : public vertices_constraint_base {


        protected:


            enum class type {

                circle,
                sphere

            };


        private:


            type t_;


        protected:


            circle_sphere_constraint_base (const OpenGP::SurfaceMesh &, std::vector<OpenGP::SurfaceMesh::Vertex>, float, type);


        public:


            virtual points_type project (points_type ps=points_type{}) const override;


    };


}
