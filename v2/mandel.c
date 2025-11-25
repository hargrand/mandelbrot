#include "mandel.h"
#include "image.h"

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color_t;

unsigned int mandel(double x0, double y0, unsigned int max_iters)
{
    double x = 0.0;
    double y = 0.0;
    unsigned int i = 0;
    double xtemp;

    while (i < max_iters && (x * x + y * y) < 4.0)
    {
        xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
        ++i;
    }
    return i;
}

void gen_color(unsigned int val, color_t *color, unsigned int max_iters)
{
    if (val == max_iters)
    {
        color->red = 0;
        color->green = 0;
        color->blue = 0;
    }
    else
    {
        color->red = val & 0xff;
        color->green = (val >> 8) & 0xff;
        color->blue = (val >> 16) & 0xff;
    }
}

void create_image(mandel_config_ptr mdl,
                  image_config_ptr img)
{
    color_t color;
    double scale = mdl->height / img->height;
    double view_top = mdl->bottom + mdl->height;

    for (unsigned int row = 0; row < img->height; row++)
    {
        png_bytep image_row = img->rows_ptr[row];
        double y = view_top - row * scale;
        for (unsigned int col = 0; col < img->width; col++)
        {
            double x = mdl->left + col * scale;
            unsigned int iters = mandel(x, y, mdl->max_iters);
            png_bytep px = &(image_row[col * 3]);
            gen_color(iters, &color, mdl->max_iters);
            px[0] = color.red;
            px[1] = color.green;
            px[2] = color.blue;
        }
    }
}
