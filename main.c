#include "lib.h"
#include "audio_player.h"

int main(int argc, char const *argv[])
{
    FILE *f=fopen("audio_list.raw", "rb");
    if (f==NULL)
    {
        printf("File error");
        return -1;
    }
    
    struct musica sounds;
    llenar_datos(&sounds, f);

    //Punto 1
    escribir_nombres(sounds);
    
    //Punto 2
    elegir_cancion(sounds, play_audio);

    //Punto 3
    guardar_cancion(sounds);

    //Libacion de memoria
    for (uint32_t i = 0; i < sounds.cantidad; i++)
    {
        free(sounds.data[i].sound_data);
    }
    free(sounds.data);
    free(sounds.header);
    fclose(f);
    return 0;
}