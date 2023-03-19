#ifndef FINTEMPORADA_H_INCLUDED
#define FINTEMPORADA_H_INCLUDED

int gestionFinTemporada (char nombre[],int equipo,int jornada);
void modificarTemporada(char nombre[],int equipo);
void cambiarEstadisticas (char nombre[]);
void borrarResultados(char nombre[]);
int noticiasFinTemporada (char nombre[],int equipo);
void descenso (char nombre[],int equipo);
char ofertaTrabajo (char nombre[],int equipo,int bajar,int *nuevoEquipo);
void muestraMensajeDespedido (char nombre[]);
void cambiarEquipo (char nombre[],int equipo,int nuevoEquipo,char decision);
void modificarHistorial (char nombre[],int equipo);

#endif // FINTEMPORADA_H_INCLUDED
