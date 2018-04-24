#ifndef CABRITE2D_OPENGL_H
#define CABRITE2D_OPENGL_H

#if defined( __APPLE__) && !defined(__MACOSX)

#define OPENGLES 2
#include <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#elif defined(__MACOSX)
#define OPENGLES 3
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>

#elif defined (linux) || defined(__linux) || defined(__linux__)

#define OPENGLES 2
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else
#define OPENGLES 0
#include <GL/glew.h>

#endif

#endif
