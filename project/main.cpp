#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderShaded.h>
#include <OpenGP/SurfaceMesh/GL/SurfaceMeshRenderFlat.h>
#include "ArcballWindow.h"
#include <csc486a/scaling_constraint.hpp>
#include <csc486a/solver.hpp>
#include <optional.hpp>
using namespace OpenGP;

struct MainWindow : public ArcballWindow{
    SurfaceMesh mesh;
    SurfaceMeshRenderFlat renderer = SurfaceMeshRenderFlat(mesh);
    std::optional<csc486a::scaling_constraint> sc_;
    std::optional<csc486a::solver> s_;
 
    MainWindow(int argc, char** argv) : ArcballWindow(__FILE__,400,400){
        if(argc!=2) mFatal("application requires one parameter! e.g. sphere.obj");
        bool success = mesh.read(argv[1]);
        if(!success) mFatal() << "File not found: " << argv[1];
        mesh.triangulate();
        mesh.update_face_normals(); ///< shading
        this->scene.add(renderer);
        
        sc_.emplace(mesh,0.75f);
        s_.emplace(mesh);
        s_->add(*sc_);
        
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
