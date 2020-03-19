//Implementation of the input example from raylib using rayfork
#include <stdlib.h>
#include <time.h>
#include "rayfork.h"
#include "glad/glad.h"
#include "game.h"

rf_context rf_ctx;
rf_renderer_memory_buffers rf_mem;

const int screen_width = 800;
const int screen_height = 450;

const int max_buildings = 100;

rf_rec buildings[100] = { 0 };
rf_color buildColors[100] = { 0 };

rf_rec player = { 400, 280, 40, 40 };

int spacing = 0;

rf_camera2d camera = { 0 };

int get_random_value(int min, int max)
{
    return rand() % (max - min) + min;
}

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, screen_width, screen_height, RF_DEFAULT_OPENGL_PROCS);
    rf_set_target_fps(60);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    //Seed the rand() function
    srand(time(NULL));

    camera.target = (rf_vec2){ player.x + 20, player.y + 20 };
    camera.offset = (rf_vec2){ screen_width/2, screen_height/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    for (int i = 0; i < max_buildings; i++)
    {
        buildings[i].width = get_random_value(50, 100);
        buildings[i].height = get_random_value(100, 800);
        buildings[i].y = screen_height - 130 - buildings[i].height;
        buildings[i].x = -6000 + spacing;

        spacing += buildings[i].width;

        buildColors[i] = (rf_color){ get_random_value(200, 240), get_random_value(200, 240), get_random_value(200, 250), 255 };
    }


}



void on_frame(const input_data input)
{
    //Update

    // Player movement
    if (input.right_pressed) player.x += 2;
    else if (input.left_pressed) player.x -= 2;

    // Camera target follows player
    camera.target = (rf_vec2){ player.x + 20, player.y + 20 };

    // Camera rotation controls
    if (input.a_pressed) camera.rotation--;
    else if (input.s_pressed) camera.rotation++;

    // Limit camera rotation to 80 degrees (-40 to 40)
    if (camera.rotation > 40) camera.rotation = 40;
    else if (camera.rotation < -40) camera.rotation = -40;

    // Camera zoom controls
    // @Note: No idea how to implement scrolling atm - so up and down is used instead
//    camera.zoom += ((float)GetMouseWheelMove()*0.05f);
    if (input.up_pressed) camera.zoom += 0.01f;
    else if (input.down_pressed) camera.zoom -= 0.01f;

    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

    // Camera reset (zoom and rotation)
    if (input.r_pressed)
    {
        camera.zoom = 1.0f;
        camera.rotation = 0.0f;
    }

    //Render
    rf_begin();

    rf_clear(RF_RAYWHITE);

    rf_begin_2d(camera);

        rf_draw_rectangle(-6000, 320, 13000, 8000, RF_GRAY);

        for (int i = 0; i < max_buildings; i++) rf_draw_rectangle_rec(buildings[i], buildColors[i]);

        rf_draw_rectangle_rec(player, RF_RED);

        rf_draw_line(camera.target.x, -screen_height * 10, camera.target.x, screen_height * 10, RF_GREEN);
        rf_draw_line(-screen_width * 10, camera.target.y, screen_width * 10, camera.target.y, RF_GREEN);

    rf_end_2d();

    rf_draw_text("SCREEN AREA", 640, 10, 20, RF_RED);

    rf_draw_rectangle(0, 0, screen_width, 5, RF_RED);
    rf_draw_rectangle(0, 5, 5, screen_height - 10, RF_RED);
    rf_draw_rectangle(screen_width - 5, 5, 5, screen_height - 10, RF_RED);
    rf_draw_rectangle(0, screen_height - 5, screen_width, 5, RF_RED);

    rf_draw_rectangle( 10, 10, 250, 113, rf_fade(RF_SKYBLUE, 0.5f));
    rf_draw_rectangle_outline((rf_rec){ 10, 10, 250, 113 }, 1, RF_BLUE);

    rf_draw_text("Free 2d camera controls:", 20, 20, 10, RF_BLACK);
    rf_draw_text("- Right/Left to move Offset", 40, 40, 10, RF_DARKGRAY);
    rf_draw_text("- Mouse Wheel to Zoom in-out", 40, 60, 10, RF_DARKGRAY);
    rf_draw_text("- A / S to Rotate", 40, 80, 10, RF_DARKGRAY);
    rf_draw_text("- R to reset Zoom and Rotation", 40, 100, 10, RF_DARKGRAY);

    rf_end();
}