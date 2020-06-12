// Implementation ktx images in Rayfork

#include "gfx/rayfork.h"
#include "glad.h"
#include "sokol_app.h"
#include "malloc.h"

rf_context rayfork;
rf_renderer_memory_buffers renderer_buffers;

const int screen_width = 800;
const int screen_height = 450;

rf_mipmaps_image image;
rf_texture2d texture;

void on_init(void)
{
    // Load opengl with glad
    gladLoadGL();

    // Initialise rayfork and load the default font
    rf_init(&rayfork, &renderer_buffers, screen_width, screen_height, RF_DEFAULT_OPENGL_PROCS);

    const char* path = RAYFORK_EXAMPLES_ASSETS_PATH "ktx_test.ktx";

    image = rf_load_ktx_image_from_file(path, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);
    texture = rf_load_texture_from_image_with_mipmaps(image);
}

void on_frame(void)
{
    rf_begin();
    {
        rf_clear(RF_RAYWHITE);

        rf_draw_texture(texture, (rf_vec2){ 0.0f, 0.0f }, 0.0f, 0.1f, RF_WHITE);
    }
    rf_end();
}