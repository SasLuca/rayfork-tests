//Implementation of the texture image text example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers rf_mem;
rf_default_font_buffers    default_font_buffers;

rf_font font;
rf_texture2d texture;
rf_vec2 position;

bool show_font = false;

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(&default_font_buffers);

    rf_set_target_fps(60);

    font = rf_load_ttf_font_from_file("../../../rayfork-examples/assets/KAISG.ttf", RF_DEFAULT_FONT_SIZE, RF_FONT_ANTI_ALIAS, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);

    texture = rf_load_texture_from_file("../../../rayfork-examples/assets/parrots.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);

    position = (rf_vec2) { (float)(SCREEN_WIDTH / 2 - texture.width / 2), (float)(SCREEN_HEIGHT / 2 - texture.height / 2 - 20) };

    show_font = false;
}

void on_frame(const input_data input)
{
    // Update
    if (input.space_pressed) show_font = true;
    else show_font = false;

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);

        if (!show_font)
        {
            rf_draw_texture(texture, position, 0.0f, 1.0f, RF_WHITE);

            const char* text = "[Parrots font drawing]";
            rf_draw_text_ex(font, text, strlen(text), (rf_vec2) { position.x + 20, position.y + 20 + 280 }, (float) font.base_size, 0, RF_WHITE);

            rf_draw_text("PRESS SPACE to SEE USED SPRITEFONT ", 290, 420, 10, RF_DARKGRAY);
        }
        else rf_draw_texture(font.texture, (rf_vec2) { SCREEN_WIDTH / 2 - font.texture.width / 2, 50 }, 0.0f, 1.0f, RF_BLACK);

    rf_end();
}