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

void gestionInicioPartido (char nombre[],int equipo) {

    mostrarEncuentros(nombre,equipo);
    resultado(nombre,equipo);


}


void mostrarEncuentros (char nombre[],int equipo) {

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

    /*Abrimos archivo*/

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
    fscanf(usu,"%d",&jornada);

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

    /*Mostramos encuentro de la jornada*/

    for (i = 0; i < 9; i++) {

        if (jornada == i + 1) {

            /*Borramos pantallas*/

            borrar_pantalla_principal();
            borrar_pagina();
            borrar_pause();

            /*Imprimimos jornada*/

            SetColorTexto(10);

            gotoxy(57,13);
            printf("JORNADA %d",i + 1);

            SetColorTexto(12);

        }

        /*Leemos e imprimimos equipos*/

        for (j = 0; j < 5; j++) {

            /*Leemos equipos*/

            fscanf(ptr,"%d",&local);
            fscanf(ptr,"%d",&visitante);

            if (jornada == i + 1) {

                    /*LOCAL*/

                    gotoxy(50,j+18);

                    /*Leemos nombre equipo*/

                    for (m = 0; m < local; m++) {
                        fscanf(archivo,"%s",team);
                        fscanf(archivo,"%d",&basura);
                        fscanf(archivo,"%d",&basura);
                        fscanf(archivo,"%d",&basura);
                    }

                    /*Imprimimos equipo*/

                    if (equipo == local) {
                        SetColorTexto(11);

                        printf("%s",team);

                        SetColorTexto(12);
                    }
                    else {
                        printf("%s",team);
                    }

                    /*Imprimimos raya*/

                    gotoxy(62,j+18);
                    printf("-");

                    /*Recolocamos cursor del archivo*/

                    rewind(archivo);

                    /*VISITANTE*/

                    /*Leemos nombre equipo*/

                    gotoxy(65,j+18);
                    for (m = 0; m < visitante; m++) {
                        fscanf(archivo,"%s",team);
                        fscanf(archivo,"%d",&basura);
                        fscanf(archivo,"%d",&basura);
                        fscanf(archivo,"%d",&basura);
                    }

                    /*Imprimimos equipo*/

                    if (equipo == visitante) {
                        SetColorTexto(11);

                        printf("%s",team);

                        SetColorTexto(12);
                    }
                    else {
                        printf("%s",team);
                    }

                    /*Recolocamos cursor del archivo*/

                    rewind(archivo);
                }
            }

    }

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);

}


int compararEquipos (char nombre[],int local,int visitante) {

    /*Nombramos variables*/

    int medialocal;
    int mediavisitante;
    int diferencia;
    int i;
    char basura[100];
    int defensivo;
    int medio;
    int ofensivo;
    int codigo;
    char nom[100];
    char arch[] = "BaseDatos/";

    /*Codigo 1 -> 2-2*/
    /*Codigo 2 -> 2-1*/
    /*Codigo 3 -> 3-1*/

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Leemos archivo*/

    for (i = 0; i < local; i++) {
        fscanf(archivo,"%s",basura);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);
    }

    /*Calculamos media*/

    medialocal = (defensivo + medio + ofensivo) / 3;

    /*Recolocamos cursor en archivo*/

    rewind(archivo);

    /*Leemos archivo*/

    for (i = 0; i < visitante; i++) {
        fscanf(archivo,"%s",basura);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);
    }

    /*Calculamos media*/

    mediavisitante = (defensivo + medio + ofensivo) / 3;

    /*Cerramos archivo*/

    fclose(archivo);

    /*Analizamos y calculamos diferencia*/

    if (mediavisitante < medialocal) {
        diferencia = medialocal - mediavisitante;
    }
    else if (mediavisitante > medialocal) {
        diferencia = mediavisitante - medialocal;
    }
    else {
        diferencia = 0;
    }

    /*Analizamos y calculamos codigo*/

    if (diferencia < 2) {
        codigo = 1;
    }
    else if (5 < diferencia && diferencia <= 2) {
        codigo = 2;
    }
    else {
        codigo = 3;
    }

    /*Devolvemos codigo*/

    return codigo;

}

int equipoMejor (char nombre[],int local, int visitante) {

    /*Nombramos variables*/

    char basura[100];
    int defensivo;
    int medio;
    int ofensivo;
    int medialocal;
    int mediavisitante;
    char nom[100];
    char arch[] = "BaseDatos/";
    int i;
    int mayor;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Leemos archivo*/

    for (i = 0; i < local; i++) {
        fscanf(archivo,"%s",basura);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);
    }

    /*Calculamos media*/

    medialocal = (defensivo + medio + ofensivo) / 3;

    /*Recolocamos cursor del archivo*/

    rewind(archivo);

    /*Leemos archivo*/

    for (i = 0; i < visitante; i++) {
        fscanf(archivo,"%s",basura);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);
    }

    /*Calculamos media*/

    mediavisitante = (defensivo + medio + ofensivo) / 3;

    /*Cerramos archivo*/

    fclose(archivo);

    /*Analizamos y calculamos mayor*/

    if (medialocal < mediavisitante) {
        mayor = 2;
    }
    else if (medialocal > mediavisitante) {
        mayor = 1;
    }
    else {
        mayor = 0;
    }

    /*Devolvemos mayor*/

    return mayor;

}


void resultado (char nombre[],int equipo) {

    /*Nombramos variables*/

    char basura[100];
    int basura2;
    int jornada;
    int i,j,k;
    int local;
    int visitante;
    int codigo;
    int mayor;
    int maxlocal;
    int maxvisitante;
    int gollocal;
    int golvisitante;
    int ganar;
    char arch[] = "BaseDatos/";
    char nom[100];
    int estadoOnline;
    int estadoPartidos;
    int estadoDescenso;

    /*Abrimos archivo*/

    FILE *ajus;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/ajustes.txt");
    strcat(arch,nom);

    ajus = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(ajus,"%d",&estadoOnline);
    fscanf(ajus,"%d",&estadoPartidos);
    fscanf(ajus,"%d",&estadoDescenso);

    /*Cerramos archivo*/

    fclose(ajus);

    /*Abrimos archivo*/

    FILE *usu;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    usu = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(usu,"%s",basura);
    fscanf(usu,"%d",&basura2);
    fscanf(usu,"%d",&basura2);
    fscanf(usu,"%d",&basura2);
    fscanf(usu,"%d",&jornada);

    /*Cerramos archivo*/

    fclose(usu);

    /*Abrimos archivo*/

    FILE *archivo;

    archivo = fopen("BaseDatos/partidos.txt","rt");

    /*Leemos archivo*/

    for (i = 0; i < jornada - 1; i++) {
        for (j = 0; j < 5; j++) {
            fscanf(archivo,"%d",&local);
            fscanf(archivo,"%d",&visitante);
        }
    }

    fscanf(archivo,"%d",&local);
    fscanf(archivo,"%d",&visitante);

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

    /*Pause*/

    gotoxy(5,32);
    system("pause");

    /*Analizamos y LLamamos a funciones*/

    if (estadoPartidos == 0) {
         partidoEnDirecto(nombre,equipo,local,visitante,gollocal,golvisitante);
    }

    subirResultado(nombre,equipo,local,visitante,gollocal,golvisitante);

    /*Repetimos proceso*/

    for (k = 0; k < 4; k++) {
        fscanf(archivo,"%d",&local);
        fscanf(archivo,"%d",&visitante);

        codigo = compararEquipos(nombre,local,visitante);
        mayor = equipoMejor(nombre,local,visitante);

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

        srand(time(NULL));

        gollocal = rand()%(maxlocal + 1);
        golvisitante = rand()%(maxvisitante + 1);

        if (estadoPartidos == 0) {
            partidoEnDirecto(nombre,equipo,local,visitante,gollocal,golvisitante);
        }

        subirResultado(nombre,equipo,local,visitante,gollocal,golvisitante);

    }

    /*Cerramos archivo*/

    fclose(archivo);

    /*LLamamos a funciones*/

    mostrarResultadosJornada(nombre,equipo,jornada);

    subirPuntuacion(nombre,equipo,jornada);

    imprimirClasificacion(nombre,equipo);

    experienciaJornada(nombre,equipo);

    ganar = gestionFinTemporada(nombre,equipo,jornada);

    /*Analizamos*/

    if (ganar == 0) {
        sumarJornada(nombre);
    }

}


void partidoEnDirecto (char nombre[],int equipo,int local,int visitante,int gollocal,int golvisitante) {

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
    char nom[100];
    char arch[] = "BaseDatos/";

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

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

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


void subirResultado (char nombre[],int equipo,int local,int visitante,int gollocal,int golvisitante) {

    FILE *ptr;

    char nom[100];

    char archv[] = "BaseDatos/";

    strcpy(nom,nombre);
    strcat(nom,"/resultados.txt");
    strcat(archv,nom);

    ptr = fopen(archv,"at");

    /*Resultados*/

    fprintf(ptr,"%d ",gollocal);
    fprintf(ptr,"%d\n",golvisitante);

    fclose(ptr);

}

void mostrarResultadosJornada (char nombre[],int equipo,int jornada) {

    int i, j, k;
    int equip;
    char team[100];
    int basura;
    int linea;
    int gol;
    char arch[] = "BaseDatos/";
    char nom[100];

    linea = 14;

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    muestraPagina("R E S U L T A D O S");

    FILE *archivo;
    FILE *ptr;
    FILE *arr;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    ptr = fopen("BaseDatos/partidos.txt","rt");

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/resultados.txt");
    strcat(arch,nom);

    arr = fopen(arch,"rt");

    for (i = 0; i < jornada; i++) {
        for (j = 0; j < 10; j++) {
            fscanf(ptr,"%d",&equip);

            for (k = 0; k < equip; k++) {
                fscanf(archivo,"%s",team);
                fscanf(archivo,"%d",&basura);
                fscanf(archivo,"%d",&basura);
                fscanf(archivo,"%d",&basura);
            }

            rewind(archivo);

            if (i == jornada - 1) {
                if (j % 2 == 0) {
                    gotoxy(40,linea);
                }
                else if (j % 2 == 1) {
                    gotoxy(70,linea);
                    linea += 2;
                }

                if (equipo == equip) {
                    SetColorTexto(11);
                    printf("%s",team);
                    SetColorTexto(12);
                }
                else {
                    printf("%s",team);
                }
            }

        }
    }

    linea = 14;

    for (i = 0; i < jornada - 1; i++) {
        for (j = 0; j < 10; j++) {
            fscanf(arr,"%d",&gol);
        }
    }

    for (i = 0; i < 10; i++) {
        fscanf(arr,"%d",&gol);

        if (i % 2 == 0) {
            gotoxy(55,linea);
        }
        if (i % 2 == 1) {
            gotoxy(65,linea);
            linea += 2;
        }

        printf("%d",gol);
    }

    gotoxy(5,32);
    system("pause");

    fclose(archivo);
    fclose(ptr);
    fclose(arr);

}


void subirPuntuacion (char nombre[],int equipo,int jornada) {

    int i,j;
    int puntos[10];
    int goles[10];
    int local;
    int puntolocal;
    int gollocal;
    int auxgollocal;
    int visitante;
    int puntovisitante;
    int golvisitante;
    int puntoanterior;
    int golanterior;
    char arch[] = "BaseDatos/";
    char nom[100];

    FILE *archivo;
    FILE *ptr;
    FILE *arr;

    strcpy(nom,nombre);
    strcat(nom,"/estadisticas.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"r+");

    ptr = fopen("BaseDatos/partidos.txt","rt");

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/resultados.txt");
    strcat(arch,nom);

    arr = fopen(arch,"rt");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < jornada - 1; j++) {
            fscanf(ptr,"%d",&local);
            fscanf(arr,"%d",&gollocal);
            fscanf(ptr,"%d",&visitante);
            fscanf(arr,"%d",&golvisitante);
        }
    }


    for (i = 0; i < 5; i++) {

        fscanf(ptr,"%d",&local);
        fscanf(arr,"%d",&gollocal);
        fscanf(ptr,"%d",&visitante);
        fscanf(arr,"%d",&golvisitante);

        if (gollocal > golvisitante) {
            puntolocal = 3;
            puntovisitante = 0;
        }
        else if (gollocal < golvisitante) {
            puntolocal = 0;
            puntovisitante = 3;
        }
        else {
            puntolocal = 1;
            puntovisitante = 1;
        }

        for (j = 0; j < local; j++) {
            fscanf(archivo,"%d",&puntoanterior);
            fscanf(archivo,"%d",&golanterior);
        }

        rewind(archivo);

        puntolocal = puntolocal + puntoanterior;
        auxgollocal =  gollocal;
        gollocal = gollocal + golanterior - golvisitante;

        puntos[local - 1] = puntolocal;
        goles[local - 1] = gollocal;

        for (j = 0; j < visitante; j++) {
            fscanf(archivo,"%d",&puntoanterior);
            fscanf(archivo,"%d",&golanterior);
        }

        rewind(archivo);

        puntovisitante = puntovisitante + puntoanterior;
        golvisitante = golvisitante + golanterior - auxgollocal;

        puntos[visitante - 1] = puntovisitante;
        goles[visitante - 1] = golvisitante;


    }

    for (i = 0; i < 10; i++) {

        fprintf(archivo,"%d ",puntos[i]);
        fprintf(archivo,"%d\n",goles[i]);
    }



    fclose(archivo);
    fclose(ptr);
    fclose(arr);

}


void sumarJornada (char nombre[]) {

    /*Nombramos variables*/

    char contrasena[100];
    int estado;
    int equip;
    int temporada;
    int jornada;
    int temporadasganadas;
    int experiencia;
    char nom[100];
    char arch[] = "BaseDatos/";

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

    /*Incrementamos jornada*/

    jornada = jornada + 1;

    /*Imprimimos variables en archivo*/

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

void experienciaJornada (char nombre[],int equipo) {

    /*Nombramos variables*/

    int posicion;
    int sumaXp;

    /*Recogemos posicion*/

    posicion = posicionEquipo(nombre,equipo);

    /*Valoramos*/

    if (posicion >= 8) {
        sumaXp = 200;
    }
    else if (posicion < 8 && 3 < posicion) {
        sumaXp = 500;
    }
    else if (posicion < 3) {
        sumaXp = 750;
    }

    /*Modificamos archivo*/

    sumarExperiencia(nombre,sumaXp);

}
