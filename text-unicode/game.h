#pragma once

#define SCREEN_WIDTH  (800)
#define SCREEN_HEIGHT (450)

typedef struct input_data input_data;
struct input_data
{
    int space_down;

    int mouse_left_pressed;
    int mouse_left_up;

    int mouse_x;
    int mouse_y;
};

void on_init(void);
void on_frame(input_data);