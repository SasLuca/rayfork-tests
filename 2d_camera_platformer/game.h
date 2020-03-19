#pragma once

typedef struct input_data input_data;
struct input_data
{
    int up_pressed;
    int down_pressed;
    int left_pressed;
    int right_pressed;
    int a_pressed;
    int c_pressed;
    int s_pressed;
    int r_pressed;
    int space_pressed;
};

void on_init(void);
void on_frame(input_data);