//Implementation of the font spritefont example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;
rf_default_font_buffers     default_font_buffers;

const char msg_1[50] = "THIS IS A custom SPRITE FONT...";
const char msg_2[50] = "...and this is ANOTHER CUSTOM font...";
const char msg_3[50] = "...and a THIRD one! GREAT! :D";

rf_font font_1;
rf_font font_2;
rf_font font_3;

rf_vec2 font_position_1;
rf_vec2 font_position_2;
rf_vec2 font_position_3;

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(&default_font_buffers);

    rf_set_target_fps(60);

    // @Todo: Fix once loading font from png is implemented
    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    font_1 = rf_load_png_font_from_file("../../../rayfork-examples/assets/fonts/custom_mecha.png");          // Font loading
    font_2 = rf_load_png_font_from_file("../../../rayfork-examples/assets/fonts/custom_alagard.png");        // Font loading
    font_3 = rf_load_png_font_from_file("../../../rayfork-examples/assets/fonts/custom_jupiter_crash.png");  // Font loading

    font_position_1 = (rf_vec2){ SCREEN_WIDTH/2 - rf_measure_text(font_1, msg_1, strlen(msg_1), font_1.base_size, -3).width/2,
                      SCREEN_HEIGHT/2 - font_1.base_size/2 };

    font_position_2 = (rf_vec2){ SCREEN_WIDTH/2 - rf_measure_text(font_2, msg_2, strlen(msg_2), font_2.base_size, -2).width/2,
                      SCREEN_HEIGHT/2 - font_2.base_size/2 };

    font_position_3 = (rf_vec2){ SCREEN_WIDTH/2 - rf_measure_text(font_3, msg_3, strlen(msg_3), font_3.base_size, 2).width/2,
                              SCREEN_HEIGHT/2 - font_3.base_size/2 + 50 };
}

void on_frame(const input_data input)
{
    // Update

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);


    rf_draw_text_ex(font_1, msg_1, strlen(msg_1), font_position_1, font_1.base_size, -3, RF_WHITE);
    rf_draw_text_ex(font_2, msg_2, strlen(msg_2), font_position_2, font_2.base_size, -2, RF_WHITE);
    rf_draw_text_ex(font_3, msg_3, strlen(msg_3), font_position_3, font_3.base_size, 2, RF_WHITE);

    rf_end();
}