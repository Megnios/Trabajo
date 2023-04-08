#include <string>

#include "vector.h"

using namespace std;


void chequear_espacio_vector(vector* vector_dinamico){

    if(vector_dinamico->cantidad_paises == vector_dinamico->tamanio - 1){
        ampliar_vector(vector_dinamico);
    }

}


void generar_vector(vector* vector_dinamico){

    vector_dinamico->paises = new datos_grupo[vector_dinamico->tamanio];

}

void ampliar_vector(vector* vector_dinamico){
    vector_dinamico->tamanio *= 2;

    datos_grupo* nuevo_vector = new datos_grupo[vector_dinamico->tamanio];

    for(int i = 0; i < vector_dinamico->cantidad_paises; i++){
        nuevo_vector[i] = vector_dinamico->paises[i];

    }

    delete[] vector_dinamico->paises;
    
    vector_dinamico->paises = nuevo_vector;

}


void eliminar_vector(vector* vector_dinamico){

    if(vector_dinamico->paises != nullptr){
        delete[] vector_dinamico->paises;
    }

}
