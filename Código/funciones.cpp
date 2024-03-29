#include "funciones.h"

int ** Crear_Matriz_Mecanicamente(int *&Dim_Matriz, int Numero_Matriz)
{
    int Dim =  ValidarDimensionImpar();
    int **Matriz =  new int*[Dim];
    Crear_Elementos_Internos(Matriz,Dim);
    Matriz_Estado_Neutro(Matriz, Dim);
    Dim_Matriz[Numero_Matriz] = Dim;
    return Matriz;
}

void Crear_Elementos_Internos(int **&Matriz, int Dim)
{
    for (int i = 0; i < Dim; i++){
        Matriz[i] = new int[Dim];
    }
}

void Eliminar_Matriz_Bidimensional(int **&Matriz, int Dim)
{
    for (int i = 0; i < Dim; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;
}


void Matriz_Estado_Neutro(int **&Matriz, int Dim)
{
    bool Bandera = false;
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            if (Bandera == 0){
                Matriz[i][k] = i*Dim + k + 1;
                if (i == Dim/2 && k == Dim/2) Matriz[i][k] = 0, Bandera = true;
            }
            else Matriz[i][k] = i*Dim + k;
        }
    }
}
void Mostrar_Matriz(int **& Matriz, int Dim)
{
    cout << endl;
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            printf("%3d ", Matriz[i][k]);
        }
        cout << endl;
    }
    cout << endl;
}

int ValidarDimensionImpar()
{
    int Dim;
    while (true){
        cout << "Ingrese la dimension de la matriz, recuerde que debe ser impar: "; cin >> Dim;
        if (Dim %2 != 0)break;
        else cout << "El numero es par" << endl << endl;
    }
    return Dim;
}

void Matrices_Rotadas(int **&Matriz, int Dim){
    int ** Matriz_Rotada = new int*[Dim];
    Crear_Elementos_Internos(Matriz_Rotada,Dim);
    Matriz_Estado_1(Matriz_Rotada, Matriz, Dim);
    Mostrar_Matriz(Matriz_Rotada, Dim);
    Matriz_Estado_2(Matriz_Rotada,Matriz,Dim);
    Mostrar_Matriz(Matriz_Rotada, Dim);
    Matriz_Estado_3(Matriz_Rotada,Matriz,Dim);
    Mostrar_Matriz(Matriz_Rotada, Dim);
    Eliminar_Matriz_Bidimensional(Matriz_Rotada, Dim);
}


void Matriz_Estado_1(int **&MatrizRotada, int **&MatrizOriginal, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            MatrizRotada [i][k] = MatrizOriginal[k][Dim-1-i];
        }
    }
}

void Matriz_Estado_3(int **&MatrizRotada, int **&MatrizOriginal, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            MatrizRotada[i][k] = MatrizOriginal[Dim-1-k][i];
        }
    }
}

void Matriz_Estado_2(int **&MatrizRotada, int **&MatrizOriginal, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            MatrizRotada[i][k] = MatrizOriginal[Dim-1-i][Dim-1-k];
        }
    }
}

void CrearCerradura()
{
    int Tamano_Cerradura;
    cout << "Ingrese la cantidad de estructuras presentes en la cerradura: ";  cin >> Tamano_Cerradura;

    int *** X = new int**[Tamano_Cerradura];
    int *Dim_Matrices = new int[Tamano_Cerradura];

    for (int i = 0; i < Tamano_Cerradura; i++){
        X[i] = Crear_Matriz_Mecanicamente(Dim_Matrices, i);
    }
    Imprimir_Matrices_Cerradura(X, Tamano_Cerradura, Dim_Matrices);

    Eliminar_Cerradura(X, Tamano_Cerradura, Dim_Matrices);
    delete[] Dim_Matrices;
}

void Eliminar_Cerradura(int ***&X, int Tamano_Cerradura, int*& Dim_Matrices)
{
    int *ptr = Dim_Matrices;
    for (int i = 0; i < Tamano_Cerradura; ++i) {
        Eliminar_Matriz_Bidimensional(X[i], ptr[i]);
    }
    delete[] X;
}

void Imprimir_Matrices_Cerradura(int ***& X, int Tamano_Cerradura, int*& Dim_Matrices)
{
    int *ptr = Dim_Matrices;
    for (int i = 0; i < Tamano_Cerradura; ++i) {
        Mostrar_Matriz(X[i], ptr[i]);
    }
}
