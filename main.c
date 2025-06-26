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
    //tamaño del archivo
    fseek(f, 0, SEEK_END);
    int size_file=ftell(f);
    fseek(f, 0, SEEK_SET);

    uint32_t cant;
   /* do
    {
        fread(&cant, sizeof(uint32_t), 1, f);
        printf("Cantidad de pistas: %u", cant);
        header=malloc(sizeof(struct encabezado)*cant);
        fread(header, sizeof(struct encabezado), cant, f);
        data=malloc(sizeof(struct muestras)*cant);
        for (uint32_t i = 0; i < cant; i++)
        {
            fread(data[i].sound_data, sizeof(float), header[i].sample_count, f);
        }
    } while (ftell(f)<size_file);*/
     fread(&cant, sizeof(uint32_t), 1, f);
        printf("Cantidad de pistas: %u", cant);
        header=malloc(sizeof(struct encabezado)*cant);
        fread(header, sizeof(struct encabezado), cant, f);
        data=malloc(sizeof(struct muestras)*cant);
        for (uint32_t i = 0; i < cant; i++)
        {
            data[i].sound_data=malloc(sizeof(float)*header[i].sample_count);
            fread(data[i].sound_data, sizeof(float), header[i].sample_count, f);
        }
    play_audio(header[0].sample_rate, header[0].sample_count,data[0].sound_data);
    for (uint32_t i = 0; i < cant; i++)
    {
        free(data[i].sound_data);
    }
    free(data);
    free(header);
    fclose(f);
    return 0;
}