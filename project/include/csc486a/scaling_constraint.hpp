/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    class scaling_constraint : public constraint_base {
        
        
        private:
        
        
            float s_;
        
        
        public:
        
        
            scaling_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float s, float w);
        
        
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}
