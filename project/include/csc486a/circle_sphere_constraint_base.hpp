/**
 *  \file
 */


#pragma once


#include <csc486a/vertices_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {


    /**
     *  A base class which encapsulates the common
     *  logic of circle and sphere constraints.
     */
    class circle_sphere_constraint_base : public vertices_constraint_base {


        protected:


            /**
             *  Indicates the type of constraint.
             */
            enum class type {

                circle, /**<    A circle constraint */
                sphere  /**<    A sphere constraint */

            };


        private:


            type t_;


        protected:


            /**
             *  Creates a new circle_sphere_constraint_base.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of this object or the behaviour is undefined.
             *  \param [in] vs
             *      A collection of vertices upon which this
             *      constraint shall operate.  All vertices must
             *      be from \em mesh or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             *  \param [in] t
             *      An enumeration value which indicates whether
             *      this constraint shall be a circle or sphere
             *      constraint.
             */
            circle_sphere_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t);


        public:


            virtual points_type project (points_type ps=points_type{}) const override;


    };


}
