#ifndef ARCHIVO_VECTOR_DINAMICO
#define ARCHIVO_VECTOR_DINAMICO

#include <string>

struct datos_grupo{
    std::string nombre_equipo;
    std::string grupo;
};

struct vector{
    int tamanio = 5;
    int cantidad_paises = 0;
    datos_grupo* paises = nullptr;
};



// Pre: -
// Post: Chequea si al vector le queda espacio para guardar datos. Realiza las acciones pertinentes en caso de no quedar mas memoria libre.
void chequear_espacio_vector(vector* vector_dinamico);


// Pre: -
// Post: Pide memoria y la asigna al vector dinamico.
void generar_vector(vector* vector_dinamico);


// Pre: -
// Post: Reemplaza el vector dinamico original por otro con el doble de memoria y con la informacion preexistente cargada en el mismo orden.
void ampliar_vector(vector* vector_dinamico);


// Pre: -
// Post: Libera la memoria pedida para el vector dinamico.
void eliminar_vector(vector* vector_dinamico);



#endif
