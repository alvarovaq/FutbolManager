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

int gestionFinTemporada (char nombre[],int equipo,int jornada) {

    /*Nombramos variables*/

   int finTemp;
   int bajar;
   char decision;
   int nuevoEquipo;
   char nom[100];
   char arch[] = "BaseDatos/";
   int basura;
   int estadoDescenso;

   /*Abrimos archivo*/

   FILE *archivo;

   strcpy(nom,nombre);
   strcat(nom,"/ajustes.txt");
   strcat(arch,nom);

   archivo = fopen(arch,"rt");

   /*Leemos archivo*/

   fscanf(archivo,"%d",&basura);
   fscanf(archivo,"%d",&basura);
   fscanf(archivo,"%d",&estadoDescenso);

   /*Cerramos archivo*/

   fclose(archivo);

   /*Analizamos y ejecutamos*/

   if (jornada == 9) {
        finTemp = 1;
        modificarTemporada(nombre,equipo);
        modificarHistorial(nombre,equipo);
        bajar = noticiasFinTemporada(nombre,equipo);
        if (estadoDescenso == 0) {
            descenso(nombre,equipo);
        }
        decision = ofertaTrabajo(nombre,equipo,bajar,&nuevoEquipo);

        cambiarEquipo(nombre,equipo,nuevoEquipo,decision);

        cambiarEstadisticas(nombre);
        borrarResultados(nombre);
   }
   else {
        finTemp = 0;
   }

    /*Devolvemos la variable finTemp*/

   return finTemp;

}

void modificarTemporada (char nombre[],int equipo) {

    /*Nombramos variables*/

    char contrasena[100];
    int estado;
    int equip;
    int temporada;
    int jornada;
    int temporadasGanadas;
    int experiencia;
    char nom[100];
    char arch[] = "BaseDatos/";
    int posicion;

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
    fscanf(archivo,"%d",&temporadasGanadas);
    fscanf(archivo,"%d",&experiencia);

    /*Recolocamos cursor*/

    rewind(archivo);

    /*Modificamos variables*/

    temporada++;
    jornada = 1;

    /*Recogemos variables*/

    posicion = posicionEquipo(nombre,equipo);

    /*Analizamos*/

    if (posicion == 1) {
        temporadasGanadas++;
    }

    /*Imprimimos en archivo*/

    fprintf(archivo,"%s\n",contrasena);
    fprintf(archivo,"%d\n",estado);
    fprintf(archivo,"%d\n",equipo);
    fprintf(archivo,"%d\n",temporada);
    fprintf(archivo,"%d\n",jornada);
    fprintf(archivo,"%d\n",temporadasGanadas);
    fprintf(archivo,"%d\n",experiencia);

    /*Cerramos experiencia*/

    fclose(archivo);

}

void cambiarEstadisticas (char nombre[]) {

    /*Nombrar variables*/

    int i;
    char nom[100];
    char arch[] = "BaseDatos/";

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/estadisticas.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"wt");

    /*Imprimimos en archivo*/

    for (i = 0; i < 10; i++) {
        fprintf(archivo,"0 0\n");
    }

    /*Cerramos archivo*/

    fclose(archivo);

}

void borrarResultados (char nombre[]) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/resultados.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"wt");

    /*Cerramos archivo*/

    fclose(archivo);

}


int noticiasFinTemporada (char nombre[],int equipo) {

    /*Nombramos variables*/

    int posicion;
    char team[100];
    int i;
    int basura;
    char arch[] = "BaseDatos/";
    char nom[100];
    int bajar;

    /*Inicializamos variables*/

    bajar = 0;

    /*Abrimos Archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Inicializamos team*/

    for (i = 0; i < equipo; i++) {
        fscanf(archivo,"%s",team);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
    }

    /*Cerramos archivo*/

    fclose(archivo);

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pagina();
    borrar_pause();

    /*Imprimimos Titulo*/

    muestraPagina("F I N   T E M P O R A D A");

    /*Recogemos posicion*/

    posicion = posicionEquipo(nombre,equipo);

    /*Imprimimos  informacion*/

    gotoxy(30,12);
    printf("Se ha acabado la temporada y este ha sido tu resultado:");

    gotoxy(30,16);
    printf("Entrenador: %s",nombre);
    gotoxy(30,18);
    printf("Equipo: %s",team);
    gotoxy(30,20);
    printf("Posicion: %d",posicion);

    /*Analizamos e imprimimos*/

    if (posicion < 4) {
        gotoxy(30,23);
        printf("Estamos muy orgullosos de tu trabajo, de verdad has hecho un gran trabajo");
    }
    else if (posicion >= 4 && posicion < 8) {
        gotoxy(30,23);
        printf("Buen trabajo %s, pero esperamos mas de ti",nombre);
    }
    else if (posicion >= 8) {
        gotoxy(30,23);
        printf("Sabemos que no te ha sido facil pero creemos que lo podrias hacer mucho mejor");
        bajar = -1;
    }

    /*pause*/
    gotoxy(5,32);
    system("pause");

    /*Devolvemos la variable bajar*/

    return bajar;


}


void descenso (char nombre[],int equipo) {

    /*Nombrar variables*/

    int i;
    char nom[100];
    char arch[] = "BaseDatos/";
    char team[11][100];
    int defensivo[11];
    int medio[11];
    int ofensivo[11];
    char teamDes[4][100];
    int defensivoDes[4];
    int medioDes[4];
    int ofensivoDes[4];
    int posicion;
    int posVector[11];
    int cont;
    int y;

    /*Inicializamos las variables*/

    cont = 0;

    /*Abrimos archivo*/

    FILE * archivo;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Abrimos archivo*/

    FILE *arr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/descenso.txt");
    strcat(arch,nom);

    arr = fopen(arch,"rt");

    /*Leemos archivo*/

     for (i = 0; i < 10; i++) {
        fscanf(archivo,"%s",team[i]);
        fscanf(archivo,"%d",&defensivo[i]);
        fscanf(archivo,"%d",&medio[i]);
        fscanf(archivo,"%d",&ofensivo[i]);
     }

     for (i = 0; i < 3; i++) {
        fscanf(arr,"%s",teamDes[i]);
        fscanf(arr,"%d",&defensivoDes[i]);
        fscanf(arr,"%d",&medioDes[i]);
        fscanf(arr,"%d",&ofensivoDes[i]);
     }

     /*Reiniciamos posicion del cursor*/

     rewind(archivo);
     rewind(arr);

     /*Calculamos la posicion*/

     for (i = 0; i < 11; i++) {
        posicion = posicionEquipo(nombre,i + 1);
        posVector[i] = posicion;
     }

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"wt");

    /*Abrimos archivo*/

    FILE *des;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/descenso.txt");
    strcat(arch,nom);

    des = fopen(arch,"wt");

    /*Imprimimos nuevo equipo*/

    for (i = 0; i < 10; i++) {
        if (posVector[i] < 8) {
            fprintf(ptr,"%s ",team[i]);
            fprintf(ptr,"%d ",defensivo[i]);
            fprintf(ptr,"%d ",medio[i]);
            fprintf(ptr,"%d\n",ofensivo[i]);
        }
        else {
            fprintf(ptr,"%s ",teamDes[cont]);
            fprintf(ptr,"%d ",defensivoDes[cont]);
            fprintf(ptr,"%d ",medioDes[cont]);
            fprintf(ptr,"%d\n",ofensivoDes[cont]);

            cont++;
        }
    }

    /*Imprimimos nuevo descenso*/

    for (i = 0; i < 10; i++) {
        if (posVector[i] >= 8) {
            fprintf(des,"%s ",team[i]);
            fprintf(des,"%d ",defensivo[i]);
            fprintf(des,"%d ",medio[i]);
            fprintf(des,"%d\n",ofensivo[i]);
        }
    }

    /*Cerramos los archivos*/

    fclose(archivo);
    fclose(arr);
    fclose(ptr);
    fclose(des);


    /*INTERFAZ USUARIO*/

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pagina();
    borrar_pause();

    SetColorTexto(7);

    gotoxy(40,15);
    printf("Descensos: ");

    gotoxy(70,15);
    printf("Ascensos: ");

    /*Imprimir descensos en pantalla*/

    SetColorTexto(4);

    y = 19;

    gotoxy(40,y);

    for (i = 0; i < 10; i++) {
        if (posVector[i] >= 8) {
            printf("%s",team[i]);

            y += 2;

            gotoxy(40,y);

        }
    }


    /*Imprimir ascensos*/

    SetColorTexto(2);

    gotoxy(70,19);

    for (i = 0; i < 3; i++) {
        printf("%s",teamDes[i]);
        if (i == 0) {
            gotoxy(70,21);
        }
        if (i == 1) {
            gotoxy(70,23);
        }
    }

    SetColorTexto(12);

    /*pause*/

    gotoxy(5,32);
    system("pause");

}


char ofertaTrabajo (char nombre[],int equipo,int bajar,int *nuevoEquipo)  {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    char team[100];
    int basura;
    char decision;
    int i;

    /*Abrimo archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    archivo = fopen(arch,"rt");

    /*Analizamos*/

    if (bajar == 0) {

        /*Borramos pantallas*/

        borrar_pantalla_principal();
        borrar_pause();
        borrar_pagina();

        /*Mostramos titulo*/

        muestraPagina("O F E R T A   DE   T R A B A J O");

        /*Nuevo equipo*/

        do{
            /*Conseguir un numero aleatorio*/

            srand (time(NULL));

            /*Inicializamos variable*/

            *nuevoEquipo =1 + rand()%9;

        }while (*nuevoEquipo == equipo);

        /*Nombre del nuevo equipo*/

        for (i = 0; i < *nuevoEquipo; i++) {
            fscanf(archivo,"%s",team);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
        }

        /*INTERFAZ USUARIO*/

        gotoxy(30,13);
        printf("Hola de nuevo %s, he recibido una nueva oferta de trabajo para usted:",nombre);

        gotoxy(30,16);
        printf("Mensage del director del %s:",team);

        gotoxy(30,18);
        printf("Buenos dias %s, tras nuestra gran interes en usted le ofrecemos una oferta",nombre);
        gotoxy(30,20);
        printf("de trabajo como entrenador de nuestro equipo, el %s.",team);
        gotoxy(30,22);
        printf("Un cordial saludo.                              Director del %s.",team);

        muestramensaje("Haceptar oferta?(s/n): ");
        fflush(stdin);
        scanf("%c",&decision);

    }

    else {

        muestraMensajeDespedido(nombre);

        /*Borramos pantallas*/

        borrar_pantalla_principal();
        borrar_pause();
        borrar_pagina();

        /*Mostramos titulo*/

        muestraPagina("O F E R T A   DE   T R A B A J O");

        /*Conseguir un numero aleatorio*/

        srand (time(NULL));

        /*Inicializamos variable*/

        *nuevoEquipo =1 + rand()%9;

        /*Nombre del nuevo equipo*/

        /*Sera un equipo que acaba de ascender*/

        for (i = 0; i < *nuevoEquipo; i++) {
            fscanf(archivo,"%s",team);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
            fscanf(archivo,"%d",&basura);
        }

        /*INTERFAZ USUARIO*/

        gotoxy(30,13);
        printf("Hola de nuevo %s, he recibido una nueva oferta de trabajo para usted:",nombre);

        gotoxy(30,16);
        printf("Mensage del director del %s:",team);

        gotoxy(30,18);
        printf("Buenos dias %s, tras nuestra gran interes en usted le ofrecemos una oferta",nombre);
        gotoxy(30,20);
        printf("de trabajo como entrenador de nuestro equipo, el %s.",team);
        gotoxy(30,22);
        printf("Un cordial saludo.                                Director del %s.",team);

        gotoxy(30,26);
        printf("Tras su despedida con el anterior equipo, he tenido que aceptarlo.");
        gotoxy(30,27);
        printf("Tu nuevo equipo es el %s.",team);

        decision = 's';

    }

    /*Cerramos archivo*/

    fclose(archivo);

    /*Pause*/

    gotoxy(5,32);
    system("pause");


    return decision;

}

void muestraMensajeDespedido (char nombre[]) {

    /*Borramos pantallas*/

    borrar_pantalla_principal();
    borrar_pagina();
    borrar_pause();

    /*Imprimir titulo*/

    muestraPagina("D E S P E D I D A");

    /*Imprimir mensaje*/

    gotoxy(20,13);
    printf("Buenas tardes %s, tras la mala temporada resultante, tanto yo como el equipo tecnico",nombre);
    gotoxy(20,15);
    printf("hemos tenido interes de fichar a otro entrenador, para poderle sustituir, lamentablemente");
    gotoxy(20,17);
    printf("esto es una despedida, desde aqui le deseamos un gran futuro profesiona y personal.");
    gotoxy(20,19);
    printf("Un cordial saludo.");

    /*Pause*/

    gotoxy(5,32);
    system("pause");

}


void cambiarEquipo (char nombre[],int equipo,int nuevoEquipo,char decision) {

    /*Nombramos variables*/

    char nom[100];
    char arch[] = "BaseDatos/";
    char contrasena[100];
    int estado;
    int equip;
    int temporada;
    int jornada;
    int temporadasGanadas;
    int experiencia;
    char team[100];
    int basura;
    int i;

    /*Abrimos archivo*/

    FILE *archivo;

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"r+");

    /*Abrimos archivo*/

    FILE *ptr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/equipos.txt");
    strcat(arch,nom);

    ptr = fopen(arch,"rt");

    /*Analizamos*/

    if (decision == 's' || decision == 'S') {

        /*Leemos nombre equipo*/

        for (i = 0; i < nuevoEquipo; i++) {
            fscanf(ptr,"%s",team);
            fscanf(ptr,"%d",&basura);
            fscanf(ptr,"%d",&basura);
            fscanf(ptr,"%d",&basura);
        }

        /*Leemos archivo*/

        fscanf(archivo,"%s",contrasena);
        fscanf(archivo,"%d",&estado);
        fscanf(archivo,"%d",&equip);
        fscanf(archivo,"%d",&temporada);
        fscanf(archivo,"%d",&jornada);
        fscanf(archivo,"%d",&temporadasGanadas);
        fscanf(archivo,"%d",&experiencia);

        /*Recolocamos cursor del archivo*/

        rewind(archivo);

        /*Imprimimos variables en el archivo*/

        fprintf(archivo,"%s\n",contrasena);
        fprintf(archivo,"%d\n",estado);
        fprintf(archivo,"%d\n",nuevoEquipo);
        fprintf(archivo,"%d\n",temporada);
        fprintf(archivo,"%d\n",jornada);
        fprintf(archivo,"%d\n",temporadasGanadas);
        fprintf(archivo,"%d\n",experiencia);

        /*INTERFAZ USUARIO*/

        /*Borrar pantallas*/

        borrar_pantalla_principal();
        borrar_pagina();
        borrar_pause();

        /*Imprimir titulo*/

        muestraPagina("B I E N V E N I D A");

        /*Imprimir mensaje*/

        gotoxy(20,13);
        printf("Bienvenido %s a nuestro club, estamos muy contentos de tu llegada.",nombre);
        gotoxy(20,15);
        printf("Ahora pertence a nuestro equipo, el %s, y esperamos grandes objetivos con usted.",team);
        gotoxy(20,19);
        printf("Entrenador: %s",nombre);
        gotoxy(20,21);
        printf("Equipo: %s",team);

    }

    else {

        /*Leemos nombre equipo*/

        for (i = 0; i < equipo; i++) {
            fscanf(ptr,"%s",team);
            fscanf(ptr,"%d",&basura);
            fscanf(ptr,"%d",&basura);
            fscanf(ptr,"%d",&basura);
        }

        /*Borrramos pantallas*/

        borrar_pantalla_principal();
        borrar_pagina();
        borrar_pause();

        /*Imprimir titulo*/

        muestraPagina("M E N S A J E");

        /*Imprimimos mensaje*/

        gotoxy(20,13);
        printf("Desde aqui %s, nos alegramos de su decision y eso nos motiva a que nuestro club",nombre);
        gotoxy(20,15);
        printf(" %s credca mas y tenga un gran potencial para arrancar con fuerza esta temporada.",team);
        gotoxy(20,19);
        printf("Entrenador: %s",nombre);
        gotoxy(20,21);
        printf("Equipo: %s",team);

    }

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);

    /*Pause*/

    gotoxy(5,32);
    system("pause");

}


void modificarHistorial (char nombre[],int equipo) {

    /*Nombrar variables*/

    int i;
    char nom[100];
    char arch[] = "BaseDatos/";
    char bas[100];
    int basura;
    char team[100];
    int temporada;
    int posicion;

    /*Abrimos archivo*/

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

    /*Abrimos archivo*/

    FILE *arr;

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,"/historial.txt");
    strcat(arch,nom);

    arr = fopen(arch,"at");

    /*Leemos archivo*/

    for (i = 0; i < equipo; i++) {
        fscanf(archivo,"%s",team);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
        fscanf(archivo,"%d",&basura);
    }

    /*Leemos archivo*/

    fscanf(ptr,"%s",bas);
    fscanf(ptr,"%d",&basura);
    fscanf(ptr,"%d",&basura);
    fscanf(ptr,"%d",&temporada);
    fscanf(ptr,"%d",&basura);
    fscanf(ptr,"%d",&basura);

    /*Damos valor a posicion*/

    posicion = posicionEquipo(nombre,equipo);

    /*Imprimimos variables en el archivo*/

    fprintf(arr,"%d ",temporada - 1);
    fprintf(arr,"%s ",team);
    fprintf(arr,"%d\n",posicion);

    /*Cerramos archivos*/

    fclose(archivo);
    fclose(ptr);
    fclose(arr);

}

void experienciaTemporada (char nombre[],int equipo) {

    /*Nombramos variables*/

    int posicion;
    int sumaXp;

    /*Recogemos posicion*/

    posicion = posicionEquipo(nombre,equipo);

    /*Valoramos*/

    if (posicion >= 8) {
        sumaXp = 800;
    }
    else if (posicion < 8 && 3 < posicion) {
        sumaXp = 1100;
    }
    else if (posicion < 3) {
        sumaXp = 1700;
    }

    /*Modificamos archivo*/

    sumarExperiencia(nombre,sumaXp);

}

