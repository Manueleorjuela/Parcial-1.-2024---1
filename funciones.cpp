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

void CopiarMatriz(int **&Matriz_Rotada, int **Matriz_Original, int Dim)
{
    for (int i = 0; i < Dim; i++){
        for (int k = 0; k<  Dim; k++){
            Matriz_Rotada[i][k] = Matriz_Original[i][k];
        }
    }
}

int *** CrearCerradura(int &Tamano_Cerradura, int *& Dim_Matrices)
{
    int *** X = new int**[Tamano_Cerradura];
    for (int i = 0; i < Tamano_Cerradura; i++){
        X[i] = Crear_Matriz_Mecanicamente(Dim_Matrices, i);
    }
    return X;
}

void Eliminar_Matriz_Bidimensional(int **&Matriz, int Dim)
{

    for (int i = 0; i < Dim; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;
    Matriz = nullptr;
}

void Eliminar_Cerradura(int ***&X, int Tamano_Cerradura, int*&Dim_Matrices)
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

    int Tamano_Cerradura = 0;
    cout << "Ingrese la cantidad de estructuras presentes en la cerradura: ";  cin >> Tamano_Cerradura;
    int *Dim_Matrices = new int[Tamano_Cerradura], *Estructuras_Rotadas = new int[Tamano_Cerradura];
    bool Bandera = false;
    int *** X = CrearCerradura(Tamano_Cerradura, Dim_Matrices);
    int * Regla = Crear_Regla(Tamano_Cerradura, Dim_Matrices);
    Crear_Cerradura_Rotada(X, Tamano_Cerradura, Dim_Matrices, Estructuras_Rotadas, Regla, Bandera);
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

    int Dim = std::numeric_limits<int>::max();
    for (int i = 0; i < Tamano_Cerradura; i++){
        if (Dim_Matrices[i] < Dim) Dim = Dim_Matrices[i];
    }
    return Dim;
}

void Crear_Cerradura_Rotada(int ***&X, int &Tamano_Cerradura, int *&Dim_Matrices, int *&Cerraduras_Rotadas, int *&Regla, bool &Bandera)
{
    int Fila = (Regla[0]) - 1;
    int Columna = (Regla[1]) - 1;
    Bandera = false;
    Cerraduras_Rotadas[0] = 0;
    int Dim_Minima = Dimension_Menor(Dim_Matrices, Tamano_Cerradura);


    //Algoritmo para encontrar soluciones posibles de acuerdo a las condiciones siguientes
    for (int y = 0; y < Tamano_Cerradura-1; y++){

        int *Dimensiones_Posibles = nullptr, *Rotaciones_Posibles = nullptr, ***Posibilidades = nullptr, ** Guardar = nullptr, A;
        Posibilidades = Casos_Probables(Posibilidades, X[y], X[y+1], Fila, Columna, Regla[y+2], Dim_Matrices[y], Dim_Matrices[y+1], Dimensiones_Posibles, Rotaciones_Posibles);

        if (Posibilidades != 0){

            A = Dimension_Casos_Posibles(Posibilidades);


            int Condicion_Siguiente  =  Regla[y+3];
            if (y== Tamano_Cerradura-2){
                Condicion_Siguiente = Regla[y+2];
            }

            Guardar = Evaluar_Posibilidades(Guardar, Posibilidades, A, Condicion_Siguiente, Dim_Matrices[y+1], Dim_Minima, Fila, Columna, Cerraduras_Rotadas, Rotaciones_Posibles, y+1);
            CopiarMatriz(X[y+1], Guardar, Dim_Matrices[y+1]);

            //Liberacion
            Eliminar_Matriz_Bidimensional(Guardar, Dim_Matrices[y+1]);
            Eliminar_Cerradura(Posibilidades, A, Dimensiones_Posibles);
            delete[] Dimensiones_Posibles; delete[] Rotaciones_Posibles;

            if (y == Tamano_Cerradura-2){;
                Bandera = true;
                break;
            }
        }else{
            break;
            }
        }
    Validar_Impresion(Bandera, X, Tamano_Cerradura, Dim_Matrices, Cerraduras_Rotadas);
}

int ***Casos_Probables(int ***&Posibilidades, int**&Estructura1, int **&Estructura2, int Fila, int Col, int Condicion, int Dim1, int Dim2, int *&Dimensiones_Posibles, int *& Rotaciones_Posibles){
    int **Matriz_Rotada = new int *[Dim2];
    Crear_Elementos_Internos(Matriz_Rotada, Dim2);
    CopiarMatriz(Matriz_Rotada, Estructura2, Dim2);
    bool Estado = false;

    for (int i = 0; i<= 3; i++){
        int filaEstructura, colEstructura, filaRotada, colRotada;
        Ubicacion_Celda(Dim1, Dim2, Fila, Col, filaEstructura, colEstructura, filaRotada, colRotada);
        switch(Condicion){
        case 1:
            Estado = (Estructura1[filaEstructura][colEstructura] > Matriz_Rotada[filaRotada][colRotada]);
            break;
        case -1:
            Estado = (Estructura1[filaEstructura][colEstructura] < Matriz_Rotada[filaRotada][colRotada]);
            break;
        case 0:
            Estado = (Estructura1[filaEstructura][colEstructura] == Matriz_Rotada[filaRotada][colRotada]);
            break;
        }
        if (Estado){
            Dimensiones_Posibles = Copiar_Dimensiones_Posibles_Fijas(Posibilidades, Dimensiones_Posibles, Dim2);
            Rotaciones_Posibles = Copiar_Rotaciones_Posibles_Fijas(Posibilidades, Rotaciones_Posibles, i);
            Posibilidades = Copiar_Datos_Casos_Posibles_Fijo(Posibilidades, Dimensiones_Posibles, Matriz_Rotada, Dim2);

        }
        if (i == 0) Matriz_Rotada = Matriz_Estado_1(Matriz_Rotada, Estructura2, Dim2);
        if (i == 1) Matriz_Rotada = Matriz_Estado_2(Matriz_Rotada, Estructura2, Dim2);
        if (i == 2) Matriz_Rotada = Matriz_Estado_3(Matriz_Rotada, Estructura2, Dim2);
    }

    Eliminar_Matriz_Bidimensional(Matriz_Rotada, Dim2);
    return Posibilidades;
}

void Validar_Impresion(bool Bandera, int ***& X, int &Tamano_Cerradura, int *& Dim_Matrices, int *& Cerraduras_Rotadas)
{
    if(Bandera) Imprimir_Matrices_Cerradura(X, Tamano_Cerradura, Dim_Matrices, Cerraduras_Rotadas);
    //else cout << "No hay combinacion posible" << endl;
}

bool Validacion_PosicionCentral(int **Estructura1, int **Estructura2, int Fila, int Col)
{
    if(Estructura1[Fila][Col] == 0 or Estructura2[Fila][Col] == 0) return 0;
    else return 1;
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

int ***Copiar_Datos_Casos_Posibles_Fijo(int ***&Posibilidades, int *Dimensiones, int **Estructura, int Dim_Añadir)
{
    int Nueva_Dim = Dimension_Casos_Posibles(Posibilidades);

    int *** Nuevas_Posibilidades = new int **[Nueva_Dim+2];

    if(Posibilidades == nullptr){
        Nuevas_Posibilidades[Nueva_Dim] = new int *[Dim_Añadir];
        Crear_Elementos_Internos(Nuevas_Posibilidades[Nueva_Dim], Dim_Añadir);
        CopiarMatriz(Nuevas_Posibilidades[Nueva_Dim], Estructura, Dim_Añadir);
    }else{
        for (int i = 0; i < Nueva_Dim; ++i) {
            int Dim_Matrices = Dimensiones[i];
            Nuevas_Posibilidades[i] = new int *[Dim_Matrices];
            Crear_Elementos_Internos(Nuevas_Posibilidades[i], Dim_Matrices);
            CopiarMatriz(Nuevas_Posibilidades[i], Posibilidades[i], Dim_Matrices);
        }
        Nuevas_Posibilidades[Nueva_Dim] = new int *[Dim_Añadir];
        Crear_Elementos_Internos(Nuevas_Posibilidades[Nueva_Dim], Dim_Añadir);
        CopiarMatriz( Nuevas_Posibilidades[Nueva_Dim], Estructura, Dim_Añadir);
    }

    Nuevas_Posibilidades[Nueva_Dim+1] = nullptr;
    return Nuevas_Posibilidades;
}

int *Copiar_Dimensiones_Posibles_Fijas(int*** & Posibilidades, int *&Dimensiones, int Dim)
{
    int Dim_Nueva = Dimension_Casos_Posibles(Posibilidades);
    int *Añadir_Dimensiones = new int[Dim_Nueva+1];

    if (Dimensiones == nullptr){
        Añadir_Dimensiones[0] = Dim;
    }else{
        for (int i = 0; i < Dim_Nueva; i++) {
            Añadir_Dimensiones[i] = Dimensiones[i];
        }
        Añadir_Dimensiones[Dim_Nueva]  = Dim;
    }
    return Añadir_Dimensiones;
}


int ** Evaluar_Posibilidades(int **& Matriz_Guardar, int ***&Posibilidades, int Tamano, int Condicion_Siguiente, int Dim, int Dim_Minima, int Fila, int Col, int*& R, int*& P, int Pos)
{
    int Mayor = std::numeric_limits<int>::min();
    int Menor = std::numeric_limits<int>::max();
    bool Copiar = false;
    int Desfase = Alineacion_Casos_Posibles(Dim, Dim_Minima);

    if(Desfase == 0) Desfase =0;

    for (int i = 0; i < Tamano; i++){
            switch(Condicion_Siguiente){
                case 1:
                if (Posibilidades[i][Fila+Desfase][Col+Desfase] > Mayor){
                    Copiar = true;
                    Mayor = Posibilidades[i][Fila+Desfase][Col+Desfase];
                }
                break;
                case -1:

                if (Posibilidades[i][Fila+Desfase][Col+Desfase] < Menor){
                    Copiar = true;
                    Menor = Posibilidades[i][Fila+Desfase][Col+Desfase];
                }
                break;
                case 0:
                Copiar = true;
                break;
            }
        if (Copiar){
        R[Pos] = P[i];
        Matriz_Guardar = new int*[Dim];
        Crear_Elementos_Internos(Matriz_Guardar, Dim);
        CopiarMatriz(Matriz_Guardar, Posibilidades[i], Dim);
        Copiar = false;
        }
    }
    return Matriz_Guardar;
}

int *Copiar_Rotaciones_Posibles_Fijas(int***& Posibilidades, int*& Rotaciones_Posibles, int Rotacion){
    int Dim = Dimension_Casos_Posibles(Posibilidades);
    int *Añadir_Rotaciones = new int[Dim + 1];

    if (Rotaciones_Posibles == nullptr){
           Añadir_Rotaciones[Dim] = Rotacion;
    }else{
        for (int i = 0; i < Dim; i++) {
            Añadir_Rotaciones[i] = Rotaciones_Posibles[i];
        }
        Añadir_Rotaciones[Dim] = Rotacion;
    }
    return Añadir_Rotaciones;
}

int Alineacion_Casos_Posibles(int Dim1, int Dim2){
    int Diferencia = abs(Dim1-Dim2)/2;
    return Diferencia;
}

void Ubicacion_Celda(int Dim1, int Dim2, int Fila, int Col, int& filaEstructura, int& colEstructura, int& filaRotada, int& colRotada){
    int Alineacion = abs(Dim1-Dim2)/2;


    if (Dim1 > Dim2) {
        filaEstructura = Fila + Alineacion;
        colEstructura = Col + Alineacion;
        filaRotada = Fila;
        colRotada = Col;
    } else {
        filaEstructura = Fila;
        colEstructura = Col;
        filaRotada = Fila + Alineacion;
        colRotada = Col + Alineacion;
    }
}

void Generar_Cerradura_A_Partir_De_Una_Regla() {
    int Tamano_Cerradura = 0;
    int *Regla = Crear_Regla_Para_Generar(Tamano_Cerradura);
    bool Bandera = false;
    int Dim_Mayor = Dimension_Dim_Matrices(Regla);

    int *Dim_Matrices = new int[Tamano_Cerradura];

    while(true) {
        int *Estructuras_Rotadas = new int[Tamano_Cerradura], *** X;
        //Buscar combinaciones con numeros aleatorios
        Generar_Caso_Con_Numeros_Aleatorios(Dim_Matrices, Dim_Mayor, Tamano_Cerradura);
        //Crear cerradura a partir de las dimensiones
        X = Cerradura_Regla(Tamano_Cerradura, Dim_Matrices);
        // Evaluamos
        Crear_Cerradura_Rotada(X, Tamano_Cerradura, Dim_Matrices, Estructuras_Rotadas, Regla, Bandera);
        // Liberación de memoria
        Eliminar_Cerradura(X, Tamano_Cerradura, Dim_Matrices);
        delete[] Estructuras_Rotadas;
        if (Bandera) {
            break;
        }
    }

    delete[] Dim_Matrices;
    delete[] Regla;
}

int *Crear_Regla_Para_Generar(int &Tamano_Cerradura)
{
    cout << "Dimension de la cerradura" << endl;
    while(true){
        cout << "Ingrese la cantidad de estructuras en la cerradura, recuerde que la compania maneja maximo 5 de ellas: ";
        cin >> Tamano_Cerradura;
        if (Tamano_Cerradura > 5 or Tamano_Cerradura <=0) cout << "Tamano invalido" << endl;
        else break;
    }

    int *Regla = new int[Tamano_Cerradura + 1];
    cout << endl << "Recuerde que manejamos hasta maximo 11 dimensiones en cada estructura de la cerradura " << endl;
    for (int i = 0; i < Tamano_Cerradura+1; i++){
        if (i < 2) Regla[i] = Posiciones_Regla_Generada(i);
        else Regla[i] = Condiciones_Regla_Generada(i);
    }

    return Regla;
}

int Posiciones_Regla_Generada(int Pos)
{

    if (Pos == 0) cout << endl << "Valor para la fila " << endl;
    if (Pos == 1) cout << endl <<"Valor para la columna " << endl;
    int Condicion;
    while (true){
        cout << "Ingrese un valor para la celda a evaluar: " ;
        cin >> Condicion;
        if (Condicion > 0 && Condicion <= 11) break;
        else cout << "Posicion invalida" << endl << endl;
    }
    return Condicion;
}

int Condiciones_Regla_Generada(int M)
{
    int Condicion;
    cout << "\n1. Que sea mayor" << "\n-1. Que sea menor" << "\n0. Que sean iguales" << endl;
    while (true){
        cout << endl << "Ingrese la condicion entre las estructuras " << M - 1  <<" y " << M <<": "; cin >> Condicion;
            if (Condicion >= -1 && Condicion <= 1)break;
            else cout << "La condicion NO es valida" << endl << endl;
        }
        return Condicion;
}


int *Crear_Dimensiones_Regla(int Dimension_Mayor, int Tamano_Cerradura)
{
    int *Dimensiones = new int[Tamano_Cerradura];
    for (int i = 0; i < Tamano_Cerradura; i ++){
            Dimensiones[i]  = Dimension_Mayor;
    }
    return Dimensiones;
}

int Dimension_Dim_Matrices(int *&Regla){

    int Dim;
    if (Regla[0] > Regla[1]) Dim = Regla[0];
    else Dim = Regla[1];

    if (Dim == 1) Dim+=2;
    if (Dim%2 == 0) Dim +=1;
    return Dim;
}

int ***Cerradura_Regla(int Tamano_Cerradura, int *Dimensiones)
{
    int ***X = new int **[Tamano_Cerradura];
    for (int i = 0; i < Tamano_Cerradura;i++){
        X[i] =  new int*[Dimensiones[i]];
        Crear_Elementos_Internos(X[i], Dimensiones[i]);
        Matriz_Estado_Neutro(X[i], Dimensiones[i]);
    }
    return X;
}

void Generar_Caso_Con_Numeros_Aleatorios(int *&Dimensiones, int Dim_Mayor, int Tamano)
{
    srand(time(0));

    int opciones[] = {3, 5, 7, 9, 11};
    int IndiceMin;
    int IndiceMax = 4;

    for (int i = 0; i < 5; i++){
        if(opciones[i] == Dim_Mayor) IndiceMin = i;
    }
    int size = IndiceMax - IndiceMin;
    for (int i = 0; i < Tamano; i++) {
        int indice_aleatorio = IndiceMin + rand() % size;
        Dimensiones[i] = opciones[indice_aleatorio];
    }
}
