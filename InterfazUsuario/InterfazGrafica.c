#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "InterfazGrafica.h"
#include "InterfazUsuario.h"
#include "../InterfazSistema/DatosUsuario.h"
#include "../InterfazSistema/SistemaEquipos.h"
#include "../InterfazSistema/iniciarPartido.h"
#include "../InterfazSistema/finTemporada.h"
#include "../Online/VerUsuarios.h"
#include "../Online/PartidoRapido.h"
#include "../Ajustes/Ajustes.h"

void SetColorTexto(int colors) { /*Nos permite cambiar el color del texto*/
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colors);
}

void gotoxy(int x, int y) { /*Nos permite colocar el cursor en el lugar deseado*/
    COORD coord;

   coord.X = x;
   coord.Y = y;

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

   return;
}

void borrar_mensaje () {
    int i;

    for (i = 0; i < 70; i++) {
        gotoxy(10,27);
        printf(" ");
    }
}

void borrar_pantalla_principal () { /*Borra la pantalla*/

    int i, j;

    for (i = 0; i < 21; i++) {
        for (j = 0; j < 113; j++) {
            gotoxy(j + 6,i + 9);
            printf(" ");
        }
    }

}

void borrar_pause () {

    gotoxy(5,32);
    printf("                                         ");

}

void borrar_pagina () {

    gotoxy(50,7);
    printf("                                ");
}


void muestraPagina (char pagina[]) {

    gotoxy(50,7);
    printf("%s",pagina);
}

void muestramensaje(char mensaje[]) {
    gotoxy(10,27);
    printf("%s",mensaje);
}

int leerOpcionValida(char mensaje[],char num) {  /*Leer opcion del usuario y verificar que sea un valor correcto*/

    int usuario;

    do {

        borrar_mensaje();
        muestramensaje(mensaje);
        usuario = getche(); /*Recoge un caracter y no se imprime*/

    } while (usuario > num); /*Se sale cuando usuario sea menor que num, esta en modo ASCII*/

    usuario = usuario - 48;

    return usuario; /*Devuelve la opcion escogida por el usuario*/

}
