//Implementation of the font spritefont example from raylib using rayfork

#include "game.h"
#include "rayfork.h"
#include "glad.h"

rf_context   rf_ctx;
rf_renderer_memory_buffers rf_mem;
rf_default_font    default_font_buffers;

const char msg_1[50] = " T HIS IS A custom SPRITE FONT...";
const char msg_2[50] = "...and this is ANOTHER CUSTOM font...";
const char msg_3[50] = "...and a THIRD one! GREAT! :D";

rf_font font_1;
rf_font font_2;
rf_font font_3;

rf_vec2 font_position_1;
rf_vec2 font_position_2;
rf_vec2 font_position_3;

rf_image img;
rf_texture2d texture;


void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, SCREEN_WIDTH, SCREEN_HEIGHT, RF_DEFAULT_OPENGL_PROCS);
    //rf_load_default_font(&default_font_buffers);
    rf_set_target_fps(60);

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    font_1 = rf_load_image_font_from_file("../../../rayfork-examples/assets/custom_mecha.png", RF_DEFAULT_KEY_COLOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);          // Font loading
    font_2 = rf_load_image_font_from_file("../../../rayfork-examples/assets/custom_alagard.png", RF_DEFAULT_KEY_COLOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);        // Font loading
    font_3 = rf_load_image_font_from_file("../../../rayfork-examples/assets/custom_jupiter_crash.png", RF_DEFAULT_KEY_COLOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR, RF_DEFAULT_IO);  // Font loading

    font_position_1 = (rf_vec2){ SCREEN_WIDTH/2 - rf_measure_text(font_1, msg_1, strlen(msg_1), font_1.base_size, -3).width/2, SCREEN_HEIGHT/2 - font_1.base_size/2 - 80 };
    font_position_2 = (rf_vec2){ SCREEN_WIDTH/2 - rf_measure_text(font_2, msg_2, strlen(msg_2), font_2.base_size, -2).width/2, SCREEN_HEIGHT/2 - font_2.base_size/2 };
    font_position_3 = (rf_vec2){ SCREEN_WIDTH/2 - rf_measure_text(font_3, msg_3, strlen(msg_3), font_3.base_size, 2).width/2, SCREEN_HEIGHT/2 - font_3.base_size/2 + 50 };

    rf_color* src = RF_ALLOC(RF_DEFAULT_ALLOCATOR, 8 * 8 * 4);
    img.width  = 8;
    img.height = 8;
    for (int y = 0; y < img.height; y++)
    {
        for (int x = 0; x < img.width - 1; x++)
        {
            src[y * img.width + x] = RF_BLUE;
        }
    }

    for (int y = 0; y < img.height; y++)
    {
        for (int x = img.width - 1; x < img.width; x++)
        {
            src[y * img.width + x] = RF_RED;
        }
    }
    img.format = RF_UNCOMPRESSED_R8G8B8A8;
    img.data = src;
    img.valid = true;

    texture = rf_load_texture_from_image(img);
}

void on_frame(const input_data input)
{
    // Draw
    rf_begin();

    rf_clear(RF_RAYWHITE);

//    rf_draw_texture_region(texture, (rf_rec) { 0, 0, 8, 8 }, (rf_rec) {0, 0, 8 * 20, 8 * 20 }, (rf_vec2){0}, 0.0f, RF_WHITE);

    //font_1.glyphs['T' - ' '].width = 18;
    rf_draw_text_ex(font_1, "Thor", 4, font_position_1, font_1.base_size * 3, -3, RF_WHITE);
//    rf_draw_text_ex(font_2, msg_2, strlen(msg_2), font_position_2, font_2.base_size, -2, RF_WHITE);
//    rf_draw_text_ex(font_3, msg_3, strlen(msg_3), font_position_3, font_3.base_size, 2, RF_WHITE);

    rf_end();
}