#pragma once 

#include "../../../filesystem/filesystem.h"

namespace Datatypes {
    struct Shader
    {   
        unsigned int ID;

        Flake::File vertex_shader_file;
        Flake::File fragment_shader_file;
        
        void load();
        void use();
    };
}