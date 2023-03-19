#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "Ajustes.h"
#include "../Online/VerUsuarios.h"
#include "../Online/PartidoRapido.h"
#include "../InterfazSistema/DatosUsuario.h"
#include "../InterfazSistema/SistemaEquipos.h"
#include "../InterfazSistema/iniciarPartido.h"
#include "../InterfazSistema/finTemporada.h"
#include "../InterfazUsuario/InterfazGrafica.h"
#include "../InterfazUsuario/InterfazUsuario.h"

void gestionAjustes (char nombre[]) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    int estadoOnline;
    int estadoPartidos;
    int estadoDescensos;
    char letra;
    int EmpezarInicio;
    int cursor;
    int cursorH[4];
    char contrasena[100];

    /*Inicializar variables*/

    EmpezarInicio = 0;
    cursor = 0;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/ajustes.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"r+");

    /*Leemos archivo*/

    fscanf(archivo,"%d",&estadoOnline);
    fscanf(archivo,"%d",&estadoPartidos);
    fscanf(archivo,"%d",&estadoDescensos);

    /*Recolocamos cursor*/

    rewind(archivo);

    /*Inicializamos variables*/

    cursorH[0] = estadoOnline;
    cursorH[1] = estadoPartidos;
    cursorH[2] = estadoDescensos;
    cursorH[3] = 1;

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos Titulo*/

    muestraPagina("A J U S T E S");

    /*Imprimimos mensajes*/

    gotoxy(45,16);
    printf("Privacidad del usuario: ");
    gotoxy(45,18);
    printf("Ver partidos en directo: ");
    gotoxy(45,20);
    printf("Descensos en temporada: ");
    gotoxy(45,22);
    printf("Reiniciar cuenta: ");

    /*Imprimimos instrucciones*/

    gotoxy(6,9);

    printf("//a o d --> Cambiar Respuesta // w --> Subir // s --> Bajar // l --> Salir//");

    do {

        /*Cambiamos color*/

        SetColorTexto(11);

        /*Imprimimos respuestas*/

        /*Privacidad*/

        if (cursor % 4 == 0) {
            SetColorTexto(10);

            gotoxy(70,16);

            if (cursorH[0] % 2 == 0) {
                printf("PUBLICO");
            }
            else {
                printf("PRIVADO");
            }

            SetColorTexto(11);
        }
        else {

            gotoxy(70,16);

            if (cursorH[0] % 2 == 0) {
                printf("PUBLICO");
            }
            else {
                printf("PRIVADO");
            }
        }

        /*Ver partidos en directo*/

        if (cursor % 4 == 1) {
            SetColorTexto(10);

            gotoxy(70,18);

            if (cursorH[1] % 2 == 0) {
                printf("SI");
            }
            else {
                printf("NO");
            }

            SetColorTexto(11);
        }
        else {

            gotoxy(70,18);

            if (cursorH[1] % 2 == 0) {
                printf("SI");
            }
            else {
                printf("NO");
            }
        }

        /*Descensos en temporada*/

        if (cursor % 4 == 2) {
            SetColorTexto(10);

            gotoxy(70,20);

            if (cursorH[2] % 2 == 0) {
                printf("SI");
            }
            else {
                printf("NO");
            }

            SetColorTexto(11);
        }
        else {

            gotoxy(70,20);

            if (cursorH[2] % 2 == 0) {
                printf("SI");
            }
            else {
                printf("NO");
            }
        }

        /*Nueva partida*/

        if (cursor % 4 == 3) {
            SetColorTexto(10);

            gotoxy(70,22);

            if (cursorH[3] % 2 == 0) {
                printf("SI");

                SetColorTexto(12);

                muestramensaje("*Debes salir del programa y volver a entrar*");

            }
            else {
                printf("NO");

                gotoxy(10,27);
                printf("                                                    ");
            }

            SetColorTexto(11);
        }
        else {

            gotoxy(70,22);

            if (cursorH[3] % 2 == 0) {
                printf("SI");
            }
            else {
                printf("NO");
            }
        }


        /*Recogemos variables*/

        letra = getch();

        /*Recolocar cursor pantalla*/

        if (letra == 's') {
            cursor++;
        }
        else if (letra == 'w') {
            cursor--;
        }

        /*Cambiamos variables*/

        else if (letra == 'a' || letra == 'd') {

                cursorH[cursor % 4] = cursorH[cursor % 4] + 1;

        }

        /*Cambiamos color*/

        SetColorTexto(12);

    } while (letra != 'l');

    /*Analizamos y cambiamos valores de variables*/

    estadoOnline = cursorH[0] % 2;
    estadoPartidos = cursorH[1] % 2;
    estadoDescensos = cursorH[2] % 2;
    EmpezarInicio = cursorH[3] % 2;

    /*Imprimimos en el archivo*/

    fprintf(archivo,"%d\n",estadoOnline);
    fprintf(archivo,"%d\n",estadoPartidos);
    fprintf(archivo,"%d\n",estadoDescensos);

    /*Analizamos*/

    FILE *ptr;
    FILE *arr;
    FILE *resultadoArchivo;

    if (EmpezarInicio == 0) {

        /*Abrimos archivo*/

        sprintf(arch,"BaseDatos/");

        strcpy(nom,nombre);
        strcat(nom,".txt");
        strcat(arch,nom);

        ptr = fopen(arch,"rt");

        /*Leemos archivo*/

        fscanf(ptr,"%s",contrasena);

        /*Recolocamos cursor*/

        rewind(ptr);

        /*Cerramos archivo*/

        fclose(ptr);

        /*Abrimos archivo*/

        sprintf(arch,"BaseDatos/");

        strcpy(nom,nombre);
        strcat(nom,".txt");
        strcat(arch,nom);

        arr = fopen(arch,"wt");

        /*Imprimimos en archivo*/

        fprintf(arr,"%s\n0\n",contrasena);

        /*Cerramos archivo*/

        fclose(arr);

        /*Abrimos archivo*/

        sprintf(arch,"BaseDatos/");

        strcpy(nom,nombre);
        strcat(nom,"/resultados.txt");
        strcat(arch,nom);

        resultadoArchivo = fopen(arch,"wt");

        /*Cerramos archivo*/

        fclose(resultadoArchivo);

    }


    /*Cerramos archivo*/

    fclose(archivo);

}

void crearAjustes (char nombre[]) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/ajustes.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"wt");

    /*Imprimimos en archivo*/

    fprintf(archivo,"0\n0\n0\n");

    /*Publico,SiVerPartidosEnDirecto,ConDescenso*/

    /*Cerramos archivo*/

    fclose(archivo);

}
