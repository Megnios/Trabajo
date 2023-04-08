#include <string>
#include <iostream>
#include <fstream>

#include "utiles.h"
#include "vector.h"
#include "constantes.h"


using namespace std;


int len(string texto){
    int cantidad_caracteres = 0;
    string string_innecesaria = ESPACIO_VACIO;

    for(char c: texto){
        cantidad_caracteres++;                 
        string_innecesaria = c;                                            // No encontre otra manera de sacar el warning de unused variable porque no estaba
    }                                                                      // usando el char c.

    return cantidad_caracteres;
}


void separar_linea(string linea_leida, string datos[], int &tope_datos){
    string dato_actual = ESPACIO_VACIO;
    tope_datos = 0;

    for(int i = 0; i <= len(linea_leida); i++){

        if(linea_leida[i] != ESPACIO && i != len(linea_leida)){
            dato_actual += linea_leida[i];
        }
        else{
            datos[tope_datos] = dato_actual;
            dato_actual = ESPACIO_VACIO;
            tope_datos++;
        }

    }

}


string arreglar_nombre_pais(string nombre_pais){
    string linea_arreglada = ESPACIO_VACIO;

    for(char c: nombre_pais){
        if (c != GUION_BAJO){
            linea_arreglada += c;
        }
        else{
            linea_arreglada += ESPACIO;
        }
    }
    return linea_arreglada;

}


void insertar_pais(vector* vector_dinamico, string pais, string grupo){
    int i = vector_dinamico->cantidad_paises -1;

    while(pais < vector_dinamico->paises[i].nombre_equipo && i >= 0){
        vector_dinamico->paises[i + 1] = vector_dinamico->paises[i];
        i--;
        
    }

    if(vector_dinamico->cantidad_paises == 0){
        vector_dinamico->paises[vector_dinamico->cantidad_paises].nombre_equipo = pais;
        vector_dinamico->paises[vector_dinamico->cantidad_paises].grupo = grupo;
        vector_dinamico->cantidad_paises++;
    }
    else{
        vector_dinamico->paises[i + 1].nombre_equipo = pais;
        vector_dinamico->paises[i + 1].grupo = grupo;
        vector_dinamico->cantidad_paises++;
    }

}


void procesar_archivo_grupos(ifstream &archivo, vector* vector_dinamico){
    string linea_leida;
    string datos[MAX_CAMPOS_ARCHIVO_GRUPOS];
    int tope_datos = 0;

    generar_vector(vector_dinamico);

    while(getline(archivo, linea_leida)){
        separar_linea(linea_leida, datos, tope_datos);
        datos[NOMBRE_PAIS] = arreglar_nombre_pais(datos[NOMBRE_PAIS]);       

        chequear_espacio_vector(vector_dinamico);

        insertar_pais(vector_dinamico, datos[NOMBRE_PAIS], datos[GRUPO_PAIS]);
        
    }

}


void actualizar_instancia(string linea_leida, char &instancia_actual){

    if(linea_leida == LINEA_LEIDA_GRUPOS){
        instancia_actual = INSTANCIA_GRUPOS;
    }
    else if(linea_leida == LINEA_LEIDA_OCTAVOS){
        instancia_actual = INSTANCIA_OCTAVOS;
    }
    else if(linea_leida == LINEA_LEIDA_CUARTOS){
        instancia_actual = INSTANCIA_CUARTOS;
    }
    else if(linea_leida == LINEA_LEIDA_SEMIFINALES){
        instancia_actual = INSTANCIA_SEMIFINALES;
    }
    else if(linea_leida == LINEA_LEIDA_TERCER_PUESTO){
        instancia_actual = INSTANCIA_TERCER_PUESTO;
    }
    else if(linea_leida == LINEA_LEIDA_FINAL){
        instancia_actual = INSTANCIA_FINAL;
    }

}


int buscar_posicion_pais(fase fase_actual, string pais_a_buscar){
    int posicion_pais = 0;
    int posicion_encontrada = NO_ENCONTRADA;

    while(posicion_encontrada == NO_ENCONTRADA && posicion_pais < fase_actual.tope_paises){

        if(pais_a_buscar == fase_actual.paises[posicion_pais].nombre_pais){
            posicion_encontrada = posicion_pais;
        }
        posicion_pais++;

    }
    return posicion_encontrada;
}

void asignar_posiciones_grupos(string vector_datos[], fase &grupos){

    if(!es_pais_existente(grupos, vector_datos[NOMBRE_PAIS1])){
        grupos.paises[grupos.tope_paises].nombre_pais = vector_datos[NOMBRE_PAIS1];
        grupos.tope_paises++;
    }

    if(!es_pais_existente(grupos, vector_datos[NOMBRE_PAIS_2])){
        grupos.paises[grupos.tope_paises].nombre_pais = vector_datos[NOMBRE_PAIS_2];
        grupos.tope_paises++;
    }
}   


void asignar_puntos_grupos(int goles_pais1, int goles_pais2, int posicion_pais1, int posicion_pais2, fase &grupos){

    if(goles_pais1 > goles_pais2){
        grupos.paises[posicion_pais1].cantidad_puntos += 3;
    }

    else if(goles_pais2 > goles_pais1){
        grupos.paises[posicion_pais2].cantidad_puntos += 3;
    }

    else{
        grupos.paises[posicion_pais1].cantidad_puntos += 1;
        grupos.paises[posicion_pais2].cantidad_puntos += 1;
    }

}


void asignar_info_grupos(string vector_datos[], fase &grupos){

    asignar_posiciones_grupos(vector_datos, grupos);
    
    int posicion_pais1 = buscar_posicion_pais(grupos, vector_datos[NOMBRE_PAIS]);
    int posicion_pais2 = buscar_posicion_pais(grupos, vector_datos[NOMBRE_PAIS_2]);

    asignar_puntos_grupos(stoi(vector_datos[GOLES_EQUIPO_1]), stoi(vector_datos[GOLES_EQUIPO_2]),
                          posicion_pais1, posicion_pais2, grupos);

}


void intercambiar(pais &pais1, pais &pais2){
    pais aux = pais1;
    pais1 = pais2;
    pais2 = aux;

}


void ordenar_por_puntaje(fase &fase_actual, int posicion_pais){
    int i = 0;

    while(i < fase_actual.tope_paises){

        if(fase_actual.paises[posicion_pais].cantidad_puntos > fase_actual.paises[i].cantidad_puntos){
            intercambiar(fase_actual.paises[i], fase_actual.paises[posicion_pais]);
        }
        i++;
    }


}


void asignar_puntos_eliminatorias(int penales_pais1, int penales_pais2, int goles_pais1, int goles_pais2, fase &fase_actual, int posicion_pais1, int posicion_pais2){
    
    if(penales_pais1 == NO_HAY_PENALES){

        if(goles_pais1 > goles_pais2){
            fase_actual.paises[posicion_pais1].cantidad_puntos += 3;
        }
        else{
            fase_actual.paises[posicion_pais2].cantidad_puntos += 3;
        }
    }

    else if(penales_pais1 > penales_pais2){
        fase_actual.paises[posicion_pais1].cantidad_puntos += 2;
        fase_actual.paises[posicion_pais2].cantidad_puntos += 1;

    }
    else{
        fase_actual.paises[posicion_pais2].cantidad_puntos += 2;
        fase_actual.paises[posicion_pais1].cantidad_puntos += 1;

    }
}



void asignar_posiciones_eliminatorias(fase &fase_actual, string vector_datos[]){

    if(!es_pais_existente(fase_actual, vector_datos[NOMBRE_PAIS1])){
        fase_actual.paises[fase_actual.tope_paises].nombre_pais = vector_datos[NOMBRE_PAIS1];
        fase_actual.tope_paises++;
    }

    if(!es_pais_existente(fase_actual, vector_datos[NOMBRE_PAIS2])){
        fase_actual.paises[fase_actual.tope_paises].nombre_pais = vector_datos[NOMBRE_PAIS2];
        fase_actual.tope_paises++;
    }
}


void asignar_info_eliminatorias(fase &fase_actual, string vector_datos[]){

    asignar_posiciones_eliminatorias(fase_actual, vector_datos);

    int posicion_pais1 = buscar_posicion_pais(fase_actual, vector_datos[NOMBRE_PAIS1]);
    int posicion_pais2 = buscar_posicion_pais(fase_actual, vector_datos[NOMBRE_PAIS2]);

    asignar_puntos_eliminatorias(stoi(vector_datos[PENALES_EQUIPO1]), stoi(vector_datos[PENALES_EQUIPO2]),
                                 stoi(vector_datos[GOLES_EQUIPO_1]), stoi(vector_datos[GOLES_EQUIPO2]), fase_actual,
                                 posicion_pais1, posicion_pais2);

    
    ordenar_por_puntaje(fase_actual, posicion_pais1);
    ordenar_por_puntaje(fase_actual, posicion_pais2);

}


void procesar_informacion_resultados(string vector_datos[], copa_mundial &copa_2022, char instancia_actual){

    switch(instancia_actual){
                
        case INSTANCIA_GRUPOS:
            asignar_info_grupos(vector_datos, copa_2022.grupos);
            break;
                
        case INSTANCIA_OCTAVOS:
            asignar_info_eliminatorias(copa_2022.octavos, vector_datos);
            break;
                
        case INSTANCIA_CUARTOS:
            asignar_info_eliminatorias(copa_2022.cuartos, vector_datos);
            break;
                
        case INSTANCIA_SEMIFINALES:
            asignar_info_eliminatorias(copa_2022.semifinales, vector_datos);
            break;

        case INSTANCIA_TERCER_PUESTO:
            asignar_info_eliminatorias(copa_2022.tercer_puesto, vector_datos);
            break;

        case INSTANCIA_FINAL:
            asignar_info_eliminatorias(copa_2022.final, vector_datos);
            break;
     
    }   

}


void procesar_linea(string linea, string vector[], int &tope_vector){
    string palabra_actual = ESPACIO_VACIO;
    tope_vector = 0;

    for(int i = 0; i <= len(linea); i++){

        if(linea[i] == COMA || i == len(linea)){
            vector[tope_vector] = palabra_actual;
            tope_vector++;
            palabra_actual = ESPACIO_VACIO;
        }
        else{
            palabra_actual += linea[i];
        }
    }

}




void procesar_archivo_resultados(ifstream &archivo_resultados, copa_mundial &copa_2022){
    string vector_datos[MAX_CAMPOS_ARCHIVO_RESULTADO];
    int tope_vector_datos = 0;
    string linea_leida;
    char instancia_actual;

    while(getline(archivo_resultados, linea_leida)){

        procesar_linea(linea_leida, vector_datos, tope_vector_datos);

        if(tope_vector_datos == 1){
            actualizar_instancia(linea_leida, instancia_actual);
        }
        else{ 
            procesar_informacion_resultados(vector_datos, copa_2022, instancia_actual);

        }
    }
}



bool es_pais_existente(fase fase_actual, string pais_a_buscar){
    bool esta_en_fase = false;
    int pais_actual = 0;

    while(!esta_en_fase && pais_actual < fase_actual.tope_paises){

        if(fase_actual.paises[pais_actual].nombre_pais == pais_a_buscar){
            esta_en_fase = true;
        }

        pais_actual++;
    }

    return esta_en_fase;
}


void listar_equipos_totales(vector vector_dinamico){

    for(int i = 0; i < vector_dinamico.cantidad_paises; i++){

        cout << "PAIS: " << vector_dinamico.paises[i].nombre_equipo << " y " << "GRUPO: " << vector_dinamico.paises[i].grupo << endl << endl;
    }
    cout << endl << endl;
}


int devolver_puntaje_total(copa_mundial copa_2022, string pais){
    int puntaje_total = 0;
    int posicion_fase_actual;


    if(es_pais_existente(copa_2022.final, pais)){
        posicion_fase_actual = buscar_posicion_pais(copa_2022.final, pais);
        puntaje_total += copa_2022.final.paises[posicion_fase_actual].cantidad_puntos;
    }
    if(es_pais_existente(copa_2022.tercer_puesto, pais)){
        posicion_fase_actual = buscar_posicion_pais(copa_2022.tercer_puesto, pais);
        puntaje_total += copa_2022.tercer_puesto.paises[posicion_fase_actual].cantidad_puntos;
    }
    if(es_pais_existente(copa_2022.semifinales, pais)){
        posicion_fase_actual = buscar_posicion_pais(copa_2022.semifinales, pais);
        puntaje_total += copa_2022.semifinales.paises[posicion_fase_actual].cantidad_puntos;
    }
    if(es_pais_existente(copa_2022.cuartos, pais)){
        posicion_fase_actual = buscar_posicion_pais(copa_2022.cuartos, pais);
        puntaje_total += copa_2022.cuartos.paises[posicion_fase_actual].cantidad_puntos;
    }
    if(es_pais_existente(copa_2022.octavos, pais)){
        posicion_fase_actual = buscar_posicion_pais(copa_2022.final, pais);
        puntaje_total += copa_2022.final.paises[posicion_fase_actual].cantidad_puntos;
    }
    if(es_pais_existente(copa_2022.grupos, pais)){
        posicion_fase_actual = buscar_posicion_pais(copa_2022.grupos, pais);
        puntaje_total += copa_2022.grupos.paises[posicion_fase_actual].cantidad_puntos;
    }

    return puntaje_total;
}


void imprimir_medallas(copa_mundial copa_2022){

    string medalla_oro = copa_2022.final.paises[PRIMER_LUGAR].nombre_pais;
    string medalla_plata = copa_2022.final.paises[SEGUNDO_LUGAR].nombre_pais;
    string medalla_bronce = copa_2022.tercer_puesto.paises[TERCER_LUGAR].nombre_pais;
    
    int puntaje_oro = devolver_puntaje_total(copa_2022, medalla_oro);
    int puntaje_bronce = devolver_puntaje_total(copa_2022, medalla_bronce);
    int puntaje_plata = devolver_puntaje_total(copa_2022, medalla_plata);

    cout << "Medalla de oro: " << medalla_oro << " con un puntaje total de " << puntaje_oro << " puntos" << endl;
    cout << "Medalla de plata: " << medalla_plata << " con un puntaje total de " << puntaje_plata << " puntos" << endl;
    cout << "Medalla de bronce: " << medalla_bronce << " con un puntaje total de " << puntaje_bronce << " puntos" << endl;

    cout << endl << endl;

}


string devolver_medalla_obtenida(copa_mundial copa_2022, string pais_a_buscar){
    string medalla_obtenida = "No obtuvo medalla";

    if(pais_a_buscar == copa_2022.final.paises[PRIMER_LUGAR].nombre_pais){
        medalla_obtenida = "Medalla de oro";
    }
    else if(pais_a_buscar == copa_2022.final.paises[SEGUNDO_LUGAR].nombre_pais){
        medalla_obtenida = "Medalla de plata";
    }
    else if(pais_a_buscar == copa_2022.tercer_puesto.paises[TERCER_LUGAR].nombre_pais){
        medalla_obtenida = "Medalla de bronce";
    }

    return medalla_obtenida;
}


string devolver_instancia_alcanzada(copa_mundial copa_2022, string pais_a_buscar){
    string maxima_instancia = "Fase de grupos";

    if(es_pais_existente(copa_2022.final, pais_a_buscar)){
        maxima_instancia = "Final";
    }
    else if(es_pais_existente(copa_2022.tercer_puesto, pais_a_buscar)){
        maxima_instancia = "Tercer y cuarto puesto";
    }
    else if(es_pais_existente(copa_2022.semifinales, pais_a_buscar)){
        maxima_instancia = "Semifinales";
    }
    else if(es_pais_existente(copa_2022.cuartos, pais_a_buscar)){
        maxima_instancia = "Cuartos";
    }
    else if(es_pais_existente(copa_2022.octavos, pais_a_buscar)){
        maxima_instancia = "Octavos";
    }

    return maxima_instancia;

}



int buscar_pais_grupos(vector vector_dinamico, string pais_a_buscar){
    int inicio = 0;
    int fin = vector_dinamico.cantidad_paises -1;
    int medio = (inicio + fin) / 2;
    int indice_encontrado = -1;


    while(fin >= inicio && indice_encontrado == NO_ENCONTRADA){

        if(vector_dinamico.paises[medio].nombre_equipo == pais_a_buscar){
            indice_encontrado = medio;
        }
        else if(vector_dinamico.paises[medio].nombre_equipo > pais_a_buscar){
            fin = medio -1;
        }
        else{
            inicio = medio +1;
        }
        medio = (inicio + fin) / 2;

    }
    return indice_encontrado;


}

string formatear_pais_busqueda(string palabra){
    string palabra_arreglada = ESPACIO_VACIO;
    palabra_arreglada += (char) toupper(palabra[0]);
    
    for(int i = 1; i < len(palabra); i++){
        palabra_arreglada += (char) tolower(palabra[i]);
    }

    return palabra_arreglada;

}



string pedir_nombre_pais(){
    string pais_a_buscar;

    cout << "Ingrese el nombre del pais que quiera buscar: ";
    getline(cin, pais_a_buscar);
    cout << endl;

    return formatear_pais_busqueda(pais_a_buscar);
    
}



void buscar_nombre_equipo(copa_mundial copa_2022, vector vector_dinamico){

    string pais_a_buscar = pedir_nombre_pais();
    string medalla_obtenida = "No obtuvo medallas";
    string grupo;
    string maxima_instancia = "Fase de grupos";

    int puntaje_total = 0;
    int posicion = buscar_pais_grupos(vector_dinamico, pais_a_buscar);
 

    if(posicion != NO_ENCONTRADA){

        puntaje_total = devolver_puntaje_total(copa_2022, pais_a_buscar);
        grupo = vector_dinamico.paises[posicion].grupo;
        maxima_instancia = devolver_instancia_alcanzada(copa_2022, pais_a_buscar);
        medalla_obtenida = devolver_medalla_obtenida(copa_2022, pais_a_buscar);

        cout << "Pais: " << pais_a_buscar << endl << "Grupo: " << grupo << endl << "Maxima instancia alcanzada: " << maxima_instancia << endl;
        cout << "Medalla obtenida: " << medalla_obtenida << endl << "Puntos obtenidos: " << puntaje_total << endl << endl;

    }
    else{
        cout << "El equipo que quieres buscar no participo de esta competencia";
    }
    cout << endl;


}


int encontrar_puntaje_pais(copa_mundial copa_2022, vector vector_dinamico, string pais_a_encontrar){
    int i = 0;
    int puntaje_pais = NO_ENCONTRADA;

    while(puntaje_pais == NO_ENCONTRADA && i < copa_2022.grupos.tope_paises){
        if(pais_a_encontrar == copa_2022.grupos.paises[i].nombre_pais){
            puntaje_pais = copa_2022.grupos.paises[i].cantidad_puntos;
        }
        i++;
    }
    return puntaje_pais;

}


void insertar_pais_en_orden(grupo &grupo, int posicion_actual){
    int i = 0;

    while(i < grupo.tope_paises){

        if(grupo.paises[posicion_actual].cantidad_puntos > grupo.paises[i].cantidad_puntos){
            intercambiar(grupo.paises[posicion_actual], grupo.paises[i]);
        }
        i++;
    }

}



void asignar_grupo(grupo &grupo, copa_mundial copa_2022, vector vector_dinamico, string pais_a_agregar){

    grupo.paises[grupo.tope_paises].nombre_pais = pais_a_agregar;

    grupo.paises[grupo.tope_paises].cantidad_puntos = encontrar_puntaje_pais(copa_2022, vector_dinamico,
                                                                            pais_a_agregar);

    insertar_pais_en_orden(grupo, grupo.tope_paises);

    grupo.tope_paises++;


}


void cargar_grupos(vector vector_dinamico, copa_mundial copa_2022, grupo &grupoA, grupo &grupoB, grupo &grupoC, grupo &grupoD, grupo &grupoE, grupo &grupoF, grupo &grupoG, grupo &grupoH){

    for(int i = 0; i < vector_dinamico.cantidad_paises; i++){

        if(vector_dinamico.paises[i].grupo == GRUPO_A){
            asignar_grupo(grupoA, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_B){
            asignar_grupo(grupoB, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_C){
            asignar_grupo(grupoC, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_D){
            asignar_grupo(grupoD, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_E){
            asignar_grupo(grupoE, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);;
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_F){
            asignar_grupo(grupoF, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_G){
            asignar_grupo(grupoG, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
        else if(vector_dinamico.paises[i].grupo == GRUPO_H){
            asignar_grupo(grupoH, copa_2022, vector_dinamico, vector_dinamico.paises[i].nombre_equipo);
        }
    }    
}


void imprimir_grupo_seleccionado(grupo grupo_a_imprimir){
    for(int i = 0; i < grupo_a_imprimir.tope_paises; i++){
        cout << "Pais: " << grupo_a_imprimir.paises[i].nombre_pais <<  "  Puntaje: " << grupo_a_imprimir.paises[i].cantidad_puntos << endl;

    }

    cout << endl;
}


void imprimir_grupos(vector vector_dinamico, copa_mundial copa_2022){
    grupo grupoA, grupoB, grupoC, grupoD, grupoE, grupoF, grupoG, grupoH;

    cargar_grupos(vector_dinamico, copa_2022, grupoA, grupoB, grupoC, grupoD, grupoE, grupoF, grupoG, grupoH);
        

    cout << "Grupo A" << endl;
    imprimir_grupo_seleccionado(grupoA);

    cout << "Grupo B" << endl;
    imprimir_grupo_seleccionado(grupoB);

    cout << "Grupo C" << endl;
    imprimir_grupo_seleccionado(grupoC);

    cout << "Grupo D" << endl;
    imprimir_grupo_seleccionado(grupoD);
    
    cout << "Grupo E" << endl;
    imprimir_grupo_seleccionado(grupoE);

    cout << "Grupo F" << endl;
    imprimir_grupo_seleccionado(grupoF);

    cout << "Grupo G" << endl;
    imprimir_grupo_seleccionado(grupoG);

    cout << "Grupo H" << endl;
    imprimir_grupo_seleccionado(grupoH);

}


void imprimir_fase_eliminatoria(fase fase_a_imprimir){

    for(int i = 0; i < fase_a_imprimir.tope_paises; i++){
        cout << "Pais: " << fase_a_imprimir.paises[i].nombre_pais << "  Puntos: " << fase_a_imprimir.paises[i].cantidad_puntos << endl;
    }
    cout << endl;

}


void imprimir_info_fases(copa_mundial copa_2022, vector vector_dinamico){

    cout << "Fase de grupos" << endl << endl;
    imprimir_grupos(vector_dinamico,copa_2022);

    cout << "Fase de octavos de final" << endl << endl;
    imprimir_fase_eliminatoria(copa_2022.octavos);
    
    cout << endl << "Fase de cuartos de final" << endl << endl;
    imprimir_fase_eliminatoria(copa_2022.cuartos);

    cout << endl << "Fase de semifinales" << endl << endl;
    imprimir_fase_eliminatoria(copa_2022.semifinales);

    cout << endl << "Fase de tercer y cuarto puesto" << endl << endl;
    imprimir_fase_eliminatoria(copa_2022.tercer_puesto);

    cout << endl << "Fase final" << endl << endl;
    imprimir_fase_eliminatoria(copa_2022.final);


}



void procesar_opcion(copa_mundial copa_2022, int eleccion_usuario, vector vector_dinamico){

    switch(eleccion_usuario){

        case OPCION_LISTAR_PARTICIPANTES:
            listar_equipos_totales(vector_dinamico);
            break;

        case OPCION_LISTAR_MEDALLAS:
            imprimir_medallas(copa_2022);
            break;

        case OPCION_BUSCAR_EQUIPO:
            buscar_nombre_equipo(copa_2022, vector_dinamico);
            break;

        case OPCION_LISTAR_FASES:
            imprimir_info_fases(copa_2022, vector_dinamico);
            break;

        default:
            cout << "Opción incorrecta, porfavor vuelva a ingresarla." << endl;
            break;
    }

}


void mostrar_menu(){

    cout << "Elige lo que quieras hacer" << endl << endl;
    cout << "1- Listar equipos" << endl;
    cout << "2- Mostrar los ganadores de medallas" << endl;
    cout << "3- Buscar equipo" << endl;
    cout << "4- Mostrar info de todas las fases" << endl;
    cout << "5- Salir" << endl;

}


int devolver_opcion_usuario(){

    char eleccion;

    cin >> eleccion;
    cin.clear();
    cin.ignore();

    return atoi(&eleccion);
}


void gestionar_menu_usuario(copa_mundial copa_2022, vector vector_dinamico){
    bool quiere_salir = false;
    int eleccion_usuario;

    while(!quiere_salir){
        mostrar_menu();
        eleccion_usuario = devolver_opcion_usuario();   

        if(eleccion_usuario == OPCION_SALIDA){
            quiere_salir = true;
            cout << "Gracias por utilizar el programa" << endl;
        }

        else{
            procesar_opcion(copa_2022, eleccion_usuario, vector_dinamico);
        }
    }
}


