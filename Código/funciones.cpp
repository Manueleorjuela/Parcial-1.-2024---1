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

int ** Matriz_Estado_1(int **&MatrizRotada, int **&MatrizOriginal, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            MatrizRotada [i][k] = MatrizOriginal[k][Dim-1-i];
        }
    }
    return MatrizRotada;
}

int ** Matriz_Estado_3(int **&MatrizRotada, int **&MatrizOriginal, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            MatrizRotada[i][k] = MatrizOriginal[Dim-1-k][i];
        }
    }
    return MatrizRotada;
}

int ** Matriz_Estado_2(int **&MatrizRotada, int **&MatrizOriginal, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k < Dim; k++){
            MatrizRotada[i][k] = MatrizOriginal[Dim-1-i][Dim-1-k];
        }
    }
    return MatrizRotada;
}

void CopiarMatriz(int **&Matriz_Rotada, int **&Matriz_Original, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k<  Dim; k++){
            Matriz_Rotada[i][k] = Matriz_Original[i][k];
        }
    }
}

int *** CrearCerradura(int &Tamano_Cerradura, int *& Dim_Matrices)
{
    cout << "Ingrese la cantidad de estructuras presentes en la cerradura: ";  cin >> Tamano_Cerradura;
    int *** X = new int**[Tamano_Cerradura];
    Dim_Matrices = new int [Tamano_Cerradura];
    for (int i = 0; i < Tamano_Cerradura; i++){
        X[i] = Crear_Matriz_Mecanicamente(Dim_Matrices, i);
    }
    Imprimir_Matrices_Cerradura(X, Tamano_Cerradura, Dim_Matrices);
    return X;
}

void Eliminar_Cerradura(int ***&X, int &Tamano_Cerradura, int*& Dim_Matrices)
{
    for (int i = 0; i < Tamano_Cerradura; ++i) {
        Eliminar_Matriz_Bidimensional(X[i], Dim_Matrices[i]);
    }
    delete[] X;
}

void Imprimir_Matrices_Cerradura(int ***& X, int& Tamano_Cerradura, int*& Dim_Matrices)
{

    for (int i = 0; i < Tamano_Cerradura; ++i) {
        Mostrar_Matriz(X[i], Dim_Matrices[i]);
    }
}

void ValidarRegla_Sobre_Cerradura()
{

    int Tamano_Cerradura = 0, *Dim_Matrices, *Estructuras_Rotadas;
    int *** X = CrearCerradura(Tamano_Cerradura, Dim_Matrices);
    int * Regla = Crear_Regla(Tamano_Cerradura, Dim_Matrices);
    Crear_Cerradura_Rotada(X, Tamano_Cerradura, Dim_Matrices, Estructuras_Rotadas, Regla);
    /*
    for (int i = 0; i < Tamano_Cerradura; i++){
        cout << Dim_Matrices[i] << " ";
    }

    cout << endl << endl;
    for (int i = 0; i < (Tamano_Cerradura+1); i++){
        cout << Regla[i] << " ";
    }
    */

    Eliminar_Cerradura(X, Tamano_Cerradura, Dim_Matrices);
    delete[] Dim_Matrices; delete[] Regla;
}

int *Crear_Regla(int& Tamano_Cerradura, int*& Dim_Matrices)
{
    int *Regla = new int[Tamano_Cerradura + 1];
    int Dim_Menor = Dimension_Menor(Dim_Matrices, Tamano_Cerradura);
    for (int i = 0; i < (Tamano_Cerradura+1); i++){
        if (i < 2 ) Regla[i] = ValidarTamanoMatrices(Dim_Menor, i);
        else Regla[i] = ValidarCondicionesRegla(i-1, i);
    }
    return Regla;
}

int ValidarCondicionesRegla(int M1, int M2)
{
    int Condicion;
    cout << "\n1. Que sea mayor" << "\n-1. Que sea menor" << "\n0. Que sean iguales" << endl;
    while (true){
        cout << endl << "Ingrese la condicion entre las estructuras " << M1 <<" y " << M2<<": "; cin >> Condicion;
        if (Condicion >= -1 && Condicion <= 1)break;
        else cout << "La condicion NO es valida" << endl << endl;
    }
    return Condicion;
}


int ValidarTamanoMatrices(int Dim_Menor, int Pos)
{
    if (Pos == 0) cout << endl << "Valor para la fila " << endl;
    if (Pos == 1) cout << endl <<"Valor para la columna " << endl;
    int Condicion;
    while (true){
        cout << "Ingrese un valor para la celda a evaluar: " ;
        cin >> Condicion;
        if (Condicion > 0 && Condicion <= Dim_Menor) break;
        else cout << "Posicion invalida, recuerde que debe estar dentro del limite de todas las estructuras creadas" << endl << endl;
    }
    return Condicion;
}

int Dimension_Menor(int *&Dim_Matrices, int Tamano_Cerradura)
{
    int Dim = Dim_Matrices[0];
    for (int i = 0; i < Tamano_Cerradura; i++){
        if (Dim_Matrices[i] < Dim) Dim = Dim_Matrices[i];
    }
    return Dim;
}

void Crear_Cerradura_Rotada(int ***&X, int &Tamano_Cerraduara, int *&Dim_Matrices, int *&Cerraduras_Rotadas, int *&Regla)
{
    int Fila =  ((Regla[0])-1), Columna = ((Regla[1])-1);
    for (int i = 0; i < (Tamano_Cerraduara-1); i++){
        int ** Matriz_Rotada = new int*[ Dim_Matrices[i+1]];
        X[i+1] = Comparacion_Estructuras(X[i], X[i+1], Matriz_Rotada, Fila, Columna, Regla[i+2], Dim_Matrices[i+1]);
        Mostrar_Matriz(X[i+1], Dim_Matrices[i+1]);



        Eliminar_Matriz_Bidimensional(Matriz_Rotada, Dim_Matrices[i+1]);
        //Funcion Para Comprobar La Matriz y SuS Rotaciones
    }
}

int ** Comparacion_Estructuras(int **&Estructura1, int **&Estructura2, int**& Matriz_Rotada, int Fila, int Col, int Condicion, int Dim2)
{
    Crear_Elementos_Internos(Matriz_Rotada,Dim2);
    CopiarMatriz(Matriz_Rotada, Estructura2, Dim2);

    switch(Condicion){
    case 1: {
        for (int i = 0; i < 3; i++){
            if (Estructura1[Fila][Col] > Matriz_Rotada[Fila][Col]) return Matriz_Rotada;
            else if (i == 0) Matriz_Rotada = Matriz_Estado_1(Matriz_Rotada, Estructura2, Dim2);
            else if (i == 1) Matriz_Rotada = Matriz_Estado_2(Matriz_Rotada, Estructura2, Dim2);
            else if (i== 2) Matriz_Rotada =  Matriz_Estado_3(Matriz_Rotada, Estructura2, Dim2);
        }
    }
    break;
    case (-1): {
        for (int i = 0; i < 3; i++){
            Mostrar_Matriz(Matriz_Rotada, Dim2);
            if (Estructura1[Fila][Col] < Matriz_Rotada[Fila][Col]) return Matriz_Rotada;
            else if (i == 0) Matriz_Rotada = Matriz_Estado_1(Matriz_Rotada, Estructura2, Dim2);
            else if (i == 1) Matriz_Rotada = Matriz_Estado_2(Matriz_Rotada, Estructura2, Dim2);
            else if (i== 2) Matriz_Rotada =  Matriz_Estado_3(Matriz_Rotada, Estructura2, Dim2);
        }
    }
    break;
    case 0: {
        for (int i = 0; i < 3; i++){
            if (Estructura1[Fila][Col] == Matriz_Rotada[Fila][Col]) return Matriz_Rotada;
            else if (i == 0) Matriz_Rotada = Matriz_Estado_1(Matriz_Rotada, Estructura2, Dim2);
            else if (i == 1) Matriz_Rotada = Matriz_Estado_2(Matriz_Rotada, Estructura2, Dim2);
            else if (i== 2) Matriz_Rotada =  Matriz_Estado_3(Matriz_Rotada, Estructura2, Dim2);
        }
    }
    break;
    }

    return Matriz_Rotada;
}

