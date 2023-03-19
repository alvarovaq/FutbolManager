#ifndef INTERFAZUSUARIO_H_INCLUDED
#define INTERFAZUSUARIO_H_INCLUDED

void inicInterfazUsuario(char nombre[]);
void gestionEstadoUsuario(char nombe[]);
int GestionNuevaPartida(char nombre[]);
int NuevaPartida (char nombre[]);
int menu(char nombre[],int equipo);
void gestionMenu(char nombre[],int equipo);
int menuPrincipal (char nombre[], int equipo,int *equip);
void gestionMenuPrincipal(char nombre[],int equipo);


#endif // INTERFAZUSUARIO_H_INCLUDED
