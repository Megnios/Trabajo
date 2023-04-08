#include <iostream>
#include <fstream>
#include "vector.h"
#include "constantes.h"
#include "utiles.h"

using namespace std;



int main(){

    
    ifstream archivo_grupos;
    vector vector_dinamico;

    archivo_grupos.open(NOMBRE_EQUIPOS);

    if(!archivo_grupos.fail()){
        procesar_archivo_grupos(archivo_grupos, &vector_dinamico);
    }
    else{
        cout << "No se pudo abrir el archivo de equipos por razones desconocidas";

    }

    archivo_grupos.close();


    ifstream archivo_resultados;
    copa_mundial copa_2022;

    archivo_resultados.open(RESULTADOS);

    if(!archivo_resultados.fail()){
        procesar_archivo_resultados(archivo_resultados, copa_2022);
    }
    else{
        cout << "No se pudo abrir el archivo de resultados por razones desconocidas";

    }

    archivo_resultados.close();


    gestionar_menu_usuario(copa_2022, vector_dinamico);

    eliminar_vector(&vector_dinamico);
    
    return 0;
}