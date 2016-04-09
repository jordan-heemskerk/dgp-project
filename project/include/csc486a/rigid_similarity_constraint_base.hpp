/**
* \file
*/

#pragma once

#include <csc486a/vertices_constraint_base.hpp>

namespace csc486a {
    
    class rigid_similarity_constraint_base : public vertices_constraint_base {
        
        
    protected:
        
        enum class type {
            
            rigid,
            similarity
            
        };
        
    private:
        
        type t_;
        OpenGP::SurfaceMesh deformed_;
        float clamp_;
        
    protected:
        
        rigid_similarity_constraint_base (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh deformed, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t, float clamp);
        
    private:
        
        bool floateq(float a, float b) const;
        float variance(Eigen::MatrixXf A) const;
        
    public:
        
        virtual points_type project (points_type ps=points_type{}) const override;
        
    };
}