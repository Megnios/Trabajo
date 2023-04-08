#ifndef ARCHIVO_UTILES
#define ARCHIVO_UTILES

#include <string>

#include "vector.h"



struct pais{
    std::string nombre_pais;
    int cantidad_puntos = 0;
};

struct fase{
    pais paises[100];
    int tope_paises = 0;

};

struct copa_mundial{
    fase grupos;
    fase octavos;
    fase cuartos;
    fase semifinales;
    fase tercer_puesto;
    fase final;
};

struct grupo{
    pais paises[10];
    int tope_paises = 0;
    int puntaje = 0;
};



// Pre: -
// Post: Devuelve la cantidad de caracteres de texto.
int len(std::string texto);


// Pre: datos tiene que tener el espacio suficiente para guardar la informacion de linea_leida.
// Post: Aisla las palabras de linea_leida separadas por espacios y las guarda por orden en datos.
void separar_linea(std::string linea_leida, std::string datos[], int &tope_datos);


// Pre: -
// Post: Devuelve nombre_pais pero intercambiando el caracter "_" (guion bajo) por " " (espacio).
std::string arreglar_nombre_pais(std::string nombre_pais);


// Pre: -
// Post: Inserta pais y grupos (respetando el orden original) en el vector dinamico  teniendo en cuenta que este ultimo esta ordenado por pais ascendentemente.
void insertar_pais(vector* vector_dinamico, std::string pais, std::string grupo);


// Pre: archivo debe estar correctamente abierto.
// Post: Procesa la información de archivo y la inserta en el vector dinamico. 
void procesar_archivo_grupos(std::ifstream &archivo, vector* vector_dinamico);


// Pre: -
// Post: Actualiza la instancia actual (grupos, octavos, cuartos, semifinales, tercer puesto, o final).
void actualizar_instancia(std::string linea_leida, char &instancia_actual);


// Pre: -
// Post: Devuelve el indice del vector de paises de fase actual en donde esta pais_a_buscar. -1 si no se encuentra.
int buscar_posicion_pais(fase fase_actual, std::string pais_a_buscar);


// Pre: vector_datos tiene que tener una longitud minima de 3 elementos.
// Post: Añade, si no se encuentran, los elementos 0 y 2 de vector_datos en el vector perteneciente a grupos.
void asignar_posiciones_grupos(std::string vector_datos[], fase &grupos);


// Pre: posicion_pais1 y posicion_pais2 deben cumplir: 0 <= posicion_pais < grupos.tope_paises.
// Post: Suma 3 puntos al puntaje del ganador y 0 al perdedor.
void asignar_puntos_grupos(int goles_pais1, int goles_pais2, int posicion_pais1, int posicion_pais2, fase &grupos);


// Pre: la longitud de vector_datos tiene que ser como minimo 4 elementos.
// Post: Asigna la información de vector_datos en la fase grupos.
void asignar_info_grupos(std::string vector_datos[], fase &grupos);


// Pre: -
// Post: Intercambia la informacion de pais1 con pais2.
void intercambiar(pais &pais1, pais &pais2);


// Pre: El vector incluido en fase_actual debe estar previamente ordenado descendentemente por cantidad_puntos.
// Post: Ordena el vector incluido en fase_actual teniendo en cuenta que el orden original es descentente por cantidad_puntos.
void ordenar_por_puntaje(fase &fase_actual, int posicion_pais);


// Pre: posicion_pais1 y posicion_pais2 deben cumplir: 0 <= posicion_pais < fase_actual.tope_paises.
// Post: Si no se hubiese llegado a la definicion por penales, suma 3 al ganador, 0 al perdedor. De otra forma se le suma 2 al ganador y 1 al perdedor.
void asignar_puntos_eliminatorias(int penales_pais1, int penales_pais2, int goles_pais1, int goles_pais2, fase &fase_actual, int posicion_pais1, int posicion_pais2);


// Pre: vector_datos tiene que tener una longitud minima de 4 elementos.
// Post: Si no se encuentra, asigna una posicion al pais correspondiente en el vector de fase actual.
void asignar_posiciones_eliminatorias(fase &fase_actual, std::string vector_datos[]);


// Pre: vector_datos tiene que tener una longitud minima de 6 elementos.
// Post: Asigna la informacion contenida en vector_datos en el vector de fase_actual.
void asignar_info_eliminatorias(fase &fase_actual, std::string vector_datos[]);


// Pre: instancia actual debe ser una instancia real de alguna de las fases de la copa mundial.
// Post: Procesa instancia_actual y actua asignando la informacion correspondiente.
void procesar_informacion_resultados(std::string vector_datos[], copa_mundial &copa_2022, char instancia_actual);



// Pre: datos tiene que tener el espacio suficiente para guardar la informacion de linea_leida.
// Post: Aisla las palabras de linea_leida separadas por comas y las guarda por orden en datos.
void procesar_linea(std::string linea, std::string vector[], int &tope_vector);


// Pre: archivo_resultados tiene que estar correctamente abierto.
// Post: Procesa archivo_resultados y almacena la información en copa_2022.
void procesar_archivo_resultados(std::ifstream &archivo_resultados, copa_mundial &copa_2022);



// Pre: -
// Post: Devuelve true si pais_a_buscar esta presente entre los paises de la fase fase_actual.
bool es_pais_existente(fase fase_actual, std::string pais_a_buscar);


// Pre: -
// Post: Imprime por pantalla todos los paises en vector_dinamico junto con sus respectivos grupo.
void listar_equipos_totales(vector vector_dinamico);



// Pre: -
// Post: Devuelve el puntaje total de pais conseguido en todo su recorrido en la copa.
int devolver_puntaje_total(copa_mundial copa_2022, std::string pais);



// Pre: copa_2022.final.tope_paises >= 2 y copa_2022.tercer_puesto.tope_paises >= 1
// Post: Imprime por pantalla los 3 primeros puestos de copa_2022 y sus respectivos puntajes totales.
void imprimir_medallas(copa_mundial copa_2022);



// Pre: copa_2022.final.tope_paises >= 2 y copa_2022.tercer_puesto.tope_paises >= 1
// Post: Devuelve informacion sobre si termino o no en los primeros 3 lugares de la copa.
std::string devolver_medalla_obtenida(copa_mundial copa_2022, std::string pais_a_buscar);


// Pre: pais_a_buscar debe haber sido un participante de la copa del mundo.
// Post: Devuelve la maxima instancia alcanzada por pais_a_buscar.
std::string devolver_instancia_alcanzada(copa_mundial copa_2022, std::string pais_a_buscar);


// Pre: -
// Post: Devuelve el indice en donde se encuentra pais_a_buscar en vector_dinamico.
int buscar_pais_grupos(vector vector_dinamico, std::string pais_a_buscar);


// Pre: palabra debe tener una longitud mayor o igual a 1.
// Post: Devuelve palabra con la primera letra en mayusculas y el resto en minusculas.
std::string formatear_pais_busqueda(std::string palabra);


// Pre: -
// Post: Pide un nombre de pais al usuario y lo devuelve.
std::string pedir_nombre_pais();


// Pre: -
// Post: Pide el nombre de un pais al usuario e imprime por pantalla informacion en el siguiente orden:
//       Nombre del pais, grupo al que pertenecio, maxima instancia alcanzada, si obtuvo o no una medalla y los puntos totales obtenidos.
//       Si el pais no jugo la copa del mundo, se le informa al usuario. 
void buscar_nombre_equipo(copa_mundial copa_2022, vector vector_dinamico);


// Pre: -
// Post: Devuelve el puntaje obtenido por pais_a_encontrar en la fase de grupos. Si el pais no jugo la copa del mundo se devuelve -1.
int encontrar_puntaje_pais(copa_mundial copa_2022, vector vector_dinamico, std::string pais_a_encontrar);


// Pre: posicion_actual debe estar entre: 0 < posicion_actual < grupo.tope_paises.
// Post: Inserta, respetando el orden original, el pais en posicion_actual en el vector perteneciente a grupo. El orden antes mencionado es descendente por puntaje.
void insertar_pais_en_orden(grupo &grupo, int posicion_actual);


// Pre: 
// Post: Se le asigna a pais_a_agregar una posicion dentro del vector de grupo (respetando el orden original), junto con su puntaje obtenido en la fase de grupos. 
void asignar_grupo(grupo &grupo, copa_mundial copa_2022, vector vector_dinamico, std::string pais_a_agregar);


// Pre: -
// Post: Carga la informacion presente en vector_dinamico y copa_2022 en cada grupo segun corresponda.
void cargar_grupos(vector vector_dinamico, copa_mundial copa_2022, grupo &grupoA, grupo &grupoB, grupo &grupoC, grupo &grupoD, grupo &grupoE, grupo &grupoF);


// Pre: -
// Post: Imprime los paises pertenecientes a grupo_a_imprimir y sus puntajes en el orden en el que fueron guardados.
void imprimir_grupo_seleccionado(grupo grupo_a_imprimir);


// Pre: -
// Post: Imprime por cada grupo los paises participantes y sus respectivos puntajes en el orden que estan guardados.
void imprimir_grupos(vector vector_dinamico, copa_mundial copa_2022);


// Pre: -
// Post: Imprime los paises participantes de fase_a_imprimir, junto al puntaje obtenido en dicha fase en el orden en el que fueron guardados.
void imprimir_fase_eliminatoria(fase fase_a_imprimir);


// Pre: -
// Post: Imprime por cada fase los paises participantes y su puntajes conseguidos en orden descendente por puntaje.
void imprimir_info_fases(copa_mundial copa_2022, vector vector_dinamico);


// Pre -
// Post: Procesa la opción elegida por el usuario.
void procesar_opcion(copa_mundial copa_2022, char eleccion_usuario, vector vector_dinamico);


// Pre: -
// Post: Imprime por pantalla las opciones del menu principal.
void mostrar_menu();



// Pre: -
// Post: Devuelve la opcion elegida por el usuario.
int devolver_opcion_usuario();


// Pre: -
// Post: Gestiona el menu en donde el usuario decide que hacer.
void gestionar_menu_usuario(copa_mundial copa_2022, vector vector_dinamico);


#endif