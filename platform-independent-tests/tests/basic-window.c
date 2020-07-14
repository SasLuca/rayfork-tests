#include "rayfork.h"
#include "platform.h"

int screen_width  = 800;
int screen_height = 450;

rf_context ctx;
rf_render_batch batch;

extern void on_init(rf_gfx_backend_init_data* gfx_data)
{
    rf_init(&ctx, screen_width, screen_height, gfx_data);
    batch = rf_create_default_render_batch(RF_DEFAULT_ALLOCATOR);
    rf_set_active_render_batch(&batch);
}

extern void on_frame(const input_t* input)
{
    rf_begin();
    {
        rf_clear(RF_RAYWHITE);

        char*    text = "Congrats! You created your first window!";
        rf_sizef size = rf_measure_text(rf_get_default_font(), text, 20, 2);
        rf_vec2  pos  = rf_center_to_screen(size.width, size.height);
        rf_draw_text(text, pos.x, pos.y, 20, RF_BLACK);
    }
    rf_end();
}

extern void on_resize(int width, int height)
{
    screen_width  = width;
    screen_height = height;

    rf_set_viewport(screen_width, screen_height);
}