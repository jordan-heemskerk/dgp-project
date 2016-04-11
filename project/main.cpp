#include <csc486a/closeness_constraint.hpp>
#include <csc486a/scaling_constraint.hpp>
#include <csc486a/window_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <utility>


namespace {
    
    
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


static void main_impl (int argc, char ** argv) {
    
    if (argc!=2) {
        
        std::ostringstream ss;
        ss << "Expected 1 command line parameter, got " << (argc-1);
        throw std::runtime_error(ss.str());
        
    }
    
    OpenGP::SurfaceMesh mesh;
    if (!mesh.read(argv[1])) {
        
        std::ostringstream ss;
        ss << "Failed reading file " << argv[1];
        throw std::runtime_error(ss.str());
        
    }
    
    test_window win(std::move(mesh));
    if (win.run()!=0) throw std::runtime_error("Window reported error");
    
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
