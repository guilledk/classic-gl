#pragma once

#include <iostream>
#include <map>
#include <string>

#include "buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "utils.hpp"


std::map<std::string, buffers> init_buffers() {
    buffers quad_buffers;

    GLfloat vertices[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    buffer vert_buffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices), GL_STATIC_DRAW);
    quad_buffers.verts = vert_buffer.buffer_id;

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    buffer index_buffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), GL_STATIC_DRAW);
    quad_buffers.indices = index_buffer.buffer_id;

    GLfloat tex_coords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };

    buffer tex_coord_buffer(GL_ARRAY_BUFFER, tex_coords, sizeof(tex_coords), GL_STATIC_DRAW);
    quad_buffers.uvs = tex_coord_buffer.buffer_id;

    std::map<std::string, buffers> buffers_map;
    buffers_map["quad"] = quad_buffers;

    return buffers_map;
}

std::map<std::string, shader> init_shaders(const json& shader_manifest) {
    std::map<std::string, shader> shaders;

    for (const json& item : shader_manifest) {
        shader s(
            item["name"],
            item["vertex"],
            item["fragment"],
            item["attr"].get<std::vector<std::string>>(),
            item["unif"].get<std::vector<std::string>>()
        );
        shaders.emplace(std::make_pair(s.name, s));
    }

    return shaders;
}

std::map<std::string, texture> init_textures(const json& texture_manifest) {
    std::map<std::string, texture> textures;

    for (const json& item : texture_manifest) {
        texture t(
            item["name"],
            item["src"]
        );
        textures.emplace(std::make_pair(t.name, t));
    }

    return textures;
}
