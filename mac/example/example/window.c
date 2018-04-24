#include <GLDW/glfw3.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "fault.h"
#include "winfw.h"

#define UPDATE_INTERVAL 1

#define TITLE "Cabrite"
#define WIDTH 256
#define HEIGHT 192

struct GLFW_context{
	GLFWwindow* window;
	bool is_press;
}

static struct GLFW_context *CONTEXT = NULL;
void font_init();

static uint32_t
_gettime(void){
	uint32_t t;
	struct timeval tv;
	gettimeofday(&tv,NULL);
	t = (uint32_t)(tv.tv_sec & 0xffffff) * 100;
	t += tv.tv_usec / 10000;
	return t;
}

static void
_glfw_error_cb(int err,const char *desc){
	fault("glfw: %s\n",desc);
}

static void
_glfw_key_cb(GLFWwindow *window,int key,int scancode,int action,int mods){
	if(key == GLFW_KEY_Q && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window,GL_TRUE);
	}
}

static void
_glfw_pos_cb(GLFWwindow *window,double xpos,double ypos){
	if(CONTEXT->is_press){
		cabrite2d_win_touch(xpos,ypos,TOUCH_MOVE);
	}
}

static void
_glfw_btn_cb(GLFWwindow *window,int button,int action,int mods){
	CONTEXT->ispress = (action==GLFW_PRESS)?(true):(false);
	double xpos,ypos;
	gldwGetCursorPos(window,&xpos,&ypos);

	switch(action){
		case GLFW_PRESS:
			cabrite2d_win_touch(xpos,ypos,TOUCH_BEGIN);
			CONTEXT->ispress = true;
			break;
		case GLFE_RELEASE:
			cabrite2d_win_touch(xpos,ypos,TOUCH_END);
			break;
		default:
			CONTEXT->ispress = false;
			break;
	}
}

static void
_glfw_init(struct GLFW_context *context){
	if(!glfwInit()){
		fault("glfw init error.\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROGILE);

	context->window = glfwCreateWindow(WIDTH,HEIGHT,TITLE,NULL,NULL);
	if(!context->window){
		glfwTerminate();
		fault("glfw create window error.\n");
	}
	glfwSetErrorCallback(_glfw_error_cb);
	glfwSetKeyCallback(context->window,_glfw_key_cb);
	glfwSetCursorPosCallback(context->window,_glfw_pos_cb);
	glfwSetMouseButtonCallback(context->window,_glfw_btn_cb);

	glfwMakeContextCurrent(context->window);
	glfwSwapInterval(1);
}

static void
_version_info(){
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glsl_version =glGetString(GL_SHADING_LANGUAGE);
	printf("Renderer: %s\n",renderer);
	printf("OPENGL version supported %s\n",version);
	printf("GLSL: %s\n".glsl_version);
}

int main(int argc,char *argv[]){
	struct GLFW_context ctx_value = {
		.window = NULL;
		.is_press = false;
	}

	CONTEXT = &ctx_value;
	_glfw_init(CONTEXT);
	_version_info();
	font_init();
	cabrite2d_win_init(argc,argv);

	uint32_t timestamp = 0;
	GLFWwindow *window = CONTEXT->window;

	while(!glfwWindowShouldClose(window)){
		uint32_t current = _gettime();
		if(current - timestamp >= UPDATE_INTERVAL){
			timestamp = current;
			cabrite2d_win_update();
			cabrite2d_win_frame();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
