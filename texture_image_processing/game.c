//Implementation of the texture image loading example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;

#define NUM_PROCESSES    8

typedef enum {
    NONE = 0,
    COLOR_GRAYSCALE,
    COLOR_TINT,
    COLOR_INVERT,
    COLOR_CONTRAST,
    COLOR_BRIGHTNESS,
    FLIP_VERTICAL,
    FLIP_HORIZONTAL
} image_process;

static const char *process_text[] = {
    "NO PROCESSING",
    "COLOR GRAYSCALE",
    "COLOR TINT",
    "COLOR INVERT",
    "COLOR CONTRAST",
    "COLOR BRIGHTNESS",
    "FLIP VERTICAL",
    "FLIP HORIZONTAL"
};

rf_image image;
rf_texture2d texture;

int current_process = NONE;
bool texture_reload = false;

rf_rec select_recs[NUM_PROCESSES] = { 0 };

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    rf_set_target_fps(60);

    image = rf_load_image_from_file("../../../examples/assets/parrots.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);
    rf_image_format(&image, RF_UNCOMPRESSED_R8G8B8A8, RF_DEFAULT_ALLOCATOR);

    texture = rf_load_texture_from_image(image);

    for (int i = 0; i < NUM_PROCESSES; i++) select_recs[i] = (rf_rec){ 40.0f, (float)(50 + 32*i), 150.0f, 30.0f };
}

void on_frame(const input_data input)
{
    // Update
    if (input.down_down)
    {
        current_process++;
        if (current_process > 7) current_process = 0;
        texture_reload = true;
    }
    else if (input.up_down)
    {
        current_process--;
        if (current_process < 0) current_process = 7;
        texture_reload = true;
    }

    if (texture_reload)
    {
        rf_unload_image(image);                         // Unload current image data
        image = rf_load_image_from_file("../../../examples/assets/parrots.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO); // Re-load image data

        // NOTE: Image processing is a costly CPU process to be done every frame,
        // If image processing is required in a frame-basis, it should be done
        // with a texture and by shaders
        switch (current_process)
        {
            case COLOR_GRAYSCALE: rf_image_color_grayscale(&image, RF_DEFAULT_ALLOCATOR); break;
            case COLOR_TINT: rf_image_color_tint(&image, RF_GREEN, RF_DEFAULT_ALLOCATOR); break;
            case COLOR_INVERT: rf_image_color_invert(&image, RF_DEFAULT_ALLOCATOR); break;
            case COLOR_CONTRAST: rf_image_color_contrast(&image, -40, RF_DEFAULT_ALLOCATOR); break;
            case COLOR_BRIGHTNESS: rf_image_color_brightness(&image, -80, RF_DEFAULT_ALLOCATOR); break;
            case FLIP_VERTICAL: rf_image_flip_vertical(&image, RF_DEFAULT_ALLOCATOR); break;
            case FLIP_HORIZONTAL: rf_image_flip_horizontal(&image, RF_DEFAULT_ALLOCATOR); break;
            default: break;
        }

        rf_color *pixels = rf_get_image_pixel_data(image, RF_DEFAULT_ALLOCATOR);       // Get pixel data from image (RGBA 32bit)
        rf_update_texture(texture, pixels);                                                     // Update texture with new image data
        RF_FREE(RF_DEFAULT_ALLOCATOR, pixels);                                                  // Unload pixels data from RAM

        texture_reload = false;
    }

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);

        rf_draw_text("IMAGE PROCESSING:", 40, 30, 10, RF_DARKGRAY);

        // Draw rectangles
        for (int i = 0; i < NUM_PROCESSES; i++)
        {
            rf_draw_rectangle_rec(select_recs[i], (i == current_process) ? RF_SKYBLUE : RF_LIGHTGRAY);
            rf_draw_rectangle_outline((rf_rec){ (int)select_recs[i].x, (int) select_recs[i].y, (int) select_recs[i].width, (int) select_recs[i].height }, 1.0f, (i == current_process) ? RF_BLUE : RF_GRAY);

            rf_sizef text_size = rf_measure_text(rf_get_default_font(), process_text[i], strlen(process_text[i]), 10, 1.0f);
            rf_draw_text(process_text[i],
                    (int)(select_recs[i].x + select_recs[i].width / 2 - text_size.width / 2),
                    (int) select_recs[i].y + 11, 10,
                    (i == current_process) ? RF_DARKBLUE : RF_DARKGRAY);
        }

        rf_draw_texture(texture, (rf_vec2){ SCREEN_WIDTH - texture.width - 60, SCREEN_HEIGHT / 2 - texture.height / 2 }, 0.0f, 1.0f, RF_WHITE);
        rf_draw_rectangle_outline((rf_rec){ SCREEN_WIDTH - texture.width - 60, SCREEN_HEIGHT / 2 - texture.height / 2, texture.width, texture.height}, 1.0f, RF_BLACK);

    rf_end();
}