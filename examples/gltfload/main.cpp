#include "ow/io/gltf.h"
#include <memory>

using namespace ow;

int main(int argc, char** argv){
    if(argc != 2){
        std::cout << "Usage: " << argv[0] <<" <path>" << std::endl;
        return 1;
    }
    auto scene = io::GLTFLoader::load(std::string(argv[1]));
}