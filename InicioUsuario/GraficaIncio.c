
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "../InterfazUsuario/InterfazGrafica.h"
#include "GraficaInicio.h"
#include "InterfazInicio.h"

void borrar_todo () {
    int i, j;

    for (i = 0; i < 35; i++) {
        for (j = 0; j < 63; j++) {
            gotoxy(0,0);
            printf(" ");
        }
    }
}

void borrar_pantalla () {

    int i, j;

    for (i = 0; i < 52; i++) {
        for (j = 0; j < 24; j++) {

            gotoxy(i+6,j+6);
            printf(" ");

        }
    }

}



void borrar_bordeinf () {

    int i, j;

    for (i = 0; i < 35 - 31; i++) {
        for (j = 0; j < 63; j++) {
            gotoxy(j,i + 31);
            printf(" ");
        }
    }

}



int leerOpcionValidaInicio(char num) {

    int usuario;

    do {

        usuario = getch(); /*Recoge un caracter y no se imprime*/

    } while (usuario > num); /*Se sale cuando usuario sea menor que num, esta en modo ASCII*/

    return usuario; /*Devuelve la opcion escogida por el usuario*/

}
