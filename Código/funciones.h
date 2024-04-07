#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <limits>
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
void Imprimir_Matrices_Cerradura(int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices, int *& Cerraduras_Rotadas);
void Eliminar_Cerradura(int ***& X, int &Tamano_Cerradura, int *&Dim_Matrices);

//Validar una regla sobre una Cerradura
void ValidarRegla_Sobre_Cerradura();
void Crear_Cerradura_Rotada(int ***& X, int & Tamano_Cerraduara, int *& Dim_Matrices, int *& Cerraduras_Rotadas, int *& Regla);
int *Crear_Regla( int& Tamano_Cerradura, int*& Dim_Matrices);
void CopiarMatriz(int **& Matriz_Rotada, int ** &Matriz_Original, int Dim);

//Crear_Una_Cerradura_A_Partir_De_Una_Regla
void Generar_Configuracion_Cerradura();
void Crear_Regla_Para_Generar_Cerradura(int*& Regla, int& Tamano);
int **Crear_Matriz_Automaticamente(int Dim);
int Dimension_Minima_Cerradura_Generada(int*& Regla);
void Modificar_Dimension_Cerradura(int*& Dim_Matrices, int Pos, int Condicion);

//Validaciones
int ValidarDimensionImpar();
int ValidarCondicionesRegla(int M1, int M2);
int ValidarTamanoMatrices(int Dim_Mayor, int Pos);
int Dimension_Menor(int *& Dim_Matrices, int Tamano_Cerradura);
void Validar_Impresion(bool Bandera, int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices, int *& Cerraduras_Rotadas);
bool Validacion_PosicionCentral(int** Estructura1, int **Estructura2, int Fila, int Col);
int Validar_Posicion_Regla_Para_Generar_Cerradura(int Pos);

//Almacenar TODAS las combinaciones posbiles donde se cumpla
int ***Combinaciones_Estructuras_Iniciales(int**& Estructura1, int**& Estructura2, int Fila, int Col, int Condicion, int Dim1, int Dim2, int***& Casos, int*&Respectivas_Rotaciones, int*&Respectivas_Dimensiones);
int ***Copiar_Datos_Casos_Posibles(int ***&Casos, int Dim1, int Dim2, int**& Estructura1, int**& Estructura2);
int *Copiar_Rotaciones_Posibles(int ***& Casos, int *&Rotaciones, int Cond1, int Cond2);
int *Copiar_Dimensiones_Posibles(int ***& Casos, int *&Dimensiones, int Dim1, int Dim2);
int Dimension_Casos_Posibles(int ***&Casos);

//Almacenar CASOS que tiene una matriz fija sobre otra
int ***Casos_Probables(int ***&Posibilidades, int**&Estructura1, int **&Estructura2, int Fila, int Col, int Condicion, int Dim2, int *& Dimensiones_Posibles);
int ***Copiar_Datos_Casos_Posibles_Fijo(int***&Posibilidades, int *Dimensiones, int **Estructura, int Dim_Añadir);
int *Copiar_Dimensiones_Posibles_Fijas(int ***& Posibilidades, int *&Dimensiones, int Dim);
int** Evaluar_Posibilidades(int **& Matriz_Guardar, int***& Posibilidades, int Tamano, int Condicion_Siguiente, int Dimension, int Fila, int Col);

#endif // FUNCIONES_H
