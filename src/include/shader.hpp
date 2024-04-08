#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "utils.hpp"


GLuint shader_load(GLenum type, const GLchar* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint compile_success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_success);
    if (!compile_success) {
        GLchar info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << info_log << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint shader_program_init(const GLchar* vs_source, const GLchar* fs_source) {
    GLuint vertex_shader = shader_load(GL_VERTEX_SHADER, vs_source);
    GLuint fragment_shader = shader_load(GL_FRAGMENT_SHADER, fs_source);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint link_success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &link_success);
    if (!link_success) {
        GLchar info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}


class shader {
public:
    GLuint program;
    std::string name;
    std::map<std::string, GLuint> attr;
    std::map<std::string, GLuint> unif;

    shader(
        const std::string& name,
        const std::string& vertex_path,
        const std::string& fragment_path,
        const std::vector<std::string>& attributes,
        const std::vector<std::string>& uniforms
    ) : name(name) {
        std::string vertex_code = read_file(vertex_path);
        std::string fragment_code = read_file(fragment_path);
        program = shader_program_init(
            vertex_code.c_str(), fragment_code.c_str());

        for (const auto& attr : attributes) {
            this->attr[attr] = glGetAttribLocation(program, attr.c_str());
        }
        for (const auto& unif : uniforms) {
            this->unif[unif] = glGetUniformLocation(program, unif.c_str());
        }
    }

    void bind() {
        glUseProgram(program);
    }

    void unbind() {
        glUseProgram(0);
    }
};
