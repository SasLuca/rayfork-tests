//Implementation of the format text example from raylib using rayfork

#include <stdio.h>
#include "game.h"
#include "gfx/rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;
rf_default_font     default_font_buffers;

int score = 100020;
int hiscore = 200450;
int lives = 5;

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(&default_font_buffers);

    rf_set_target_fps(60);
}

void on_frame(const input_data input)
{
    // Update

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);

        char text[100];
        snprintf(text, 100, "Score: %08i", score);
        rf_draw_text(text, 200, 80, 20, RF_RED);

        snprintf(text, 100, "HiScore: %08i", hiscore);
        rf_draw_text(text, 200, 120, 20, RF_GREEN);

        snprintf(text, 100, "Lives: %02i", lives);
        rf_draw_text(text, 200, 160, 40, RF_BLUE);

        snprintf(text, 100, "Elapsed Time: %02.02f ms", rf_get_frame_time() * 1000);
        rf_draw_text(text, 200, 220, 20, RF_BLACK);

    rf_end();
}