#include "lib.h"

void llenar_datos(struct encabezado **h, struct muestras **d, uint32_t *c, FILE *f)
{
    //tamaño del archivo
    fseek(f, 0, SEEK_END);
    int size_file=ftell(f);
    fseek(f, 0, SEEK_SET);

    //Datos del archivo guardados
    do
    {
        fread(c, sizeof(uint32_t), 1, f);
        printf("Cantidad de pistas: %u", *c);
        *h = malloc(sizeof(struct encabezado) * (*c));
        fread(*h, sizeof(struct encabezado), (*c), f);
        *d = malloc(sizeof(struct muestras) * (*c));
        for (uint32_t i = 0; i < (*c); i++)
        {
            (*d)[i].sound_data = malloc(sizeof(float) * (*h)[i].sample_count);
            fread((*d)[i].sound_data, sizeof(float), (*h)[i].sample_count, f);
        }
    } while (ftell(f) < size_file);
}