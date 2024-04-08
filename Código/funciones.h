#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

//Creacion de estructura de datos variable
int ** Crear_Matriz_Mecanicamente(int *& Dimension_Matriz, int Numero_Matriz);
void Crear_Elementos_Internos(int **& Matriz, int Dim);
void Matriz_Estado_Neutro(int **& Matriz, int Dim);
void Mostrar_Matriz (int**& Matriz, int Dim);

//Rotaciones de las estructuras
int ** Matriz_Estado_1(int **& MatrizRotada, int **&MatrizOriginal, int Dim);
int ** Matriz_Estado_2(int **& MatrizRotada, int **&MatrizOriginal, int Dim);
int ** Matriz_Estado_3(int **& MatrizRotada, int **&MatrizOriginal, int Dim);

//CrearCerradurasDeTamañoVariableDeFormaManual
int ***CrearCerradura(int &Tamano_Cerradura, int *& Dim_Matrices);
void Imprimir_Matrices_Cerradura(int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices, int *& Cerraduras_Rotadas);

//Libreacion de Memoria
void Eliminar_Cerradura(int ***&X, int Tamano_Cerradura, int *&Dim_Matrices);
void Eliminar_Matriz_Bidimensional(int ** &Matriz, int Dim);

//Validar una regla sobre una CerraduraCreadaManualmente
void ValidarRegla_Sobre_Cerradura();
void Crear_Cerradura_Rotada(int ***& X, int & Tamano_Cerraduara, int *& Dim_Matrices, int *& Cerraduras_Rotadas, int *& Regla, bool& Bandera, int Si);
int *Crear_Regla( int& Tamano_Cerradura, int*& Dim_Matrices);
void CopiarMatriz(int **&Matriz_Rotada, int ** Matriz_Original, int Dim);
void Ubicacion_Celda(int Dim1, int Dim2, int Fila, int Col, int& filaEstructura, int& colEstructura, int& filaRotada, int& colRotada);
int Alineacion_Casos_Posibles(int Dim1, int Dim2);

//Validaciones
int ValidarDimensionImpar();
int ValidarCondicionesRegla(int M1, int M2);
int ValidarTamanoMatrices(int Dim_Mayor, int Pos);
int Dimension_Menor(int *& Dim_Matrices, int Tamano_Cerradura);
void Validar_Impresion(bool Bandera, int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices, int *& Cerraduras_Rotadas, int Si);
bool Validacion_PosicionCentral(int** Estructura1, int **Estructura2, int Fila, int Col);

//Almacenar CASOS posibles donde se cumple una condicion
int ***Casos_Probables(int ***&Posibilidades, int**&Estructura1, int **&Estructura2, int Fila, int Col, int Condicion, int Dim1, int Dim2, int *& Dimensiones_Posibles, int*& Rotaciones_Posibles);
int ***Copiar_Datos_Casos_Posibles_Fijo(int***&Posibilidades, int *Dimensiones, int **Estructura, int Dim_Añadir);
int *Copiar_Dimensiones_Posibles_Fijas(int ***& Posibilidades, int *&Dimensiones, int Dim);
int * Copiar_Rotaciones_Posibles_Fijas(int***& Posibilidades, int*& Rotaciones_Posibles, int Rotacion);
int** Evaluar_Posibilidades(int **& Matriz_Guardar, int***& Posibilidades, int Tamano, int Condicion_Siguiente, int Dimension, int Dim_Minima, int Fila, int Col, int*& R, int*& P, int Pos);
int Dimension_Casos_Posibles(int ***&Casos);

//Creacion de cerraduras a partir de una regla

//Regla
int *Crear_Regla_Para_Generar(int &Tamano_Cerradura);
void Generar_Cerradura_A_Partir_De_Una_Regla();
int Posiciones_Regla_Generada(int Pos);
int Condiciones_Regla_Generada(int M);

//Creacion Dimension De Matrices para una relga
int *Crear_Dimensiones_Regla(int Dimension_Mayor, int Tamano_Cerradura);
int Dimension_Dim_Matrices(int *&Regla);

//Creacion_Cerradura
int *** Cerradura_Regla(int Tamano_Cerradura, int *Dimensiones);
void Generar_Caso_Con_Numeros_Aleatorios(int *&Dimensiones, int Dim_Mayor, int Tamano);

//Para el Menu
void Menu();

#endif // FUNCIONES_H




