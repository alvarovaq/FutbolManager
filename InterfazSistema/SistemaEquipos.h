#ifndef SISTEMAEQUIPOS_H_INCLUDED
#define SISTEMAEQUIPOS_H_INCLUDED

void muestraEquipos();
void modificarEstadisticas (char nombre[],int team, int puntos, int goles);
void imprimirClasificacion (char nombre[],int equipo);
void imprimirCalendario (char nombre[],int equipo);
void verResultados(char nombre[],int equipo);
int posicionEquipo(char nombre[],int equipo);
void crearArchivoEquipos(char nombre[]);

#endif // SISTEMAEQUIPOS_H_INCLUDED
