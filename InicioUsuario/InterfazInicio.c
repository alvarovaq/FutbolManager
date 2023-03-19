#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "../InterfazUsuario/InterfazGrafica.h"
#include "../InterfazUsuario/InterfazUsuario.h"
#include "GraficaInicio.h"
#include "InterfazInicio.h"
#include "OpcionesInicio.h"

void gestionInicio ()
{
    borrar_todo();

    system("title FutbolManager");

    system("mode con cols=63 lines=35");

    system("color F0");

    marcos(); /*Muestra los marcos del programa*/

    opciones(); /*Muestra el menu donde muestra las diversas opciones*/
}


void marcos () {

    marco_arriba();
    marco_abajo();

}


void marco_arriba() {

    int i;

    /*Esquinas*/

    gotoxy(5,2);
    printf("%c",201);

    gotoxy(5,4);
    printf("%c",200);

    gotoxy(58,2);
    printf("%c",187);

    gotoxy(58,4);
    printf("%c",188);

    /*Barras verticales*/

    gotoxy(5,3);
    printf("%c",186);

    gotoxy(58,3);
    printf("%c",186);

    /*Barras horizontales*/

    for (i = 0; i < 52; i++) {

        gotoxy(i + 6,2);
        printf("%c",205);

        gotoxy(i + 6,4);
        printf("%c",205);

    }

    /*Titulo*/

    gotoxy(25,3);
    printf("I N I C I O");

    gotoxy(5,30);

}



void marco_abajo () {

    int i;

    /*Esquinas*/

    gotoxy(5,5);
    printf("%c",218);

    gotoxy(5,30);
    printf("%c",192);

    gotoxy(58,5);
    printf("%c",191);

    gotoxy(58,30);
    printf("%c",217);

    /*Barras verticales*/

    for (i = 0; i < 24; i++) {

        gotoxy(5,i + 6);
        printf("%c",179);

        gotoxy(58,i + 6);
        printf("%c",179);

    }

    /*Barras horizontales*/

    for (i = 0; i < 52; i++) {

        gotoxy(i + 6,5);
        printf("%c",196);

        gotoxy(i + 6,30);
        printf("%c",196);

    }

    gotoxy(5,32);

}


int menuInicio () {

    /*Nombramos variables*/

    int usuario;

    /*Borramos pantallas*/

    borrar_pantalla();
    borrar_bordeinf();

    /*Imprimimos titulos*/

    gotoxy(12,8);
    printf("ESCOJA UNA DE LAS SIGUIENTES OPCIONES:");

    /*Imprimimos opciones*/

    gotoxy(20,12);
    printf("[1] Iniciar sesi%cn.",162);

    gotoxy(20,14);
    printf("[2] Crear cuenta.");

    gotoxy(20,16);
    printf("[3] Ajustes.");

    gotoxy(20,18);
    printf("[0] Salir del programa.");


    gotoxy(12,24);
    printf("OPCI%cN: ",224);

    /*Recogemos decision del usuario*/

    usuario = leerOpcionValidaInicio('3');

    /*Debolvemos usuario*/

    return usuario;

}



void opciones() {

    /*Nombramos variables*/

    int usuario;

    do {

        /*Imprimimos opciones y recogemos decision del usuario*/

        usuario = menuInicio();

        /*Analizamos*/

        switch (usuario) {
            case 49: {
                iniciar_sesion();
                break;
            }
            case 50: {
                crear_cuenta();
                break;
            }
            case 51: {
                ajustes();
                break;
            }
            case 48: break;

        }

    } while (usuario != 48);

    gotoxy(5,32);

}
