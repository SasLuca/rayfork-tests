#pragma once

#define SCREEN_WIDTH  (800)
#define SCREEN_HEIGHT (450)

typedef struct input_data input_data;
struct input_data
{
    float mouse_scroll_y;

    int one_down;
    int two_down;
    int three_down;

    int left_down;
    int left_pressed;

    int right_down;
    int right_pressed;
};

void on_init(void);
void on_frame(input_data);