/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>


namespace csc486a {
    
    
    class line_plane_constraint_base : public constraint_base {
        
        
        protected:
        
        
            enum class type {
                
                line,
                plane
                
            };
        
        
        private:
        
        
            type t_;
        
        
        protected:
        
        
            line_plane_constraint_base (const OpenGP::SurfaceMesh &, std::vector<OpenGP::SurfaceMesh::Vertex>, float, type);
        
        
        public:
        
        
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}

