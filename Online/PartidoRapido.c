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


void gestionPartidoCPU (char nombre[]) {

    /*Nombrar variables*/

    int local;
    int visitante;
    int codigo;
    int mayor;
    int maxlocal;
    int maxvisitante;
    int gollocal;
    int golvisitante;

    /*Recogemos variable*/

    elegirEquipo(nombre,&local,&visitante);

    /*Recogemos codigo y mayor*/

    codigo = compararEquipos(nombre,local,visitante);
    mayor = equipoMejor(nombre,local,visitante);

    /*Analizamos y calculamos los golesmaximos*/

    if (codigo == 1) {
        maxlocal = 2;
        maxvisitante = 2;
    }
    else if (codigo == 2) {
        if (mayor == 1) {
            maxlocal = 2;
            maxvisitante = 1;
        }
        else {
            maxlocal = 1;
            maxvisitante = 2;
        }
    }
    else { /*Codigo == 3*/
        if (mayor == 1) {
            maxlocal = 3;
            maxvisitante = 1;
        }
        else {
            maxlocal = 1;
            maxvisitante = 3;
        }
    }

    /*Recogemos numero aleatorio*/

    srand(time(NULL));

    gollocal = rand()%(maxlocal + 1);
    golvisitante = rand()%(maxvisitante + 1);

    partidoEnDirectoPartidoRapido(nombre,local,local,visitante,gollocal,golvisitante);

}

void elegirEquipo (char nombre[],int *local,int *visitante) {

    /*Nombramos variables*/

    char letra;
    int contador;
    char team[100];
    int basura;
    int i;

    /*Inicializamos variables*/

    contador = 0;

    /*Abrimos archivo*/

    FILE *archivo;

    archivo = fopen("BaseDatos/equipos.txt","rt");

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("P A R T I D O   R A P I D O");

     /*Imprimimos mensaje*/

    gotoxy(30,17);
    printf("Local : ");

    gotoxy(65,17);
    printf("Visitante : ");

    muestramensaje("*Pulsa 'a' para cambiar y 'l' para seleccionar*");

    do {

        /*Borramos pantalla*/

        gotoxy(40,17);
        printf("                 ");

        /*Leemos archivo*/

        for (i = 0; i < (contador % 13) + 1; i++) {
            fscanf(archivo,"%s",team);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
        }

        /*Recolocamos cursor*/

        rewind(archivo);

        /*Imprimimos nombre del equipo*/

        SetColorTexto(11);

        gotoxy(40,17);
        printf("%s",team);

        SetColorTexto(12);

        /*Modificamos variable*/

        letra = getch();

        if (letra == 'a') {
            contador++;
        }

    } while (letra != 'l');

    /*Modificamos variables*/

    *local = (contador % 13) + 1;
    contador = 0;


    do {

        /*Borramos pantalla*/

        gotoxy(79,17);
        printf("                 ");

        /*Leemos archivo*/

        for (i = 0; i < (contador % 13) + 1; i++) {
            fscanf(archivo,"%s",team);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
        }

        /*Recolocamos cursor*/

        rewind(archivo);

        /*Imprimimos nombre del equipo*/

        SetColorTexto(7);

        gotoxy(79,17);
        printf("%s",team);

        SetColorTexto(12);

        /*Modificamos variable*/

        letra = getch();

        if (letra == 'a') {
            contador++;
        }

    } while (letra != 'l');

    /*Modificamos variables*/

    *visitante = (contador % 13) + 1;
    contador = 0;

    /*Cerramos archivo*/

    fclose(archivo);

    /*Pause*/

    gotoxy(5,32);
    system("pause");

}



void partidoEnDirectoPartidoRapido (char nombre[],int equipo,int local,int visitante,int gollocal,int golvisitante) {

    /*Nombramos variables*/

    char team1[100];
    char team2[100];
    int basura;
    int i;
    int tiempo;
    int contadorLocal;
    int contadorVisitante;
    int minutosLocal[gollocal - 1];
    int minutosVisitante[golvisitante - 1];
    int linea;
    int letra;
    int aux;

    /*Inicializamos variables*/

    aux = 0;
    linea = 16; /*Indica la linea donde debe ponerse el siguiente comentario*/
    tiempo = 0;
    contadorLocal = 0;
    contadorVisitante = 0;

    /*Recogemos numeros aleatorios*/

    srand(time(NULL));

    for (i = 0; i < gollocal; i++) {

        minutosLocal[i] = rand()%85;
    }
    for (i = 0; i < golvisitante; i++) {

        minutosVisitante[i] = rand()%85;
    }

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Abrimos archivo*/

    FILE *archivo;

    archivo = fopen("BaseDatos/equipos.txt","rt");

    /*Leemos archivo*/

    for (i = 0; i < local; i++) {
        fscanf(archivo,"%s",team1);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
    }

    /*Imprimimos variables*/

    gotoxy(61,20);
    printf("%s",team1);

    /*Recolocamos cursor del archivo*/

    rewind(archivo);

    /*Leemos archivo*/

    for (i = 0; i < visitante; i++) {
        fscanf(archivo,"%s",team2);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
    }

    /*Imprimimos variable*/

    gotoxy(101,20);
    printf("%s",team2);

    /*Imprimimos decorado*/

    gotoxy(83,20);
    printf("-");

    for (i = 0; i < 21; i++) {
        gotoxy(47,i +9);
        printf("%c",179);
    }

    SetColorTexto(15);
    gotoxy(65,28);
    printf("*Pulse 'a' para saltarse el partido.*");
    SetColorTexto(12);

    gotoxy(15,12);
    printf("C O M E N T A R I O S");
    gotoxy(15,13);
    printf("---------------------");

    /*Imprimimos comentario*/

    gotoxy(12,linea);
    printf("El partido acaba de comenzar.");
    linea++;

    do {

        if (kbhit() != 0) {

            /*Recogemos variable*/

            letra = getch();

            /*Analizamos*/

            if (letra == 'a') {
                aux = 1;
                tiempo = 90;
            }
        }

        /*Analizamos*/

        for (i = 0; i < gollocal; i++) {
            if (minutosLocal[i] > tiempo - 5 && minutosLocal[i] <= tiempo) {
                contadorLocal++;
                gotoxy(12,linea);
                printf("%s marca gol en el %d",team1,minutosLocal[i]);
                linea++;
            }
        }
        for (i = 0; i < golvisitante; i++) {
            if (minutosVisitante[i] > tiempo - 5 && minutosVisitante[i] <= tiempo) {
                contadorVisitante++;
                gotoxy(12,linea);
                printf("%s marca gol en el %d",team2,minutosVisitante[i]);
                linea++;
            }
        }

        /*Borramos tiempo*/

        gotoxy(60,10);
        for (i = 0; i < 45; i++) {
            printf(" ");
        }

        /*Imprimimos tiempo*/

        gotoxy(81,10);
        printf("%d:00",tiempo);

        /*Incrementamos tiempo*/

        tiempo += 5;

        /*Imprimimos variables*/

        SetColorTexto(11);
        gotoxy(79,20);
        printf("%d",contadorLocal);
        gotoxy(87,20);
        printf("%d",contadorVisitante);
        SetColorTexto(12);

        /*Analizamos*/

        if (tiempo == 50) {

            /*Imprimimos comentario*/

            gotoxy(12,linea);
            printf("Fin de la primera parte.");
            linea++;

            /*Borramos mensaje*/

            gotoxy(65,28);
            printf("                                       ");

            /*Pause*/

            gotoxy(5,32);
            system("pause");

            /*Imprimimos comentario*/

            gotoxy(12,linea);
            printf("Inicio de la segunda parte.");
            linea++;

            /*Borramos*/

            borrar_pause();

            SetColorTexto(15);

            /*Imprimimos mensaje*/

            gotoxy(65,28);
            printf("*Pulse 'a' para saltarse el partido.*");
            SetColorTexto(12);
        }

        /*Analizamos y paramos programa durante un tiempo*/

        if (aux == 0) {
            Sleep(1000);
        }

    } while (tiempo != 95 && aux == 0);

    /*Borramos mensaje*/

    gotoxy(65,28);
    printf("                                       ");

    /*Analizamos*/

    if (aux == 1) {
        SetColorTexto(11);
        gotoxy(79,20);
        printf("%d",gollocal);
        gotoxy(87,20);
        printf("%d",golvisitante);
        SetColorTexto(12);
    }

    /*Imprimimos comentarios*/

    gotoxy(12,linea);
    printf("Fin del partido.");
    linea++;
    if (gollocal > golvisitante) {
        gotoxy(12,linea);
        printf("El partido acaba con victoria del");
        linea++;
        gotoxy(12,linea);
        printf("%s.",team1);
        linea++;
    }
    else if (gollocal < golvisitante) {
        gotoxy(12,linea);
        printf("El partido acaba con victoria del");
        linea++;
        gotoxy(12,linea);
        printf("%s.",team2);
        linea++;
    }
    else {
        gotoxy(12,linea);
        printf("El partido acaba en empate.");
        linea++;
    }

    gotoxy(12,linea);
    printf("Resultado final:");
    linea++;
    gotoxy(12,linea);
    printf("%s: %d",team1,gollocal);
    linea++;
    gotoxy(12,linea);
    printf("%s: %d",team2,golvisitante);
    linea++;

    /*Cerramos archivo*/

    fclose(archivo);

    gotoxy(5,32);
    system("pause");

}
