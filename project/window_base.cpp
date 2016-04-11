#include <csc486a/window_base.hpp>
#include <Eigen/Dense>
#include <utility>


namespace csc486a {
    
    
    void window_base::vertex_click (vertex_click_event) {   }
    
    
    void window_base::add (constraint & c) {
        
        s_.add(c);
        
    }
    
    
    window_base::window_base (OpenGP::SurfaceMesh mesh) : ArcballWindow("CSC486A",400,400), mesh_(std::move(mesh)), renderer_(mesh_), s_(mesh_) {
        
        mesh_.triangulate();
        mesh_.update_face_normals();
        scene.add(renderer_);
        
    }
    
    
    void window_base::key_callback (int key, int scancode, int action, int mods) {
        
        ArcballWindow::key_callback(key,scancode,action,mods);
        
        if ((key==GLFW_KEY_SPACE) && (action==GLFW_RELEASE)) {
            
            acc_=std::nullopt;
            s_();
            mesh_.update_face_normals();
            renderer_.init_data();
            
        }
        
    }
    
    
    void window_base::mouse_press_callback (int button, int action, int mod) {
        
        ArcballWindow::mouse_press_callback(button,action,mod);
        
        if (button!=GLFW_MOUSE_BUTTON_LEFT) return;
        
        if (action==GLFW_PRESS) {
            
            press_=clock_type::now();
            
            return;
            
        }
        
        //  Can it take on other values?  Who knows...
        if (action!=GLFW_RELEASE) return;
        
        //  Ignore clicks that are deemed to be drags
        std::chrono::milliseconds max(1000U/4U);
        auto since=std::chrono::duration_cast<std::chrono::milliseconds>(clock_type::now()-press_);
        if (since>max) return;
            
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
        
        // Find closest vertex
        if (!acc_) acc_.emplace(mesh_);
        auto closest=acc_->closest_vertex(np_wc3);
        vertex_click(vertex_click_event{closest});
        
    }
    
    
}
