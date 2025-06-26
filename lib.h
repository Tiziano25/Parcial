#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "audio_player.h"

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

struct musica
{
    struct encabezado *header;
    struct muestras *data;
};

void llenar_datos(struct musica *s, uint32_t *c, FILE *f);

void escribir_nombres(struct musica s, uint32_t c);

void elegir_cancion(struct musica s, int(*reproducir)(uint32_t, uint32_t, float *));

int guardar_cancion(struct musica s);