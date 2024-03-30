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
int ** Matriz_Estado_1(int **& MatrizRotada, int **&MatrizOriginal, int Dim);
int ** Matriz_Estado_2(int **& MatrizRotada, int **&MatrizOriginal, int Dim);
int ** Matriz_Estado_3(int **& MatrizRotada, int **&MatrizOriginal, int Dim);

//CrearCerradurasDeTamañoVariable
int ***CrearCerradura(int &Tamano_Cerradura, int *& Dim_Matrices);
void Imprimir_Matrices_Cerradura(int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices);
void Eliminar_Cerradura(int ***& X, int &Tamano_Cerradura, int *&Dim_Matrices);

//Validar una regla sobre una Cerradura
void ValidarRegla_Sobre_Cerradura();
void Crear_Cerradura_Rotada(int ***& X, int & Tamano_Cerraduara, int *& Dim_Matrices, int *& Cerraduras_Rotadas, int *& Regla);
int *Crear_Regla( int& Tamano_Cerradura, int*& Dim_Matrices);
int ** Comparacion_Estructuras(int **&Estructura1, int **& Estructura2, int **&Matriz_Rotada, int Fila, int Col, int Condicion, int Dim2);
void CopiarMatriz(int **& Matriz_Rotada, int **& Matriz_Original, int Dim);

//Validaciones
int ValidarDimensionImpar();
int ValidarCondicionesRegla(int M1, int M2);
int ValidarTamanoMatrices(int Dim_Mayor, int Pos);
int Dimension_Menor(int *& Dim_Matrices, int Tamano_Cerradura);

#endif // FUNCIONES_H
