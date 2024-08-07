#ifndef OPENGL_POC_SRC_DEBUG_H_
#define OPENGL_POC_SRC_DEBUG_H_

#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>
#include "render.h"

void debug();
void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam);

extern const int ENABLE_DEBUG;

int debugMat4Print(mat4 mat);

#endif //OPENGL_POC_SRC_DEBUG_H_
