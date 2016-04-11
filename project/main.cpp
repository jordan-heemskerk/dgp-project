#include <csc486a/scaling_constraint.hpp>
#include <csc486a/window_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <cstdlib>
#include <deque>
#include <stdexcept>
#include <utility>


namespace {
    
    
    class test_window : public csc486a::window_base {
        
        
        private:
        
        
            std::deque<csc486a::scaling_constraint> cs_;
        
        
        public:
        
        
            explicit test_window (OpenGP::SurfaceMesh mesh) : csc486a::window_base(std::move(mesh)) {
            
                for (auto && v : mesh_.vertices()) {
                    
                    cs_.emplace_back(mesh_,v,1.5f,1.0f);
                    add(cs_.back());
                    
                }
            
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
