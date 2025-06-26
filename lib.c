#include "lib.h"

void llenar_datos(struct musica *s, FILE *f)
{
    //tamaño del archivo
    fseek(f, 0, SEEK_END);
    int size_file=ftell(f);
    fseek(f, 0, SEEK_SET);

    //Datos del archivo guardados
    do
    {
        fread(&s->cantidad, sizeof(uint32_t), 1, f);
        s->header = malloc(sizeof(struct encabezado) * (*s).cantidad);
        fread(s->header, sizeof(struct encabezado), (*s).cantidad, f);
        s->data = malloc(sizeof(struct muestras) * (*s).cantidad);
        for (uint32_t i = 0; i < (*s).cantidad; i++)
        {
            s->data[i].sound_data = malloc(sizeof(float) * (*s).header[i].sample_count);
            fread(s->data[i].sound_data, sizeof(float), (*s).header[i].sample_count, f);
        }
    } while (ftell(f) < size_file);
}

void escribir_nombres(struct musica s)
{
    printf("Nombres de las canciones:\n");
    for (int i = 0; i < s.cantidad; i++)
    {
        printf("Cancion %u: %s\n", (i+1), s.header[i].sound_name);
    }
}

void elegir_cancion(struct musica s, int(*reproducir)(uint32_t, uint32_t, float *))
{
    printf("\nEliga que cancion desea escuchar (El numero a elegir debe ser entre 1 y %u): ", s.cantidad);
    int n;
    do
    {
        scanf("%d", &n);
    } while (n>s.cantidad||n<1);
    reproducir(s.header[n-1].sample_rate, s.header[n-1].sample_count, s.data[n-1].sound_data);
}

int guardar_cancion(struct musica s)
{
    FILE *a=fopen("sound.raw", "wb");
    if (a==NULL)
    {
        printf("File error");
        return -1;
    }

    printf("\nEliga que cancion desea guardar (El numero a elegir debe ser entre 1 y %u): ", s.cantidad);
    int n;
    do
    {
        scanf("%d", &n);
    } while (n>s.cantidad||n<1);
    fwrite(s.data[n-1].sound_data, sizeof(float), s.header[n-1].sample_count, a);
    fclose(a);
    
    return 0;
}