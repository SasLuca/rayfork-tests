#include "stdint.h"
#include "rayfork.h"

typedef struct game_data_t game_data_t;
struct game_data_t
{
    rf_context rf_ctx;
    rf_renderer_memory_buffers rf_mem;
    rf_default_font default_font_mem;

    int screen_width;
    int screen_height;

    int reload_count;

    void* (*alloc)(size_t size);
    void (*free)(void*);
};