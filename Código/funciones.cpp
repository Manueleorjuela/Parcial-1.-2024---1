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
        if (Dim %2 != 0 and Dim!= 1)break;
        else cout << "Dimension par ingresada o incoherente" << endl << endl;

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
    return X;
}

void Eliminar_Cerradura(int ***&X, int &Tamano_Cerradura, int*& Dim_Matrices)
{
    for (int i = 0; i < Tamano_Cerradura; ++i) {
        Eliminar_Matriz_Bidimensional(X[i], Dim_Matrices[i]);
    }
    delete[] X;
}

void Imprimir_Matrices_Cerradura(int ***& X, int& Tamano_Cerradura, int*& Dim_Matrices, int *& Estructuras_Rotadas)
{

    for (int i = 0; i < Tamano_Cerradura; ++i) {
        Mostrar_Matriz(X[i], Dim_Matrices[i]);
        if (Estructuras_Rotadas[i] == 0) cout << "Estado " << "Neutro " << endl;
        else cout << "Estado " << Estructuras_Rotadas[i] << endl;
    }
}

void ValidarRegla_Sobre_Cerradura()
{

    int Tamano_Cerradura = 0, *Dim_Matrices, *Estructuras_Rotadas;
    int *** X = CrearCerradura(Tamano_Cerradura, Dim_Matrices);
    int * Regla = Crear_Regla(Tamano_Cerradura, Dim_Matrices);
    Estructuras_Rotadas = new int[Tamano_Cerradura];
    Crear_Cerradura_Rotada(X, Tamano_Cerradura, Dim_Matrices, Estructuras_Rotadas, Regla);
    Eliminar_Cerradura(X, Tamano_Cerradura, Dim_Matrices);
    delete[] Dim_Matrices; delete[] Regla; delete[] Estructuras_Rotadas;
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

void Crear_Cerradura_Rotada(int ***&X, int &Tamano_Cerradura, int *&Dim_Matrices, int *&Cerraduras_Rotadas, int *&Regla)
{
    int Fila = (Regla[0]) - 1;
    int Columna = (Regla[1]) - 1;
    int ***Casos = nullptr,  *Respectivas_Rotaciones = nullptr, *Respectivas_Dimensiones = nullptr; //*** Casos_Fijos = nullptr;
    Casos = Combinaciones_Estructuras_Iniciales(X[0], X[1], Fila, Columna , Regla[2], Dim_Matrices[0], Dim_Matrices[1], Casos, Respectivas_Rotaciones, Respectivas_Dimensiones);
    int Posibilidad = Dimension_Casos_Posibles(Casos);
    bool Bandera;
    //Imprimir_Matrices_Cerradura(Casos, Posibilidad, Respectivas_Dimensiones, Respectivas_Rotaciones);
    X[0] = Casos[6];
    X[1] = Casos[7];
    int* Dimensiones_Posibles  = nullptr;
    int *** Posibilidades = nullptr;
    Posibilidades = Casos_Probables(Posibilidades, X[1], X[2], Fila, Columna, Regla[3], 5, Dimensiones_Posibles);
    int A =  Dimension_Casos_Posibles(Posibilidades);
    int ** Guardar = Evaluar_Posibilidades(Posibilidades, A, 1, Dim_Matrices[1], Fila, Columna , Bandera);
    if (Bandera){
        X[2] = Guardar;
    }
    Imprimir_Matrices_Cerradura(X, Tamano_Cerradura, Dim_Matrices, Cerraduras_Rotadas);

    //Funciona el maldito



    /*
    cout << Dimensiones_Posibles[0] << endl;
    cout << Dimensiones_Posibles[1] << endl;
    */
    //A =  Dimension_Casos_Posibles(Posibilidades);
    //cout << A << endl;
    //Imprimir_Matrices_Cerradura(Posibilidades, A, Dimensiones_Posibles, Cerraduras_Rotadas);
    /*
    for (int i = 0; i <= Posibilidad; i+=2){
        X[0] = Casos[i]; Cerraduras_Rotadas[0] = Respectivas_Rotaciones[i];
        X[1] = Casos[i+1]; Cerraduras_Rotadas[1] = Respectivas_Rotaciones[i+1];

        for (int j = 1; j < Tamano_Cerradura-1; j++){
            Comparacion_Estructuras(X[j], X[j+1], Fila, Columna, Regla[j+2], Dim_Matrices[j+1], Bandera);
            if(!Bandera) break;
        }
        if (Bandera) break;
    }*/


    //Validar_Impresion(Bandera, X, Tamano_Cerradura, Dim_Matrices, Cerraduras_Rotadas);
    delete[] Respectivas_Rotaciones; delete[] Respectivas_Dimensiones; delete[] Dimensiones_Posibles;
    //Eliminar_Cerradura(Casos, Posibilidad, Respectivas_Dimensiones);
    //Eliminar_Cerradura(Posibilidades, A, Dimensiones_Posibles);

}

int ***Casos_Probables(int ***&Posibilidades, int**&Estructura1, int **&Estructura2, int Fila, int Col, int Condicion, int Dim2, int *&Dimensiones_Posibles){
    int **Matriz_Rotada = new int *[Dim2];
    Crear_Elementos_Internos(Matriz_Rotada, Dim2);
    CopiarMatriz(Matriz_Rotada, Estructura2, Dim2);
    bool Estado = false;


    for (int i = 0; i<= 3; i++){
        switch(Condicion){
        case 1:
            Estado = (Estructura1[Fila][Col] > Matriz_Rotada[Fila][Col]);
            break;
        case -1:
            Estado = (Estructura1[Fila][Col] < Matriz_Rotada[Fila][Col]);
            break;
        case 0:
            Estado = (Estructura1[Fila][Col] == Matriz_Rotada[Fila][Col]);
            break;
        }
        if (Estado){
            Dimensiones_Posibles = Copiar_Dimensiones_Posibles_Fijas(Posibilidades, Dimensiones_Posibles, Dim2);
            Posibilidades = Copiar_Datos_Casos_Posibles_Fijo(Posibilidades, Dimensiones_Posibles, Matriz_Rotada, Dim2);
        }
        if (i == 0) Matriz_Rotada = Matriz_Estado_1(Matriz_Rotada, Estructura2, Dim2);
        if (i == 1) Matriz_Rotada = Matriz_Estado_2(Matriz_Rotada, Estructura2, Dim2);
        if (i == 2) Matriz_Rotada = Matriz_Estado_3(Matriz_Rotada, Estructura2, Dim2);
    }
    return Posibilidades;
}

void Validar_Impresion(bool Bandera, int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices, int *& Cerraduras_Rotadas)
{
    if(Bandera) Imprimir_Matrices_Cerradura(X, Tamano_Cerradura, Dim_Matrices, Cerraduras_Rotadas);
}

bool Validacion_PosicionCentral(int **Estructura1, int **Estructura2, int Fila, int Col)
{
    if(Estructura1[Fila][Col] == 0 or Estructura2[Fila][Col] == 0) return 0;
    else return 1;
}

void Crear_Regla_Para_Generar_Cerradura(int *&Regla, int &Tamano)
{

    cout << "Ingrese el tamano de la cerradura que desea generar: ";
    cin >> Tamano;
    Regla = new int[Tamano+1];
    for (int i = 0; i < (Tamano+1); i++){
        if (i < 2){
            Regla[i] = Validar_Posicion_Regla_Para_Generar_Cerradura(i);
        }else Regla[i] = ValidarCondicionesRegla(i-1, i);
    }
}


int Validar_Posicion_Regla_Para_Generar_Cerradura(int Pos)
{
    int Condicion;
    if (Pos == 0) cout << endl << "Valor para la fila " << endl;
    if (Pos == 1) cout << endl <<"Valor para la columna " << endl;
    cout << "Ingrese un valor para la celda a evaluar: " ;
    cin >> Condicion;
    return Condicion;
}

void Crear_Dimensiones_Para_Generar_Cerradura(int *&Regla, int *&Dim_Matrices, int &Tamano)
{
    int Dim_Menor = Dimension_Minima_Cerradura_Generada(Regla);
    Dim_Matrices = new int[Tamano];
    for (int i = 0; i < Tamano; i++){
        Dim_Matrices[i] = Dim_Menor;
    }
}

int Dimension_Minima_Cerradura_Generada(int *&Regla)
{
    int Menor;
    if (Regla[0] > Regla[1]){
        Menor = Regla[0];
    }
    else{
        Menor = Regla[1];
    }
    if (Menor%2 == 0){
        Menor++;
    }
    if(Regla[0] == 1 && Regla[1] == 1){
        Menor+=2;
    }
    return Menor;
}

int *** Crear_Cerradura_Estandar_Para_Generar(int ***& X_Generada, int *&Dim_Matrices, int &Tamano)
{

    X_Generada = new int **[Tamano];
    for (int k = 0; k < Tamano; k++){
        X_Generada[k] = Crear_Matriz_Automaticamente(Dim_Matrices[k]);
    }
    return X_Generada;
}

int **Crear_Matriz_Automaticamente(int Dim)
{
    int **Matriz =  new int*[Dim];
    Crear_Elementos_Internos(Matriz,Dim);
    Matriz_Estado_Neutro(Matriz, Dim);
    return Matriz;
}

void Modificar_Dimension_Cerradura(int *&Dim_Matrices, int Pos, int Condicion)
{
    if (Condicion == 1){
        Dim_Matrices[Pos]+=2;
    }else if (Condicion == -1){
        Dim_Matrices[Pos+1] += 2;
    }
}

int*** Combinaciones_Estructuras_Iniciales(int **&Estructura1, int **&Estructura2, int Fila, int Col, int Condicion, int Dim1, int Dim2, int***& Casos, int*&Respectivas_Rotaciones, int*& Respectivas_Dimensiones)
{
    int **Matriz_Rotada1 = new int *[Dim1], **Matriz_Rotada2 = new int *[Dim2];
    Crear_Elementos_Internos(Matriz_Rotada1, Dim1);
    Crear_Elementos_Internos(Matriz_Rotada2, Dim2);
    CopiarMatriz(Matriz_Rotada1, Estructura1, Dim1);
    bool Estado = false;

    for (int i = 0; i <= 3; i++){
        CopiarMatriz(Matriz_Rotada2, Estructura2, Dim2);
        for (int j = 0; j <= 3; j++){
            switch(Condicion){
                case 1:
                Estado = (Matriz_Rotada1[Fila][Col] > Matriz_Rotada2[Fila][Col]);
                break;
                case -1:
                Estado = (Matriz_Rotada1[Fila][Col] < Matriz_Rotada2[Fila][Col]);
                break;
                case 0:
                Estado = (Matriz_Rotada1[Fila][Col] == Matriz_Rotada2[Fila][Col]);
                break;
            }
            if (Estado){
                Respectivas_Rotaciones = Copiar_Rotaciones_Posibles(Casos, Respectivas_Rotaciones, j, i);
                Respectivas_Dimensiones = Copiar_Dimensiones_Posibles(Casos, Respectivas_Dimensiones, Dim1, Dim2);
                Casos = Copiar_Datos_Casos_Posibles(Casos, Dim1, Dim2, Matriz_Rotada1, Matriz_Rotada2);
            }
            if (j == 0) Matriz_Rotada2 = Matriz_Estado_1(Matriz_Rotada2, Estructura2, Dim2);
            if (j == 1) Matriz_Rotada2 = Matriz_Estado_2(Matriz_Rotada2, Estructura2, Dim2);
            if (j == 2) Matriz_Rotada2 = Matriz_Estado_3(Matriz_Rotada2, Estructura2, Dim2);
        }
        if (i == 0) Matriz_Rotada1 = Matriz_Estado_1(Matriz_Rotada1, Estructura1, Dim1);
        if (i == 1) Matriz_Rotada1 = Matriz_Estado_2(Matriz_Rotada1, Estructura1, Dim1);
        if (i == 2) Matriz_Rotada1 = Matriz_Estado_3(Matriz_Rotada1, Estructura1, Dim1);
    }

    Eliminar_Matriz_Bidimensional(Matriz_Rotada1, Dim1);
    Eliminar_Matriz_Bidimensional(Matriz_Rotada2, Dim2);
    return Casos;

}

int ***Copiar_Datos_Casos_Posibles(int ***&Casos, int Dim1, int Dim2, int **&Estructura1, int **&Estructura2)
{

    int Dim = Dimension_Casos_Posibles(Casos);

    int ***Añadir_Casos = new int **[Dim + 2];

        for (int i = 0; i < Dim; ++i) {
        int tamano_matriz = (i % 2 == 0) ? Dim1 : Dim2;

        Añadir_Casos[i] = new int *[tamano_matriz];
        Crear_Elementos_Internos(Añadir_Casos[i], tamano_matriz);
        CopiarMatriz(Añadir_Casos[i], Casos[i], tamano_matriz);
    }


    Añadir_Casos[Dim] = new int *[Dim1];
    Crear_Elementos_Internos(Añadir_Casos[Dim], Dim1);
    CopiarMatriz(Añadir_Casos[Dim], Estructura1, Dim1);

    Añadir_Casos[Dim + 1] = new int *[Dim2];
    Crear_Elementos_Internos(Añadir_Casos[Dim + 1], Dim2);
    CopiarMatriz(Añadir_Casos[Dim + 1], Estructura2, Dim2);

    Añadir_Casos[Dim+2] = nullptr;

    return Añadir_Casos;
}

int *Copiar_Rotaciones_Posibles(int ***& Casos, int *&Rotaciones, int Cond2, int Cond1) {
    int Dim = Dimension_Casos_Posibles(Casos);
    int *Añadir_Rotaciones = new int[Dim + 2];

    for (int i = 0; i < Dim; i++) {
        Añadir_Rotaciones[i] = Rotaciones[i];
    }
    Añadir_Rotaciones[Dim] = Cond1;
    Añadir_Rotaciones[Dim + 1] = Cond2;

    return Añadir_Rotaciones;
}

int Dimension_Casos_Posibles(int ***&Casos)
{
    if (Casos == nullptr) {
        return 0;
    }
    int Tamano = 0;
    while (Casos[Tamano] != nullptr) {
        Tamano++;
    }
    return Tamano;
}

int *Copiar_Dimensiones_Posibles(int ***&Casos, int *&Dimensiones, int Dim1, int Dim2)
{
    int Dim = Dimension_Casos_Posibles(Casos);
    int *Añadir_Dimensiones = new int[Dim + 2];

    for (int i = 0; i < Dim; i++) {
            Añadir_Dimensiones[i] = Dimensiones[i];
    }
    Añadir_Dimensiones[Dim] = Dim1;
    Añadir_Dimensiones[Dim + 1] = Dim2;

    return Añadir_Dimensiones;
}

int ***Copiar_Datos_Casos_Posibles_Fijo(int ***&Posibilidades, int *Dimensiones, int **Estructura, int Dim_Añadir)
{
    int Nueva_Dim = Dimension_Casos_Posibles(Posibilidades);

    int *** Nuevas_Posibilidades = new int **[Nueva_Dim+1];


    for (int i = 0; i < Nueva_Dim; ++i) {
        int Dim_Matrices = Dimensiones[i];
        Nuevas_Posibilidades[i] = new int *[Dim_Matrices];
        Crear_Elementos_Internos(Nuevas_Posibilidades[i], Dim_Matrices);
        CopiarMatriz(Nuevas_Posibilidades[i], Posibilidades[i], Dim_Matrices);
    }


    Nuevas_Posibilidades[Nueva_Dim] = new int *[Dim_Añadir];
    Crear_Elementos_Internos(Nuevas_Posibilidades[Nueva_Dim], Dim_Añadir);
    CopiarMatriz( Nuevas_Posibilidades[Nueva_Dim], Estructura, Dim_Añadir);

        Nuevas_Posibilidades[Nueva_Dim+1] = nullptr;
    return Nuevas_Posibilidades;
}

int *Copiar_Dimensiones_Posibles_Fijas(int*** & Posibilidades, int *&Dimensiones, int Dim)
{
    int Dim_Nueva = Dimension_Casos_Posibles(Posibilidades);
    int *Añadir_Dimensiones = new int[Dim_Nueva + 1];
    for (int i = 0; i < Dim_Nueva; i++) {
            Añadir_Dimensiones[i] = Dimensiones[i];
    }
    Añadir_Dimensiones[Dim_Nueva]  = Dim;
    return Añadir_Dimensiones;
}


int ** Evaluar_Posibilidades(int ***&Posibilidades, int Tamano, int Condicion_Siguiente, int Dim, int Fila, int Col, bool &Estado)
{
    int **Matriz_Guardar;
    int Mayor = 0;


    for (int k = 0; k < Tamano; k++){
            if (Posibilidades[k][Fila][Col] > Mayor){
            Mayor = Posibilidades[k][Fila][Col];
            Matriz_Guardar = new int*[Dim];
            Crear_Elementos_Internos(Matriz_Guardar, Dim);
            CopiarMatriz(Matriz_Guardar, Posibilidades[k],Dim);
            Estado = true;
        }
    }
    return Matriz_Guardar;
}
