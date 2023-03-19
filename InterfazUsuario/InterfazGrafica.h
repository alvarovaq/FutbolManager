#ifndef INTERFAZGRAFICA_H_INCLUDED
#define INTERFAZGRAFICA_H_INCLUDED

void SetColorTexto(int colors);
void gotoxy(int x, int y);
void borrar_mensaje ();
void borrar_pantalla_principal();
void borrar_pause();
void borrar_pagina();
void muestraPagina(char pagina[]);
void muestramensaje(char mensaje[]);
int leerOpcionValida(char mensaje[],char num);

#endif // INTERFAZGRAFICA_H_INCLUDED
