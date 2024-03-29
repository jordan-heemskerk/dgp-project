/**
 *  \file
 */


#pragma once


#include <csc486a/constraint.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <type_traits>


namespace csc486a {
    
    
    /**
     *  \cond
     */
    
    
    class has_vertices {
        
        
        protected:
        
        
            OpenGP::SurfaceMesh::Vertex_property<constraint::point_type> vpoints_;
        
        
            explicit has_vertices (const OpenGP::SurfaceMesh &);
        
        
        public:
        
        
            has_vertices () = delete;
            has_vertices (const has_vertices &) = default;
            has_vertices (has_vertices &&) = default;
            has_vertices & operator = (const has_vertices &) = default;
            has_vertices & operator = (has_vertices &&) = default;
        
        
    };
    
    
    class no_vertices { };
    
    
    template <bool has_vertices>
    using has_mesh_base=typename std::conditional<has_vertices,csc486a::has_vertices,no_vertices>::type;
    
    
    /**
     *  \endcond
     */
    
    
    /**
     *  A convenience base class for any class which holds
     *  a reference to a SurfaceMesh.
     *
     *  \tparam has_vertices
     *      If \em true the class shall have a \em vpoints_
     *      protected member which encapsulates the "v:points"
     *      property of the mesh-in-question.  Defaults to
     *      \em true.
     *  \tparam is_const
     *      If \em true the reference to the SurfaceMesh object
     *      shall be a reference to a const qualified SurfaceMesh
     *      object.  Defaults to \em false.
     *  \tparam is_volatile
     *      If \em true the reference to the SurfaceMesh object
     *      shall be a reference to a volatile qualified SurfaceMesh
     *      object.  Defaults to \em false.
     */
    template <bool has_vertices=true, bool is_const=false, bool is_volatile=false>
    class has_mesh : protected has_mesh_base<has_vertices> {
        
        
        private:
        
        
            using base=has_mesh_base<has_vertices>;
            using volatile_type=typename std::conditional<
                is_volatile,
                typename std::add_volatile<OpenGP::SurfaceMesh>::type,
                OpenGP::SurfaceMesh
            >::type;
            using const_type=typename std::conditional<
                is_const,
                typename std::add_const<volatile_type>::type,
                volatile_type
            >::type;
            using reference_type=typename std::add_lvalue_reference<const_type>::type;
        
        
        protected:
        
        
            /**
             *  A reference to the mesh with which this
             *  object was constructed.
             */
            reference_type mesh_;
        
        
            /**
             *  Creates a has_mesh object.
             *
             *  \param [in] mesh
             *      A reference to the mesh upon which the
             *      class shall be constructed.
             */
            explicit has_mesh (reference_type mesh) noexcept(std::is_nothrow_constructible<base,reference_type>::value) : base(mesh), mesh_(mesh) {  }
        
        
        public:
        
        
            has_mesh () = delete;
            has_mesh (const has_mesh &) = default;
            has_mesh (has_mesh &&) = default;
            has_mesh & operator = (const has_mesh &) = default;
            has_mesh & operator = (has_mesh &&) = default;
        
        
    };
    
    
}
