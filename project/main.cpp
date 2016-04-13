#include <csc486a/closeness_constraint.hpp>
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
        
        std::deque<csc486a::rigid_constraint> rcs_;
        std::deque<csc486a::closeness_constraint> ccs_;
        
        void move_handle(Eigen::Vector3f offset) {
            
            // displace the mesh!
            auto vpoints = mesh_.get_vertex_property<Eigen::Vector3f>("v:point");
            if (!vpoints) throw std::logic_error("vpoints doesn't exist");
            
            vpoints[OpenGP::SurfaceMesh::Vertex(0)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(35)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(19)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(47)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(4)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(48)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(20)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(36)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(3)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(27)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(79)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(63)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(78)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(28)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(70)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(51)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(69)] += offset;
            vpoints[OpenGP::SurfaceMesh::Vertex(26)] += offset;
        }
        
        protected:
        
        
        public:
        
        
        // use with quad2
        // here we defer the triangulation so that one rings are done on the quad mesh
        explicit rigid_demo (OpenGP::SurfaceMesh mesh) : csc486a::window_base(std::move(mesh), true) {
            
            
            // copy the original to displaced
            OpenGP::SurfaceMesh original = OpenGP::SurfaceMesh(mesh_);

            
            // define handle
            OpenGP::SurfaceMesh::Vertex_property<bool> is_handle = mesh_.add_vertex_property<bool>("v:is_handle", false);
            is_handle[OpenGP::SurfaceMesh::Vertex(0)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(35)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(19)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(47)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(4)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(48)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(20)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(36)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(3)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(27)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(79)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(63)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(78)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(28)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(70)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(51)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(69)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(26)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(30)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(74)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(56)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(66)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(37)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(77)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(60)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(67)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(34)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(1)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(31)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(15)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(43)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(5)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(41)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(13)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(29)] = true;
            is_handle[OpenGP::SurfaceMesh::Vertex(2)] = true;
            
            
            // closeness on handles
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(0),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(35),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(19),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(47),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(4),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(48),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(20),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(36),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(3),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(27),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(79),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(63),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(78),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(28),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(70),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(51),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(69),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(26),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(30),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(74),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(56),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(66),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(37),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(77),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(60),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(67),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(34),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(1),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(31),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(15),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(43),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(5),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(41),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(13),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(29),1.0f);
            ccs_.emplace_back(mesh_,OpenGP::SurfaceMesh::Vertex(2),1.0f);
            
            
            //loop over onerings and add constraint for each one. weight this less than holding the handles
            unsigned int curr = 0;
            std::vector<OpenGP::SurfaceMesh::Vertex> onering;
            onering.reserve(10); // should be sufficient for quad and triangle
            for (auto && v : mesh.vertices()) {

                //if (is_handle[v]) continue;
                onering.clear();
                onering.push_back(v);

                for (auto && he : mesh.halfedges(v)) {
                    OpenGP::SurfaceMesh::Vertex v_or = mesh.to_vertex(he);
                    onering.push_back(v_or);
                }

                rcs_.emplace_back(mesh_, original, onering, 0.05f);
                add(rcs_.back());
                
                /*//progress report (for large meshes)
                if (curr % (mesh.n_vertices()/20) == 0) {
                    float prog = (curr * 100.0)/mesh.n_vertices();
                    std::cout << "Onering Progress: " << prog << std::endl;
                }
                curr++;*/
            }
            
            // add closeness constriants
            for (auto && cc : ccs_) add(cc);
            
            // now triangulate and add to scene
            add_mesh_to_scene();
            
        }
        
#define IT 5
        void key_callback (int key, int scancode, int action, int mods) {
            
            window_base::key_callback(key, scancode, action, mods);
            
            Eigen::Vector3f offset;
            
            if ((key==GLFW_KEY_UP) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,-0.1,0);
                move_handle(offset);
                for(int i = 0; i < IT; i++)s_();
                mesh_.update_face_normals();
                renderer_.init_data();
                
            }
            
            if ((key==GLFW_KEY_LEFT) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,0,-0.1);
                move_handle(offset);
                for(int i = 0; i < IT; i++)s_();
                mesh_.update_face_normals();
                renderer_.init_data();
            }
            
            if ((key==GLFW_KEY_DOWN) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,0.1,0);
                move_handle(offset);
                for(int i = 0; i < IT; i++)s_();
                mesh_.update_face_normals();
                renderer_.init_data();
            }
            
            if ((key==GLFW_KEY_RIGHT) && (action==GLFW_RELEASE)) {
                offset = Eigen::Vector3f(0,0,0.1);
                move_handle(offset);
                for(int i = 0; i < IT; i++)s_();
                mesh_.update_face_normals();
                renderer_.init_data();
            }
            
            
            
        }
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
    if (std::strcmp(name,"rigid")==0) return pointer(new rigid_demo(std::move(mesh)));
    if (std::strcmp(name,"sphere")==0) return pointer(new sphere_demo(std::move(mesh)));
    
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
