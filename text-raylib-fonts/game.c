//Implementation of the raylib fonts example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

#define MAX_FONTS (8)

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;
rf_default_font_buffers     default_font_buffers;

rf_font fonts[MAX_FONTS] = { 0 };
rf_vec2 positions[MAX_FONTS] = { 0 };
rf_color colors[MAX_FONTS] = { RF_MAROON, RF_ORANGE, RF_DARKGREEN, RF_DARKBLUE, RF_DARKPURPLE, RF_LIME, RF_GOLD, RF_RED };

const char *messages[MAX_FONTS] = { "ALAGARD FONT designed by Hewett Tsoi",
                                    "PIXELPLAY FONT designed by Aleksander Shevchuk",
                                    "MECHA FONT designed by Captain Falcon",
                                    "SETBACK FONT designed by Brian Kent (AEnigma)",
                                    "ROMULUS FONT designed by Hewett Tsoi",
                                    "PIXANTIQUA FONT designed by Gerhard Grossmann",
                                    "ALPHA_BETA FONT designed by Brian Kent (AEnigma)",
                                    "JUPITER_CRASH FONT designed by Brian Kent (AEnigma)" };

const int spacings[MAX_FONTS] = { 2, 4, 8, 4, 3, 4, 4, 1 };

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(&default_font_buffers);

    rf_set_target_fps(60);

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    // @Todo: Fix after loading fonts from png is implemented
    fonts[0] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/alagard.png");
    fonts[1] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/pixelplay.png");
    fonts[2] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/mecha.png");
    fonts[3] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/setback.png");
    fonts[4] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/romulus.png");
    fonts[5] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/pixantiqua.png");
    fonts[6] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/alpha_beta.png");
    fonts[7] = rf_load_png_font_file("../../../rayfork-examples/assets/fonts/jupiter_crash.png");



    for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = SCREEN_WIDTH/2 - rf_measure_text(fonts[i], messages[i], strlen(messages[i]), fonts[i].base_size * 2, spacings[i] *2).width / 2;
        positions[i].y = 60 + fonts[i].base_size + 45*i;
    }

    // Small Y position corrections
    positions[3].y += 8;
    positions[4].y += 2;
    positions[7].y -= 8;


}

void on_frame(const input_data input)
{
    // Update

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);

        rf_draw_text("free fonts included with raylib", 250, 20, 20, RF_DARKGRAY);
        rf_draw_line(220, 50, 590, 50, RF_DARKGRAY);

        for (int i = 0; i < MAX_FONTS; i++)
        {
            rf_draw_text_ex(fonts[i], messages[i], strlen(messages[i]), positions[i], fonts[i].base_size*2, spacings[i], colors[i]);
        }


    rf_end();
}