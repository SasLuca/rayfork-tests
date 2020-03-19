//Implementation of the texture image text example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;

rf_image parrots;
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
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    rf_set_target_fps(60);

    // TTF Font loading with custom generation parameters
    parrots = rf_load_image_from_file("../../../examples/assets/parrots.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO); // Load image in CPU memory (RAM)

    // Draw over image using custom font
    font = rf_load_font_from_file("../../../examples/assets/KAISG.ttf", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);

    const char* text = "[Parrots font drawing]";
    rf_image_draw_text_ex(&parrots,(rf_vec2){ 20.0f, 20.0f }, font, text, strlen(text), (float)font.base_size, 0.0f, RF_RED, RF_DEFAULT_ALLOCATOR);

    texture = rf_load_texture_from_image(parrots);  // Image converted to texture, uploaded to GPU memory (VRAM)

    rf_unload_image(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    position = (rf_vec2){ (float)(SCREEN_WIDTH / 2 - texture.width / 2), (float)(SCREEN_HEIGHT / 2 - texture.height / 2 - 20) };

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
            // Draw texture with text already drawn inside
            rf_draw_texture(texture, position, 0.0f, 1.0f, RF_WHITE);

            // Draw text directly using sprite font
            const char* text = "[Parrots font drawing]";
            rf_draw_text_ex(font, text, strlen(text), (rf_vec2){ position.x + 20, position.y + 20 + 280 }, (float)font.base_size, 0.0f, RF_WHITE);
        }
        else rf_draw_texture(font.texture, (rf_vec2){ SCREEN_WIDTH / 2 - font.texture.width / 2, 50 }, 0.0f, 1.0f, RF_BLACK);

        rf_draw_text("PRESS SPACE to SEE USED SPRITEFONT ", 290, 420, 10, RF_DARKGRAY);

    rf_end();
}