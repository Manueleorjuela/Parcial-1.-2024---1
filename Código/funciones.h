#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
using namespace std;

//Creacion de estructura de datos variable
int ** Crear_Matriz_Mecanicamente(int *& Dimension_Matriz, int Numero_Matriz);
void Crear_Elementos_Internos(int **& Matriz, int Dim);
void Eliminar_Matriz_Bidimensional(int **& Matriz, int Dim);
void Matriz_Estado_Neutro(int **& Matriz, int Dim);
void Mostrar_Matriz (int**& Matriz, int Dim);

//Rotaciones de las estructuras
void Matrices_Rotadas(int **&MatrizOriginal, int Dim);
void Matriz_Estado_1(int **& MatrizRotada, int **&MatrizOriginal, int Dim);
void Matriz_Estado_2(int **& MatrizRotada, int **&MatrizOriginal, int Dim);
void Matriz_Estado_3(int **& MatrizRotada, int **&MatrizOriginal, int Dim);

//CrearCerradurasDeTamañoVariable
void CrearCerradura();
void Imprimir_Matrices_Cerradura(int ***& X, int Tamano_Cerradura, int *& Dim_Matrices);

void Eliminar_Cerradura(int ***& X, int Tamano_Cerradura, int *&Dim_Matrices);

//Validaciones
int ValidarDimensionImpar();

#endif // FUNCIONES_H
