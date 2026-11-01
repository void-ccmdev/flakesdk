#include "shader.h"

#include <string>
#include <glad/glad.h>
#include "../../../output/output.h"

Flake::FileServer fs;
Flake::OutputServer os;

using namespace Datatypes;

void Shader::load() {
    //Read shader sources.
    std::string vert_shader_code = fs.readFile(vertex_shader_file);
    std::string frag_shader_code = fs.readFile(fragment_shader_file);

    //Create shaders + info logs in case of failing compilation.
    GLuint vertex_shader, fragment_shader;
    int success;
    char infoLog[512];

    const char* vert_shader_data = vert_shader_code.data(); 
    const char* frag_shader_data = frag_shader_code.data(); 

    //std::cout << vert_shader_data << std::endl;
    //std::cout << frag_shader_data << std::endl;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vert_shader_data, NULL);
    glCompileShader(vertex_shader); //Compiling shader
    //Checking for compile errors.
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::string err = "Failed to compile vertex shader! --Info-log >> ";
        os.printErr(err);
        os.print(infoLog);
    }

    fragment_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment_shader, 1, &frag_shader_data, NULL);
    glCompileShader(fragment_shader); //Compiling shader

    //Checking for compile errors.
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::string err = "Failed to compile fragment shader! --Info-log >> ";
        os.printErr(err);
        os.print(infoLog);
    }

    //Creating shader program and linking shaders to it.
    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glLinkProgram(ID);

    glGetShaderiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(ID, 512, NULL, infoLog);
        std::string err = "Failed to link shaders! --Info-log >> ";
        os.printErr(err);
        os.print(infoLog);
    }  

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
void Shader::use() {
    glUseProgram(ID);
}