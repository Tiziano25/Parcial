#include "lib.h"
#include "audio_player.h"

int main(int argc, char const *argv[])
{
    FILE *f1=fopen("C:\\Users\\tizia\\Documents\\UTN 2025\\Informatica 2\\Primer cuatrimestre\\Parcial\\Examen - Archivos\\audio_list.raw", "rb");
    if (f1==NULL)
    {
        printf("File error");
        return -1;
    }
    struct encabezado *header;
    struct muestras *data;
    uint32_t cant;
    llenar_datos(&header, &data, &cant, f1);

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

    //Punto 3
    FILE *f2=fopen("C:\\Users\\tizia\\Documents\\UTN 2025\\Informatica 2\\Primer cuatrimestre\\Parcial\\Programa\\sound.raw", "wb");
    printf("\nEliga que cancion desea guardar (El numero a elegir debe ser entre 1 y 4): ");
    do
    {
        scanf("%d", &n);
    } while (n>4||n<1);
    fwrite(data[n-1].sound_data, sizeof(float), header[n-1].sample_count, f2);

    //Libacion de memoria
    for (uint32_t i = 0; i < cant; i++)
    {
        free(data[i].sound_data);
    }
    free(data);
    free(header);
    fclose(f1);
    fclose(f2);
    return 0;
}