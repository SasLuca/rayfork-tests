// Implementation ktx images in Rayfork

#include "rayfork.h"
#include "glad.h"
#include "sokol_app.h"
#include "malloc.h"

rf_context rf_ctx;
rf_renderer_memory_buffers  rf_mem;

const int screen_width = 800;
const int screen_height = 450;

rf_image image;
rf_texture2d texture;

void on_init(void)
{
    // Load opengl with glad
    gladLoadGL();

    // Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, screen_width, screen_height, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    const char* path = "../../../examples/assets/ktx_test.ktx";

    int size = RF_DEFAULT_IO.get_file_size_proc(path);
    void* buffer = malloc(size);

    RF_DEFAULT_IO.read_file_into_buffer_proc(path, buffer, size);

    image = rf_load_image_from_ktx(buffer, RF_DEFAULT_ALLOCATOR);
    texture = rf_load_texture_from_image(image);
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