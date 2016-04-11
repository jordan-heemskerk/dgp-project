/**
 *  \file
 */


#pragma once


#include <ArcballWindow.h>
#include <csc486a/constraint.hpp>
#include <csc486a/solver.hpp>
#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderFlat.h>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <SurfaceMeshVerticesKDTree.h>
#include <optional.hpp>
#include <chrono>
#include <memory>
#include <vector>


namespace csc486a {
    
    
    class window_base : public ::ArcballWindow {
        
        
        protected:
        
        
            OpenGP::SurfaceMesh mesh_;
        
        
            class vertex_click_event {
            
            
                public:
                
                
                    OpenGP::SurfaceMesh::Vertex vertex;
                
            
            };
        
        
            virtual void vertex_click (vertex_click_event);
            void add (const constraint & c);
        
        
            explicit window_base (OpenGP::SurfaceMesh mesh);
        
        
        private:
        
        
            using clock_type=std::chrono::steady_clock;
            using time_point_type=clock_type::time_point;
        
        
            OpenGP::SurfaceMeshRenderFlat renderer_;
            solver s_;
            std::optional<OpenGP::SurfaceMeshVerticesKDTree> acc_;
            time_point_type press_;
        
        
        public:
        
        
            virtual void key_callback (int, int, int, int) override;
            virtual void mouse_press_callback (int, int, int) override;
        
        
    };
    
    
}
