//Implementation of the texture to imageexample from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;

rf_image fudesumi_raw;
rf_texture2d fudesumi;

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    rf_set_target_fps(60);

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    // Load RAW image data (512x512, 32bit RGBA, no file header)

    fudesumi_raw = rf_load_image_from_data_in_format("resources/fudesumi.raw", 384, 512, UNCOMPRESSED_R8G8B8A8, 0);
    Texture2D fudesumi = LoadTextureFromImage(fudesumiRaw);  // Upload CPU (RAM) image to GPU (VRAM)
    UnloadImage(fudesumiRaw);                                // Unload CPU (RAM) image data

    // Generate a checked texture by code
    int width = 960;
    int height = 480;

    // Dynamic memory allocation to store pixels data (Color type)
    Color *pixels = (Color *)malloc(width*height*sizeof(Color));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (((x/32+y/32)/1)%2 == 0) pixels[y*width + x] = ORANGE;
            else pixels[y*width + x] = GOLD;
        }
    }

    // Load pixels data into an image structure and create texture
    Image checkedIm = LoadImageEx(pixels, width, height);
    Texture2D checked = LoadTextureFromImage(checkedIm);
    UnloadImage(checkedIm);         // Unload CPU (RAM) image data

    // Dynamic memory must be freed after using it
    free(pixels);                   // Unload CPU (RAM) pixels data
}

void on_frame(const input_data input)
{
    // Update

    // Draw
    rf_begin();

        rf_clear(RF_RAYWHITE);



    rf_end();
}