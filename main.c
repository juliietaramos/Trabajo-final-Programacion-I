#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pila.h"
/// ------------------------------------------------------------ESTRUCTURAS ------------------------------------------------------------///
typedef struct /// stcliente
{
    char nombre[100];
    char telefono[100];
} stCLIENTE;

typedef struct /// stusuario
{
    char usuario[100];
    char contrasena[100];
    stCLIENTE cliente;
} stUSUARIO;

typedef struct /// streserva
{
    stUSUARIO cliente;
    int numMesa;
    char Fecha [11];
    float Horario;
    int cantidadPersonas;
} stRESERVA;

typedef struct /// stmesas
{
    int numeroDeMesa;
    int capacidad;
    float disponible[21][2]; /// 21 horarios , 0 o 1 si esta o no disponible (cuadro de doble entrada)
} stMESAS;
/// ------------------------------------------------------------ESTRUCTURAS ------------------------------------------------------------///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ------------------------------------------------------------PROTOTIPADO------------------------------------------------------------///
void crearArchivoMesas (char archivo[]); /// 1 FUNC PARA CREAR EL ARCHIVO DE MESAS
void generarMatrizMesa(float matriz[][2], int filas); /// 2 FUNC PARA GENERAR LA MATRIZ
void registrarUsuario (char archivo[]); /// FUNC 3 PARA CREAR UN USUARIO AL ARCHIVO
stUSUARIO iniciarSesion (char archivo[], int *verificacion);  /// FUNC 4 PARA VERIFICAR SI EL CLIENTE SE REGISTRO Y PUEDA INICIAR SESION
void mostrarArchivoClientes(char archivo[]); /// FUNC 5 PARA OSTRAR EL ARCHIVO CLIENTES
void mostrarArchivoMesas(char archivo[]); /// FUNC 6 PARA MOSTRAR EL ARCHIVO MESAS
void crearReserva (char archivoReserva[], char archivoMesas[], stUSUARIO cliente);   /// FUNC 7 PARA CREAR LA RESERVA
float horarioReserva(char archivoMesas[], int numHorario);  /// FUNC 8 PARA TRAER EL HORARIO
int buscarNumHorario(); /// FUNC 9 PARA BUBSCAR EL I DE LA MATRIZ HORARIO
int buscarMesa (char archivo[], int cantPersonas, int numHorario);   /// FUNC 10 PARA VER EL NUM DE LA MESA
void mostrarReservas (char archivo[]); /// FUNC 11 PARA MOSTRAR ARCHIVO RESERVA
void modificarReserva (char archivoReservas[], int numReserva, char archivoMesas[], stUSUARIO cliente);    /// FUNC 12 PARA MODIFICAR UNA RESERVA
void mostrarReservasPorUsuario (char archivoReservs[], stUSUARIO usuarioRegistrado);  /// FUNC 13 PARA MOSTRAR RESERVAS X USUARIO
int pasarArchivoUsuariosAArreglo (char archivoUsuarios[], stUSUARIO arreglo[]);  /// FUNC 14 PARA PASAR LOS USUARIOS A UN ARREGLO
void ordenarUsuarios (stUSUARIO arreglo[], int validos);  /// FUNC 15 PARA ORDENAR EL ARREGLO
int posicionMenor (stUSUARIO arreglo[], int posInicioBusqueda, int cantidad);   /// FUNC 16 PARA BUSCAR LA POSICION MENOR DEL ARREGLO USUARIOS
void mostrarArregloUsuarios (stUSUARIO arreglo[], int validos);  /// FUNC 17 PARA MOSTRAR EL ARREGLO DE USUARIOS
void pasarArregloAArchivo (stUSUARIO arreglo[], int validos, char archivo[]);   /// FUNC 18 PARA PASAR EL ARR ORDENADO AL ARCHIVO USUARIOS
void guardarNumMesasEnPila (char archivo[], Pila*pilaMesas);  /// FUNC 19 PARA APILAR LOS NUMEROS DE MESA
void mostrarMesasReservadas (Pila pilaMesas); /// FUNC 20 PARA MOSTRAR LOS DATOS DE LA PILA
void vaciarPila (Pila*pilaMesas); /// FUNC 21 PARA VACIAR LA PILA
int contarElementos (char archivo[], int tamanioDato);  /// FUNC 22 PARA CONTAR LA CANTIDAD DE DATOS EN EL ARCHIVO
void pasarArchivoReservas (char archivo[], stRESERVA **arreglo, int cantDatos, int numReserva, char archivoMesas[], stUSUARIO cliente);      /// FUNC 23 PARA PASAR EL ARCHIVO RESERVAS AL ARREGLO
void mostrarArregloReservas (stRESERVA **arreglo, int validos);  /// FUNC 24 PARA MOSTRAR EL ARREGLO DE RESERVAS
void modificarMatriz (char archivo[], float horarioAnterior, int numMesa);   /// FUNC 25 PARA VOLVER 0 LA MATRIZ
int buscarIHorario (float horario); /// FUNC 26 PARA BUSCAR EL SUBINCIDE DE LA MATRIZ
void eliminarRegistroDelArreglo (stRESERVA **arreglo, stUSUARIO clienteReserva, int *validos, int datoACancelar);    /// FUNC 27 PARA ELIMINAR UN REGISTRO DEL ARREGLO RESERVAS
void cambiarTamanio (stRESERVA **arreglo, int validos);  /// FUNC 28 PARA CAMBIAR EL TAMAÑO DEL ARRAY
float traerHorario (char archivo[], stUSUARIO cliente, int numReserva, int *numMesa);    /// FUNC 29 PARA RETORNAR EL HORARIO
void reEscribirArchivoReservas (char archivoReservas[], stRESERVA**arreglo, int validos);   /// FUNC 30 PARA GAURDAR LAS RESRVAS SIN LA CANCLADA
/// ------------------------------------------------------------PROTOTIPADO------------------------------------------------------------///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// --------------------------------------------------------------FUNCIONES--------------------------------------------------------------///
int main()
{
    srand(time(NULL));
    /// ARCHIVOS:
    char archivoMesas[]= {"archivoMesas.bin"};
    char archivoClientes[]= {"archivoClientes.bin"};
    char archivoReservas[]= {"archivoReservas.bin"};

    /// ARREGLOS:
    stUSUARIO arregloUsuarios[1000];
    int usuariosValidos=pasarArchivoUsuariosAArreglo (archivoClientes, arregloUsuarios);
    ordenarUsuarios(arregloUsuarios,usuariosValidos);
    pasarArregloAArchivo (arregloUsuarios, usuariosValidos, archivoClientes);

    /// PILA:
    Pila pilaMesasOcupadas;
    inicpila(&pilaMesasOcupadas);

    /// VARIABLES PARA LA SELECCION:
    int seleccion1;
    int seleccion11;
    int seleccion2;
    int seleccion22;
    do
    {
        system("cls");
        printf("¡Bienvenidos al restaurante!\n");
        printf("1. Entrar en modo usuario.\n");
        printf("2. Entrar en modo cliente.\n");
        printf("0. Salir.\n");
        printf("Seleccione una opcion para comenzar: ");
        fflush(stdin);
        scanf("%i", &seleccion1);
        switch(seleccion1)
        {
        case 1:
            do
            {
                system("cls");

                printf("1. Cargar mesas.\n"); //1.1
                printf("2. Mostrar mesas.\n"); //1.2
                printf("3. Mostrar reservas.\n"); //1.3
                printf("4. Mostrar totalidad de clientes.\n"); //1.4
                printf("5. Mostrar mesas reservadas.\n"); //1.5
                printf("0. Volver al menu principal.\n");
                printf("Seleccione una opcion para comenzar: ");
                fflush(stdin);
                scanf("%i", &seleccion11);
                switch (seleccion11)
                {
                case 1:
                    system("cls");
                    printf("1. Cargar mesas.\n");
                    //crearArchivoMesas(archivoMesas);
                    /// FUNCION PARA CARGAR MESAS EN EL ARCHIVO
                    printf("Mesas cargadas correctamente!.\n");
                    system("pause");
                    break;

                case 2:
                    system("cls");
                    printf("2. Mostrar mesas.\n"); //1.2
                    /// FUNCION PARA MOSTRAR LAS MESAS DEL ARCHIVO --> ORDENADAS X CANT DE PERSONAS
                    mostrarArchivoMesas(archivoMesas);
                    system("pause");
                    break;

                case 3:
                    system("cls");
                    printf("3. Mostrar reservas.\n"); //1.3
                    /// FUNCION PARA MOSTRAR LAS RESERVAS DEL ARCHIVO
                    mostrarReservas (archivoReservas);
                    system("pause");
                    break;

                case 4:
                    system("cls");
                    printf("4. Mostrar totalidad de clientes.\n"); //1.4
                    /// FUNCION PARA MOSTRAR EL ARCHIVO CLIENTES ---> ORDENADOS ALFABETICAMNETE
                    mostrarArchivoClientes(archivoClientes); /// FUNC PARA OSTRAR EL ARCHIVO CLIENTES
                    system("pause");
                    break;

                case 5:
                    system("cls");
                    printf("5. Mostrar mesas reservadas.\n"); //1.5
                    /// FUNCION PARA MOSTRAR LA PILA DE MESAS RESERVADAS
                    vaciarPila (&pilaMesasOcupadas);
                    guardarNumMesasEnPila (archivoReservas, &pilaMesasOcupadas);
                    printf("Mesas reservadas:\n");
                    mostrarMesasReservadas(pilaMesasOcupadas);
                    system("pause");

               default:
                    printf("\nVolviendo al menu principal\n");
                    system("pause");
                    break;
                }
            }
            while(seleccion11!=0);
            break;

        case 2:
            do
            {
                system("cls");
                printf("1. Registrarse.\n"); //1.1
                printf("2. Iniciar sesion.\n"); //1.2
                printf("0. Volver al menu principal.\n");
                printf("Seleccione una opcion para comenzar: ");
                fflush(stdin);
                scanf("%i", &seleccion2);
                switch(seleccion2)
                {
                case 1:
                    system("cls");
                    printf("1. Registrarse.\n"); //1.1
                    /// FUNCION PARA CREAR UN USUARIO EN EL ARCHIVO USUARIO
                    registrarUsuario (archivoClientes);
                    system("pause");
                    break;

                case 2:
                    system("cls");
                    printf("2. Iniciar sesion.\n"); //1.2
                    /// FUNCION PARA VERIFICAR QUE EL USUARIO SE ENCUNETRE EN EL ARCHIVO
                    int verificacion=0;
                    stUSUARIO usuarioRegistrado=iniciarSesion(archivoClientes, &verificacion);
                    if (verificacion==1)
                    {
                        do
                        {
                            system("cls");
                            printf("Bienvenido/a %s\n", usuarioRegistrado.cliente.nombre);
                            printf("1. Crear una reserva.\n");
                            printf("2. Mostrar reserva.\n");
                            printf("3. Modificar reserva.\n");
                            printf("4. Cancelar reserva.\n");
                            printf("0. Salir.\n");
                            fflush(stdin);
                            scanf("%i", &seleccion22);
                            switch(seleccion22)
                            {
                            case 1:
                                system("cls");
                                printf("1. Crear una reserva.\n");
                                /// FUNCION PARA CREAR UNA RESERVA AL ARCHIVO
                                crearReserva(archivoReservas,archivoMesas,usuarioRegistrado);
                                system("pause");
                                break;

                            case 2:
                                system("cls");
                                printf("2. Mostrar reserva.\n");
                                /// FUNCION PARA MOSTRAR LA RESERVA DEL CLIENTE
                                mostrarReservasPorUsuario (archivoReservas, usuarioRegistrado);
                                system("pause");
                                break;

                            case 3:
                                system("cls");
                                printf("3. Modificar reserva.\n");
                                /// FUNCION PARA MODIFICAR LA RESERVA DEL CLIENTE
                                mostrarReservas(archivoReservas);
                                printf("Ingrese el num de reserva a modificar: ");
                                fflush(stdin);
                                int numReserva;
                                scanf("%i", &numReserva);
                                modificarReserva (archivoReservas, numReserva, archivoMesas,usuarioRegistrado);
                                system("pause");
                                break;

                            case 4:
                                system("cls");
                                printf("4. Cancelar reserva.\n");
                                /// FUNCION PARA CANCELAR LA RESERVA DEL CLIENTE
                                int cantReservas=contarElementos (archivoReservas, sizeof(stRESERVA));
                                //printf("cant de reservas antes: %i\n\n\n" , cantReservas);
                                stRESERVA *arregloReservas=(stRESERVA*)malloc(sizeof(stRESERVA)*cantReservas);
                                mostrarReservasPorUsuario (archivoReservas, usuarioRegistrado);
                                printf("Ingrese el num de reserva a cancelar: ");
                                fflush(stdin);
                                int numReserva2;
                                scanf("%i", &numReserva2);
                                pasarArchivoReservas (archivoReservas, &arregloReservas, cantReservas,numReserva2,archivoMesas,usuarioRegistrado);
                                eliminarRegistroDelArreglo(&arregloReservas,usuarioRegistrado,&cantReservas,numReserva2-1);
                                cambiarTamanio(&arregloReservas,cantReservas);
                                //printf("\n\n\ncant de reservas despues: %i\n\n\n" , cantReservas);
//                                printf("\n nuevo arreglo: \n");
//                                mostrarArregloReservas(&arregloReservas,cantReservas);
                                reEscribirArchivoReservas (archivoReservas, &arregloReservas, cantReservas);


                                system("pause");
                                break;

                            default:
                    printf("\nVolviendo al menu\n");
                    system("pause");
                    break;
                            }
                        }
                        while (seleccion22!=0);
                    }
                    else
                    {
                        printf("Usuario no encontrado.\n");
                        seleccion2=0;
                    }

                    break;
                default:
                    printf("\nVolviendo al menu principal\n");
                    system("pause");
                    break;

                }
            }
            while (seleccion2!=0);
            break;

        default:
            printf("\nSaliendo del sistema...\n");

            break;
        }
    }
    while (seleccion1!=0);
    return 0;
}

void crearArchivoMesas (char archivo[]) /// 1 FUNC PARA CREAR EL ARCHIVO DE MESAS
{
    srand(time(NULL));
    stMESAS nueva;
    FILE*archi=fopen(archivo,"wb");
    if (archi!=NULL)
    {
        for (int i=1; i!=31; i++)
        {
            nueva.numeroDeMesa=i;
            int num=1;
            //generarNunPar(num);
            while(num%2!=0 || num==0)
            {
                num=rand()%15;
            }
            nueva.capacidad=num;
            generarMatrizMesa(nueva.disponible, 21);
            fwrite(&nueva,sizeof(stMESAS),1,archi);
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo\n");
}

void generarMatrizMesa(float matriz[][2], int filas) /// 2 FUNC PARA GENERAR LA MATRIZ
{
    float valores[21][2] =
    {
        {12.00, 0}, {12.30, 0}, {13.00, 0}, {13.30, 0}, {14.00, 0}, {14.30, 0},
        {15.00, 0}, {15.30, 0}, {16.00, 0}, {16.30, 0}, {17.00, 0}, {17.30, 0},
        {18.00, 0}, {18.30, 0}, {19.00, 0}, {19.30, 0}, {20.00, 0}, {20.30, 0},
        {21.00, 0}, {21.30, 0}, {22.00, 0}
    };

    // Copiar los valores a la matriz pasada como parámetro
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matriz[i][j] = valores[i][j];
        }
    }
}

void registrarUsuario (char archivo[]) /// FUNC 3 PARA CREAR UN USUARIO AL ARCHIVO
{
    stUSUARIO nuevo;
    FILE *archi=fopen(archivo,"ab");
    if (archi!=NULL)
    {
        printf("Ingrese su nombre y apellido: ");
        fflush(stdin);
        gets (&nuevo.cliente.nombre);
        printf("Ingrese su numero de telefono: ");
        fflush(stdin);
        //scanf("%i", &nuevo.cliente.telefono);
        gets(&nuevo.cliente.telefono);
        printf("Ingrese un nombre de usuario: ");
        fflush(stdin);
        gets(&nuevo.usuario);
        printf("Ingrese una contrtaseña: ");
        fflush(stdin);
        gets(&nuevo.contrasena);
        fwrite(&nuevo,sizeof(stUSUARIO),1,archi);
        printf("Usuario registrado con exito!\n");
        fclose(archi);
    }
}

stUSUARIO iniciarSesion (char archivo[], int *verificacion)  /// FUNC 4 PARA VERIFICAR SI EL CLIENTE SE REGISTRO Y PUEDA INICIAR SESION
{
    printf("Ingrese su usuario: ");
    char usuario[100];
    fflush(stdin);
    gets(&usuario);
    printf("Ingrese su contraseña: ");
    char contrasenia[100];
    fflush(stdin);
    gets(&contrasenia);
    stUSUARIO aux;
    FILE*archi=fopen(archivo,"rb");
    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(stUSUARIO),1,archi)>0 && (*verificacion==0))
        {
            if(strcmp(aux.usuario,usuario)==0 && strcmp(aux.contrasena,contrasenia)==0)
            {
                (*verificacion)=1;
                fseek(archi,sizeof(stUSUARIO)*(-1),SEEK_CUR);

            }
        }
        fclose(archi);
    }
    return aux;
}

void mostrarArchivoClientes(char archivo[]) /// FUNC 5 PARA OSTRAR EL ARCHIVO CLIENTES
{
    stUSUARIO aux;
    FILE*archi=fopen(archivo,"rb");
    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(stUSUARIO),1,archi)>0)
        {
            printf("Nombre y apellido: %s\n", aux.cliente.nombre);

            printf("Numero de telefono: %s\n", aux.cliente.telefono);

            printf("Nombre de usuario: %s\n", aux.usuario);

            printf("Contrtaseña: %s\n", aux.contrasena);
            puts("\n");
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo.\n");
}

void mostrarArchivoMesas(char archivo[]) /// FUNC 6 PARA MOSTRAR EL ARCHIVO MESAS
{
    FILE *archi = fopen(archivo, "rb");
    if (archi != NULL)
    {
        stMESAS mesa;
        while (fread(&mesa, sizeof(stMESAS), 1, archi) > 0)
        {
            printf("Numero de Mesa: %i\n", mesa.numeroDeMesa);
            printf("Capacidad: %i\n", mesa.capacidad);
            printf("Disponibilidad:\n");
            for (int i = 0; i < 21; i++)
            {
                printf("  Hora: %.2f - Disponible: %.0f\n", mesa.disponible[i][0], mesa.disponible[i][1]);
            }
            printf("\n");
        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo\n");
    }
}

void crearReserva (char archivoReserva[], char archivoMesas[], stUSUARIO cliente )   /// FUNC 7 PARA CREAR LA RESERVA
{
    stRESERVA nueva;
    stMESAS aux;
    FILE*archi=fopen(archivoReserva,"ab");
    if (archi!=NULL)
    {
        //strcpy(nueva.cliente,cliente);
        nueva.cliente=cliente;
        printf("Ingrese la fecha de la reserva (DD/MM/AAAA): ");
        fflush(stdin);
        gets(&nueva.Fecha);
        printf("Ingrese la cantidad de personas (ingrese un numero par): ");
        fflush(stdin);
        scanf("%i", &nueva.cantidadPersonas);
        int numIHorario= buscarNumHorario();
        int numMesa=buscarMesa (archivoMesas, nueva.cantidadPersonas, numIHorario);
        if(numMesa == -1)
        {
            printf("No hay mesas disponibles. \n");
        }
        else
        {
            nueva.numMesa = numMesa;

            float horarioDeReserva=horarioReserva(archivoMesas, numIHorario);

            nueva.Horario=horarioDeReserva;

            fwrite(&nueva,sizeof(stRESERVA),1,archi);
        }
        printf("Reserva guardada!\n");
        fclose(archi);
    }
}

float horarioReserva(char archivoMesas[], int numHorario)  /// FUNC 8 PARA TRAER EL HORARIO
{
    stMESAS aux;
    FILE*archi=fopen(archivoMesas,"rb");
    if (archi!=NULL)
    {
        fread(&aux,sizeof(stMESAS),1,archi);
        fclose(archi);
    }
    return aux.disponible[numHorario][0];
}

int buscarNumHorario() /// FUNC 9 PARA BUBSCAR EL I DE LA MATRIZ HORARIO
{

    int numHorario;
    printf("0. 12:00\n");
    printf("1. 12:30\n");
    printf("2. 13:00\n");
    printf("3. 13:30\n");
    printf("4. 14:00\n");
    printf("5. 14:30\n");
    printf("6. 15:00\n");
    printf("7. 15:30\n");
    printf("8. 16:00\n");
    printf("9. 16:30\n");
    printf("10. 17:00\n");
    printf("11. 17:30\n");
    printf("12. 18:00\n");
    printf("13. 18:30\n");
    printf("14. 19:00\n");
    printf("15. 19:30\n");
    printf("16. 20:00\n");
    printf("17. 20:30\n");
    printf("18. 21:00\n");
    printf("19. 21:30\n");
    printf("20. 22:00\n");
    do
    {
         printf("Ingrese el horario de la reserva: ");
    fflush(stdin);
    scanf("%i", &numHorario);
    if (numHorario>20 || numHorario<0)
    {
        printf("Numero invalido. Intente otra vez.\n");
    }
    } while(numHorario>20 || numHorario<0);


    return numHorario;
}

int buscarMesa (char archivo[], int cantPersonas, int numHorario)   /// FUNC 10 PARA VER EL NUM DE LA MESA
{
    int numMesa=-1;
    int seguir=0;
    stMESAS aux;
    FILE*archi=fopen(archivo,"r+b");
    if (archi!=NULL)
    {
        //fseek(archi,0,SEEK_SET);
        while (fread(&aux, sizeof(stMESAS),1,archi)>0 && seguir==0)
        {
            if (aux.capacidad==cantPersonas && aux.disponible[numHorario][1]==0.00)
            {
                aux.disponible[numHorario][1]=1.00;
                fseek(archi, -sizeof(stMESAS), SEEK_CUR);
                fwrite(&aux, sizeof(stMESAS), 1, archi);
                numMesa=aux.numeroDeMesa;
                seguir=1;
            }
        }
        fclose(archi);
    }
    return numMesa;
}

void mostrarReservas (char archivo[]) /// FUNC 11 PARA MOSTRAR ARCHIVO RESERVA
{
    int i=1;
    stRESERVA aux;
    FILE*archi=fopen(archivo,"rb");
    if (archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&aux,sizeof(stRESERVA),1,archi);
            if (!feof(archi))
            {
                printf("Reserva numero %i\n", i);
                printf("nombre y apellido: %s\n", aux.cliente.cliente.nombre);
                printf("Num de mesa: %i\n", aux.numMesa);
                printf("Fecha: %s\n", aux.Fecha);
                printf("Horario: %.2f\n", aux.Horario);
                printf("Cantidad de personas: %i\n", aux.cantidadPersonas);
                i++;
                puts("\n");
            }
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo\n");

}

void modificarReserva (char archivoReservas[], int numReserva, char archivoMesas[], stUSUARIO cliente)    /// FUNC 12 PARA MODIFICAR UNA RESERVA
{
    stRESERVA aux;
    char seguir='n';
    FILE*archi=fopen(archivoReservas,"r+b");
    if (archi!=NULL)
    {
        int numReservaAnterior=numReserva-1;
        fseek(archi,sizeof(stRESERVA)*numReservaAnterior,SEEK_SET);
        fread(&aux,sizeof(stRESERVA),1,archi);
        if (strcmpi(cliente.cliente.nombre,aux.cliente.cliente.nombre)==0)
        {
            aux.cliente=cliente;
            printf("Desea mdificar la fecha de la reserva (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
            if (seguir=='s')
            {
                printf("Ingrese la fecha de la reserva (DD/MM/AAAA): ");
                fflush(stdin);
                gets(&aux.Fecha);
            }
            seguir='n';
            printf("Desea modificar la cantidad de personas de la reserva? (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
            if (seguir=='s')
            {
                modificarMatriz(archivoMesas,aux.Horario,aux.numMesa);
                printf("Ingrese la cantidad de personas: ");
                fflush(stdin);
                scanf("%i", &aux.cantidadPersonas);
            }
            seguir='n';
            int numIHorario= buscarIHorario(aux.Horario);
            printf("Desea modificar el horario de la reserva? (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
            if (seguir=='s')
            {
                modificarMatriz (archivoMesas, aux.Horario, aux.numMesa);
                numIHorario=buscarNumHorario();
            }
            aux.numMesa= buscarMesa (archivoMesas, aux.cantidadPersonas, numIHorario);
            float horarioDeReserva=horarioReserva(archivoMesas, numIHorario);
            aux.Horario=horarioDeReserva;
            fseek(archi,sizeof(stRESERVA)*numReservaAnterior,SEEK_SET);
            fwrite(&aux, sizeof(stRESERVA),1,archi);
            printf("Reserva modificada con exito!\n");
            fclose(archi);
        }
        else
            printf("No puede modificar la reserva de otro usuario.\n");
    }
}

void mostrarReservasPorUsuario (char archivoReservs[], stUSUARIO usuarioRegistrado)  /// FUNC 13 PARA MOSTRAR RESERVAS X USUARIO
{
    int i=1;
    stRESERVA aux;
    FILE*archi=fopen(archivoReservs,"rb");
    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(stRESERVA),1,archi)>0)
        {
            if (strcmp(aux.cliente.cliente.nombre,usuarioRegistrado.cliente.nombre)==0)
            {
                printf("Reserva numero %i\n", i);
                printf("Nombre y apellido: %s\n", aux.cliente.cliente.nombre);
                printf("Num de mesa: %i\n", aux.numMesa);
                printf("Fecha: %s\n", aux.Fecha);
                printf("Horario: %.2f\n", aux.Horario);
                printf("Cantidad de personas: %i\n", aux.cantidadPersonas);
                puts("\n");
                i++;
            }
        }
        fclose(archi);
    }
}

void modificarMesa (char archivo[]) /// func para modificar datos de mesas asignadas
{
    stMESAS aux;
    FILE*archi=fopen(archivo,"r+b");
    if (archi!=NULL)
    {
        fseek(archi,sizeof(stMESAS)*9,SEEK_SET);
        fread(&aux,sizeof(stMESAS),1,archi);
        aux.numeroDeMesa=10;
        //aux.capacidad=2;
        fseek(archi,sizeof(stMESAS)*9,SEEK_SET);
        fwrite(&aux,sizeof(stMESAS),1,archi);

        fseek(archi,sizeof(stMESAS)*3,SEEK_SET);
        fread(&aux,sizeof(stMESAS),1,archi);
        aux.numeroDeMesa=4;
        //aux.capacidad=2;
        fseek(archi,sizeof(stMESAS)*3,SEEK_SET);
        fwrite(&aux,sizeof(stMESAS),1,archi);

//        fseek(archi,sizeof(stMESAS)*8,SEEK_SET);
//        fread(&aux,sizeof(stMESAS),1,archi);
//        aux.numeroDeMesa=9;
//        //aux.capacidad=2;
//        fseek(archi,sizeof(stMESAS)*8,SEEK_SET);
//        fwrite(&aux,sizeof(stMESAS),1,archi);
//
//        fseek(archi,sizeof(stMESAS)*14,SEEK_SET);
//        fread(&aux,sizeof(stMESAS),1,archi);
//        aux.numeroDeMesa=15;
//        //aux.capacidad=2;
//        fseek(archi,sizeof(stMESAS)*14,SEEK_SET);
//        fwrite(&aux,sizeof(stMESAS),1,archi);

        fclose(archi);
    }
}

int pasarArchivoUsuariosAArreglo (char archivoUsuarios[], stUSUARIO arreglo[])  /// FUNC 14 PARA PASAR LOS USUARIOS A UN ARREGLO
{
    //stUSUARIO arreglo[1000];
    int i=0;
    stUSUARIO aux;
    int cantDeUsuarios;
    FILE*archi=fopen(archivoUsuarios,"rb");
    if (archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cantDeUsuarios=ftell(archi)/sizeof(stUSUARIO);
        fseek(archi,0,SEEK_SET);
        for (i=0; i<cantDeUsuarios; i++)
        {
            fread(&aux,sizeof(stUSUARIO),1,archi);
            arreglo[i]=aux;
        }
        fclose(archi);
    }
    return i;
}

void ordenarUsuarios (stUSUARIO arreglo[], int validos)  /// FUNC 15 PARA ORDENAR EL ARREGLO
{
    int posMenor;
    stUSUARIO aux;
    int i = 0;
    while (i<validos-1) ///el arreglo empieza con valor 0
    {
        posMenor = posicionMenor (arreglo, i, validos);   ///llamo a la funcion que me permite saber cual es la posicion del menor valor
        aux = arreglo[posMenor]; ///en la variante aux guardo el valor menor
        arreglo[posMenor] = arreglo[i]; ///en la posicion donde esta el menor guardo el valor de la posicion i
        arreglo[i] = aux; /// en la posicion i guardo el valor de aux (el valor menor)
        i++;
    }
}

int posicionMenor (stUSUARIO arreglo[], int posInicioBusqueda, int cantidad)   /// FUNC 16 PARA BUSCAR LA POSICION MENOR DEL ARREGLO USUARIOS
{
    stUSUARIO menor = arreglo[posInicioBusqueda]; ///guardo en la variable el valor que se encuentra al inicio de la busqueda
    int posmenor = posInicioBusqueda; /// guardo en la variable la posicion donde empiezo a buscar
    int i=posInicioBusqueda+1; /// en i uso un valor mas del inicio
    while (i<cantidad)
    {
        //strcmp(menor.nombre,arregloTareas[posicionInicial].nombre) > 0
        if (strcmpi(menor.cliente.nombre,arreglo[i].cliente.nombre)>0) /// si lo que tengo guardado en menor es mayor al siguiente entro
        {
            menor=arreglo[i]; /// guardo en la variable menor el dato
            posmenor=i; /// guardo en la variable la posicion menor
        }
        i++;
    }
    return posmenor;
}

void mostrarArregloUsuarios (stUSUARIO arreglo[], int validos)  /// FUNC 17 PARA MOSTRAR EL ARREGLO DE USUARIOS
{
    for (int i=0; i<validos; i++)
    {
        printf("Usuario %i\n", i+1);
        printf("Nombre y apellido: %s\n", arreglo[i].cliente.nombre);

        printf("Numero de telefono: %s\n", arreglo[i].cliente.telefono);

        printf("Nombre de usuario: %s\n", arreglo[i].usuario);

        printf("Contrtaseña: %s\n", arreglo[i].contrasena);
        puts("\n");
    }
}

void pasarArregloAArchivo (stUSUARIO arreglo[], int validos, char archivo[])   /// FUNC 18 PARA PASAR EL ARR ORDENADO AL ARCHIVO USUARIOS
{
    FILE*archi=fopen(archivo,"wb");
    if (archi!=NULL)
    {
        stUSUARIO aux;
        for (int i=0; i<validos; i++)
        {
            aux=arreglo[i];
            fwrite(&aux,sizeof(stUSUARIO),1,archi);
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo.");
}

void guardarNumMesasEnPila (char archivo[], Pila*pilaMesas)  /// FUNC 19 PARA APILAR LOS NUMEROS DE MESA
{
    stRESERVA aux;
    FILE*archi=fopen(archivo,"rb");
    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(stRESERVA),1,archi)>0)
        {
            apilar(pilaMesas,aux.numMesa);
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo.\n");
}

void mostrarMesasReservadas (Pila pilaMesas) /// FUNC 20 PARA MOSTRAR LOS DATOS DE LA PILA
{
    Pila aux;
    inicpila(&aux);
    int i=1;
    while(!pilavacia(&pilaMesas))
    {
        apilar(&aux,desapilar(&pilaMesas));

    }
    while(!pilavacia(&aux))
    {
        printf("%i° mesa reservada: %i\n", i, tope(&aux));
        apilar(&pilaMesas,desapilar(&aux));
        i++;
    }
}

void vaciarPila (Pila*pilaMesas) /// FUNC 21 PARA VACIAR LA PILA
{
    while(!pilavacia(pilaMesas))
    {
        desapilar(pilaMesas);
    }
}

int contarElementos (char archivo[], int tamanioDato)  /// FUNC 22 PARA CONTAR LA CANTIDAD DE DATOS EN EL ARCHIVO
{
    int cantDatos;
    FILE*archi=fopen(archivo,"rb");
    if (archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cantDatos=ftell(archi)/tamanioDato;
        fclose(archi);
    }
    return cantDatos;
}

void pasarArchivoReservas (char archivo[], stRESERVA **arreglo, int cantDatos, int numReserva, char archivoMesas[], stUSUARIO cliente)      /// FUNC 23 PARA PASAR EL ARCHIVO RESERVAS AL ARREGLO
{
    int numMesa=0;
    float horReserva;
    horReserva=traerHorario(archivo,cliente,numReserva,&numMesa);
    stRESERVA aux;
    int i=0;
    FILE*archi=fopen(archivo,"rb");
    if (archi!=NULL)
    {
        //fseek(archi,0,SEEK_SET);
        while(fread(&aux,sizeof(stRESERVA),1,archi)>0)
        {
            (*arreglo)[i]=aux;
            i++;
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo.\n");

    modificarMatriz(archivoMesas,horReserva,numMesa);
}

void mostrarArregloReservas (stRESERVA **arreglo, int validos)  /// FUNC 24 PARA MOSTRAR EL ARREGLO DE RESERVAS
{
    for (int i=0; i<validos; i++)
    {
        printf("Reserva numero %i\n", i+1);
        printf("Nombre y apellido: %s\n", (*arreglo)[i].cliente.cliente.nombre);
        printf("Num de mesa: %i\n", (*arreglo)[i].numMesa);
        printf("Fecha: %s\n", (*arreglo)[i].Fecha);
        printf("Horario: %.2f\n", (*arreglo)[i].Horario);
        printf("Cantidad de personas: %i\n", (*arreglo)[i].cantidadPersonas);
        puts("\n");
    }
}

void modificarMatriz (char archivo[], float horarioAnterior, int numMesa)   /// FUNC 25 PARA VOLVER 0 LA MATRIZ
{
    stMESAS aux;
    FILE* archi = fopen(archivo, "r+b");
    if (archi != NULL)
    {
        while (fread(&aux, sizeof(stMESAS), 1, archi) > 0)
        {
            if (aux.numeroDeMesa == numMesa)
            {
                for (int i = 0; i < 21; i++)
                {
                    if (aux.disponible[i][0] == horarioAnterior)
                    {
                        aux.disponible[i][1] = 0.00;
                        //printf("Horario anterior eliminado: %.2f!\n", horarioAnterior);
                    }
                }
                fseek(archi, -sizeof(stMESAS), SEEK_CUR);
                fwrite(&aux, sizeof(stMESAS), 1, archi);
                break;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

int buscarIHorario (float horario) /// FUNC 26 PARA BUSCAR EL SUBINCIDE DE LA MATRIZ
{
    int posicion;
    float arreglo[21]= {12.00, 12.30, 13.00, 13.30, 14.00, 14.30, 15.00, 15.30, 16.00, 16.30, 17.00, 17.30, 18.00, 18.30, 19.00, 19.30, 20.00, 20.30, 21.00, 21.30, 22.00};
    for (int i=0; i<21; i++)
    {
        if (horario==arreglo[i])
        {
            posicion=i;
        }
    }
    return posicion;
}

void eliminarRegistroDelArreglo (stRESERVA **arreglo, stUSUARIO clienteReserva, int *validos, int datoACancelar)    /// FUNC 27 PARA ELIMINAR UN REGISTRO DEL ARREGLO RESERVAS
{
    int j=0;
    int i=0;
    int flag=0;
    while (i < (*validos) && flag == 0)
    {
        if (strcmp((*arreglo)[i].cliente.cliente.nombre, clienteReserva.cliente.nombre) == 0)
        {
            while(j==datoACancelar && flag==0)
            {
                printf("Reserva encontrada!\n");
                (*arreglo)[i]=(*arreglo)[i+1];
                flag=1;
                printf("Reserva cancelada!\n");
            }
            j++;
        }
        i++;
    }
    while(i<(*validos)-1)
    {
        (*arreglo)[i]=(*arreglo)[i+1];
        i++;
    }
    (*validos)--;
}

void cambiarTamanio (stRESERVA **arreglo, int validos)  /// FUNC 28 PARA CAMBIAR EL TAMAÑO DEL ARRAY
{
    stRESERVA *temp = realloc(*arreglo, sizeof(stRESERVA) * validos);
    if (temp != NULL)
    {
        *arreglo = temp;
        //free(temp);
    }
    else
    {
        printf("Error al redimensionar la memoria.\n");
    }
}

float traerHorario (char archivo[], stUSUARIO cliente, int numReserva, int *numMesa)    /// FUNC 29 PARA RETORNAR EL HORARIO
{
    stRESERVA aux;
    FILE*archi=fopen(archivo,"rb");
    int i=0;
    float horReserva;
    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(stRESERVA),1,archi)>0)
        {
            if (strcmpi(cliente.cliente.nombre,aux.cliente.cliente.nombre)==0)
            {
                i++;
                if (i==numReserva)
                {
                    horReserva=aux.Horario;
                    (*numMesa)=aux.numMesa;
//                int posicionHorario=buscarIHorario(aux.Horario);
//                horReserva=aux
                }
            }
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo\n");

    return horReserva;
}

void reEscribirArchivoReservas (char archivoReservas[], stRESERVA**arreglo, int validos)   /// FUNC 30 PARA GAURDAR LAS RESRVAS SIN LA CANCLADA
{
    stRESERVA aux;
    FILE*archi=fopen(archivoReservas,"wb");
    if (archi!=NULL)
    {
        for (int i=0; i<validos; i++)
        {
            aux=(*arreglo)[i];
            fwrite(&aux,sizeof(stRESERVA),1,archi);
        }
        fclose(archi);
    }
    else
        printf("Error al abrir el archivo.\n");
}

/// --------------------------------------------------------------FUNCIONES--------------------------------------------------------------///
