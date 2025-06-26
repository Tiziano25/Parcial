#include "lib.h"
#include "audio_player.h"

int main(int argc, char const *argv[])
{
    FILE *f=fopen("C:\\Users\\tizia\\Documents\\UTN 2025\\Informatica 2\\Primer cuatrimestre\\Parcial\\Examen - Archivos\\audio_list.raw", "rb");
    if (f==NULL)
    {
        printf("File error");
        return -1;
    }
    struct encabezado *header;
    struct muestras *data;
    uint32_t cant;
    llenar_datos(&header, &data, &cant, f);

    printf("Nombres de las canciones:\n");
    for (uint32_t i = 0; i < cant; i++)
    {
        printf("Cancion %u: %s\n", (i+1), header[i].sound_name);
    }
    

    for (uint32_t i = 0; i < cant; i++)
    {
        free(data[i].sound_data);
    }
    free(data);
    free(header);
    fclose(f);
    return 0;
}