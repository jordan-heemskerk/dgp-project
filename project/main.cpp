#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderShaded.h>
#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderFlat.h>
#include "ArcballWindow.h"
#include "SurfaceMeshVerticesKDTree.h"
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

        
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
        glDepthRange(0.0f, 1.0f);
        
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
    
    // get vertex from clicking
    void mouse_press_callback(int button, int action, int mod) override {
        
        // do arc ball stuff first!
        ArcballWindow::mouse_press_callback(button, action, mod);
        
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                
                // get cursor
                double x, y;
                glfwGetCursorPos(_window, &x, &y);
                
                // get viewport
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);
                
                // assume model is I and compute unprojection matrix
                auto pm = scene._projection * scene._view;
                auto unprojected = pm.inverse();
                
                float ogl_y = _height - y;
                
                // get depth value for mesh intersection
                float z;
                glReadPixels(x, ogl_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
                
                // do the unprojection
                Eigen::Vector4f win_pos((2*(x-viewport[0])/viewport[2])-1,(2*(ogl_y-viewport[1])/viewport[3])-1,(2*z)-1,1);
                Eigen::Vector4f wc4 = unprojected * win_pos;
            
                // homogenuos coordinates -> Vec3
                Eigen::Vector3f np_wc3 = Eigen::Vector3f(wc4(0)/wc4[3], wc4(1)/wc4[3], wc4(2)/wc4[3]);
            
                // Find closest vertex - TODO when should we build the index?
                SurfaceMeshVerticesKDTree accelerator = SurfaceMeshVerticesKDTree(mesh);
                SurfaceMesh::Vertex closest = accelerator.closest_vertex(np_wc3);
                std::cout << "You clicked vertex with index: " << closest << std::endl;
                
            }
        }
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
