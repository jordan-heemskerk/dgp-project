#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderShaded.h>
#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderFlat.h>
#include "ArcballWindow.h"
#include <csc486a/closeness_constraint.hpp>
#include <csc486a/rigid_constraint.hpp>
#include <csc486a/solver.hpp>
#include <optional.hpp>
#include <deque>
#include <utility>
using namespace OpenGP;

struct MainWindow : public ArcballWindow{
    SurfaceMesh mesh;
    SurfaceMeshRenderFlat renderer = SurfaceMeshRenderFlat(mesh);
    std::optional<csc486a::solver> s_;
    std::deque<csc486a::closeness_constraint> ccs_;
    std::deque<csc486a::rigid_constraint> rcs_;
    //std::optional<csc486a::line_constraint> lc_;
 
    MainWindow(int argc, char** argv) : ArcballWindow(__FILE__,400,400){
        if(argc!=2) mFatal("application requires one parameter! e.g. sphere.obj");
        bool success = mesh.read(argv[1]);
        if(!success) mFatal() << "File not found: " << argv[1];

        mesh.triangulate();
        mesh.update_face_normals(); ///< shading
        this->scene.add(renderer);
        
        // closeness constraint on all points
        std::vector<OpenGP::SurfaceMesh::Vertex> vs;
        for (auto && v : mesh.vertices()) {
            
            ccs_.emplace_back(mesh,v,1.0f);
            vs.push_back(v);
            
        }

        // copy the original to displaced
        SurfaceMesh displaced = SurfaceMesh(mesh);
        
        // displace the mesh!
        auto vpoints = displaced.get_vertex_property<Eigen::Vector3f>("v:point");
        if (!vpoints) throw std::logic_error("vpoints doesn't exist");
        
        // drag a patch somewhere
        OpenGP::SurfaceMesh::Vertex target(0);
        Eigen::Vector3f offset(0,0.1,-0.2);
        vpoints[target] += offset;
        for (auto && he : mesh.halfedges(target)) {
            vpoints[mesh.to_vertex(he)] += offset;
        }
        
        // offset some vertices
        /*size_t itt = 0;
        for (auto && v : displaced.vertices()) {
            if (itt > 40) break;
            vpoints[v] += Eigen::Vector3f(0,0,-1);
            ++itt;
        }*/
        
        // add conformal one ring constraints TODO optimize this!
        unsigned int curr = 0;
        std::vector<OpenGP::SurfaceMesh::Vertex> onering;
        onering.reserve(10);
        for (auto && v : mesh.vertices()) {
            onering.clear();
            onering.push_back(v);
            
            for (auto && he : mesh.halfedges(v)) {
                onering.push_back(mesh.to_vertex(he));
            }
            
            rcs_.emplace_back(mesh, displaced, onering, 1.0f);
            
            //progress report
            if (curr % (mesh.n_vertices()/20) == 0) {
                float prog = (curr * 100.0)/mesh.n_vertices();
                std::cout << "Progress: " << prog << std::endl;
            }
            curr++;
            
        }
        
        // add to solver
        s_.emplace(mesh);
        for (auto && cc : ccs_) s_->add(cc);
        for (auto && rc : rcs_) s_->add(rc);
        
    }
    
    void key_callback(int key, int scancode, int action, int mods) override{
        ArcballWindow::key_callback(key, scancode, action, mods);
        if(key==GLFW_KEY_SPACE && action==GLFW_RELEASE){
            (*s_)();
            mesh.update_face_normals();
            renderer.init_data();
        }
    }
};

int main(int argc, char** argv){
    MainWindow window(argc, argv);
    return window.run();
}
