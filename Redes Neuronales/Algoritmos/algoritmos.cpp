#include<iostream>
#include<fstream>
#include<array>
#include<vector>
#include<string.h>
#include<regex.h>
#include<ctype.h>
#include<algorithm>

using namespace std;

// Número de columnas y de filas de la matriz para representar el tablero
const int filas = 8;
const int columnas = 8;
// Número de piezas distintas sin contar los reyes y distinguiendo colores
const int piezas = 12;
// Número de pieza que representa cada pieza en el vector de vecores de piezas
// Rey blanco
const int reyB = 0;
// Dama blanca
const int damaB = 1;
// Torre blanca
const int torreB = 2;
// Alfil blanco
const int alfilB = 3;
// Caballo blanco
const int caballoB = 4;
// Peón blanco
const int peonB = 5;
// Rey negro
const int reyN = 6;
// Dama negra
const int damaN = 7;
// Torre negra
const int torreN = 8;
// Alfil negro
const int alfilN = 9;
// Caballo negro
const int caballoN = 10;
// Peón negro
const int peonN = 11;



//////////////////////////////////////////////////////////////////////
// Enteros que representan una pieza o casilla vacía en el tablero: //
// Vacío: 0                                                         //
// REY: K=1 ó k=-1                                                  //
// DAMA: Q=2 ó q=-2                                                 //
// TORRES: R=3 ó r=-3                                               //
// ALFILES: B=4 ó b=-4                                              //
// CABALLOS: N=5 ó n=-5                                             //
// PEONES: P=6 ó p=-6                                               //
//////////////////////////////////////////////////////////////////////


/**
 * @brief Convertimos el código fen a una matriz donde colocamos en cada posición la pieza correspondiente. 
 * Además obtenemos las posiciones de los peones tanto blancos como negros y las almacenamos en un array. 
 * 
 * @param fen código fen que representa la posición
 * @param longPrimerCampo  longitud del primer campo del código fen que representa la posición
 * @param posicion tablero de ajedrez donde representaremos la posición
 * @param posicionesPiezas vector de vectores donde almacenamos para cada posición las casillas de cada pieza del mismo tipo. En total 12.
 * @param peonesBlancos array para almacenar el número de peones blancos por columnas
 * @param peonesNegros array para almacenar el número de peones negros por columnas
 */
void crearTablero(const string fen, const int longPrimerCampo, int posicion[][columnas], vector<vector<int>> & posicionesPiezas, int peonesBlancos[], int peonesNegros[]){
    // Indices
    int j = 7, k = 0;

    for (int i = 0; i < longPrimerCampo ; i++){

        // Casilla vacía, comprobamos si es un dígito
        if (isdigit(fen[i])){
            k += (fen[i] - '0');
        }

        else{
            // Cambio de fila
            if (fen[i] == '/'){
                j--;
                k = 0;
            }

            // Obtenemos el entero de dos dígitos, columna-fila

            string s1 = to_string(k+1);
            string s2 = to_string(j+1);

            string s = s1 + s2;
            
            int colfil = stoi(s);

            // Rey blanco
            if (fen[i] == 'K'){
                posicion[j][k] = 1;
                k += 1;
                posicionesPiezas[reyB].push_back(colfil);
            }

            // Rey negro
            if (fen[i] == 'k'){
                posicion[j][k] = -1;
                k += 1;
                posicionesPiezas[reyN].push_back(colfil);
            }

            // Dama blanca
            if (fen[i] == 'Q'){
                posicion[j][k] = 2;
                k += 1;
                posicionesPiezas[damaB].push_back(colfil);
            }

            // Dama negra
            if (fen[i] == 'q'){
                posicion[j][k] = -2;
                k += 1;
                posicionesPiezas[damaN].push_back(colfil);
            }

            // Torre blanca
            if (fen[i] == 'R'){
                posicion[j][k] = 3;
                k += 1;
                posicionesPiezas[torreB].push_back(colfil);
            }

            // Torre negra
            if (fen[i] == 'r'){
                posicion[j][k] = -3;
                k += 1;
                posicionesPiezas[torreN].push_back(colfil);
            }

            // Alfil blanco
            if (fen[i] == 'B'){
                posicion[j][k] = 4;
                k += 1;
                posicionesPiezas[alfilB].push_back(colfil);
            }

            // Alfil negro
            if (fen[i] == 'b'){
                posicion[j][k] = -4;
                k += 1;
                posicionesPiezas[alfilN].push_back(colfil);
            }

            // Caballo blanco
            if (fen[i] == 'N'){
                posicion[j][k] = 5;
                k += 1;
                posicionesPiezas[caballoB].push_back(colfil);
            }

            // Caballo negro
            if (fen[i] == 'n'){
                posicion[j][k] = -5;
                k += 1;
                posicionesPiezas[caballoN].push_back(colfil);
            }

            // Peón blanco
            if (fen[i] == 'P'){
                posicion[j][k] = 6;
                peonesBlancos[k] += 1;
                k += 1;
                posicionesPiezas[peonB].push_back(colfil);
            }

            // Peón negro
            if (fen[i] == 'p'){
                posicion[j][k] = -6;
                peonesNegros[k] += 1;
                k += 1;
                posicionesPiezas[peonN].push_back(colfil);
            }
        }
    }
}


/**
 * @brief Imprime el tablero de una posición de ajedrez para una pieza concreta (peones, alfiles, caballos...)
 * 
 * @param posicion matriz donde almacenamos el tablero
 * @param foutTablero fichero de salida para almacenar el tablero
 * @param pieza1 pieza blanca que queremos imprimir sobre el tablero
 * @param pieza2 pieza del mismo tipo pero negra que queremos imprimir sobre el tablero
 */
void imprimirTablero(const int posicion[][columnas], ofstream & foutTablero, const int pieza1, const int pieza2){
    for (int i = filas-1; i >= 0; i--){
        for (int j = 0; j < columnas; j++){
            if (posicion[i][j] == pieza1){
                if (i == 0 && j == columnas-1){
                    foutTablero << 1;
                }
                else{
                    foutTablero << 1 << ",";
                }
            }
            else if (posicion[i][j] == pieza2){
                if (i == 0 && j == columnas-1){
                    foutTablero << -1;
                }
                else{
                    foutTablero << -1 << ",";
                }
            }
            else{
                if (i == 0 && j == columnas-1){
                    foutTablero << 0;
                }
                else{
                    foutTablero << 0 << ",";
                }
            }
        }
    }

    foutTablero << ";";
}

/**
 * @brief Comprueba si una casilla está ocupada
 * 
 * @param v vector de vectores con las casillas ocupadas
 * @param num casilla que queremos comprobar
 * @return true si la casilla está ocupada
 * @return false si la casilla no está ocupada
 */
bool existeEnVector(const vector<vector<int>> & v,const int num) {
    for (const auto & vinterno : v){
            if ((find(vinterno.begin(), vinterno.end(), num) != vinterno.end())){
                return true;
            }
    }
    
    return false;
}


//////////////////////////////////
//////////////////////////////////
//*********ALGORITMOS*********////
//////////////////////////////////
//////////////////////////////////

/**
 * @brief Comprueba el bando que tiene ventaja de espacio
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas de ambos bandos
 * @param peonesBlancos array para almacenar el número de peones blancos por columnas
 * @param peonesNegros array para almacenar el número de peones negros por columnas
 * @return int, 1 si la ventaja es de las blancas, -1 si es de las negras y 0 si no tiene ventaja ningún bando
 */
int ventajaEspacio(const vector<vector<int>> & posicionesPiezas, const int peonesBlancos[], const int peonesNegros[]){
    // Indice
    int j = 0, k = 0;
    // Contador
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        // Peones Blancos
        if (peonesBlancos[i] != 0){
            cont += ((posicionesPiezas[peonB][j]-1) % 10);
            
            // Así solo tenemos en cuenta el peón más retrasado de la columna
            j += peonesBlancos[i];
        }
        
        // Peones Negros
        if (peonesNegros[i] != 0){
            if (peonesNegros[i] != 1){
                cont -= (columnas-(posicionesPiezas[peonN][k+(peonesNegros[i]-1)] % 10));
            }
            else{
                cont -= (columnas-(posicionesPiezas[peonN][k] % 10));
            }
            // Así solo tenemos en cuenta el peón más retrasado de la columna
            k += peonesNegros[i];
        }
    }

    if (cont > 0){
        // Ventaja blanca
        return 1;
    }
    else if (cont < 0){
        // Ventaja negra
        return -1;
    }
    else{
        // Igualdad
        return 0;
    }
    
}

/**
 * @brief Número de columnas abiertas en la posición
 * 
 * @param peonesBlancos array para almacenar el número de peones blancos por columnas
 * @param peonesNegros array para almacenar el número de peones negros por columnas
 * @param colAbiertas array para almacenar en cada posición si la columna está abierta o no
 * @return int número de columnas abiertas
 */
int colAbierta(const int peonesBlancos[], const int peonesNegros[], int colAbiertas[]){
    // Contador
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        if ((peonesBlancos[i] == 0) && (peonesNegros[i] == 0)){
            cont += 1;
            colAbiertas[i] = 1;
        }
    }
    return cont;
}


/**
 * @brief Número de columnas semiabiertas para un bando en la posición
 * 
 * @param peones1 peones del bando que comprobamos
 * @param peones2 peones del otro bando
 * @param colSemiabiertas 
 * @return int número de columnas semiabiertas de un bando
 */
int colSemiAbierta(const int peones1[], const int peones2[], int colSemiabiertas[]){
    // Contador
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        if ((peones1[i] == 0) && (peones2[i] > 0)){
            cont += 1;
            colSemiabiertas[i] = 1;
        }
    }
    return cont;
}


/**
 * @brief Número de piezas de cada tipo que tiene cada bando
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param pieza pieza que queremos contar
 * @return int total de ese tipo de pieza en la posición
 */
int numPiezas(const vector<vector<int>> & posicionesPiezas, const int pieza){
    return posicionesPiezas[pieza].size();
}


/**
 * @brief Comprueba si un bando se puede enrocar en el flanco de rey y/0 dama
 * 
 * @param fen código fen
 * @param indice índice por donde empezar a iterar en el código fen
 * @param letra letra que queremos comprobar que existe en el código fen, ya sea K, Q, k, q
 * @return true puede enrocarse en ese flanco
 * @return false no puede enrocarse en ese flanco
 */
bool enroque(const string fen, const int indice, const char letra){
    if (fen[indice] != '-'){
        for (int i = indice; i < indice+4; i++){
            if (fen[i] == letra){
                return true;
            }
            else if (fen[i] == '-'){
                return false;
            }
        }
    }

    return false;
}

////////////////////////////////
/////////PIEZAS MENORES/////////
////////////////////////////////

/**
 * @brief Comprueba si en la posición un bando tiene una pareja de piezas, normalmente alfiles o caballos
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param pieza pieza que queremos comprobar
 * @return true si existe la pareja de alfiles o de caballos
 * @return false si no existe la pareja
 */
bool pareja(const vector<vector<int>> & posicionesPiezas, const int pieza){
    if (posicionesPiezas[pieza].size() == 2){
        return true;
    }

    return false;
}


// Alfiles del mismo color
/**
 * @brief Comprubea si hay alfiles del mismo color
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @return true si existen alfiles de distinto color
 * @return false si no exiten en la posición
 */
bool mismoColor(const vector<vector<int>> & posicionesPiezas){
    if (posicionesPiezas[alfilB].size() == 1 && posicionesPiezas[alfilN].size() == 1){
        if (((abs((posicionesPiezas[alfilB][0] % 10) - (posicionesPiezas[alfilN][0] % 10)) % 2) == (abs(((posicionesPiezas[alfilB][0] / 10) % 10) - ((posicionesPiezas[alfilN][0] / 10) % 10)) % 2))){
            return true;
        }

        return false;
    }

    return false;
}


// Alfiles de distinto color
/**
 * @brief Comprueba si hay alfiles de distinto color
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @return true hay alfiles de distinto color
 * @return false no hay alfiles de distinto color
 */
bool distColor(const vector<vector<int>> & posicionesPiezas){
    if (posicionesPiezas[alfilB].size() == 1 && posicionesPiezas[alfilN].size() == 1){
        return !mismoColor(posicionesPiezas);
    }

    return false;
}


////////////////////////
/////////TORRES/////////
////////////////////////

/**
 * @brief Comprueba si una torre se encuentra en la séptima fila
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param pieza pieza que queremos comprobar en este caso las torres
 * @return true hay al menos una torre en séptima fila
 * @return false no hay ninguna torre en séptima
 */
bool torreSeptima(const vector<vector<int>> & posicionesPiezas, const int pieza){
    if (posicionesPiezas[pieza].size() > 0){
        if (posicionesPiezas[pieza].size() == 1){
            // Torre blanca
            if (pieza == torreB){
                if ((posicionesPiezas[pieza][0] % 10) == 7){
                    return true;
                }
            }

            // Torre negra
            if (pieza == torreN){
                if ((posicionesPiezas[pieza][0] % 10) == 2){
                    return true;
                }
            }
        }
        else{
            // Torres blancas
            if (pieza == torreB){
                if ( ((posicionesPiezas[pieza][0] % 10) == 7) || ((posicionesPiezas[pieza][1] % 10) == 7)){
                    return true;
                }
            }

            // Torres negras
            if (pieza == torreN){
                if (((posicionesPiezas[pieza][0] % 10) == 2) || ((posicionesPiezas[pieza][1] % 10) == 2)){
                    return true;
                }
            }
        }
    }

    return false;
}


/**
 * @brief Comprueba si hay torres dobladas
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param pieza pieza que queremos comprobar, en este caso las torres ya sean blancas o negras
 * @return true hay torres dobladas
 * @return false no hay torres dobladas
 */
bool torresDobladas(const vector<vector<int>> & posicionesPiezas, const int pieza){
    if (posicionesPiezas[pieza].size() == 2){
        if (((abs(posicionesPiezas[pieza][1] - posicionesPiezas[pieza][0])) < 10) && ((posicionesPiezas[pieza][0] % 10) < (posicionesPiezas[pieza][1] % 10))){    
                for (int i = posicionesPiezas[pieza][0]+1; i < posicionesPiezas[pieza][1]; i++){
                    if (existeEnVector(posicionesPiezas, i)){
                        return false;
                    }
                }

                return true;
        }
    }

    return false;
}


/**
 * @brief Comprueba si hay torres ligadas en la misma fila
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param pieza pieza que queremos comprobar, en este caso las torres ya sean blancas o negras 
 * @return true hay torres ligadas en la misma fila 
 * @return false no hay torres ligadas en la misma fila
 */
bool torresLigMismaFila(const vector<vector<int>> & posicionesPiezas, const int pieza){
    if (posicionesPiezas[pieza].size() == 2){
        if (((abs(posicionesPiezas[pieza][1] - posicionesPiezas[pieza][0])) % 10) == 0){    
                for (int i = posicionesPiezas[pieza][0]+10; i < posicionesPiezas[pieza][1]; i+=10){
                    if (existeEnVector(posicionesPiezas, i)){
                        return false;
                    }
                }

                return true;
        }
    }

    return false;
}


/**
 * @brief Comprueba si se verifica la estructura de la pistola de Alekhine
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param pieza1 pieza que queremos comprobar, en este caso la dama ya sea blanca o negra
 * @param pieza2 torres blancas o negras
 * @return true se verifica la estructura 
 * @return false no se verifica
 */
bool pistolaAlekhine(const vector<vector<int>> & posicionesPiezas, const int pieza1, const int pieza2){
    if (posicionesPiezas[pieza1].size() == 1 && posicionesPiezas[pieza2].size() == 2){
        if (torresDobladas(posicionesPiezas, pieza2)){
            if (((abs(posicionesPiezas[pieza1][0] - posicionesPiezas[pieza2][0])) < 10)){

                // Piezas blancas
                if ((pieza1 == damaB) && (posicionesPiezas[pieza1][0] < posicionesPiezas[pieza2][0]) && ((posicionesPiezas[pieza1][0] % 10) < (posicionesPiezas[pieza2][0] % 10))){
                    for (int i = posicionesPiezas[pieza1][0]+1; i < posicionesPiezas[pieza2][0]; i++){
                        if (existeEnVector(posicionesPiezas, i)){
                            return false;
                        }
                    }

                    return true;
                }

                // Piezas negras
                if ((pieza1 == damaN) && (posicionesPiezas[pieza1][0] > posicionesPiezas[pieza2][1]) && ((posicionesPiezas[pieza1][0] % 10) > (posicionesPiezas[pieza2][0] % 10))){
                    for (int i = posicionesPiezas[pieza2][1]+1; i < posicionesPiezas[pieza1][0]; i++){
                        if (existeEnVector(posicionesPiezas, i)){
                            return false;
                        }
                    }

                    return true;
                }
            }
        }
    }

    return false;
}


///////////////////////////////////////
/////////ESTRUCTURAS DE PEONES/////////
///////////////////////////////////////

/**
 * @brief Número de peones doblados
 * 
 * @param peones array con las columnas donde hay peones
 * @param colPeonesDoblados array para obtener las columnas donde hay peones doblados
 * @return int devuelve el número de peones doblados
 */
int peonesDoblados(const int peones[], int colPeonesDoblados[]){
    // Contador
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        if (peones[i] > 1){
            cont += 1;
            colPeonesDoblados[i] = peones[i];
        }
    }

    return cont;
}


/**
 * @brief Número de peones aislados
 * 
 * @param peones array con las columnas donde hay peones 
 * @param colPeonesAislados array para obtener las columnas donde hay peones aislados
 * @return int devuelve el número de peones aislados
 */
int peonesAislados(const int peones[], int colPeonesAislados[]){
    // Contador
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        if (peones[i] != 0){
            if (i != 0 && i != (columnas-1)){
                // Columnas centrales
                if (peones[i-1] == 0 && peones[i+1] == 0){
                    cont += peones[i];
                    colPeonesAislados[i] = peones[i];
                }       
            }
            else{
                // Columnas laterales
                if (i == 0){
                    if (peones[i+1] == 0){
                        cont += peones[i];
                        colPeonesAislados[i] = peones[i];
                    }
                }
                else{
                    if (peones[i-1] == 0){
                        cont += peones[i];
                        colPeonesAislados[i] = peones[i];
                    }
                }
            }
        }
    }

    return cont;
}


/**
 * @brief Número de peones retrasados
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param peones array con las columnas donde hay peones
 * @param pieza pieza que queremos comprobar ya sean peones blancos o negros
 * @param colPeonesRetrasados array para obtener las columnas donde hay peones retrasados
 * @return int devuelve la cantidad de peones retrasados
 */
int peonesRetrasados(const vector<vector<int>> & posicionesPiezas, const int peones[], const int pieza, int colPeonesRetrasados[]){
    // Indice
    int j = 0;
    // Contador
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        if (peones[i] != 0){
            // Columnas centrales
            if (i != 0 && i != (columnas-1)){
                if (peones[i-1] != 0 && peones[i+1] != 0){
                    // Caso peones blancos
                    if (pieza == peonB && ((posicionesPiezas[pieza][j] % 10) < (posicionesPiezas[pieza][j-peones[i-1]] % 10)) && ((posicionesPiezas[pieza][j] % 10) < (posicionesPiezas[pieza][j+peones[i]] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }

                    // Caso peones negros
                    if (pieza == peonN && ((posicionesPiezas[pieza][j+(peones[i]-1)] % 10) > (posicionesPiezas[pieza][j-1] % 10)) && ((posicionesPiezas[pieza][j+(peones[i]-1)] % 10) > (posicionesPiezas[pieza][j+(peones[i]+peones[i+1]-1)] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }
                }       
                else if (peones[i-1] != 0 && peones[i+1] == 0){
                    // Caso peones blancos
                    if (pieza == peonB && ((posicionesPiezas[pieza][j] % 10) < (posicionesPiezas[pieza][j-peones[i-1]] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }

                    // Caso peones negros
                    if (pieza == peonN && ((posicionesPiezas[pieza][j+(peones[i]-1)] % 10) > (posicionesPiezas[pieza][j-1] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }
                }
                else if (peones[i-1] == 0 && peones[i+1] != 0){
                    // Caso peones blancos
                    if (pieza == peonB && ((posicionesPiezas[pieza][j] % 10) < (posicionesPiezas[pieza][j+peones[i]] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }

                    // Caso peones negros
                    if (pieza == peonN && ((posicionesPiezas[pieza][j+(peones[i]-1)] % 10) > (posicionesPiezas[pieza][j+(peones[i]+peones[i+1]-1)] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }
                }
            }
            else{
                // Columnas laterales
                if (i == 0){
                    // Caso peones blancos
                    if (pieza == peonB && peones[i+1] != 0 && ((posicionesPiezas[pieza][j] % 10) < (posicionesPiezas[pieza][j+peones[i]] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }

                    //  Caso peones negros
                    if (pieza == peonN && peones[i+1] != 0 && ((posicionesPiezas[pieza][j+(peones[i]-1)] % 10) > (posicionesPiezas[pieza][j+(peones[i]+peones[i+1]-1)] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }
                }
                else{
                    // Caso peones blancos
                    if (pieza == peonB && peones[i-1] != 0 && ((posicionesPiezas[pieza][j] % 10) < (posicionesPiezas[pieza][j-peones[i-1]] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }

                    // Caso peones negros
                    if (pieza == peonN && peones[i-1] != 0 && ((posicionesPiezas[pieza][j+(peones[i]-1)] % 10) > (posicionesPiezas[pieza][j-1] % 10))){
                        cont += 1;
                        colPeonesRetrasados[i] = 1;
                    }
                }
            }

            j += peones[i];
        }
    }

    return cont;
}

/**
 * @brief Número de peones pasados
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param peones1 array con las columnas ocupadas por peones del bando que estamos trabajando
 * @param peones2 array con las columnas ocupadas por peones del bando contrario
 * @param pieza1 peón del bando estudiado
 * @param pieza2 peón del bando contrario
 * @param colPeonesPasados array que obtenemos con las columnas donde hay peones pasados
 * @return int devuelve la cantidad de peones pasados
 */
int peonesPasados(const vector<vector<int>> & posicionesPiezas, const int peones1[], const int peones2[], const int pieza1, const int pieza2, int colPeonesPasados[]){
    // Indices
    int j = 0, k = 0;
    // Contadoe
    int cont = 0;

    for (int i = 0; i < columnas; i++){
        if (peones1[i] != 0){
            // Columnas centrales
            if (i != 0 && i != (columnas-1)){

                // Caso peones blancos
                if (pieza1 == peonB){
                    if (peones2[i-1] == 0 && peones2[i] == 0 && peones2[i+1] == 0){
                        cont += 1;
                        colPeonesPasados[i] = 1;
                    }
                    else if (peones2[i-1] == 0 && peones2[i] == 0 && peones2[i+1] != 0){
                        if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]+peones2[i+1]-1)] % 10)){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }       
                    else if (peones2[i-1] == 0 && peones2[i] != 0 && peones2[i+1] == 0){
                        if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10)){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] != 0 && peones2[i] == 0 && peones2[i+1] == 0){
                       if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k-1] % 10)){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] == 0 && peones2[i] != 0 && peones2[i+1] != 0){
                        if (((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]+peones2[i+1]-1)] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] != 0 && peones2[i] == 0 && peones2[i+1] != 0){
                        if (((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k-1] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]+peones2[i+1]-1)] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] != 0 && peones2[i] != 0 && peones2[i+1] == 0){
                        if (((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k-1] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else{
                        if (((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k-1] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]+peones2[i+1]-1)] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                }

                // Caso peones negros
                if (pieza1 == peonN){
                    if (peones2[i-1] == 0 && peones2[i] == 0 && peones2[i+1] == 0){
                        cont += 1;
                        colPeonesPasados[i] = 1;
                    }
                    else if (peones2[i-1] == 0 && peones2[i] == 0 && peones2[i+1] != 0){
                        if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k+peones2[i]] % 10)){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }       
                    else if (peones2[i-1] == 0 && peones2[i] != 0 && peones2[i+1] == 0){
                        if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10)){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] != 0 && peones2[i] == 0 && peones2[i+1] == 0){
                       if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10)){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] == 0 && peones2[i] != 0 && peones2[i+1] != 0){
                        if (((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10)) && ((posicionesPiezas[pieza1][j] % 10) >= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else if (peones2[i-1] != 0 && peones2[i] == 0 && peones2[i+1] != 0){
                        if(((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10)) && ((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k+peones2[i]] % 10))){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                    }
                    else if (peones2[i-1] != 0 && peones2[i] != 0 && peones2[i+1] == 0){
                        if(((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10)) && ((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                    else{
                        if(((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10)) && ((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10)) && ((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k+peones2[i]] % 10))){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                    }
                }
            }
            else{
                // Columnas laterales
                if (i == 0){
                    // Caso peones blancos
                    if (pieza1 == peonB){ 
                        if (peones2[i] == 0 && peones2[i+1] == 0){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                        else if (peones2[i] == 0 && peones2[i+1] != 0){
                            if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]+peones2[i+1]-1)] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else if (peones2[i] != 0 && peones2[i+1] == 0){
                            if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else{
                            if (((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]+peones2[i+1]-1)] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10))){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                    }

                    //  Caso peones negros
                    if (pieza1 == peonN){ 
                        if (peones2[i] == 0 && peones2[i+1] == 0){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                        else if (peones2[i] == 0 && peones2[i+1] != 0){
                            if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k+peones2[i]] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else if (peones2[i] != 0 && peones2[i+1] == 0){
                            if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else{
                            if (((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k+peones2[i]] % 10)) && ((posicionesPiezas[pieza1][j] % 10) >= (posicionesPiezas[pieza2][k] % 10))){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                    }
                }
                else{
                    // Caso peones blancos
                    if (pieza1 == peonB){ 
                        if (peones2[i] == 0 && peones2[i-1] == 0){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                        else if (peones2[i] == 0 && peones2[i-1] != 0){
                            if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k-1] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else if (peones2[i] != 0 && peones2[i-1] == 0){
                            if((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else{
                            if (((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k-1] % 10)) && ((posicionesPiezas[pieza1][j+(peones1[i]-1)] % 10) >= (posicionesPiezas[pieza2][k+(peones2[i]-1)] % 10))){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                    }

                    //  Caso peones negros
                    if (pieza1 == peonN){ 
                        if (peones2[i] == 0 && peones2[i-1] == 0){
                            cont += 1;
                            colPeonesPasados[i] = 1;
                        }
                        else if (peones2[i] == 0 && peones2[i-1] != 0){
                            if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else if (peones2[i] != 0 && peones2[i-1] == 0){
                            if((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10)){
                                cont += 1;
                                colPeonesPasados[i] = 1;
                            }
                        }
                        else{
                            if (((posicionesPiezas[pieza1][j] % 10) <= (posicionesPiezas[pieza2][k] % 10)) && ((posicionesPiezas[pieza1][j] % 10) >= (posicionesPiezas[pieza2][k-peones2[i-1]] % 10))){
                                cont += 1;
                                colPeonesPasados[i] = 1; 
                            }
                        }
                    }
                }
            }
        }

        j += peones1[i];
        k += peones2[i];
    }

    return cont;    
}


/**
 * @brief Número de islas de peones
 * 
 * @param peones array con las columnas ocupadas por peones
 * @return int devuelve la cantidad de islas de peones que tiene un bando
 */
int islasPeones(const int peones[]){
    // Contadores
    int cont1 = 0;
    int cont2 = 0;

    for (int i = 0; i < columnas; i++){
        if (peones[i] > 0){
            cont1 += 1;
        }
        else{
            if (cont1 > 0){
                cont2 += 1;
                cont1 = 0;
            }
        }
    }

    if (cont1 > 0){
        cont2 += 1;
    }

    return cont2;
}


/**
 * @brief Número de falanges de peones que tiene un bando en la posición
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param peones array con el número de peones por columnas 
 * @param pieza pieza a estudiar, ya sea peón blanco o negro
 * @param falange matriz para representar con 1's y 0's las posiciones donde se encuentra la falange en el tablero
 * @return int devuelve el número de falanges de un bando en la posición
 */
int falangePeones(const vector<vector<int>> & posicionesPiezas, const int peones[], const int pieza, int falange[][columnas]){
    // Número de falanges
    int numFalanges = 0;
    // Contador
    int cont = 1;
    // Casilla que se está explorando
    int num = 0;

    if (posicionesPiezas[pieza].size() > 0){
        vector<int> auxiliar(posicionesPiezas[pieza]);
        num = auxiliar[0];
        falange[((num/10)%10)-1][(num%10)-1] += 1;

        auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
        num += 10;

        while (auxiliar.size() > 0){
            if (find(auxiliar.begin(), auxiliar.end(), num) != auxiliar.end()){
                auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                falange[((num/10)%10)-1][(num%10)-1] += 1;
                num += 10;
                cont += 1;
            }
            else if (cont == 1){
                falange[(((num-10)/10)%10)-1][(num%10)-1] = 0;
                num = auxiliar[0];
                cont = 0;
            }
            else if (cont > 1){
                numFalanges += 1;
                num = auxiliar[0];
                cont = 0;
            }
        }
    }

    if (cont > 1){
        numFalanges += 1;
    }
    else{
        falange[(((num-10)/10)%10)-1][(num%10)-1] = 0;
    }

    return numFalanges;
}


/**
 * @brief Número de grupos de peones conectados que tiene un bando en la posición
 * 
 * @param posicionesPiezas casillas ocupadas por las piezas
 * @param peones array con el número de peones por columnas 
 * @param pieza pieza a estudiar, ya sea peón blanco o negro
 * @param conectados matriz para representar con 1's y 0's las posiciones donde se encuentran los grupos de peones conectados
 * @return int devuelve el número de grupos de peones conectados de un bando en la posición
 */
int peonesConectados(const vector<vector<int>> & posicionesPiezas, const int peones[], const int pieza, int conectados[][columnas]){
    // Número de grupos de peones conectados
    int numConectados = 0;
    // Contador
    int cont = 1;
    // Posición del peón
    int num = 0;

    if (posicionesPiezas[pieza].size() > 0){
        vector<int> auxiliar(posicionesPiezas[pieza]);
        vector<int> auxiliarVisitados = {};

        num = auxiliar[0];
        auxiliarVisitados.push_back(num);
        conectados[((num/10)%10)-1][(num%10)-1] += 1;
        auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());

        while (auxiliar.size() > 0){
            if (auxiliarVisitados.size() > 0){            
                if (find(auxiliar.begin(), auxiliar.end(), auxiliarVisitados[0]+10) != auxiliar.end()){
                    num = auxiliarVisitados[0] + 10;
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    auxiliarVisitados.push_back(num);
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont += 1;
                }
                else if (find(auxiliar.begin(), auxiliar.end(), auxiliarVisitados[0]+11) != auxiliar.end()){
                    num = auxiliarVisitados[0] + 11;
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    auxiliarVisitados.push_back(num);
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont += 1;
                }
                else if (find(auxiliar.begin(), auxiliar.end(), auxiliarVisitados[0]+9) != auxiliar.end()){
                    num = auxiliarVisitados[0] + 9;
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    auxiliarVisitados.push_back(num);
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont += 1;
                }
                else if (find(auxiliar.begin(), auxiliar.end(), auxiliarVisitados[0]-10) != auxiliar.end()){
                    num = auxiliarVisitados[0] - 10;
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    auxiliarVisitados.push_back(num);
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont += 1;
                }
                else if (find(auxiliar.begin(), auxiliar.end(), auxiliarVisitados[0]-11) != auxiliar.end()){
                    num = auxiliarVisitados[0] - 11;
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    auxiliarVisitados.push_back(num);
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont += 1;
                }
                else if (find(auxiliar.begin(), auxiliar.end(), auxiliarVisitados[0]-9) != auxiliar.end()){
                    num = auxiliarVisitados[0] - 9;
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    auxiliarVisitados.push_back(num);
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont += 1;
                }
                else if (cont < 2){
                    auxiliarVisitados.erase(remove(auxiliarVisitados.begin(), auxiliarVisitados.end(), auxiliarVisitados[0]), auxiliarVisitados.end());
                    conectados[((num/10)%10)-1][(num%10)-1] = 0;
                }
                else if (cont > 1){     
                    auxiliarVisitados.erase(remove(auxiliarVisitados.begin(), auxiliarVisitados.end(), auxiliarVisitados[0]), auxiliarVisitados.end());         
                }
            }
            else{
                if (cont < 2){
                    conectados[((num/10)%10)-1][(num%10)-1] = 0;
                    num = auxiliar[0];
                    auxiliarVisitados.push_back(num);
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    cont = 1;
                }
                else{
                    num = auxiliar[0];
                    auxiliarVisitados.push_back(num);
                    auxiliar.erase(remove(auxiliar.begin(), auxiliar.end(), num), auxiliar.end());
                    conectados[((num/10)%10)-1][(num%10)-1] += 1;
                    numConectados += 1;
                    cont = 1;
                }
            }
        }
    }

    if (cont > 1){
        numConectados += 1;
    }
    else{
        conectados[((num/10)%10)-1][(num%10)-1] = 0;
    }

    return numConectados;
}




int main() {

    // Archivos donde leemos y escribimos
    ifstream fin;
    ofstream fout, foutTablero1, foutTablero2;
    
    // Código FEN
    string fen;

    // Representa la posición
    int posicion[filas][columnas] = {0};

    // Número de casillas
    int numCasillas = filas*columnas;

    // Representa el turno, 1 las piezas blancas, -1 las piezas negras
    int turno = 1;

    // Vector de vectores con las piezas del tablero
    vector<vector<int>> posicionesPiezas(piezas, vector<int> (0,0));

    // Arrays para saber las columnas en las que están los peones
    int peonesBlancos[columnas] = {0};
    int peonesNegros[columnas] = {0};

    // Arrays para las columnas abiertas y semiabiertas
    int columnasAbiertas[columnas] = {0};
    int columnasSemiabiertasB[columnas] = {0};
    int columnasSemiabiertasN[columnas] = {0};

    // Peones
    int colPeonesDobladosB[columnas] = {0};
    int colPeonesAisladosB[columnas] = {0};
    int colPeonesRetrasadosB[columnas] = {0};
    int colPeonesPasadosB[columnas] = {0};

    int colPeonesDobladosN[columnas] = {0};
    int colPeonesAisladosN[columnas] = {0};
    int colPeonesRetrasadosN[columnas] = {0};
    int colPeonesPasadosN[columnas] = {0};

    // Falanges de peones
    int falangeB[filas][columnas] = {0};
    int falangeN[filas][columnas] = {0};

    // Peones conectados
    int conectadosB[filas][columnas] = {0};
    int conectadosN[filas][columnas] = {0};

    // Contador
    int cont = 1;

    // Abrimos el archivo de entrada en modo lectura  
    fin.open("FEN_DB.txt", ios::in);

    if (fin.fail()){
        cout << "El archivo de lectura no se pudo abrir";
        exit(1);
    }

    //Abrimos el archivo de salida en modo escritura
    fout.open("Etiquetas.csv", ios::out);

    if (fout.fail()){
        cout << "El archivo de escritura Etiquetas.csv no se pudo abrir";
        exit(1);
    }

    // Primera codificación
    //Abrimos el archivo de salida para los 7 tableros en modo escritura
    foutTablero1.open("PrimeraCodificacionTablero.csv", ios::out);

    if (foutTablero1.fail()){
        cout << "El archivo de escritura PrimeraCodificacionTablero.csv no se pudo abrir";
        exit(1);
    }

    // Segunda codificación
    //Abrimos el archivo de salida para la versión de un tablero de enteros en modo escritura
    foutTablero2.open("SegundaCodificacionTablero.csv", ios::out);

    if (foutTablero2.fail()){
        cout << "El archivo de escritura SegundaCodificacionTablero.csv no se pudo abrir";
        exit(1);
    }

    // Etiquetas
    fout << "Posición número;FEN posicion;FEN movimiento;Turno;Ventaja de espacio;Número de columnas abiertas;Columnas abiertas;Alfiles del mismo color;Alfiles de distinto color;";
    fout << "Enroque corto blanco;Enroque largo blanco;Número de columnas semiabiertas para el blanco;Columnas semiabiertas para el blanco;Peones blancos;Caballos blancos;Alfiles blancos;Torres blancas;Damas blancas;Torre blanca en séptima;Torres blancas dobladas;Torres blancas ligadas en la misma fila;Pistola de Alekhine blanca;";
    fout << "Peones blancos doblados;Columnas con los peones blancos doblados;Peones blancos aislados;Columnas con los peones blancos aislados;Peones blancos retrasados;Columnas con los peones blancos retrasados;Peones blancos pasados;Columnas con los peones blancos pasados;Número de islas de peones blancos;Columnas con los peones blancos;Número de falanges de peones blancos;Tablero con las falanges de peones blancos;Número de grupos de peones blancos conectados;Tablero con los grupos de peones blancos;";
    fout << "Enroque corto negro;Enroque largo negro;Número de columnas semiabiertas para el negro;Columnas semiabiertas para el negro;Peones negros;Caballos negros;Alfiles negros;Torres negras;Damas negras;Torre negra en séptima;Torres negras dobladas;Torres negras ligadas en la misma fila;Pistola de Alekhine negra;";
    fout << "Peones negros doblados;Columnas con los peones negros doblados;Peones negros aislados;Columnas con los peones negros aislados;Peones negros retrasados;Columnas con los peones negros retrasados;Peones negros pasados;Columnas con los peones negros pasados;Número de islas de peones negros;Columnas con los peones negros;Número de falanges de peones negros;Tablero con las falanges de peones negros;Número de grupos de peones negros conectados;Tablero con los grupos de peones negros" << endl;

    // Estructura de datos de entrada 6 tableros más uno para saber el turno
    foutTablero1 << "Tablero número;Tablero Reyes;Tablero Damas;Tablero Torres;Tablero Alfiles;Tablero Caballos;Tablero Peones;Turno" << endl;

    // Estructura de datos de entrada del tablero con la representación de enteros
    foutTablero2 << "Tablero número;Tablero" << endl;

    while(!fin.eof()){
        // Leemos línea por línea el archivo
        getline(fin, fen);


        // Primer campo del código fen que representa la posición de las piezas
        int longPrimerCampo = fen.substr(0, fen.find(" ")).length();
        
        // Tercer campo del código fen que representa los enroques permitidos
        int indiceTercerCampo = longPrimerCampo+3;

        if (longPrimerCampo > 0){

            // Imprimimos el contador de la posición
            fout << cont;
            // Imprimimos el código fen
            fout << ";" << fen;

            // Comprobamos si el turno lo tienen las blancas o las negras
            fen.find("w") != string::npos ? turno = 1 : turno = -1;
            fout << ";" << turno;
                
            
            // Creamos el tablero
            crearTablero(fen, longPrimerCampo, posicion, posicionesPiezas, peonesBlancos, peonesNegros);

            /////////////////////////////////////////////////////////////////////////////////
            // Recogemos las estructuras de datos necesarias para entrenar la red neuronal //
            /////////////////////////////////////////////////////////////////////////////////

            // Primera codificación, 7 tableros, 6 para las piezas y 1 para el turno
            foutTablero1 << cont << ";";

            // Reyes
            imprimirTablero(posicion, foutTablero1, 1, -1);
            // Damas
            imprimirTablero(posicion, foutTablero1, 2, -2);
            // Torres
            imprimirTablero(posicion, foutTablero1, 3, -3);
            // Alfiles
            imprimirTablero(posicion, foutTablero1, 4, -4);
            // Caballos
            imprimirTablero(posicion, foutTablero1, 5, -5);
            // Peones
            imprimirTablero(posicion, foutTablero1, 6, -6);
            // Turno
            for (int i = 0; i < numCasillas; i++){
                if (i == numCasillas-1){
                    foutTablero1 << turno;
                }
                else{
                    foutTablero1 << turno << ",";
                }
            }

            foutTablero1 << endl;


            // Segunda codifiación, un tablero con la codificación de enteros
            foutTablero2 << cont << ";";

            // Imprimimos el tablero
            for (int i = filas-1; i >= 0; i--){
                for (int j = 0; j < columnas; j++){
                    if (i == 0 && j == columnas-1){
                        foutTablero2 << posicion[i][j];
                    }
                    else{
                        foutTablero2 << posicion[i][j] << ",";
                    }
                }
            }

            foutTablero2 << endl;




            // Ordenamos los vectores para facilitar las búsquedas de piezas ordenados por columnas y luego por filas
            sort(posicionesPiezas[torreB].begin(), posicionesPiezas[torreB].end());
            sort(posicionesPiezas[alfilB].begin(), posicionesPiezas[alfilB].end());
            sort(posicionesPiezas[caballoB].begin(), posicionesPiezas[caballoB].end());
            sort(posicionesPiezas[peonB].begin(), posicionesPiezas[peonB].end());
            sort(posicionesPiezas[torreN].begin(), posicionesPiezas[torreN].end());
            sort(posicionesPiezas[alfilN].begin(), posicionesPiezas[alfilN].end());
            sort(posicionesPiezas[caballoN].begin(), posicionesPiezas[caballoN].end());
            sort(posicionesPiezas[peonN].begin(), posicionesPiezas[peonN].end());


            // Algoritmos que simulan la obtención de etiquetas

            // Ventaja espacio
            fout << ";" << ventajaEspacio(posicionesPiezas, peonesBlancos, peonesNegros);

            // Columnas abiertas
            fout << ";" << colAbierta(peonesBlancos, peonesNegros, columnasAbiertas) << ";";

            for (int i = 0; i < columnas; i++){
                fout << columnasAbiertas[i] << " ";
            }


            // Alfiles del mismo color
            fout << ";" << mismoColor(posicionesPiezas);
            
            // Alfiles de distinto color
            fout << ";" << distColor(posicionesPiezas);


            //****** PIEZAS BLANCAS ******//

            // Enroque corto blanco
            fout << ";" << enroque(fen, indiceTercerCampo, 'K');
            // Enroque largo blanco
            fout << ";" << enroque(fen, indiceTercerCampo, 'Q');

            // Columnas semiabiertas para el blanco
            fout << ";" << colSemiAbierta(peonesBlancos, peonesNegros, columnasSemiabiertasB) << ";";

            for (int i = 0; i < columnas; i++){
                fout << columnasSemiabiertasB[i] << " ";
            }

            // Número de peones blancos
            fout << ";" << numPiezas(posicionesPiezas, peonB);

            // Número de caballos blancos
            fout << ";" << numPiezas(posicionesPiezas, caballoB);

            // Número de alfiles blancos
            fout << ";" << numPiezas(posicionesPiezas, alfilB);

            // Número de torres blancas
            fout << ";" << numPiezas(posicionesPiezas, torreB);
            
            // Número de damas blancas
            fout << ";" << numPiezas(posicionesPiezas, damaB);

            // TORRES

            // Torre blanca en séptima
            fout << ";" << torreSeptima(posicionesPiezas, torreB);

            // Torres blancas dobladas
            fout << ";" << torresDobladas(posicionesPiezas, torreB);

            // Torres blancas ligadas en la misma fila
            fout << ";" << torresLigMismaFila(posicionesPiezas, torreB);

            // Pistola de Alekhine blanca
            fout << ";" << pistolaAlekhine(posicionesPiezas, damaB, torreB);

            // ESTRUCTURAS DE PEONES

            // Peones blancos doblados
            fout << ";" << peonesDoblados(peonesBlancos, colPeonesDobladosB) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesDobladosB[i] << " ";
            }

            // Peones blancos aislados
            fout << ";" << peonesAislados(peonesBlancos, colPeonesAisladosB) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesAisladosB[i] << " ";
            }

            // Peones blancos retrasados
            fout << ";" << peonesRetrasados(posicionesPiezas, peonesBlancos, peonB, colPeonesRetrasadosB) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesRetrasadosB[i] << " ";
            }

            // Peones blancos pasados
            fout << ";" << peonesPasados(posicionesPiezas, peonesBlancos, peonesNegros, peonB, peonN, colPeonesPasadosB) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesPasadosB[i] << " ";
            }

            // Número de islas de peones blancos
            fout << ";" << islasPeones(peonesBlancos) << ";";

            for (int i = 0; i < columnas; i++){
                fout << peonesBlancos[i] << " ";
            }

            // Falange peones blancos
            fout << ";" << falangePeones(posicionesPiezas, peonesBlancos, peonB, falangeB) << ";";

            for (int i = columnas-1; i > -1; i--){
                for (int j = 0; j < filas; j++){
                    if (i == 0 && j == filas-1){
                        fout << falangeB[j][i];
                    }
                    else{
                        fout << falangeB[j][i] <<  " ";
                    }
                }
            }

            // Peones blancos conectados
            fout << ";" << peonesConectados(posicionesPiezas, peonesBlancos, peonB, conectadosB) << ";";

            for (int i = columnas-1; i > -1; i--){
                for (int j = 0; j < filas; j++){
                    if (i == 0 && j == filas-1){
                        fout << conectadosB[j][i];
                    }
                    else{
                        fout << conectadosB[j][i] <<  " ";
                    }
                }
            }



            //****** PIEZAS NEGRAS ******//

            // Enroque corto negro
            fout << ";" << enroque(fen, indiceTercerCampo, 'k');
            // Enroque largo negro
            fout << ";" << enroque(fen, indiceTercerCampo, 'q');

            // Columnas semiabiertas para el negro
            fout << ";" << colSemiAbierta(peonesNegros, peonesBlancos, columnasSemiabiertasN) << ";";

            for (int i = 0; i < columnas; i++){
                fout << columnasSemiabiertasN[i] << " ";
            }

            // Número de peones negros
            fout << ";" << numPiezas(posicionesPiezas, peonN);
            
            // Número de caballos negros
            fout << ";" << numPiezas(posicionesPiezas, caballoN);
            
            // Número de alfiles negros
            fout << ";" << numPiezas(posicionesPiezas, alfilN);
            
            // Número de torres negras
            fout << ";" << numPiezas(posicionesPiezas, torreN);
            
            // Número de damas negras
            fout << ";" << numPiezas(posicionesPiezas, damaN);


            // TORRES

            // Torre negra en séptima
            fout << ";" << torreSeptima(posicionesPiezas, torreN);

            // Torres negras dobladas
            fout << ";" << torresDobladas(posicionesPiezas, torreN);

            // Torres negras ligadas en la misma fila
            fout << ";" << torresLigMismaFila(posicionesPiezas, torreN);

            // Pistola de Alekhine negra
            fout << ";" << pistolaAlekhine(posicionesPiezas, damaN, torreN);


            // ESTRUCTURAS DE PEONES

            // Peones negros doblados
            fout << ";" << peonesDoblados(peonesNegros, colPeonesDobladosN) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesDobladosN[i] << " ";
            }

            // Peones negros aislados
            fout << ";" << peonesAislados(peonesNegros, colPeonesAisladosN) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesAisladosN[i] << " ";
            }

            // Peones negros retrasados
            fout << ";" << peonesRetrasados(posicionesPiezas, peonesNegros, peonN, colPeonesRetrasadosN) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesRetrasadosN[i] << " ";
            }

            // Peones negros pasados
            fout << ";" << peonesPasados(posicionesPiezas, peonesNegros, peonesBlancos, peonN, peonB, colPeonesPasadosN) << ";";

            for (int i = 0; i < columnas; i++){
                fout << colPeonesPasadosN[i] << " ";
            }

            // Número de islas de peones negros
            fout << ";" << islasPeones(peonesNegros) << ";";

            for (int i = 0; i < columnas; i++){
                fout << peonesNegros[i] << " ";
            }

            // Falange peones negros
            fout << ";" << falangePeones(posicionesPiezas, peonesNegros, peonN, falangeN) << ";";

            for (int i = columnas-1; i > -1; i--){
                for (int j = 0; j < filas; j++){
                    if (i == 0 && j == filas-1){
                        fout << falangeN[j][i];
                    }
                    else{
                        fout << falangeN[j][i] <<  " ";
                    }
                }
            }

            // Peones blancos conectados
            fout << ";" << peonesConectados(posicionesPiezas, peonesNegros, peonN, conectadosN) << ";";          

            for (int i = columnas-1; i > -1; i--){
                for (int j = 0; j < filas; j++){
                    if (i == 0 && j == filas-1){
                        fout << conectadosN[j][i];
                    }
                    else{
                        fout << conectadosN[j][i] <<  " ";
                    }
                }
            }

            fout << endl;

            // Restauramos valores iniciales

            // Representa la posición(tablero)
            memset(posicion, 0, sizeof(posicion));
            
            // Vector de vectores con las piezas del tablero
            for (int i = 0; i < piezas; i++){
                posicionesPiezas[i].clear();
            }
            // Arrays para saber las columnas en las que están los peones
            memset(peonesBlancos, 0, sizeof(peonesBlancos));
            memset(peonesNegros, 0, sizeof(peonesNegros));

            // Arrays para saber las columnas abiertas y semiabiertas
            memset(columnasAbiertas, 0, sizeof(columnasAbiertas));
            memset(columnasSemiabiertasB, 0, sizeof(columnasSemiabiertasB));
            memset(columnasSemiabiertasN, 0, sizeof(columnasSemiabiertasN));

            // Estructuras de peones
            memset(colPeonesDobladosB, 0, sizeof(colPeonesDobladosB));
            memset(colPeonesAisladosB, 0, sizeof(colPeonesAisladosB));
            memset(colPeonesRetrasadosB, 0, sizeof(colPeonesRetrasadosB));
            memset(colPeonesPasadosB, 0, sizeof(colPeonesPasadosB));
            memset(colPeonesDobladosN, 0, sizeof(colPeonesDobladosN));
            memset(colPeonesAisladosN, 0, sizeof(colPeonesAisladosN));
            memset(colPeonesRetrasadosN, 0, sizeof(colPeonesRetrasadosN));
            memset(colPeonesPasadosN, 0, sizeof(colPeonesPasadosN));

            // Falanges de peones
            memset(falangeB, 0, sizeof(falangeB));
            memset(falangeN, 0, sizeof(falangeN));

            // Peones conectados
            memset(conectadosB, 0, sizeof(conectadosB));
            memset(conectadosN, 0, sizeof(conectadosN));

            // Aumentamos el contador
            cont += 1;
        }
    }

    // Cerramos los archivos
    fin.close();
    fout.close();
    foutTablero1.close();
    foutTablero2.close();
}