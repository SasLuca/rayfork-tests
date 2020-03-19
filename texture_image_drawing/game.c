//Implementation of the texture srcrec destrec example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;

rf_image cat;
rf_image parrots;

rf_font font;

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

    cat = rf_load_image_from_file("../../../examples/assets/cat.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);             // Load image in CPU memory (RAM)
    rf_image_crop(&cat, (rf_rec){ 100, 10, 280, 380 }, RF_DEFAULT_ALLOCATOR);      // Crop an image piece
    rf_image_flip_horizontal(&cat, RF_DEFAULT_ALLOCATOR);                              // Flip cropped image horizontally
    rf_image_resize(&cat, 150, 200, RF_DEFAULT_ALLOCATOR);                            // Resize flipped-cropped image

    parrots = rf_load_image_from_file("../../../examples/assets/parrots.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);     // Load image in CPU memory (RAM)

    // Draw one image over the other with a scaling of 1.5f
    rf_image_draw(&parrots, cat, (rf_rec){ 0, 0, cat.width, cat.height }, (rf_rec){ 30, 40, cat.width*1.5f, cat.height*1.5f }, RF_WHITE, RF_DEFAULT_ALLOCATOR);
    rf_image_crop(&parrots, (rf_rec){ 0, 50, parrots.width, parrots.height - 100 }, RF_DEFAULT_ALLOCATOR); // Crop resulting image

    rf_unload_image(cat);       // Unload image from RAM

    // Load custom font for frawing on image
    font = rf_load_font_from_file("../../../examples/assets/custom_jupiter_crash.png", RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);

    // Draw over image using custom font
    const char text[] = "PARROTS & CAT";
    rf_image_draw_text_ex(&parrots, (rf_vec2){ 300, 230 }, font, text, strlen(text), font.base_size, -2, RF_WHITE, RF_DEFAULT_ALLOCATOR);

    rf_unload_font(font); // Unload custom spritefont (already drawn used on image)

    texture = rf_load_texture_from_image(parrots);      // Image converted to texture, uploaded to GPU memory (VRAM)
    rf_unload_image(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
}

void on_frame(const input_data input)
{
    // Update

    // Draw
    rf_begin();

    rf_clear(RF_RAYWHITE);

    rf_draw_texture(texture, (rf_vec2){ SCREEN_WIDTH/2 - texture.width/2, SCREEN_HEIGHT/2 - texture.height/2 - 40 }, 0.0f, 1.0f, RF_WHITE);
    rf_draw_rectangle_outline((rf_rec){SCREEN_WIDTH/2 - texture.width/2, SCREEN_HEIGHT/2 - texture.height/2 - 40, texture.width, texture.height }, 1.0f, RF_DARKGRAY);

    rf_draw_text("We are drawing only one texture from various images composed!", 240, 350, 10, RF_DARKGRAY);
    rf_draw_text("Source images have been cropped, scaled, flipped and copied one over the other.", 190, 370, 10, RF_DARKGRAY);

    rf_end();
}