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
    uint32_t cant;
    llenar_datos(&sounds, &cant, f);

    //Punto 1
    escribir_nombres(sounds, cant);
    
    //Punto 2
    elegir_cancion(sounds, play_audio);

    //Punto 3
    guardar_cancion(sounds);

    //Libacion de memoria
    for (uint32_t i = 0; i < cant; i++)
    {
        free(sounds.data[i].sound_data);
    }
    free(sounds.data);
    free(sounds.header);
    fclose(f);
    return 0;
}