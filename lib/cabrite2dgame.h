#ifndef CABRITE_2D_GAME_H
#define CABRITE_2D_GAME_H

#include <lua.h>

struct game{
	lua_State *L;
	float real_time;
	float logic_time;
};

struct game *cabrite2d_game();
lua_State *cabrite2d_lua_init();
void cabrite2d_game_exit(struct game *);
void cabrite2d_close_lua(struct game *);
lua_State *cabrite2d_game_lua(struct game *);
void cabrite2d_handle_error(lua_State *L,const char  err_type,const char *msg);
void cabrite2d_game_logicframe(int);
void cabrite2d_game_start(struct game *);
void cabrite2d_game_update(struct game *,float dt);
void cabrite2d_game_drawframe(struct game *);
int cabrite2d_game_touch(struct game *,int id,float x,float y,int status);;
void cabrite_game_gesture(struct game *,int type,double x1,double y1,double x2,double y2,int s);

void cabrite2d_game_message(struct game *G,int id_,const char *state,const char *data,lua_Number n);
void cabrite2d_game_pause(struct game *G);
void cabrite2d_game_resume(struct game *G);

void cabrite2d_call_lua(lua_State *L,int n,int r);
void cabrite2d_init(lua_State *L);

#endif
