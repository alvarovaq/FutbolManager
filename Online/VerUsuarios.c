#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "VerUsuarios.h"
#include "PartidoRapido.h"
#include "../InterfazSistema/DatosUsuario.h"
#include "../InterfazSistema/SistemaEquipos.h"
#include "../InterfazSistema/iniciarPartido.h"
#include "../InterfazSistema/finTemporada.h"
#include "../InterfazUsuario/InterfazGrafica.h"
#include "../InterfazUsuario/InterfazUsuario.h"
#include "../Ajustes/Ajustes.h"

void gestionVerUsuarios (char nombre[]) {

    /*Nombramos variables*/

    char nombreUsuario[100];

    /*Llamamos a funciones*/

    buscarUsuario(nombre,nombreUsuario);
    informeUsuario(nombre,nombreUsuario);

}

void buscarUsuario (char nombre[],char nombreUsuario[]) {

    /*Nombramos variables*/

    char nombreUsu[100];
    int aux;
    int aux2;
    char nom[100];
    char arch[] = "BaseDatos/";
    int estadoOnline;

    /*Inicializamos variables*/

    aux = 1;
    aux2 = 0;

    /*Abrimos archivo*/

    FILE *archivo;
    FILE *ptr;

    archivo = fopen("BaseDatos/usuarios.txt","rt");

    /*Borramos pantalla*/

    borrar_pagina();

    /*Mostramos titulo*/

    muestraPagina("V E R   U S U A R I O");

    SetColorTexto(7);

    do {

        /*Borramos pantallas*/

        borrar_pantalla_principal();
        borrar_pause();

        /*Analizamos*/

        if (aux != 1) {

            /*Mostramos mensaje*/

            muestramensaje("*El usuario no existe*");
        }

        /*Inicializamos variables*/

        aux = 0;

        /*Recogemos variable*/

        gotoxy(10,11);
        printf("BUSCAR: ");
        fflush(stdin);
        scanf("%s",nombreUsuario);

        /*Leemos archivo y verificamos existencia del usuario*/

        while (fscanf(archivo,"%s",nombreUsu) == 1) {

            if (strcmp(nombreUsuario,nombreUsu) == 0) {
                aux = 1;
            }
        }

        /*Recolocamos cursor*/

        rewind(archivo);

    } while (aux != 1);

     /*Abrimos archivo*/

    strcpy(nom,nombreUsuario);
    strcat(nom,"/ajustes.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(ptr,"%d",&estadoOnline);

    /*Cerramos archivo*/

    fclose(ptr);

    /*Analizamos*/

    if (estadoOnline != 0) {
        muestramensaje("*El usuario es Privado*");

        gotoxy(5,32);
        system("pause");

        buscarUsuario(nombre,nombreUsuario);
    }


    SetColorTexto(12);

    /*Cerramos archivo*/

    fclose(archivo);

}


void informeUsuario (char nombre[],char nombreUsuario[]) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    char bas[100];
    int basura;
    int equipoActual;
    int temporada;
    int temporadasganadas;
    int experiencia;
    char team[100];
    int i;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombreUsuario);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombreUsuario);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(archivo,"%s",bas);
    fscanf(archivo,"%d",&basura);
    fscanf(archivo,"%d",&equipoActual);
    fscanf(archivo,"%d",&temporada);
    fscanf(archivo,"%d",&basura);
    fscanf(archivo,"%d",&temporadasganadas);
    fscanf(archivo,"%d",&experiencia);

    /*Nombre del equipo*/

    for (i = 0;i < equipoActual; i++) {
        fscanf(ptr,"%s",team);
        fscanf(ptr,"%d",&basura);
        fscanf(ptr,"%d",&basura);
        fscanf(ptr,"%d",&basura);
    }

    /*Imprimimos variables*/

    gotoxy(50,14);
    printf("Nombre del usuario: %s",nombreUsuario);
    gotoxy(50,16);
    printf("Equipo actual: %s",team);
    gotoxy(50,18);
    printf("Temporada: %d",temporada);
    gotoxy(50,20);
    printf("Temporadas ganadas: %d",temporadasganadas);
    gotoxy(50,22);
    printf("Experiencia: %d Xp",experiencia);

    /*Cerramos archivo*/

    fclose(archivo);
    fclose(ptr);

    /*Pause*/

    gotoxy(5,32);
    system("pause");

    /*Imprimimos historial del usuario*/

    ImprimirHistorialUsuario(nombreUsuario);

}
