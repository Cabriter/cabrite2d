#ifndef cabrite2d_windows_fw_h
#define cabrite2d_windows_fw_h

#define WIDTH 256
#define HEIGHT 192

#define TOUCH_BEGIN 0
#define TOUCH_END 1
#define TOUCH_MOVE 2

void cabrite2d_win_init();
void cabrite2d_win_frame();
void cabrite2d_win_update();
voud cabrite2d_win_touch(int x,int y,int touch);

#endif
