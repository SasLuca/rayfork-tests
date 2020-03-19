//Implementation of the input example from raylib using rayfork
#include "rayfork.h"
#include "glad/glad.h"
#include "game.h"

rf_context rf_ctx;
rf_renderer_memory_buffers rf_mem;

const int screen_width = 800;
const int screen_height = 450;

int g_G = 400;
float g_player_jump_speed = 350.0f;
float g_player_hor_speed = 200.0f;

typedef struct s_player s_player;
struct s_player {
    rf_vec2 position;
    float speed;
    bool can_jump;
};

typedef struct s_env_item s_env_item;
struct s_env_item {
    rf_rec rect;
    int blocking;
    rf_color color;
};

void update_player(const input_data input, s_player *player, s_env_item *envItems, int env_items_length, float delta);

void update_camera_center(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height);
void update_camera_center_inside_map(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height);
void update_camera_center_smooth_follow(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height);
void update_camera_even_out_on_landing(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height);
void update_camera_player_bounds_push(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height);

s_player player = { 0 };
struct s_env_item env_items[] = {
    {{ 0, 0, 1000, 400 }, 0, RF_LIGHTGRAY },
    {{ 0, 400, 1000, 200 }, 1, RF_GRAY },
    {{ 300, 200, 400, 10 }, 1, RF_GRAY },
    {{ 250, 300, 100, 10 }, 1, RF_GRAY },
    {{ 650, 300, 100, 10 }, 1, RF_GRAY }
};
int env_items_length = sizeof(s_env_item) / sizeof(env_items[0]);
rf_camera2d camera = { 0 };

// Store pointers to the multiple update camera functions
void (*camera_updaters[])(rf_camera2d*, s_player *, struct s_env_item*, int, float, int, int) = {
        update_camera_center,
        update_camera_center_inside_map,
        update_camera_center_smooth_follow,
        update_camera_even_out_on_landing,
        update_camera_player_bounds_push
};

int camera_option = 0;
int camera_updaters_length = sizeof(camera_updaters) / sizeof(camera_updaters[0]);

char *cameraDescriptions[] = {
        "Follow player center",
        "Follow player center, but clamp to map edges",
        "Follow player center; smoothed",
        "Follow player center horizontally; updateplayer center vertically after landing",
        "Player push camera on getting too close to screen edge"
};

void on_init(void)
{
    //Load opengl with glad
    gladLoadGL();

    //Initialise rayfork and load the default font
    rf_init(&rf_ctx, &rf_mem, screen_width, screen_height, RF_DEFAULT_OPENGL_PROCS);
    rf_set_target_fps(60);
    rf_load_default_font(RF_DEFAULT_ALLOCATOR, RF_DEFAULT_ALLOCATOR);

    player.position = (rf_vec2){ 400, 280 };
    player.speed = 0;
    player.can_jump = false;

    camera.target = player.position;
    camera.offset = (rf_vec2){ screen_width / 2, screen_height / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}



void on_frame(const input_data input)
{
    //Update
    // @Note: not working as expected atm
    float delta_time = rf_get_frame_time();

    update_player(input, &player, env_items, env_items_length, delta_time);

//    camera.zoom += ((float)GetMouseWheelMove()*0.05f);
    if (input.up_pressed) camera.zoom += 0.01f;
    else if (input.down_pressed) camera.zoom -= 0.01f;

    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

    if (input.r_pressed)
    {
        camera.zoom = 1.0f;
        player.position = (rf_vec2){ 400, 280 };
    }

    if (input.c_pressed) camera_option = (camera_option + 1) % camera_updaters_length;

    // Call update camera function by its pointer
    camera_updaters[camera_option](&camera, &player, env_items, env_items_length, delta_time, screen_width, screen_height);

    //Render
    rf_begin();

        rf_clear(RF_RAYWHITE);

        rf_begin_2d(camera);

            for (int i = 0; i < env_items_length; i++) rf_draw_rectangle_rec(env_items[i].rect, env_items[i].color);

            rf_rec playerRect = { player.position.x - 20, player.position.y - 40, 40, 40 };
            rf_draw_rectangle_rec(playerRect, RF_RED);

        rf_end_2d();

        rf_draw_text("Controls:", 20, 20, 10, RF_BLACK);
        rf_draw_text("- Right/Left to move", 40, 40, 10, RF_DARKGRAY);
        rf_draw_text("- Space to jump", 40, 60, 10, RF_DARKGRAY);
        rf_draw_text("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, RF_DARKGRAY);
        rf_draw_text("- C to change camera mode", 40, 100, 10, RF_DARKGRAY);
        rf_draw_text("Current camera mode:", 20, 120, 10, RF_BLACK);
        rf_draw_text(cameraDescriptions[camera_option], 40, 140, 10, RF_DARKGRAY);

    rf_end();
}

void update_player(const input_data input, s_player *player, s_env_item *envItems, int env_items_length, float delta)
{
    if (input.left_pressed) player->position.x -= g_player_hor_speed * delta;
    if (input.right_pressed) player->position.x += g_player_hor_speed * delta;
    if (input.space_pressed && player->can_jump)
    {
        player->speed = -g_player_jump_speed;
        player->can_jump = false;
    }

    int hit_obstacle = 0;
    for (int i = 0; i < env_items_length; i++)
    {
        s_env_item *ei = envItems + i;
        rf_vec2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed*delta)
        {
            hit_obstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hit_obstacle)
    {
        player->position.y += player->speed * delta;
        player->speed += g_G * delta;
        player->can_jump = false;
    }
    else player->can_jump = true;
}

void update_camera_center(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height)
{
    camera->offset = (rf_vec2){ width / 2, height / 2 };
    camera->target = player->position;
}

void update_camera_center_inside_map(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (rf_vec2){ width / 2, height / 2 };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < env_items_length; i++)
    {
        s_env_item *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    rf_vec2 max = rf_get_world_to_screen2d((rf_vec2){ maxX, maxY }, *camera);
    rf_vec2 min = rf_get_world_to_screen2d((rf_vec2){ minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width/2);
    if (max.y < height) camera->offset.y = height - (max.y - height/2);
    if (min.x > 0) camera->offset.x = width/2 - min.x;
    if (min.y > 0) camera->offset.y = height/2 - min.y;
}

void update_camera_center_smooth_follow(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = (rf_vec2){ width/2, height/2 };
    rf_vec2 diff = rf_vec2_sub(player->position, camera->target);
    float length = rf_vec2_len(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = rf_vec2_add(camera->target, rf_vec2_scale(diff, speed*delta/length));
    }
}

void update_camera_even_out_on_landing(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera->offset = (rf_vec2){ width / 2, height / 2 };
    camera->target.x = player->position.x;

    if (eveningOut)
    {
        if (evenOutTarget > camera->target.y)
        {
            camera->target.y += evenOutSpeed * delta;

            if (camera->target.y > evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
        else
        {
            camera->target.y -= evenOutSpeed * delta;

            if (camera->target.y < evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
    }
    else
    {
        if (player->can_jump && (player->speed == 0) && (player->position.y != camera->target.y))
        {
            eveningOut = 1;
            evenOutTarget = player->position.y;
        }
    }
}

void update_camera_player_bounds_push(rf_camera2d *camera, s_player *player, s_env_item *envItems, int env_items_length, float delta, int width, int height)
{
    static rf_vec2 bbox = { 0.2f, 0.2f };

    rf_vec2 bboxWorldMin = rf_get_screen_to_world2d((rf_vec2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    rf_vec2 bboxWorldMax = rf_get_screen_to_world2d((rf_vec2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (rf_vec2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}