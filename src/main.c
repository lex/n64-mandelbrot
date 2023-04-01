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
    controller_init();

    debug_init_usblog();
    console_set_debug(true);

    const size_t max_iterations = 256;

    float minX = -2.0f;
    float maxX = 1.0f;
    float minY = -1.5f;
    float maxY = 1.5f;

    float offsetX = 0.0f;
    float offsetY = 0.0f;

    float lerpX[resolution.width];
    float lerpY[resolution.height];

    while (1)
    {
        while (!(disp = display_lock()))
        {
        }

        graphics_fill_screen(disp, 0);

        // Update lerp values when offsets change
        for (size_t px = 0; px < resolution.width; ++px)
        {
            lerpX[px] = lerp(minX - offsetX, maxX - offsetX, (float)px / resolution.width);
        }
        for (size_t py = 0; py < resolution.height; ++py)
        {
            lerpY[py] = lerp(minY - offsetY, maxY - offsetY, (float)py / resolution.height);
        }

        for (size_t py = 0; py < resolution.height; ++py)
        {
            for (size_t px = 0; px < resolution.width; ++px)
            {
                float x0 = lerpX[px];
                float y0 = lerpY[py];

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

        controller_scan();
        struct controller_data keys = get_keys_down();

        if (keys.c[0].up)
        {
            minX += 0.1f;
            maxX -= 0.1f;
            minY += 0.1f;
            maxY -= 0.1f;
        }
        else if (keys.c[0].down)
        {
            minX -= 0.1f;
            maxX += 0.1f;
            minY -= 0.1f;
            maxY += 0.1f;
        }
        else if (keys.c[0].left)
        {
            offsetX += 0.1f;
        }
        else if (keys.c[0].right)
        {
            offsetX -= 0.1f;
        }

        return 0;
    }
}
