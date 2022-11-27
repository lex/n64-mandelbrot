#include <stdio.h>

#include <libdragon.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static resolution_t resolution = RESOLUTION_320x240;
static bitdepth_t bit_depth = DEPTH_32_BPP;

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

int main(void)
{
    static surface_t *disp = 0;
    display_init(resolution, bit_depth, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    debug_init_usblog();
    console_set_debug(true);

    const size_t max_iterations = 512;

    while (1)
    {
        while (!(disp = display_lock()))
        {
        }

        graphics_fill_screen(disp, 0);

        for (size_t py = 0; py < resolution.height; ++py)
        {
            for (size_t px = 0; px < resolution.width; ++px)
            {
                float x0 = lerp(-2.0f, 1.0f, (float)px / resolution.width);
                float y0 = lerp(-1.5f, 1.5f, (float)py / resolution.height);

                float x = 0.0f;
                float y = 0.0f;

                size_t iteration = 0;

                for (iteration = 0; iteration < max_iterations; ++iteration)
                {
                    float xx = x * x - y * y + x0;
                    y = 2.0f * x * y + y0;
                    x = xx;

                    if (x * x + y * y > 2.0f)
                    {
                        break;
                    }
                }

                const uint8_t color = MIN(iteration, 255);
                graphics_draw_pixel(disp, px, py, graphics_make_color(color, color, color, 255));
            }
        }

        display_show(disp);
    }

    return 0;
}