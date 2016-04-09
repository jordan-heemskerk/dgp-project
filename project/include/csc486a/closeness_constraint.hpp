/**
 *  \file
 */


#pragma once


#include <csc486a/constraint.hpp>
#include <csc486a/has_mesh.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>


namespace csc486a {
    
    
    class closeness_constraint : public constraint, protected has_mesh<true,true> {
        
        
        private:
        
        
            OpenGP::SurfaceMesh::Vertex v_;
            point_type p_;
            float w_;
        
        
        public:
        
        
            closeness_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w);
        
        
            virtual triplets_type add (triplets_type ts=triplets_type{}) const override;
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}
