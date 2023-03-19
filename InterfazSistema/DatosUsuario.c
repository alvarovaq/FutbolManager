#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "DatosUsuario.h"
#include "SistemaEquipos.h"
#include "iniciarPartido.h"
#include "finTemporada.h"
#include "../InterfazUsuario/InterfazGrafica.h"
#include "../InterfazUsuario/InterfazUsuario.h"
#include "../Online/VerUsuarios.h"
#include "../Online/PartidoRapido.h"
#include "../Ajustes/Ajustes.h"

int EstadoUsuario (char nombre[]) {

    /*Nombramos variables*/

    int estado;
    char contrasena[100];
    char arch[] = "BaseDatos/";
    char nom[100];
    char arch2[100];

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);
    strcpy(arch2,arch);

    archivo = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(archivo,"%s",contrasena);
    fscanf(archivo,"%d",&estado);

    /*Cerramos archivo*/

    fclose(archivo);

    /*Analizamos*/

    if (estado == 0) {

        /*Abrimos archivo*/

        FILE *ptr;

        ptr = fopen(arch2,"w");

        /*Imprimimos en archivo*/

        fprintf(ptr,"%s\n1\n",contrasena);

        /*Cerramos archivo*/

        fclose(ptr);
    }

    /*Devolvemos estado*/

    return estado;

}


void ImprimirHistorialUsuario (char nombre[]) {

    /*Nombramos variables*/

    int i;
    char nom[100];
    char arch[] = "BaseDatos/";
    char bas[100];
    int basura;
    int temporada;
    int temp;
    char equip[100];
    int posicion;
    int temporadasganadas;
    int cont;

    /*Inicializamos variables*/

    cont = 0;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(archivo,"%s",bas);
    fscanf(archivo,"%d",&basura);
    fscanf(archivo,"%d",&basura);
    fscanf(archivo,"%d",&temporada);
    fscanf(archivo,"%d",&basura);
    fscanf(archivo,"%d",&temporadasganadas);

    /*Cerramos archivo*/

    fclose(archivo);

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/historial.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*INTERFAZ USUARIO*/

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pagina();
    borrar_pause();

    /*Imprimimos titulo*/

    muestraPagina("H I S T O R I A L");

    /*Analizamos*/

    if (temporada == 1) {
        gotoxy(40,16);
        printf("Aun no ha jugado ninguna temporada");
    }
    else {

        /*Imprimimos cabecera*/

        gotoxy(25,10);
        printf("TEMPORADA");
        gotoxy(57,10);
        printf("EQUIPO");
        gotoxy(85,10);
        printf("POSICION");

        /*Leemos archivo e imprimimos*/

        for (i = 0; i < temporada - 1; i++) {

            if (i == 10) {

                /*Pause*/

                gotoxy(5,32);
                system("pause");

                /*Borramos pantallas*/

                borrar_pantalla_principal();
                borrar_pagina();
                borrar_pause();

                /*Imprimimos cabecera*/

                gotoxy(25,10);
                printf("TEMPORADA");
                gotoxy(57,10);
                printf("EQUIPO");
                gotoxy(85,10);
                printf("POSICION");

                cont = 0;
            }

            fscanf(ptr,"%d",&temp);
            fscanf(ptr,"%s",equip);
            fscanf(ptr,"%d",&posicion);

            gotoxy(25,cont+13);
            printf("Temporada %d",temp);
            gotoxy(57,cont+13);
            printf("%s",equip);
            gotoxy(88,cont+13);
            printf("%d",posicion);

            muestramensaje("Temporadas ganadas: ");

            /*Imprimir variable*/

            printf("%d",temporadasganadas);

            /*Modificamos variables*/

            cont++;

        }

    }

    /*Imprimimos mensaje*/

    muestramensaje("Temporadas ganadas: ");

    /*Imprimir variable*/

    printf("%d",temporadasganadas);

    /*Cerramos archivo*/

    fclose(ptr);

    /*Pause*/

    gotoxy(5,32);
    system("pause");

}


void sumarExperiencia (char nombre[],int sumaXp) {

    /*Nombrar variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    char contrasena[100];
    int estado;
    int equip;
    int temporada;
    int jornada;
    int temporadasganadas;
    int experiencia;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"r+");

    /*Leemos archivo*/

    fscanf(archivo,"%s",contrasena);
    fscanf(archivo,"%d",&estado);
    fscanf(archivo,"%d",&equip);
    fscanf(archivo,"%d",&temporada);
    fscanf(archivo,"%d",&jornada);
    fscanf(archivo,"%d",&temporadasganadas);
    fscanf(archivo,"%d",&experiencia);

    /*Recolocamos cursor*/

    rewind(archivo);

    /*Modificamos variable*/

    experiencia = experiencia + sumaXp;

    /*Imprimimos en archivo*/

    fprintf(archivo,"%s\n",contrasena);
    fprintf(archivo,"%d\n",estado);
    fprintf(archivo,"%d\n",equip);
    fprintf(archivo,"%d\n",temporada);
    fprintf(archivo,"%d\n",jornada);
    fprintf(archivo,"%d\n",temporadasganadas);
    fprintf(archivo,"%d\n",experiencia);

    /*Cerramos archivo*/

    fclose(archivo);

}


void imprimirExperiencia (char nombre[]) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    char contrasena[100];
    int estado;
    int equip;
    int temporada;
    int jornada;
    int temporadasganadas;
    int experiencia;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(archivo,"%s",contrasena);
    fscanf(archivo,"%d",&estado);
    fscanf(archivo,"%d",&equip);
    fscanf(archivo,"%d",&temporada);
    fscanf(archivo,"%d",&jornada);
    fscanf(archivo,"%d",&temporadasganadas);
    fscanf(archivo,"%d",&experiencia);

    /*Imprimimos variable*/

    gotoxy(99,10);
    printf("%d XP",experiencia);

    /*Cerramos archivo*/

    fclose(archivo);

}


