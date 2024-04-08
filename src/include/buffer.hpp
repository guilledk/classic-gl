#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct buffers {
    GLuint verts;
    GLuint indices;
    GLuint uvs;
};

class buffer {
public:
    GLuint buffer_id;
    GLenum type;

    buffer(GLenum type, const void* data, GLsizeiptr size, GLenum usage) : type(type) {
        glGenBuffers(1, &buffer_id);
        glBindBuffer(type, buffer_id);
        glBufferData(type, size, data, usage);
        glBindBuffer(type, 0);
    }

    void bind() {
        glBindBuffer(type, buffer_id);
    }

    void unbind() {
        glBindBuffer(type, 0);
    }

    ~buffer() {
        glDeleteBuffers(1, &buffer_id);
    }
};
