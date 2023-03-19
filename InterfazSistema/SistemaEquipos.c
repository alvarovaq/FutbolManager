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

void muestraEquipos () {

    /*Nombramos variables*/

    char equipo[100];
    int ofensivo;
    int medio;
    int defensivo;
    int i;

    /*Imprimimos enumeracion*/

    gotoxy(10,13);
    printf("1.");
    gotoxy(10,14);
    printf("2.");
    gotoxy(10,15);
    printf("3.");
    gotoxy(10,16);
    printf("4.");
    gotoxy(10,17);
    printf("5.");
    gotoxy(10,18);
    printf("6.");
    gotoxy(10,19);
    printf("7.");
    gotoxy(10,20);
    printf("8.");
    gotoxy(10,21);
    printf("9.");
    gotoxy(10,22);
    printf("10.");

    /*Imprimimos cabecera de la tabla*/

    gotoxy(30,10);
    printf("EQUIPO");
    gotoxy(60,10);
    printf("DEFENSIVO");
    gotoxy(77,10);
    printf("MEDIO");
    gotoxy(90,10);
    printf("OFENSIVO");

    /*Abrimos archivo*/

    FILE *archivo;

    archivo = fopen("BaseDatos/equipos.txt","rt");

    /*Leemos e imprimimos equipos*/

    for (i = 0; i < 10; i++) {
        fscanf(archivo,"%s",equipo);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);

        gotoxy(30,i + 13);
        printf("%s",equipo);
        gotoxy(60,i + 13);
        printf("%d",defensivo);
        gotoxy(77,i + 13);
        printf("%d",medio);
        gotoxy(90,i + 13);
        printf("%d",ofensivo);
    }

    /*Cerramos Archivo*/

    fclose(archivo);



}


void imprimirClasificacion (char nombre[],int equipo) {

    /*Nombramos variables*/

    int puntos[10];
    int goles[10];
    int equip[] = {1,2,3,4,5,6,7,8,9,10};
    int i,j;
    int aux;
    char team[100];
    int defensivo;
    int medio;
    int ofensivo;
    char nom[100];
    char arch[] = "BaseDatos/";

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pagina();
    borrar_pause();

    /*Imprimimos titulo*/

    muestraPagina("C L A S I F I C A C I O N");

    /*Imprimimos enumeracion*/

    SetColorTexto(7);

    gotoxy(10,13);
    printf("1.");
    gotoxy(10,14);
    printf("2.");
    gotoxy(10,15);
    printf("3.");

    //SetColorTexto(12);

    gotoxy(10,16);
    printf("4.");
    gotoxy(10,17);
    printf("5.");
    gotoxy(10,18);
    printf("6.");
    gotoxy(10,19);
    printf("7.");

    SetColorTexto(4);

    gotoxy(10,20);
    printf("8.");
    gotoxy(10,21);
    printf("9.");
    gotoxy(10,22);
    printf("10.");

    SetColorTexto(12);

    /*Imprimir cabecera de la tabla*/

    gotoxy(30,10);
    printf("EQUIPO");
    gotoxy(70,10);
    printf("GOLES");
    gotoxy(90,10);
    printf("PUNTOS");

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/estadisticas.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Leemos archivo y inicializamos los vectores*/

    for (i = 0; i < 10; i++) {
        fscanf(archivo,"%d",&puntos[i]);
        fscanf(archivo,"%d",&goles[i]);
    }

    /*Cerramos archivo*/

    fclose(archivo);

    /*Ordenar equipos por puntos y goles*/

    for (i = 0; i < 10; i++) {
        for (j = i + 1; j < 10; j++) {
            if (puntos[i] < puntos[j]) {
                aux = puntos[i];
                puntos[i] = puntos[j];
                puntos[j] = aux;

                aux = goles[i];
                goles[i] = goles[j];
                goles[j] = aux;

                aux = equip[i];
                equip[i] = equip[j];
                equip[j] = aux;
            }
            else if (puntos[i] == puntos[j]) {
                if (goles[i] < goles[j]) {
                    aux = puntos[i];
                    puntos[i] = puntos[j];
                    puntos[j] = aux;

                    aux = goles[i];
                    goles[i] = goles[j];
                    goles[j] = aux;

                    aux = equip[i];
                    equip[i] = equip[j];
                    equip[j] = aux;
                }
            }
        }
    }

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*Imprimimos resutados*/

    for (i = 0; i < 10; i++) {
        rewind(ptr);

        /*Leemos nombre de los equipos*/

        for (j = 0; j < equip[i]; j++) {
            fscanf(ptr,"%s",team);
            fscanf(ptr,"%d",&defensivo);
            fscanf(ptr,"%d",&medio);
            fscanf(ptr,"%d",&ofensivo);
        }

        /*Imprimimos nombre equipos, goles y puntos*/

        if (equipo == equip[i]) {
            SetColorTexto(11);

            gotoxy(30,i + 13);
            printf("%s",team);
            gotoxy(70,i + 13);
            printf("%d",goles[i]);
            gotoxy(90,i + 13);
            printf("%d",puntos[i]);

            SetColorTexto(12);
        }
        else {
            gotoxy(30,i + 13);
            printf("%s",team);
            gotoxy(70,i + 13);
            printf("%d",goles[i]);
            gotoxy(90,i + 13);
            printf("%d",puntos[i]);
        }

        gotoxy(5,32);

    }

    /*Cerramos archivo*/

    fclose(ptr);

    /*pause*/

    system("pause");
}


void imprimirCalendario (char nombre[],int equipo) {

    /*Nombramos variables*/

    int i,j,m;
    char bas[100]; /*Basura*/
    int basura; /*Basura*/
    int jornada;
    int local;
    int visitante;
    char team[100];
    char nom[100];
    char arch[] = "BaseDatos/";

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pagina();
    borrar_pause();

    /*Imprimimos titulo*/

    muestraPagina("P A R T I D O S");

    /*Imprimimos archivo*/

    FILE *usu;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    usu = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(usu,"%s",bas);
    fscanf(usu,"%d",&basura);
    fscanf(usu,"%d",&basura);
    fscanf(usu,"%d",&basura);
    fscanf(usu,"%d",&jornada); /*Lo que nos interesa*/

    /*Cerramos archivo*/

    fclose(usu);

    /*Abrimos archivo*/

    FILE *archivo;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Abrimos archivo*/

    FILE *ptr;

    ptr = fopen("BaseDatos/partidos.txt","rt");

    /*Imprimimos calendario*/

    for (i = 0; i < 9; i++) {

        /*Borramos pantallas*/

        borrar_pantalla_principal();
        borrar_pagina();
        borrar_pause();

        /*Imprimimos jornada*/

        if (jornada == i + 1) {
            SetColorTexto(10);

            gotoxy(57,13);
            printf("JORNADA %d",i + 1);

            SetColorTexto(12);
        }

        else {
            gotoxy(55,13);
            printf("JORNADA %d",i + 1);
        }

        /*Leemos e imprimos equipos*/

        for (j = 0; j < 5; j++) {

            /*Leemos equipos*/

            fscanf(ptr,"%d",&local);
            fscanf(ptr,"%d",&visitante);


            /*LOCAL*/

            /*Leemos nombre*/

            gotoxy(50,j+18);

            for (m = 0; m < local; m++) {
                fscanf(archivo,"%s",team);
                fscanf(archivo,"%d",&basura);
                fscanf(archivo,"%d",&basura);
                fscanf(archivo,"%d",&basura);
            }

            /*Imprimimos nombre*/

            if (equipo == local) {
                SetColorTexto(11);

                printf("%s",team);

                SetColorTexto(12);
            }
            else {
                printf("%s",team);
            }


            /*Imprimimos barra*/

            gotoxy(62,j+18);
            printf("-");

            /*Raton del archivo al inicio*/

            rewind(archivo);


            /*VISITANTE*/

            gotoxy(65,j+18);

            /*Leemos nombre*/

            for (m = 0; m < visitante; m++) {
                fscanf(archivo,"%s",team);
                fscanf(archivo,"%d",&basura);
                fscanf(archivo,"%d",&basura);
                fscanf(archivo,"%d",&basura);
            }

            /*Imprimimos nombre*/

            if (equipo == visitante) {
                SetColorTexto(11);

                printf("%s",team);

                SetColorTexto(12);
            }
            else {
                printf("%s",team);
            }

            /*Raton del archivo al inicio*/

            rewind(archivo);
        }

        gotoxy(5,32);
        system("pause");
    }

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);

}


void verResultados (char nombre[],int equipo) {

    /*Nombramos variables*/

    int i, j;
    int basura;
    char basu[100];
    int jornada;
    int jor;
    int local[5];
    int visitante[5];
    int gollocal[5];
    int golvisitante[5];
    char team[100];
    char nom[100];
    char arch[] = "BaseDatos/";

    /*Borrar pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("R E S U L T A D O S");

    /*Abrimos archivo*/

    FILE *usu;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    usu = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(usu,"%s",basu);
    fscanf(usu,"%d",&basura);
    fscanf(usu,"%d",&basura);
    fscanf(usu,"%d",&basura);
    fscanf(usu,"%d",&jornada);

    /*Cerramos archivo*/

    fclose(usu);

    /*Abrimos archivo*/

    FILE *archivo;

    archivo = fopen("BaseDatos/partidos.txt","rt");

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/resultados.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*Abrimos archivo*/

    FILE *arr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    arr = fopen(arch,"rt");

    /*Imprimimir calendario*/

    if (jornada != 1) {


         jor = jornada - 1;


        do {

            /*Borramos pantallas*/

            borrar_pantalla_principal();
            borrar_pause();
            borrar_pagina();

            /*Imprimimos jornada elegida*/

            gotoxy(61,12);
            printf("JORNADA %d",jor);

            /*Leemos equipos y goles*/

            for (i= 0; i < jor; i++) {
                    for (j = 0; j < 5; j++) {
                        fscanf(archivo,"%d",&local[j]);
                        fscanf(archivo,"%d",&visitante[j]);
                        fscanf(ptr,"%d",&gollocal[j]);
                        fscanf(ptr,"%d",&golvisitante[j]);
                    }
            }

            /*Recolocamos raton en los archivos*/

            rewind(archivo);
            rewind(ptr);

            for (i = 0; i < 5; i++) {


                /*Local*/

                /*Leemos nombre equipo*/

                for (j = 0; j < local[i]; j++) {
                    fscanf(arr,"%s",team);
                    fscanf(arr,"%d",&basura);
                    fscanf(arr,"%d",&basura);
                    fscanf(arr,"%d",&basura);
                    fscanf(arr,"%d",&basura);
                }

                /*Recolocamos raton en los archivos*/

                rewind(arr);

                /*Imprimos equipo*/

                if (equipo == local[i]) {
                    SetColorTexto(11);

                    gotoxy(45,i+16);
                    printf("%s",team);

                    SetColorTexto(12);
                }
                else {
                    gotoxy(45,i+16);
                    printf("%s",team);
                }

                /*Visitante*/

                /*Leemos nombre equipo*/

                for (j = 0; j < visitante[i]; j++) {
                    fscanf(arr,"%s",team);
                    fscanf(arr,"%d",&basura);
                    fscanf(arr,"%d",&basura);
                    fscanf(arr,"%d",&basura);
                    fscanf(arr,"%d",&basura);
                }

                /*Recolocamos raton en los archivos*/

                rewind(arr);

                /*Imprimimo equipos*/

                if (equipo == visitante[i]) {
                    SetColorTexto(11);

                    gotoxy(75,i+16);
                    printf("%s",team);

                    SetColorTexto(12);
                }
                else {
                    gotoxy(75,i+16);
                    printf("%s",team);
                }

                /*Goles*/

                gotoxy(60,i+16);
                printf("%d",gollocal[i]);

                gotoxy(65,i+16);
                printf("-");

                gotoxy(70,i+16);
                printf("%d",golvisitante[i]);
                }

                /*Preguntamos jornada*/

                do {
                    gotoxy(10,27);
                    printf("                                             ");
                    gotoxy(10,27);
                    printf("Introduce la jornada(0 para salir): ");
                    scanf("%d",&jor);
                } while (jor > jornada - 1);


        } while (jor != 0);


    }
    else {

        /*Borramos pantallas*/

        borrar_pantalla_principal();
        borrar_pause();
        borrar_pagina();

        /*Imprimimos mensaje*/

        gotoxy(48,20);
        printf("Aun no se ha jugado ningun partidos");

        /*Pause*/

        gotoxy(5,32);
        system("pause");
    }

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);
    fclose(arr);
}


int posicionEquipo (char nombre[],int equipo) {

    /*Nombramos variables*/

    int puntos[10];
    int goles[10];
    int equip[] = {1,2,3,4,5,6,7,8,9,10};
    int i,j;
    int aux;
    int posicion;
    char nom[100];
    char arch[] = "BaseDatos/";

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/estadisticas.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Inicializamos vectores*/

    for (i = 0; i < 10; i++) {
        fscanf(archivo,"%d",&puntos[i]);
        fscanf(archivo,"%d",&goles[i]);
    }

    /*Cerramos archivo*/

    fclose(archivo);

    /*Ordenamos equipos segun puntos y goles*/

    for (i = 0; i < 10; i++) {
        for (j = i + 1; j < 10; j++) {
            if (puntos[i] < puntos[j]) {
                aux = puntos[i];
                puntos[i] = puntos[j];
                puntos[j] = aux;

                aux = goles[i];
                goles[i] = goles[j];
                goles[j] = aux;

                aux = equip[i];
                equip[i] = equip[j];
                equip[j] = aux;
            }
            else if (puntos[i] == puntos[j]) {
                if (goles[i] < goles[j]) {
                    aux = puntos[i];
                    puntos[i] = puntos[j];
                    puntos[j] = aux;

                    aux = goles[i];
                    goles[i] = goles[j];
                    goles[j] = aux;

                    aux = equip[i];
                    equip[i] = equip[j];
                    equip[j] = aux;
                }
            }
        }
    }

    /*Calculamos posicion del equipo*/

    i = 0;

    while (equipo != equip[i]) {

        i++;

    }

    posicion = i + 1;

    /*Devolvemos la posicion*/

    return posicion;

}



void crearArchivoEquipos (char nombre[]) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    int i;
    char team[100];
    int defensivo;
    int medio;
    int ofensivo;

    /*Abrimos archivo equipos*/

    FILE *archivo;

    archivo = fopen("BaseDatos/equipos.txt","rt");

    /*Abrimos nuevo archivo*/

    FILE *ptr;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"wt");

    /*Abrimos archivo*/

    FILE *arr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/descenso.txt");
    strcat(arch,nom);

    arr = fopen(arch,"wt");

    /*Leemos e imprimimos variables*/

    for (i = 0; i < 10; i++) {
        fscanf(archivo,"%s",team);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);

        fprintf(ptr,"%s ",team);
        fprintf(ptr,"%d ",defensivo);
        fprintf(ptr,"%d ",medio);
        fprintf(ptr,"%d\n",ofensivo);
    }

    for (i = 0; i < 3; i++) {
        fscanf(archivo,"%s",team);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);

        fprintf(arr,"%s ",team);
        fprintf(arr,"%d ",defensivo);
        fprintf(arr,"%d ",medio);
        fprintf(arr,"%d\n",ofensivo);
    }

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);
    fclose(arr);



}
