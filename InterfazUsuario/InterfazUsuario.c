#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include "InterfazGrafica.h"
#include "InterfazUsuario.h"
#include "../InterfazSistema/DatosUsuario.h"
#include "../InterfazSistema/SistemaEquipos.h"
#include "../InterfazSistema/iniciarPartido.h"
#include "../InterfazSistema/finTemporada.h"
#include "../Online/VerUsuarios.h"
#include "../Online/PartidoRapido.h"
#include "../Ajustes/Ajustes.h"

void inicInterfazUsuario (char nombre[]) {

    system("title FutbolManager");

    system("color 0C");

    system("mode con cols=125 lines=35");


     /*MARCO DE ARRIBA*/


    int i;

    /*Esquinas*/

    gotoxy(5,1);
    printf("%c",201);

    gotoxy(5,3);
    printf("%c",200);

    gotoxy(119,1);
    printf("%c",187);

    gotoxy(119,3);
    printf("%c",188);

    /*Barras verticales*/

    gotoxy(5,2);
    printf("%c",186);

    gotoxy(119,2);
    printf("%c",186);

    /*Barras horizontales*/

    for (i = 0; i < 113; i++) {

        gotoxy(i + 6,1);
        printf("%c",205);

        gotoxy(i + 6,3);
        printf("%c",205);

    }

    /*Imprimimos titulo*/

    gotoxy(50,2);
    printf("F U T B O L   M A N A G E R");


    /*MARCO DE ABAJO*/


    /*Esquinas*/

    gotoxy(5,5);
    printf("%c",218);

    gotoxy(5,30);
    printf("%c",192);

    gotoxy(119,5);
    printf("%c",191);

    gotoxy(119,30);
    printf("%c",217);

    /*Barras verticales*/

    for (i = 0; i < 24; i++) {

        gotoxy(5,i + 6);

        if (i + 6 == 8)
            printf("%c",195);

        else
            printf("%c",179);

        gotoxy(119,i + 6);

        if (i + 6 == 8)
            printf("%c",180);

        else
            printf("%c",179);

    }

    /*Barras horizontales*/

    for (i = 0; i < 113; i++) {

        gotoxy(i + 6,5);
        printf("%c",196);

        gotoxy(i + 6, 8);
        printf("%c",196);

        gotoxy(i + 6,30);
        printf("%c",196);

    }

    /*Fecha*/

    gotoxy(7,7);

    time_t t;
    struct tm *tm;
    char fechayhora[100];

    t=time(NULL);
    tm=localtime(&t);
    strftime(fechayhora, 100, "%d/%m/%Y", tm);
    printf ("Hoy es: %s\n", fechayhora);

    /*Nombre*/

    gotoxy(95,7);
    printf("Manager: %s",nombre);


    gotoxy(5,32);

}


void gestionEstadoUsuario (char nombre[]) {

    /*Nombramos variables*/

    int estado;
    int equipo;
    int i;
    char arch[] = "BaseDatos/";
    char nom[100];

    /*Recogemos estado del usuario*/

    estado = EstadoUsuario(nombre);

    /*Analizamos*/

    if (estado == 0) {

        /*Damos instrucciones y recogemos equipo elegido*/

        equipo = GestionNuevaPartida(nombre);
    }
    else {

        /*Abrimos archivo*/

        FILE *archivo;

        strcpy(nom,nombre);
        strcat(nom,".txt");
        strcat(arch,nom);

        archivo = fopen(arch,"rt");

        /*Leemos archivo*/

        for (i = 0; i < 3; i++) {

            fscanf(archivo,"%d",&equipo);

        }

        /*Cerramos archivo*/

        fclose(archivo);
    }

    gestionMenu(nombre,equipo);


}

int GestionNuevaPartida (char nombre[]) {

    /*Nombramos variables*/

    char mensaje[100];
    int equipo;
    int i;
    char arch[] = "BaseDatos/";
    char nom[100];
    char carpeta[] = "MD BaseDatos\\";

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"at");

    if (archivo == NULL) {
        sprintf(mensaje, "El archivo usuario.txt no se ha podido crear.\n");

        gotoxy(5,32);
        printf("%s",mensaje);
    }

    /*Recogemos equipo elegido*/

    equipo = NuevaPartida(nombre);

    /*Imprimimos variable en el archivo*/

    fprintf(archivo,"%d\n", equipo);

    fprintf(archivo,"1\n"); /*temporada*/
    fprintf(archivo,"1\n"); /*jornada*/
    fprintf(archivo,"0\n"); /*Temporadas ganadas*/
    fprintf(archivo,"0\n"); /*Experiencia*/

    /*Creamos nueva carpeta*/

    strcpy(nom,nombre);
    strcat(carpeta,nom);

    system(carpeta);

    /*Borramos parte de abajo*/

    gotoxy(0,33);
    printf("                                                                            ");

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/estadisticas.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"wt");

    /*Imprimimos en archivo*/

    for (i = 0; i < 10; i++) {
        fprintf(ptr,"0 0\n");
    }

    /*Cerramos archivos*/

    fclose(ptr);
    fclose(archivo);

    /*Crear nuevo archivo*/

    crearArchivoEquipos(nombre);

    /*Crear nuevo archivo*/

    crearAjustes(nombre);

    /*Devolvemos equipo*/

    return equipo;

}



int NuevaPartida (char nombre[]) {

    /*Nombramos variables*/

    int equipo;
    char team[100];
    int defensivo;
    int medio;
    int ofensivo;
    int i;

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("B I E V E N I D A");

    /*Imprimimos mensaje*/

    gotoxy(25,15);
    printf("--Bienvenido %s a FutbolManager, est%cs empezando una nueva aventura",nombre,160);
    gotoxy(25,17);
    printf("donde entrenar%cs a uno de los mejores equipos del mundo, pero antes de nada",160);
    gotoxy(25,19);
    printf("deber%cs elegirlo, pulsa una tecla para continuar y mucha suerte.--",160);

    /*Pause*/

    gotoxy(5,32);
    system("pause");

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("E Q U I P O S");

    /*Mostramos lista de equipos*/

    muestraEquipos();

    /*Recogemos variable*/

    muestramensaje("INTRODUCE EL NUMERO DEL EQUIPO:  ");
    scanf("%d",&equipo);

    /*Abrimos archivo*/

    FILE *archivo;

    archivo = fopen("BaseDatos/equipos.txt","rt");

    /*Leemos archivo*/

    for (i = 0; i < equipo; i++) {
        fscanf(archivo,"%s",team);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);
    }

    /*Cerramos archivo*/

    fclose(archivo);

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("N O T I C I A");

    /*Imprimimos mensaje*/

    gotoxy(20,12);
    printf("NOTICIA REVELADORA EN TODO EL MUNDO:");
    gotoxy(20,14);
    printf("!!!%s entrenar%c al %s esta temporada!!!",nombre,160,team);

    gotoxy(20,22);
    printf("--Muy buena elecci%cn, ahora tu equipo es el %s,",162,team);
    gotoxy(20,24);
    printf("los jugadores est%cn ansiosos por que llegues y empiece la temporada.--",160);

    /*Pause*/

    gotoxy(5,32);
    system("pause");

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("I N F O R M A C I O N ");

    /*Imprimimos mensaje*/

    gotoxy(45,15);
    printf("- -   M U C H A   S U E R T E   - -");

    gotoxy(45,26);
    printf("*Para mas informacion vaya a ajustes*");

    /*Pause*/

    gotoxy(5,32);
    system("pause");

    /*Devolvemos equipo*/

    return equipo;

}


int menu (char nombre[],int equipo) {

    /*Nombramos variables*/

    int usuario;

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("M E N U   P R I N C I P A L");

    /*Recogemos e imprimimos experiencia*/

    imprimirExperiencia(nombre);

    /*Imprimimos opciones*/

    gotoxy(50,14);
    printf("1. Iniciar Temporada.");
    gotoxy(50,16);
    printf("2. Partido Rapido.");
    gotoxy(50,18);
    printf("3. Ver Usuarios.");
    gotoxy(50,20);
    printf("4. Ajustes.");
    gotoxy(50,22);
    printf("0. Salir del programa.");

    /*Recogemos usuario*/

    usuario = leerOpcionValida("Escoja una opcion: ",'4');

    /*Devolvemos usuario*/

    return usuario;

}

void gestionMenu (char nombre[],int equipo) {

    /*Nombramos variables*/

    int usuario;

    do {

        usuario = menu(nombre,equipo);

        switch (usuario) {

            case 1: {
                    gestionMenuPrincipal(nombre,equipo);
                    break;
            };

            case 2: {
                    gestionPartidoCPU(nombre);
                    break;
            };

            case 3: {
                    gestionVerUsuarios(nombre);
                    break;
            };

            case 4: {
                    gestionAjustes(nombre);
                    break;
            };

        }

    } while (usuario != 0);

}



int menuPrincipal (char nombre[], int equipo, int *equip) {

    /*Nombramos variables*/

    int i;
    char team[100];
    int defensivo;
    int medio;
    int ofensivo;
    int usuario;
    char arch[] = "BaseDatos/";
    char nom[100];
    char contrasena[100];
    int estado;
    int temporada;
    int jornada;

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pause();
    borrar_pagina();

    /*Imprimimos titulo*/

    muestraPagina("T E M P O R A D A");

    /*Abrimos archvio*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*Leemos archivo*/

    fscanf(ptr,"%s",contrasena);
    fscanf(ptr,"%d",&estado);
    fscanf(ptr,"%d",equip);
    fscanf(ptr,"%d",&temporada);
    fscanf(ptr,"%d",&jornada);

    /*Nombre del equipo*/

    for (i = 0; i < *equip; i++) {
        fscanf(archivo,"%s",team);
        fscanf(archivo,"%d",&defensivo);
        fscanf(archivo,"%d",&medio);
        fscanf(archivo,"%d",&ofensivo);
    }

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);

    /*Imprimimos variables*/

    gotoxy(10,10);
    printf("Equipo: %s",team);
    gotoxy(10,11);
    printf("Temporada: %d",temporada);
    gotoxy(10,12);
    printf("Joranada: %d",jornada);

    imprimirExperiencia(nombre);

    /*Imprimimos opciones*/

    gotoxy(50,13);
    printf("1. Ver tabla de clasificaciones.");
    gotoxy(50,15);
    printf("2. Ver resultados.");
    gotoxy(50,17);
    printf("3. Ver calendario de partidos.");
    gotoxy(50,19);
    printf("4. Iniciar siguiente jornada.");
    gotoxy(50,21);
    printf("5. Historial del usuario.");
    gotoxy(50,23);
    printf("0. Salir.");

    /*Recogemos decision del usuario*/

    usuario = leerOpcionValida("Escoja una opcion: ",'5');

    /*Devolvemos usuario*/

    return usuario;

}

void gestionMenuPrincipal(char nombre[],int equipo) {

    /*Nombramos variables*/

    int usuario;
    int equip;

    do {

        /*Imprimimos opciones y recogemos decision del usuario*/

        usuario = menuPrincipal(nombre,equipo,&equip);

        /*Analizamos*/

        switch (usuario) {
            case 1: {
                    imprimirClasificacion(nombre,equip);
                    break;
            };
            case 2: {
                    verResultados(nombre,equip);
                    break;
            };
            case 3: {
                    imprimirCalendario(nombre,equip);
                    break;
            };
            case 4: {
                    gestionInicioPartido(nombre,equip);
                    break;
            };
            case 5: {
                    ImprimirHistorialUsuario(nombre);
                    break;
            };
            case 0: {
                    break;
            };
        }

    } while (usuario != 0);

    gotoxy(5,32);

}


