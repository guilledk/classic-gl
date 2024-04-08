#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h> // Include GLEW to get OpenGL functions
#include <iostream> // For error logging

GLuint load_texture(const std::string& filepath) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load image using stb_image.h
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;
}

class texture {
public:
    GLuint tex_id;
    std::string name;
    std::string source;

    texture(
        const std::string& name,
        const std::string& source
    ) : name(name), source(source) {
        tex_id = load_texture(source);
    }

    void bind(int tex_core) {
        glActiveTexture(tex_core);
        glBindTexture(GL_TEXTURE_2D, tex_id);
    }
};
