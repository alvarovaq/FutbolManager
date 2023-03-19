#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "../InterfazUsuario/InterfazGrafica.h"
#include "../InterfazUsuario/InterfazUsuario.h"
#include "GraficaInicio.h"
#include "InterfazInicio.h"
#include "OpcionesInicio.h"


void crear_cuenta () {

    /*Nombramos variables*/

    char nombre[100]; //nombre de usuario
    char contrasena[100]; //contrasena del usuario
    char nom[100]; //variable auxiliar par nombre
	int i, aux;
	char basedatos [] = "BaseDatos/";

	/*Inicializamos variables*/

	aux = 0;

	/*Nombramos variables*/

    FILE *usuarios; //leer en usuarios.txt
	FILE *usu; //escribir en usuarios.txt
	FILE *archivo; //crea archivo con el nombre del usuario

    do {

        /*Borramos pantallas*/

        borrar_bordeinf();
	   	borrar_pantalla();

        /*Imprimimos titulo*/

	    gotoxy(25,8);
	    printf("CREAR CUENTA");


		if (aux == 1) {
            gotoxy(8,28);
			printf("*El NOMBRE de usuario ya existe, intenta otro...");
		}

		/*Recogemos variable*/

		gotoxy(15,12);
	    printf("Introduce el NOMBRE del usuario: ");
	    fflush(stdin);
	    gotoxy(25,14);
		scanf("%s",nombre);	//nos da el nombre

		/*Abrimos archivo*/

		usuarios = fopen("BaseDatos/usuarios.txt","a");
		usu = fopen("BaseDatos/usuarios.txt","r");

		/*Inicializamos variables*/

		aux = 0;

		/*Comprobamos la no existencia de nombre*/

		for (i = 0; i < 100 && aux == 0; i++) { //repite la operacion hasta llegar a N o a que aux sea 1
			fscanf(usu,"%s",nom); //leemos usuarios.txt y lo metemos en nom

	 		if (strcmp(nom,nombre) == 0) { //si nom y nombre son iguales salimos del ciclo
	 			//printf("El nombre de usuario ya existe, intenta otro...\n\n");

	 			aux = 1;
			 }
		}

		/*Recolocamos cursor en archivo*/

		rewind(usu);

	} while (aux == 1); //si existe otro usuario con el mismo nombre, repite la operacion

    /*Imprimimos variable en el archivo*/

	fprintf(usuarios,"%s ",nombre); //si no  hay otro usuario con el mismo nombre, lo metemos en usuarios.txt

	/*Abrimos archivo*/

	strcat(nombre,".txt"); //unimos la variable nombre com .txt //ej: alvaro.txt
	strcat(basedatos,nombre);
	archivo = fopen(basedatos,"wt"); //creamos un archivo con el nombre del usuario

	/*Recogemos variable*/

    gotoxy(15,16);
	printf("Introduce la CONTRASENA del usuario: ");
	fflush(stdin);
	gotoxy(25,18);
	fgets(contrasena, 100, stdin); //recogemos la contraseña

	/*Imprimimos variable en el archivo*/

	fprintf(archivo,"%s0",contrasena);	//imprimos la contraseña en el archivo del usuario propio

	/*Cerramos archivos*/

	fclose(usu); //cerramos los archivos
	fclose(usuarios);
	fclose(archivo);

	/*Pause*/

	gotoxy(5,31);
	system("pause");

}


void iniciar_sesion () {

    /*Nombrar variables*/

    char nombre[100];
	char contrasena[100];
	char nom[100]; //variable auxiliar
	char cont[100]; //variable auxiliar
	int aux, i, error;
	char basedatos[] = "BaseDatos/";

	/*Inicializar variables*/

	aux = 1; //para que al entrar el ciclo no ponga que no exista el usuario
	error = 0;

	/*Nombramos variables*/

	FILE *usuarios;
	FILE *archivo;

	do {
		do {

            /*Borrar pantallas*/

			borrar_bordeinf();
			borrar_pantalla();

			/*Imprimir titulo*/

			gotoxy(25,8);
			printf("INICIAR SESI%cN",224);

			if (error == 1) { //si nos dio un error al poner la contraseña imprimimos esto
                gotoxy(15,26);
				printf("*La CONTRASENA NO es correcta...");
			}

			/*Inicializar variables*/

			error = 0;

			if (aux == 0) { //si no existe el nombre de usuario imprimimos esto
			    gotoxy(9,26);
				printf("*El NOMBRE de usuario introducido NO existe...");
			}

			/*Recoger variable*/

			gotoxy(15,12);
			printf("Introduce el NOMBRE del usuario: ");
			fflush(stdin);
			gotoxy(25,14);
			scanf("%s",nombre); //recogemos el nombre de usuario introducido

			/*Abrimos archivo*/

			usuarios = fopen("BaseDatos/usuarios.txt","rt"); //abrimos archivo usuarios.txt para leer

			/*Inicializamos variable*/

			aux = 0;

			/*Comprobamos existencia del nombre de ese usuario*/

			for (i = 0; i < 100 && aux == 0; i++) {
				fscanf(usuarios,"%s",nom); //leemos usuarios.txt

				if (strcmp(nom,nombre) == 0) { //si nom es igual a nombre existe un usuario con ese nombre y salimos del ciclo
					aux = 1; //1 si existe, 0 si no existe
				}
			}

			/*Cerramos archivo*/

			fclose(usuarios);

		}while (aux == 0);

		/*Recogemos variable*/

		gotoxy(15,16);
		printf("Introduce la CONTRASENA del usuario: ");
	    fflush(stdin);
	    gotoxy(25,18);
		fgets(contrasena, 100, stdin); //recogemos la contraseña

		/*Abrimos archivo*/

		sprintf(basedatos,"BaseDatos/");

		strcpy(nom,nombre);
		strcat(nombre,".txt");  //unimos la variable nombre con .txt
		strcat(basedatos,nombre);

		archivo = fopen(basedatos,"rt"); //abrimos archivo del usuario para leer

		/*Leemos archivo*/

		fscanf(archivo,"%s",cont); //leemos el archivo donde esta su contraseña

		/*Verificamos contrasena*/

		if (strncmp (contrasena,cont,strlen(cont))) { //si contrasena y cont no son iguales se repite el ciclo
			error = 1;
		}
		else { //si contrasena y cont son iguales imprimimos esto

            gotoxy(5,32);

			inicInterfazUsuario(nom);
			gestionEstadoUsuario(nom);

			gestionInicio();

		}

		/*Cerramos archivo*/

		fclose(archivo);

    }while(error == 1); //si la contraseña no coincide con la del usuario, se repite el ciclo

    /*Pause*/

    gotoxy(5,32);
    system("pause");
}


void ajustes () {

    /*Nombramos variables*/

    int usuario;

    do {

    /*Borramos pantallas*/

	borrar_bordeinf();
	borrar_pantalla();

    /*Imprimimos titulo*/

	gotoxy(22,8);
	printf("AJUSTES DEL SISTEMA");

	/*Imprimimos opciones*/

	gotoxy(20,13);
	printf("[1] Cambiar contrasena.");
	gotoxy(20,15);
	printf("[2] Usuarios.");
	gotoxy(20,17);
	printf("[0] Menu Anterior.");

	gotoxy(12,24);
    printf("OPCI%cN: ",224);



        /*Recogemos decision del usuario*/

        usuario = leerOpcionValidaInicio('2');

        /*Analizamos*/

        switch (usuario) {
            case 49: {
                fcontrasenas();
                break;
            };
            case 50: {
                fusuarios();
                break;
            };
        }

	} while (usuario != 48);
}

void fcontrasenas() {

    /*Nombramos variables*/

	char nombre[100],nom[100];
	char contrasena[100];
	int i,aux;
	char arch[] = "BaseDatos/";
	char cont[100];
	int estado;
	int equipo;
	int temporada;
	int jornada;
	int temporadasganadas;

	/*Inicializamos variables*/

	aux = 1;

	/*Nombramos archivos*/

	FILE *usuarios;
	FILE *archivo;

	do {

        /*Borramos pantallas*/

		borrar_bordeinf();
		borrar_pantalla();

        /*Imprimimos titulo*/

		gotoxy(22,8);
		printf("CAMBIAR CONTRASENA");


		if (aux == 0) { //si el usuario introducido no existe esto, imprimimos esto
            gotoxy(8,28);
			printf("*el NOBRE del usuario introducido NO existe...");
		}

		/*Recogemos variable*/

		gotoxy(15,12);
		printf("Introduce el NOMBRE del usuario: ");
		fflush(stdin);
		gotoxy(25,14);
		scanf("%s",nombre); //recogemos el nombre del usuario

		/*Inicializamos variables*/

		aux = 0;

		/*Abrimos archivo*/

		usuarios = fopen("BaseDatos/usuarios.txt","rt"); //abrimos usuarios.txt para leer

		/*Verificamos existencia de nombre*/

		for (i = 0; i < 100 && aux == 0; i++) {
			fscanf(usuarios,"%s",nom); //leemos palabra de usuarios.txt

			if (strcmp(nom,nombre) == 0) { //si nombre y nom coinciden, se van del ciclo
				aux = 1;
			}
		}

		/*Recolocamos cursor en archivo*/

		rewind(usuarios);

    }while(aux == 0);

     /*Abrimos archivo*/

    sprintf(arch,"BaseDatos/");

    strcpy(nom,nombre);
    strcat(nom,".txt");
    strcat(arch,nom);

    archivo = fopen(arch,"r+"); //abrimos archivo del usuario para escribir

    /*Recogemos variable*/

    gotoxy(15,16);
    printf("Introdudca la nueva CONTRASENA: ");
    fflush(stdin);
    gotoxy(25,18);
    scanf("%s",contrasena); //recogemos contraseña

    /*Leemos archivo*/

    fscanf(archivo,"%s",cont);
    fscanf(archivo,"%d",&estado);

    if (estado == 1) {
        fscanf(archivo,"%d",&equipo);
        fscanf(archivo,"%d",&temporada);
        fscanf(archivo,"%d",&jornada);
        fscanf(archivo,"%d",&temporadasganadas);
    }

    /*Recolocamos cursor del archivo*/

    rewind(archivo);

    /*Imprimimos variables en el archivo*/

    fprintf(archivo,"%s\n",contrasena); //metemos la nueva contraseña borrando la anterior
    fprintf(archivo,"%d\n",estado);

    if (estado == 1) {
        fprintf(archivo,"%d\n",equipo);
        fprintf(archivo,"%d\n",temporada);
        fprintf(archivo,"%d\n",jornada);
        fprintf(archivo,"%d\n",temporadasganadas);
    }

    /*Imprimimos mensaje*/

    gotoxy(20,22);
    printf("CONTRASENA cambiada...");

    /*Cerramos archivos*/

    fclose(usuarios); //cerramos los archivos
    fclose(archivo);

    /*Pause*/

    gotoxy(5,32);
    system("pause");
}



void fusuarios () {

    /*Nombramos variables*/

    int usuario;

    do {

        /*Borramos pantallas*/

        borrar_bordeinf();
        borrar_pantalla();

        /*Imprimimos titulo*/

        gotoxy(25,8);
        printf("USUARIOS");

        /*Imprimimos opciones*/

        gotoxy(16,13);
        printf("[1] Ver todos los usuarios.");
        gotoxy(16,15);
        printf("[2] Borrar todos los usuarios.");
        gotoxy(16,17);
        printf("[0] Menu Anterior.");

        gotoxy(12,24);
        printf("OPCI%cN: ",224);


        /*Recogemos decision del usuario*/

        usuario = leerOpcionValidaInicio('2');

        /*Analizamos*/

        switch (usuario) {
            case 49: {
                fver();
                break;
            };
            case 50: {
                fborrar();
                break;
            };
        }

	} while (usuario != 48);

}


void fver () {

    /*Nombramos variables*/

    char usu[100];
	int i;

	/*Inicializamos variables*/

	i = 0;

	/*Borramos pantallas*/

	borrar_bordeinf();
	borrar_pantalla();

	/*Imprimimos titulo*/

	gotoxy(25,8);
	printf("VER USUARIOS");

	/*Abrimos archivo*/

	FILE *usuarios;

	usuarios = fopen("BaseDatos/usuarios.txt","r");

	/*Leemos e imprimimos variable*/

	while (fscanf(usuarios,"%s",usu) == 1) {
        gotoxy(27,i + 12);
        printf("+ %s.\n",usu);

        i++;
	}

	/*Cerramos archivo*/

	fclose(usuarios); //cerramos usuarios

	/*Pause*/

	gotoxy(5,32);
	system ("pause");

}


void fborrar () {  /*Sin terminar*/

    /*Nombramos variables*/

    char op;
    int pass, error;

    /*Inicializamos variables*/

    error = 0;

    do {

        /*Borramos pantallas*/

        borrar_bordeinf();
        borrar_pantalla();

        if (error == 1) {
            gotoxy(14,28);
            printf("*La contrasena es incorrecta");
        }

        /*Imprimir titulo*/

        gotoxy(20,8);
        printf("BORRAR TODOS LOS USUARIOS");

        /*Recogemos variable*/

        gotoxy(21,12);
        printf("Introduce la contrasena");
        gotoxy(30,14);
        scanf("%d",&pass);

        /*Inicializamos variable*/

        error = 0;

        /*Verificamos contrasena*/

        if (pass != 2904) {
            error = 1;
        }


    } while (error == 1);

    /*Recogemos variable*/

	gotoxy(7,18);
	printf("seguro que quieres borrar todos los usuarios (s/n):");
	fflush(stdin);
	gotoxy(30,20);
	scanf("%c",&op); //recogemos opcion

	/*Analizamos*/

	if (op == 's' || op == 'S') { //si ponen que si:

		 fborrararchivos(); //borra todos los archivos de los usuarios

		 FILE *usuarios;

		 usuarios = fopen("BaseDatos/usuarios.txt","w"); //abrimos usuarios.txt para borrar y escribir(w)

		 fclose(usuarios); //cerramos archivos

		 fprintf(usuarios," ");

		 gotoxy(25,25);
		 printf("USUARIOS BORRADOS.");

		 fclose(usuarios); //cerramos archivos
	}
	else { //si tocan otra tecla no pasa nada
        gotoxy(25,25);
		printf("Operacion cancelada");
	}

    gotoxy(5,32);
    system("pause");

    gestionInicio();

    exit(1);

}


void fborrararchivos () {

    char nombre[100];
	char arch[] = "BaseDatos/";


	FILE *usuarios;

	usuarios = fopen("BaseDatos/usuarios.txt","rt");

	while (!feof(usuarios)) {

            sprintf(arch,"BaseDatos/");

            fscanf(usuarios,"%s",nombre); //leemos usuarios.txt

            strcat(nombre,".txt"); //añadimos .txt a la variable nombre
            strcat(arch,nombre);
            remove(arch); //borramos el archivo del usuario

	}

	fclose(usuarios);

}

