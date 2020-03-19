//Implementation of the texture image generation example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

#define NUM_TEXTURES 7 // Currently we have 7 generation algorithms

rf_context   rf_ctx;
rf_renderer_memory_buffers    rf_mem;

rf_image vertical_gradient;
rf_image horizontal_gradient;
rf_image radial_gradient;
rf_image checked;
rf_image white_noise;
rf_image perlin_noise;
rf_image cellular;

rf_texture2d textures[NUM_TEXTURES] = { 0 };

int current_texture = 0;

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    rf_set_target_fps(60);

    vertical_gradient = rf_gen_image_gradient_v(SCREEN_WIDTH, SCREEN_HEIGHT, RF_RED, RF_BLUE, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);
    horizontal_gradient = rf_gen_image_gradient_h(SCREEN_WIDTH, SCREEN_HEIGHT, RF_RED, RF_BLUE, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);
    radial_gradient = rf_gen_image_gradient_radial(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, RF_WHITE, RF_BLACK, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);
    checked = rf_gen_image_checked(SCREEN_WIDTH, SCREEN_HEIGHT, 32, 32, RF_RED, RF_BLUE, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);
    white_noise = rf_gen_image_white_noise(SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);
    perlin_noise = rf_gen_image_perlin_noise(SCREEN_WIDTH, SCREEN_HEIGHT, 50, 50, 4.0f, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);
    cellular = rf_gen_image_cellular(SCREEN_WIDTH, SCREEN_HEIGHT, 32, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    textures[0] = rf_load_texture_from_image(vertical_gradient);
    textures[1] = rf_load_texture_from_image(horizontal_gradient);
    textures[2] = rf_load_texture_from_image(radial_gradient);
    textures[3] = rf_load_texture_from_image(checked);
    textures[4] = rf_load_texture_from_image(white_noise);
    textures[5] = rf_load_texture_from_image(perlin_noise);
    textures[6] = rf_load_texture_from_image(cellular);

    rf_unload_image(vertical_gradient);
    rf_unload_image(horizontal_gradient);
    rf_unload_image(radial_gradient);
    rf_unload_image(checked);
    rf_unload_image(white_noise);
    rf_unload_image(perlin_noise);
    rf_unload_image(cellular);
}

void on_frame(const input_data input)
{
    // Update
    if (input.mouse_left_down || input.right_down)
    {
        current_texture = (current_texture + 1) % NUM_TEXTURES; // Cycle between the textures
    }

    // Draw
    rf_begin();

    rf_clear(RF_RAYWHITE);

    rf_draw_texture(textures[current_texture], (rf_vec2){ 0, 0 }, 0.0f, 1.0f, RF_WHITE);

    rf_draw_rectangle(30, 400, 325, 30, rf_fade(RF_SKYBLUE, 0.5f));
    rf_draw_rectangle_outline((rf_rec){ 30, 400, 325, 30 }, 1.0f, rf_fade(RF_WHITE, 0.5f));
    rf_draw_text("MOUSE LEFT BUTTON to CYCLE PROCEDURAL TEXTURES", 40, 410, 10, RF_WHITE);

    switch(current_texture)
    {
        case 0: rf_draw_text("VERTICAL GRADIENT", 560, 10, 20, RF_RAYWHITE); break;
        case 1: rf_draw_text("HORIZONTAL GRADIENT", 540, 10, 20, RF_RAYWHITE); break;
        case 2: rf_draw_text("RADIAL GRADIENT", 580, 10, 20, RF_LIGHTGRAY); break;
        case 3: rf_draw_text("CHECKED", 680, 10, 20, RF_RAYWHITE); break;
        case 4: rf_draw_text("WHITE NOISE", 640, 10, 20, RF_RED); break;
        case 5: rf_draw_text("PERLIN NOISE", 630, 10, 20, RF_RAYWHITE); break;
        case 6: rf_draw_text("CELLULAR", 670, 10, 20, RF_RAYWHITE); break;
        default: break;
    }

    rf_end();
}