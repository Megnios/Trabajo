#ifndef ARCHIVO_CONSTANTES
#define ARCHIVO_CONSTANTES

#include <string>

const std::string NOMBRE_EQUIPOS = "equipos.txt";
const std::string RESULTADOS = "resultados.csv";

const std::string GRUPO_A = "A";
const std::string GRUPO_B = "B";
const std::string GRUPO_C = "C";
const std::string GRUPO_D = "D";
const std::string GRUPO_E = "E";
const std::string GRUPO_F = "F";
const std::string GRUPO_G = "G";
const std::string GRUPO_H = "H";

const std::string LINEA_LEIDA_GRUPOS = "grupos";
const std::string LINEA_LEIDA_OCTAVOS = "octavos";
const std::string LINEA_LEIDA_CUARTOS = "cuartos";
const std::string LINEA_LEIDA_SEMIFINALES = "semifinales";
const std::string LINEA_LEIDA_TERCER_PUESTO = "tercer puesto";
const std::string LINEA_LEIDA_FINAL = "final";

const char COMA = ',';
const char ESPACIO = ' ';
const char GUION_BAJO = '_';
const std::string ESPACIO_VACIO = "";

const char INSTANCIA_GRUPOS = 'G';
const char INSTANCIA_OCTAVOS = 'O';
const char INSTANCIA_CUARTOS = 'C';
const char INSTANCIA_SEMIFINALES = 'S';
const char INSTANCIA_TERCER_PUESTO = 'T';
const char INSTANCIA_FINAL = 'F';

const int NOMBRE_PAIS = 0;
const int GRUPO_PAIS = 1;
const int GOLES_EQUIPO_1 = 1;
const int NOMBRE_PAIS_2 = 2;
const int GOLES_EQUIPO_2 = 3;
const int NOMBRE_PAIS1 = 0;
const int NOMBRE_PAIS2 = 3;
const int GOLES_EQUIPO2 = 4;
const int PENALES_EQUIPO1 = 2;
const int PENALES_EQUIPO2 = 5;
const int NO_HAY_PENALES = -1;

const int NO_ENCONTRADA = -1;

const int PRIMER_LUGAR = 0;
const int SEGUNDO_LUGAR = 1;
const int TERCER_LUGAR = 0;

const int OPCION_LISTAR_PARTICIPANTES = 1;
const int OPCION_LISTAR_MEDALLAS = 2;
const int OPCION_BUSCAR_EQUIPO = 3;
const int OPCION_LISTAR_FASES = 4;
const int OPCION_SALIDA = 5;

const int MAX_CAMPOS_ARCHIVO_GRUPOS = 5;
const int MAX_CAMPOS_ARCHIVO_RESULTADO = 10;


#endif