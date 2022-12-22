/**
 * @file calcu.h
 * @author {Rubio Haro Diego} ({rubiodiego001@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 Funciones
 */

// Preprocesador
#ifndef _calculadora_
#define _calculadora_

// Macros
#define BITS_RED_A 8 
#define BITS_HOSTS_A 24

#define BITS_RED_B 16
#define BITS_HOSTS_C 16

#define BITS_RED_C 24
#define BITS_HOSTS 8

#define BITS_DIR_IP 32

#define MASCARA_A "255.0.0.0"
#define MASCARA_B "255.255.0.0"
#define MASCARA_C "255.255.255.0"


//Estructuras
typedef struct 
{
  int mascara;
  int num_saltos;
  int num_hosts;
  int num_subredes;
  int mascara_subred[4];
  int dir_broadcast[4];
  int host_min[4];
  int host_max[4];
  int dir_red[4];
}datosIP;

typedef struct
{
  int clase;
  char *ip;
  int *array_pos;
  int *array_valores;
  int longitud;
  datosIP dat;
} IP;

typedef IP *DIRECCION;

//Descripcion informal de funciones
DIRECCION crearStruct(char *);
//Asignar
void asignar_pos(DIRECCION, int, int);
void asignar_salto(DIRECCION,int);
void asignar_valor(DIRECCION, int, int);
void asignar_mascara(DIRECCION,int);
void asignar_hosts(DIRECCION,int);
void asignar_subredes(DIRECCION,int);
void asigna_host_sub(DIRECCION,int,int);
void asignar_clase(DIRECCION,int);
//Obtener
char *obtenIP(DIRECCION);
char obtenCaractIP(DIRECCION, int);
int obten_clase(DIRECCION);
int obten_pos(DIRECCION, int);
int obten_longitud(DIRECCION);
int obten_valores(DIRECCION, int);
int obten_salto(DIRECCION);
int obten_hosts(DIRECCION);
int obten_subredes(DIRECCION);
int obten_mascara(DIRECCION);
int obten_masc_octeto(int);

//Validar
void validarIP(DIRECCION);
void valid_masc(DIRECCION);
void valid_1(DIRECCION);
void valid_2(DIRECCION);
int digitos_funt(DIRECCION, int, int, int *);
int digitos_funt_0(DIRECCION);
void array_pos(DIRECCION, int *);
int digitos(int);


//Funciones de calculo
void calcularIP(DIRECCION);
void IP_A(DIRECCION);
void IP_B(DIRECCION);
void IP_C(DIRECCION);
// Funciones de tabla
void tabla_rangos(DIRECCION);

#endif