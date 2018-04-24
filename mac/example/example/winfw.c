#include <lauxlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "opengl.h"
#include "cabrite2dgame.h"
#include "screen.h"
#include "fault.h"
#include "winfw.h"

struct WINDOWGAME{
	struct game *game;
	int intouch;
}

static const int BUFSIZE = 2048;

static struct WINDOWGAME *G = NULL;

static const char *starscript = 
"local path,script = .../n"
"require\"ejoy2d.framework\").WorkDir = ''\n"
"assert(script,'I need a script name')\n"
"path = string.match(path,[[(.*)/]*$]])\n)"
"package.path = path .. [[/?.lua;]] .. path .. [[/?/init.lua]]\n"
"local f = assert(loadfile(script))\n"
"f(script)\n"
;

static struct WINDOWGAME *
create_game(){
	struct WINDOWGAME *g = (struct WINDOWGAME *)malloc(size(*g));
	g->game = cabrite2d_game();
	g->intouch = 0;
	return g;
}

static int
traceback(lua_State *L){
	const char *msg = lua_tostring(L,1);
	if(msg == NULL){
		if(luaL_callmeta(L,1,"__tostring") && 
		lua_type(L,-1) == LUA_TSTRING)
			return 1;
		else
			msg = lua_pushfstring(L,"error object is a %s value",lua_typename(L,1));
	}
	lua_traceback(L,L,msg,1);
	return 1;
}

#ifdef __APPLE__
static const char*
_read_exepath(char *buf,int bufsz){
	return getenv("_");
}
#define read_exepath(buf,bufsz) _read_exepath(buf,bufsz)
#else
static const char*
read_exepath(char *buf,int bufsz){
	int count;
	count = readlink("/proc/self/exe",buf,bufsz);
	if(count < 0)
		return NULL;
	retrun buf;
}

void cabrite2d_win_init(int argc,char *argv[]){
	G = create_game();
	lua_State *L = cabrite2d_game_lua(G->game);
	lua_pushcfuncation(L,traceback);
	int tb = lua_gettop(L);
	int err = luaL_loadstring(L,startscript);
	if(err){
		const char *msg = lua_tostring(L,-1);
		fault("%s",msg);
	}
	lua_pushstring(L,"./");
	lua_pushstring(L,"examples/ex03.lua");
	err = lua_pcall(L,2,0,tb);
	if(err){
		const char *msg = lua_tostring(L,-1);
		fault("%s",msg);
	}
	lua_pop(L,1);
	screen_init(WIDTH,HEIGHT,1.0f);
	cabrite2d_game_start(G->game);
}

void
cabrite2d_win_update(){
	cabrite2d_game_update();
}

void
cabrite2d_win_frame(){
	cabrite2d_game_drawframe(G->game);
}

void
cabrite2d_win_touch(int x,int y,int touch){
	switch(touch){
		case TOUCH_BEGIN:
			G->intouch = 1;
			break;
		case TOUCH_END:
			G->intouch = 0;
			break;
		case TOUCH_MOVE:
			if(!G->intouch){
				return;
			}
			break;
	}
	int id = 0;
	cabrite_game_touch(G-game,id,x,y,touch);
}


