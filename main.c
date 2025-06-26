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

    //Punto 1
    printf("Nombres de las canciones:\n");
    for (int i = 0; i < cant; i++)
    {
        printf("Cancion %u: %s\n", (i+1), header[i].sound_name);
    }
    
    //Punto 2
    printf("\nEliga que cancion desea escuchar (El numero a elegir debe ser entre 1 y 4): ");
    int n;
    do
    {
        scanf("%d", &n);
    } while (n>4||n<1);
    play_audio(header[n-1].sample_rate, header[n-1].sample_count, data[n-1].sound_data);

    //Liberacion de memoria
    for (uint32_t i = 0; i < cant; i++)
    {
        free(data[i].sound_data);
    }
    free(data);
    free(header);
    fclose(f);
    return 0;
}