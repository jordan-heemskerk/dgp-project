/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>


namespace csc486a {
    
    
    class scaling_constraint : public constraint_base {
        
        
        private:
        
        
            float s_;
            OpenGP::SurfaceMesh::Vertex_property<point_type> vpoints_;
        
        
        public:
        
        
            scaling_constraint (const OpenGP::SurfaceMesh & mesh, float s);
        
        
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}
