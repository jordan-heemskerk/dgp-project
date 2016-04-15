#include <csc486a/closeness_constraint.hpp>
#include <csc486a/plane_constraint.hpp>
#include <csc486a/scaling_constraint.hpp>
#include <csc486a/rigid_constraint.hpp>
#include <csc486a/window_base.hpp>
#include <OpenGP/GL/GlfwWindow.h>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <cstdlib>
#include <cstring>
#include <csc486a/circle_constraint.hpp>
#include <csc486a/sphere_constraint.hpp>
#include <optional.hpp>
#include <deque>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>


static std::vector<OpenGP::SurfaceMesh::Vertex> vertices (const OpenGP::SurfaceMesh & mesh) {
    
    std::vector<OpenGP::SurfaceMesh::Vertex> retr;
    for (auto && v : mesh.vertices()) retr.push_back(v);
    
    return retr;
    
}

namespace {
    

    class sphere_demo : public csc486a::window_base {
        private:

        std::deque<csc486a::closeness_constraint> ccs_;
        std::deque<csc486a::rigid_constraint> rcs_;
        //std::optional<csc486a::line_constraint> lc_;
        std::deque<csc486a::circle_constraint> circlecs_;

        protected:

        public:

        explicit sphere_demo (OpenGP::SurfaceMesh mesh) : csc486a::window_base(std::move(mesh)) {
            //closeness constraints
            std::vector<OpenGP::SurfaceMesh::Vertex> va;
            for (auto && v : mesh_.vertices()) {
               ccs_.emplace_back(mesh_,v,1.0f);
               va.push_back(v);
            }

            //circle constraint on 40 vertices
            std::vector<OpenGP::SurfaceMesh::Vertex> vs;
            size_t itt = 0;
            for(auto && v : mesh_.vertices()){
                if(itt > 50) break;
                vs.push_back(v);
                //itt++;
            }


            circlecs_.emplace_back(mesh_,vs,1.0f);



            // add to solver
    //                    s_.emplace(mesh);
            //for (auto && cc : ccs_) s_->add(cc);
            for (auto && rc : circlecs_) add(rc);
    //                    for (auto && rc : rcs_) s_->add(rc);


        }

    };


    class rigid_demo : public csc486a::window_base {
        
        private:
        
        std::vector<unsigned int> moveable_bunny_obj =  {2, 155, 239, 46, 296, 294, 180, 110, 25, 392, 133, 489, 185, 280, 364, 493, 495, 144, 297, 170, 46, 111, 16, 192, 33, 80};
        std::vector<unsigned int> static_bunny_obj = {461, 434, 411, 431, 424, 419, 442, 415};
        std::vector <unsigned int> moveable_quad2_obj = {0,35,19,47,4,48,20,36,3,27,79,63,78,28,70,51,69,26};
        std::vector <unsigned int> static_quad2_obj = {30,74,56,66,37,77,60,67,34,1,31,15,43,5,41,13,29,2};
        
        std::vector<unsigned int> moveable_quad3_obj = {2,90,442,34,482,130,338,18,350,142,494,46,454,102,310,7,302,94,446,38,486,134,342,10,330,122,474,26,434,82,290,3,293,835,585,903,377,855,665,963,321,843,617,927,409,879,761,1035,297,833,577,897,369,849,641,945,313,837,593,909,385,861,689,981,300};
        
        std::vector<unsigned int> static_quad3_obj = {1,294,86,438,30,478,126,334,14,346,138,490,42,450,98,306,6,303,95,447,39,487,135,343,11,331,123,475,27,435,83,291,0,299,1075,814,1076,426,1078,818,1079,326,1084,826,1085,430,1087,830,1088,296,1021,742,1022,402,1024,746,1025,318,1030,754,1031,406,1033,758,1034,295};
        
        
        

        
        std::deque<csc486a::rigid_constraint> rcs_;
        std::deque<csc486a::closeness_constraint> ccs_;
        
        std::vector<unsigned int> moveable_handle;
        std::vector<unsigned int> static_handle;
        
        void move_handle(Eigen::Vector3f offset) {
            
            // displace the mesh!
            auto vpoints = mesh_.get_vertex_property<Eigen::Vector3f>("v:point");
            if (!vpoints) throw std::logic_error("vpoints doesn't exist");
            
            
            for (auto && v_i : moveable_handle) vpoints[OpenGP::SurfaceMesh::Vertex(v_i)] += offset;

        }
        
        protected:
        
        
        public:
        
        
        // use with quad2 or bunny
        // here we defer the triangulation so that one rings are done on the quad mesh
        explicit rigid_demo (OpenGP::SurfaceMesh mesh, const char * file) : csc486a::window_base(std::move(mesh), true) {
            
            
            // choose handles
            if (std::strcmp(file,"quad2.obj")==0) {
                moveable_handle = std::move(moveable_quad2_obj);
                static_handle = std::move(static_quad2_obj);
            } else if (std::strcmp(file,"bunny.obj")==0) {
                moveable_handle = std::move(moveable_bunny_obj);
                static_handle = std::move(static_bunny_obj);
            } else if (std::strcmp(file,"quad3.obj")==0) {
                moveable_handle = std::move(moveable_quad3_obj);
                static_handle = std::move(static_quad3_obj);
            } else { std::cout << "WARNING: no handles" << std::endl;}
            
            
            // copy the original to displaced
            OpenGP::SurfaceMesh original = OpenGP::SurfaceMesh(mesh_);

            // define handle
            OpenGP::SurfaceMesh::Vertex_property<bool> is_handle = mesh_.add_vertex_property<bool>("v:is_handle", false);
            
            // is handle = true for static and moveable handles
            for (auto && v_i : moveable_handle) is_handle[OpenGP::SurfaceMesh::Vertex(v_i)] = true;
            for (auto && v_i : static_handle) is_handle[OpenGP::SurfaceMesh::Vertex(v_i)] = true;
            
            // closeness on all handles
            for (auto && v_i : moveable_handle) ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(v_i),1.0f);
            for (auto && v_i : static_handle) ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(v_i),1.0f);
            
            //loop over onerings and add constraint for each one. weight this less than holding the handles
            unsigned int curr = 0;
            std::vector<OpenGP::SurfaceMesh::Vertex> onering;
            onering.reserve(10); // should be sufficient for quad and triangle
            for (auto && v : mesh.vertices()) {

                if (is_handle[v]) continue;
                onering.clear();
                onering.push_back(v);

                for (auto && he : mesh.halfedges(v)) {
                    OpenGP::SurfaceMesh::Vertex v_or = mesh.to_vertex(he);
                    onering.push_back(v_or);
                }

                rcs_.emplace_back(mesh_, original, onering, 0.05f);
                add(rcs_.back());
                
                //progress report (for large meshes)
                if (curr % (mesh.n_vertices()/20) == 0) {
                    float prog = (curr * 100.0)/mesh.n_vertices();
                    std::cout << "Onering Progress: " << prog << std::endl;
                }
                curr++;
            }
            
            // add closeness constriants
            for (auto && cc : ccs_) add(cc);
            
            // now triangulate and add to scene
            add_mesh_to_scene();
            
        }
        
        virtual void vertex_click (vertex_click_event e) override {
            
            auto h=e.vertex.idx();
            
            std::cout << "Clicked on vertex #" << h << std::endl;
            
        }

        
#define IT 5
#define STEP_SIZE 0.1f
        void key_callback (int key, int scancode, int action, int mods) {
            
            window_base::key_callback(key, scancode, action, mods);
            
            Eigen::Vector3f offset;
            bool update = false;
            
            if ((key==GLFW_KEY_UP) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,-STEP_SIZE,0);
                update = true;
            }
            
            if ((key==GLFW_KEY_LEFT) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,0,-STEP_SIZE);
                update = true;
            }
            
            if ((key==GLFW_KEY_DOWN) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,STEP_SIZE,0);
                update = true;
            }
            
            if ((key==GLFW_KEY_RIGHT) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,0,STEP_SIZE);
                update = true;

            }
            
            if ((key==GLFW_KEY_COMMA) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(-STEP_SIZE, 0, 0);
                update = true;
            }
            
            if ((key==GLFW_KEY_PERIOD) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(STEP_SIZE, 0, 0);
                update = true;
            }
            
            if (update) {
                move_handle(offset);
                for(int i = 0; i < IT; i++)s_();
                mesh_.update_face_normals();
                renderer_.init_data();
            }
            
            
        }
    };
    
    class point_pick : public csc486a::window_base {
        
        protected:
            virtual void vertex_click (vertex_click_event e) override {
                
                auto h=e.vertex.idx();
                
                std::cout << "Clicked on vertex #" << h << std::endl;
                
            }
        
        public:
            explicit point_pick (OpenGP::SurfaceMesh mesh) : csc486a::window_base(std::move(mesh)) { }
        
        
        
        
    };
    
    class test_window : public csc486a::window_base {
        
        
        private:
        
        
            std::deque<csc486a::scaling_constraint> scs_;
            std::unordered_map<int,csc486a::closeness_constraint> ccs_;
        
        
        protected:
        
        
            virtual void vertex_click (vertex_click_event e) override {
                
                auto h=e.vertex.idx();
                
                std::cout << "Clicked on vertex #" << h << std::endl;
                
                auto iter=ccs_.find(h);
                if (iter==ccs_.end()) {
                    
                    std::cout << "Already scaling constraint on vertex #" << h << ", skipping" << std::endl;
                    
                    return;
                    
                }
                
                remove(iter->second);
                ccs_.erase(iter);
                scs_.emplace_back(mesh_,e.vertex,1.5f,1.0f);
                add(scs_.back());
                std::cout << "Added scaling constraint to vertex #" << h << std::endl;
                
            }
        
        
        public:
        
        
            explicit test_window (OpenGP::SurfaceMesh mesh) : csc486a::window_base(std::move(mesh)) {
                
                for (auto && v : mesh_.vertices()) ccs_.emplace(std::piecewise_construct,std::forward_as_tuple(v.idx()),std::forward_as_tuple(mesh_,v,1.0f));
                for (auto && pair : ccs_) add(pair.second);
                
            }
        
        
    };
    
    
    class plane_demo : public csc486a::window_base {
        
        
        private:
        
        
            csc486a::plane_constraint c_;
        
        
        public:
        
        
        explicit plane_demo (OpenGP::SurfaceMesh mesh) : csc486a::window_base(std::move(mesh)), c_(mesh_,vertices(mesh_),1.0f) {
            
            add(c_);
            
        }
        
        
    };
    
}


static std::unique_ptr<OpenGP::GlfwWindow> get_window (int argc, char ** argv) {
    
    if (argc!=3) {
        
        std::ostringstream ss;
        ss << "Expected 2 command line parameters, got " << (argc-1);
        throw std::runtime_error(ss.str());
        
    }
    
    OpenGP::SurfaceMesh mesh;
    const char * file=argv[2];
    if (!mesh.read(file)) {
        
        std::ostringstream ss;
        ss << "Failed reading file " << file;
        throw std::runtime_error(ss.str());
        
    }
    
    const char * name=argv[1];
    using pointer=std::unique_ptr<OpenGP::GlfwWindow>;
    if (std::strcmp(name,"test")==0) return pointer(new test_window(std::move(mesh)));
    if (std::strcmp(name,"sphere")==0) return pointer(new sphere_demo(std::move(mesh)));
    if (std::strcmp(name,"rigid")==0) return pointer(new rigid_demo(std::move(mesh), file));
    if (std::strcmp(name,"pick")==0) return pointer(new point_pick(std::move(mesh)));
    if (std::strcmp(name,"plane")==0) return pointer(new plane_demo(std::move(mesh)));
    
    std::ostringstream ss;
    ss << "Could not find a demo named \"" << name << "\"";
    throw std::runtime_error(ss.str());
    
}


static void main_impl (int argc, char ** argv) {
    
    auto ptr=get_window(argc,argv);
    if (ptr->run()!=0) throw std::runtime_error("Window reported error");
    
}


int main (int argc, char ** argv) {
    
    try {
        
        try {
            
            main_impl(argc,argv);
            
        } catch (const std::exception & e) {
            
            std::cerr << "ERROR: " << e.what() << std::endl;
            throw;
            
        } catch (...) {
            
            std::cerr << "ERROR" << std::endl;
            throw;
            
        }
        
    } catch (...) {
    
        return EXIT_FAILURE;
     
    }
    
}
