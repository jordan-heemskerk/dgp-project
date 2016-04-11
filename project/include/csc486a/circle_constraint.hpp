/**
 *  \file
 */


#pragma once

#include <csc486a/circle_sphere_constraint_base.hpp>

namespace csc486a {

    class circle_constraint : public circle_sphere_constraint_base {

        public:

        circle_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);

    };

}
//        // closeness constraint on all points
//        std::vector<OpenGP::SurfaceMesh::Vertex> vs;
//        for (auto && v : mesh.vertices()) {

//            ccs_.emplace_back(mesh,v,1.0f);
//            vs.push_back(v);

//        }

//        // copy the original to displaced
//        SurfaceMesh displaced = SurfaceMesh(mesh);

//        // displace the mesh!
//        auto vpoints = displaced.get_vertex_property<Eigen::Vector3f>("v:point");
//        if (!vpoints) throw std::logic_error("vpoints doesn't exist");

//        // drag a patch somewhere
//        OpenGP::SurfaceMesh::Vertex target(0);
//        Eigen::Vector3f offset(0,0.1,-0.2);
//        vpoints[target] += offset;
//        for (auto && he : mesh.halfedges(target)) {
//            vpoints[mesh.to_vertex(he)] += offset;
//        }

//        // offset some vertices
//        /*size_t itt = 0;
//        for (auto && v : displaced.vertices()) {
//            if (itt > 40) break;
//            vpoints[v] += Eigen::Vector3f(0,0,-1);
//            ++itt;
//        }*/

//        // add conformal one ring constraints TODO optimize this!
//        unsigned int curr = 0;
//        std::vector<OpenGP::SurfaceMesh::Vertex> onering;
//        onering.reserve(10);
//        for (auto && v : mesh.vertices()) {
//            onering.clear();
//            onering.push_back(v);

//            for (auto && he : mesh.halfedges(v)) {
//                onering.push_back(mesh.to_vertex(he));
//            }

//            rcs_.emplace_back(mesh, displaced, onering, 1.0f);

//            //progress report
//            if (curr % (mesh.n_vertices()/20) == 0) {
//                float prog = (curr * 100.0)/mesh.n_vertices();
//                std::cout << "Progress: " << prog << std::endl;
//            }
//            curr++;

//        }
