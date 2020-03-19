//Implementation of the texture image loading example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;

rf_image image;
rf_texture2d texture;

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    rf_set_target_fps(60);

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    image = rf_load_image_from_file("../../../examples/assets/raylib_logo.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);     // Loaded in CPU memory (RAM)
    texture = rf_load_texture_from_image(image);          // Image converted to texture, GPU memory (VRAM)

    rf_unload_image(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
}

void on_frame(const input_data input)
{
    // Update

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);

        rf_draw_texture(texture, (rf_vec2){ SCREEN_WIDTH / 2 - texture.width / 2, SCREEN_HEIGHT / 2 - texture.height / 2 }, 0.0f, 1.0f, RF_WHITE);

        rf_draw_text("this IS a texture loaded from an image!", 300, 370, 10, RF_GRAY);

    rf_end();
}