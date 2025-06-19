# Trabajo Final - Programación I (UTN - FRMDP)

Este proyecto corresponde al Trabajo Práctico Final de la materia Programación I de la UTN. El objetivo es aplicar los conocimientos adquiridos durante la cursada en el desarrollo de un sistema que utilice estructuras de datos, archivos binarios y esté correctamente modularizado.

## Descripción del sistema

El sistema desarrollado permite la gestión de reservas de mesas en un restaurante. Incluye funcionalidades como:

• Registro e inicio de sesión de usuarios.

• Alta de reservas (fecha, horario, cantidad de personas).

• Asignación automática de mesas disponibles.

• Consulta y modificación de reservas.

• Listado general y por usuario.

## Estructuras de datos utilizadas

El sistema utiliza las siguientes estructuras:

• stCLIENTE: Datos personales del cliente (nombre y teléfono).

• stUSUARIO: Usuario y contraseña + cliente asociado.

• stRESERVA: Reserva realizada (usuario, mesa, fecha, horario, cantidad).

• stMESAS: Definición de mesas y matriz de disponibilidad (21x2).

## Estructuras de programación aplicadas

• Pila: utilizada mediante pila.c y pila.h.

• Arreglo dinámico: para almacenar usuarios.

• Arreglo estático: utilizado para manipulación de registros.

• Matriz: disponibilidad de mesas por horario.

• Strings: para entrada de datos y nombres.

## Compilación y ejecución

Puedes compilar el proyecto con GCC:

```bash
   gcc main.c pila.c -o reservas
./reservas
   ```

O utilizar el entorno de desarrollo Code::Blocks, ya que incluye el archivo _trabajoPracticoFinal.cbp._

## Autores

Trabajo realizado por estudiantes de la UTN - FRMDP como parte del final de Programación I. El proyecto fue desarrollado en equipo como ejercicio de integración de conocimientos.
