#pragma once

typedef struct input_data input_data;
struct input_data
{
    int left_pressed;
    int right_pressed;
    int a_pressed;
    int s_pressed;

    int r_pressed;
    int r_down;

    float mouse_scroll_y;
};

void on_init(void);
void on_frame(input_data);