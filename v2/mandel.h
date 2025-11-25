#ifndef MANDEL_H
#define MANDEL_H

#include "image.h"

typedef struct
{
    double left;
    double bottom;
    double height;
    unsigned int max_iters;
} mandel_config;

typedef mandel_config *mandel_config_ptr;

extern void create_image(mandel_config_ptr mdl,
                         image_config_ptr img);

#endif