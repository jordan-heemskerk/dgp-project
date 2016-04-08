/**
 *  \file
 */


#pragma once


#include <csc486a/constraint.hpp>
#include <Eigen/SparseCholesky>
#include <Eigen/SparseCore>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <optional.hpp>
#include <cstddef>
#include <vector>


namespace csc486a {
    
    
    /**
     *  Represents a Shape Op solver.
     */
    class solver {
        
        
        private:
        
        
            using sparse_type=Eigen::SparseMatrix<float>;
            using cholesky_type=Eigen::SimplicialLDLT<sparse_type>;
        
        
            OpenGP::SurfaceMesh & mesh_;
            std::vector<const constraint *> cs_;
            std::optional<cholesky_type> q_;
            std::size_t ps_;
            constraint::points_type b_;
            OpenGP::SurfaceMesh::Vertex_property<constraint::point_type> vpoints_;
        
        
            void create_q ();
        
        
        public:
        
        
            solver () = delete;
            solver (const solver &) = delete;
            solver (solver &&) = delete;
            solver & operator = (const solver &) = delete;
            solver & operator = (solver &&) = delete;
        
        
            /**
             *  Creates a new solver which operates on
             *  a certain mesh.
             *
             *  \param [in] mesh
             *      The mesh upon which to operate.  The
             *      mesh shall be updated in place.  The
             *      provided reference must remain valid for
             *      the lifetime of the created solver object
             *      or the behaviour is undefined.  Vertices
             *      shall not be added to the mesh or removed
             *      from it during the lifetime of the solver
             *      or the behaviour is undefined.
             */
            explicit solver (OpenGP::SurfaceMesh & mesh);
        
        
            /**
             *  Adds a constraint to the solver.
             *
             *  This method must not be called after the
             *  solver has already been used for at least
             *  one iteration.
             *
             *  The added constraint must operate on the
             *  same mesh used to construct this solver
             *  or the behaviour is undefined.
             *
             *  \param [in] c
             *      A reference to the constraint to add.
             *      This reference must remain valid for the
             *      lifetime of the solver object or the behaviour
             *      is undefined.
             */
            void add (const constraint & c);
        
        
            /**
             *  Runs one iteration of the solver.
             */
            void operator () ();
        
        
    };
    
    
}
