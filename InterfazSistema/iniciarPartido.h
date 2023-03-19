#ifndef INICIARPARTIDO_H_INCLUDED
#define INICIARPARTIDO_H_INCLUDED

void gestionInicioPartido (char nombre[],int equipo);
void mostrarEncuentros(char nombre[],int equipo);
int compararEquipos(char nombre[],int local, int visitante);
int equipoMejor(char nombre[],int local, int visitante);
void resultado (char nombre[],int equipo);
void partidoEnDirecto (char nombre[],int equipo,int local,int visitante,int gollocal,int golvisitante);
void subirResultado (char nombre[],int equipo,int local,int visitante,int gollocal,int golvisitante);
void mostrarResultadosJornada(char nombre[],int equipo,int jornada);
void subirPuntuacion (char nombre[],int equipo,int jornada);
void sumarJornada(char nombre[]);
void experienciaJornada (char nombre[],int equipo);

#endif // INICIARPARTIDO_H_INCLUDED
