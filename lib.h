#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct encabezado
{
    uint32_t sample_rate;
    uint32_t sample_count;
    char sound_name[64];
};

struct muestras
{
    float *sound_data;
};

void llenar_datos(struct encabezado **h, struct muestras **d, uint32_t *c, FILE *f);