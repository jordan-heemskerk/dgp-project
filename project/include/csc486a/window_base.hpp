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
    
    
    /**
     *  A convenience base class for demos.
     */
    class window_base : public ::ArcballWindow {
        
        
        protected:
        
        
            /**
             *  The mesh which is being rendered.
             */
            OpenGP::SurfaceMesh mesh_;
        
        
            /**
             *  Represents an event wherein a vertex in \em mesh_
             *  is clicked.
             */
            class vertex_click_event {
            
            
                public:
                
                
                    /**
                     *  The vertex from \em mesh_ which was clicked.
                     */
                    OpenGP::SurfaceMesh::Vertex vertex;
                
            
            };
        
        
            /**
             *  Invoked when a vertex in \em mesh_ is clicked.
             *
             *  Default implementation does nothing.
             *
             *  \param [in] e
             *      An object which encapsulates all details of
             *      the event.
             */
            virtual void vertex_click (vertex_click_event e);
            /**
             *  Adds a constraint to the solver.
             *
             *  \param [in] c
             *      The constraint to remove.
             */
            void add (const constraint & c);
            /**
             *  Removes a constraint from the solver.
             *
             *  \param [in] c
             *      The constraint to remove.
             */
            void remove (const constraint & c) noexcept;
            /**
             *  The renderer which is used to display \em mesh_.
             */
            OpenGP::SurfaceMeshRenderFlat renderer_;
            /**
             *  The Shape Op solver which is used to evaluate
             *  all constraints.
             */
            solver s_;


            /**
             *  Creates a new window_base.
             *
             *  \param [in] mesh
             *      The mesh to operate on.
             *  \param [in] defer_triangulation
             *      \em true if \em mesh shouldn't be immediately
             *      triangulated.  Defaults to \em false in which
             *      case the mesh shall be triangulated within the
             *      constructor.  This value is irrelevant for
             *      triangular meshes.
             */        
            explicit window_base (OpenGP::SurfaceMesh mesh, bool defer_triangulation = false);
        
        
            /**
             *  Base classes must call this if the constructor was
             *  invoked with \em defer_triangulation set to \em true,
             *  otherwise the constructor shall call this method.
             *
             *  Triangulates the mesh and adds it to \em renderer_.
             */
            void add_mesh_to_scene();
            
        
        private:
        
        
            using clock_type=std::chrono::steady_clock;
            using time_point_type=clock_type::time_point;
        
        

            std::optional<OpenGP::SurfaceMeshVerticesKDTree> acc_;
            time_point_type press_;
        
        
        public:
        
        virtual void key_callback (int, int, int, int) override;
        virtual void mouse_press_callback (int, int, int) override;
        
        
    };
    
    
}
