/**
 * @file calculadora.c
 * @author {Rubio Haro Diego} ({rubiodiego001@gmail.com})
 * @brief
 * @version 0.1
 * @date 2022-12-02
   @Grupo: 5CM4
   @Redes
 *
 Descripción de funciones
 */

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calcu.h"

// Función que crea la estructura
DIRECCION crearStruct(char *p)
{
  DIRECCION dir;
  dir = (DIRECCION)malloc(sizeof(DIRECCION));
  int aux = strlen(p);
  dir->ip = (char *)malloc(aux + 1 * sizeof(char));
  strcpy(dir->ip, p);
  dir->array_pos = (int *)malloc(3 * sizeof(int));
  dir->array_valores = (int *)malloc(4 * sizeof(int));

  if (dir->ip == NULL)
  {
    printf("\nERROR: MEMORIA ip");
  }
  dir->longitud = strlen(p);
  if (dir->array_pos == NULL)
  {
    printf("\nERROR: MEMORIA arr_pos");
  }
  if (dir->array_valores == NULL)
  {
    printf("\nERROR: MEMORIA arr_val");
  }

  return dir;
}
// Funcion para asignar el arreglo de posiciones
void asignar_pos(DIRECCION dir, int i, int elemento)
{
  dir->array_pos[i] = elemento;
}
// Funcion de validaciones
void validarIP(DIRECCION dir)
{
  valid_1(dir);
  valid_2(dir);
  calcularIP(dir);
}
// Funcion para asignar los valores
void asignar_mascara(DIRECCION dir, int elemento)
{
  dir->dat.mascara = elemento;
}

// Función que asigna la clase
void asignar_clase(DIRECCION dir, int class)
{
  dir->clase = class;
}

// Función que retorna el tipo de clase
int obten_clase(DIRECCION dir)
{
  return dir->clase;
}

// Funcion que retorna la mascara
int obten_mascara(DIRECCION dir)
{
  return dir->dat.mascara;
}
// Funcion para asignar los valores del octeto
void asignar_valor(DIRECCION dir, int i, int elemento)
{
  dir->array_valores[i] = elemento;
}
// Funcion que retorna la posicion "."
int obten_pos(DIRECCION dir, int i)
{
  return dir->array_pos[i];
}
// Funcion que retorna la longitud
int obten_longitud(DIRECCION dir)
{
  return dir->longitud;
}
// Funcion que retorna un caracter de la IP
char obtenCaractIP(DIRECCION dir, int i)
{
  return dir->ip[i];
}
// Funcion que retorna la ip (cadena)
char *obtenIP(DIRECCION dir)
{
  return dir->ip;
}

// Funcion que retorna el valor
int obten_valores(DIRECCION dir, int i)
{
  return dir->array_valores[i];
}

// Asigna el numero de saltos por subred
void asignar_salto(DIRECCION dir, int s)
{
  dir->dat.num_saltos = s;
}

// Retorna el numero de saltos por subred
int obten_salto(DIRECCION dir)
{
  return dir->dat.num_saltos;
}

// Asigna el numero de hosts
void asignar_hosts(DIRECCION dir, int h)
{
  dir->dat.num_hosts = h;
}

// Retorna el numero de hosts
int obten_hosts(DIRECCION dir)
{
  return (dir->dat.num_hosts);
}

// Agina el numero de subredes
void asignar_subredes(DIRECCION dir, int r)
{
  dir->dat.num_subredes = r;
}

// Retorna el numero de subredes
int obten_subredes(DIRECCION dir)
{
  return dir->dat.num_subredes;
}

// Funcion Calcular IP
void calcularIP(DIRECCION dir)
{

  if (obten_valores(dir, 0) >= 0 && obten_valores(dir, 0) <= 127)
  {
    printf("\nClase A");
    asignar_clase(dir, 1);
    IP_A(dir);
  }
  if (obten_valores(dir, 0) >= 128 && obten_valores(dir, 0) <= 191)
  {
    printf("\nClase B");
    asignar_clase(dir, 2);
    IP_B(dir);
  }
  if (obten_valores(dir, 0) >= 192 && obten_valores(dir, 0) <= 223)
  {
    printf("\nClase C");
    asignar_clase(dir, 3);
    IP_C(dir);
  }
  if (obten_valores(dir, 0) >= 224 && obten_valores(dir, 0) <= 239)
  {
    printf("\nClase D");
  }
  if (obten_valores(dir, 0) >= 240 && obten_valores(dir, 0) <= 255)
  {
    printf("\nClase E");
  }
  else if (obten_valores(dir, 0) < 0)
  {
    printf("\nERROR: IP INVALIDA");
    exit(1);
  }
}
// Funcion validacion 1 (Num caracteres)
void valid_1(DIRECCION dir)
{
  int aux = strlen(obtenIP(dir));
  if (aux > 18 || aux < 7)
  {
    printf("\nERROR: IP INVALIDA");
    exit(1);
  }
}
// Funcion para obtener las pocisiones de los puntos
void array_pos(DIRECCION dir, int *contador)
{
  int j = 0;
  for (int i = 0; i < obten_longitud(dir); i++)
  {
    if (obtenCaractIP(dir, i) == '.')
    {
      (*contador)++;
      asignar_pos(dir, j, i);
      j++;
    }
  }
}
// Funcion validacion 2 (Puntos e integridad)
void valid_2(DIRECCION dir)
{
  int contador = 0;
  array_pos(dir, &contador);
  if (contador < 3 || contador > 3)
  {
    printf("\nERROR: IP INVALIDA_1");
    exit(1);
  }

  if (obtenCaractIP(dir, 0) == '.')
  {
    printf("\nERROR: IP INVALIDA_2");
    exit(1);
  }
  if (obten_pos(dir, 1) - obten_pos(dir, 0) == 1 || obten_pos(dir, 2) - obten_pos(dir, 1) == 1 || obten_pos(dir, 3) - obten_pos(dir, 2) == 1)
  {
    printf("\nERROR: IP INVALIDA_3");
    exit(1);
  }
  if (obtenCaractIP(dir, obten_pos(dir, 2) + 1) == '\0')
  {
    printf("\nERROR: IP INVALIDA_4");
    exit(1);
  }
  if (obten_pos(dir, 0) > 3 || obten_pos(dir, 1) > 7 || obten_pos(dir, 2) > 11)
  {
    printf("\nERROR: IP INVALIDA_5");
    exit(1);
  }
  // Condicion de longitud de bit
  int cont = 1;
  if (digitos_funt_0(dir) == 1)
  {
    printf("\nERROR: IP INVALIDA_6");
    exit(1);
  }
  if (digitos_funt(dir, obten_pos(dir, 0), obten_longitud(dir), &cont) == 1)
  {
    printf("\nERROR: IP INVALIDA_7");
    exit(1);
  }
  if (digitos_funt(dir, obten_pos(dir, 1), obten_longitud(dir), &cont) == 1)
  {
    printf("\nERROR: IP INVALIDA_8");
    exit(1);
  }
  if (digitos_funt(dir, obten_pos(dir, 2), obten_longitud(dir), &cont) == 1)
  {
    printf("\nERROR: IP INVALIDA_9");
    exit(1);
  }
  // Validacion de mascara o bits
  valid_masc(dir);
}
// Funcion para validar la mascara
void valid_masc(DIRECCION dir)
{
  int j = 0;
  for (int i = 0; i < obten_longitud(dir); i++)
  {
    if (obtenCaractIP(dir, i) == '/')
    {
      asignar_pos(dir, 4, i);
      j++;
    }
  }
  if (j != 1)
  {
    printf("\nERROR: SIN MASCARA");
    exit(1);
  }
  fflush(stdin);

  char *p = (char *)malloc(sizeof(char) * obten_longitud(dir) + 1);
  strcpy(p, obtenIP(dir));
  asignar_mascara(dir, atoi(obtenIP(dir) + obten_pos(dir, 4) + 1));
  if (obten_mascara(dir) < 0 || obten_mascara(dir) > 32)
  {
    printf("\n\nERROR: BITS INVALIDOS");
    exit(1);
  }
  dir->ip = NULL;
  dir->ip = (char *)malloc(sizeof(char) * obten_longitud(dir) + 1);
  strcpy(dir->ip, p);
}
// Funcion que regresa el numero de digitos de un numero
int digitos(int n)
{
  int r, con = 0;
  while (n > 0)
  {
    r = n % 10;
    con++;
    n = n / 10;
  }
  return con;
}
// Funcion que devuelve el numero de digitos por cada bloque
int digitos_funt(DIRECCION dir, int n, int limite, int *cont)
{
  int temp = n;
  char string_aux[limite - n + 1];
  strncpy(string_aux, obtenIP(dir) + n + 1, limite);
  int num = atoi(string_aux);
  if (digitos(num) > 3)
  {
    return 1;
  }
  if (num > 255)
  {
    return 1;
  }
  if (num < 0)
  {
    printf("\nERROR: IP INVALIDA");
    exit(1);
  }

  asignar_valor(dir, *cont, num);

  (*cont)++;
  return 0;
}
// Funcion que devuelve el numero de digitos por cada bloque
int digitos_funt_0(DIRECCION dir)
{

  int num = atoi(obtenIP(dir));
  asignar_valor(dir, 0, num);

  if (digitos(num) > 3)
  {
    return 1;
  }
  if (num > 255)
  {
    return 1;
  }
  if (num < 0)
  {
    printf("\nERROR: IP INVALIDA");
    exit(1);
  }

  return 0;
}

// Funcion que retorna el numero de la representacion binaria de los bists prestados
void asigna_host_sub(DIRECCION dir, int n, int clase)
{
  int aux;
  if (clase == 1)
  {
    printf("\nValor mascara: %i", n);
    if (n <= 16)
    {

      aux = obten_masc_octeto(n - 8);
      printf("\nMascara: 255.%i.0.0", aux);
      dir->dat.mascara_subred[0] = 255;
      dir->dat.mascara_subred[1] = aux;
      dir->dat.mascara_subred[2] = 0;
      dir->dat.mascara_subred[3] = 0;
    }

    if (n > 16 && n <= 24)
    {
      aux = obten_masc_octeto(n - 16);
      printf("\nMascara: 255.255.%i.0", aux);
      dir->dat.mascara_subred[0] = 255;
      dir->dat.mascara_subred[1] = 255;
      dir->dat.mascara_subred[2] = aux;
      dir->dat.mascara_subred[3] = 0;
    }
    if (n > 24)
    {
      aux = obten_masc_octeto(n - 24);
      printf("\nMascara: 255.255.255.%i", aux);
      dir->dat.mascara_subred[0] = 255;
      dir->dat.mascara_subred[1] = 255;
      dir->dat.mascara_subred[2] = 255;
      dir->dat.mascara_subred[3] = aux;
    }
    // Broadcast
    dir->dat.dir_broadcast[0] = obten_valores(dir, 0);
    dir->dat.dir_broadcast[1] = 255;
    dir->dat.dir_broadcast[2] = 255;
    dir->dat.dir_broadcast[3] = 255;
    // Hosts Minimos
    dir->dat.host_min[0] = obten_valores(dir, 0);
    dir->dat.host_min[1] = 0;
    dir->dat.host_min[2] = 0;
    dir->dat.host_min[3] = 1;
    // Hosts Máximos
    dir->dat.host_max[0] = obten_valores(dir, 0);
    dir->dat.host_max[1] = 255;
    dir->dat.host_max[2] = 255;
    dir->dat.host_max[3] = 254;
    // Direccion de red
    dir->dat.dir_red[0] = obten_valores(dir, 0);
    dir->dat.dir_red[1] = 0;
    dir->dat.dir_red[2] = 0;
    dir->dat.dir_red[3] = 0;

    asignar_subredes(dir, pow(2, n - 8));
    asignar_hosts(dir, pow(2, 32 - n) - 2);
    asignar_salto(dir, 256 - aux);
  }
  if (clase == 2)
  {
    printf("\nValor mascara: %i", n);
    if (n > 16 && n <= 24)
    {
      aux = obten_masc_octeto(n - 16);
      printf("\nMascara: 255.255.%i.0", aux);
      dir->dat.mascara_subred[0] = 255;
      dir->dat.mascara_subred[1] = 255;
      dir->dat.mascara_subred[2] = aux;
      dir->dat.mascara_subred[3] = 0;
    }
    if (n > 24)
    {
      aux = obten_masc_octeto(n - 24);
      printf("\nMascara: 255.255.255.%i", aux);
      dir->dat.mascara_subred[0] = 255;
      dir->dat.mascara_subred[1] = 255;
      dir->dat.mascara_subred[2] = 255;
      dir->dat.mascara_subred[3] = aux;
    }
    // Broadcast
    dir->dat.dir_broadcast[0] = obten_valores(dir, 0);
    dir->dat.dir_broadcast[1] = obten_valores(dir, 1);
    dir->dat.dir_broadcast[2] = 255;
    dir->dat.dir_broadcast[3] = 255;
    // Hosts Minimos
    dir->dat.host_min[0] = obten_valores(dir, 0);
    dir->dat.host_min[1] = obten_valores(dir, 1);
    dir->dat.host_min[2] = 0;
    dir->dat.host_min[3] = 1;
    // Hosts Máximos
    dir->dat.host_max[0] = obten_valores(dir, 0);
    dir->dat.host_max[1] = obten_valores(dir, 1);
    dir->dat.host_max[2] = 255;
    dir->dat.host_max[3] = 254;
    // Direccion de red
    dir->dat.dir_red[0] = obten_valores(dir, 0);
    dir->dat.dir_red[1] = obten_valores(dir, 1);
    dir->dat.dir_red[2] = 0;
    dir->dat.dir_red[3] = 0;
    asignar_subredes(dir, pow(2, n - 16));
    asignar_hosts(dir, pow(2, 32 - n) - 2);
    asignar_salto(dir, 256 - aux);
  }
  if (clase == 3)
  {
    printf("\nValor mascara: %i", n);
    aux = obten_masc_octeto(n - 24);
    printf("\nMascara: 255.255.255.%i", aux);
    // Subred
    dir->dat.mascara_subred[0] = 255;
    dir->dat.mascara_subred[1] = 255;
    dir->dat.mascara_subred[2] = 255;
    dir->dat.mascara_subred[3] = aux;
    // Broadcast
    dir->dat.dir_broadcast[0] = obten_valores(dir, 0);
    dir->dat.dir_broadcast[1] = obten_valores(dir, 1);
    dir->dat.dir_broadcast[2] = obten_valores(dir, 2);
    dir->dat.dir_broadcast[3] = 255;

    // Hosts Minimos
    dir->dat.host_min[0] = obten_valores(dir, 0);
    dir->dat.host_min[1] = obten_valores(dir, 1);
    dir->dat.host_min[2] = obten_valores(dir, 2);
    dir->dat.host_min[3] = 1;
    // Hosts Máximos
    dir->dat.host_max[0] = obten_valores(dir, 0);
    dir->dat.host_max[1] = obten_valores(dir, 1);
    dir->dat.host_max[2] = obten_valores(dir, 2);
    dir->dat.host_max[3] = 254;
    // Dir de red
    dir->dat.dir_red[0] = obten_valores(dir, 0);
    dir->dat.dir_red[1] = obten_valores(dir, 1);
    dir->dat.dir_red[2] = obten_valores(dir, 2);
    dir->dat.dir_red[3] = 0;

    asignar_subredes(dir, pow(2, n - 24));
    asignar_hosts(dir, pow(2, 32 - n) - 2);
    asignar_salto(dir, 256 - aux);
  }
}

// Funcion que obtiene el octeto de mascara prestado
int obten_masc_octeto(int n)
{

  if (n == 1)
  {
    return 128;
  }
  if (n == 2)
  {
    return 192;
  }
  if (n == 3)
  {
    return 224;
  }
  if (n == 4)
  {
    return 240;
  }
  if (n == 5)
  {
    return 248;
  }
  if (n == 6)
  {
    return 252;
  }
  if (n == 7)
  {
    return 254;
  }
  if (n == 8)
  {
    return 255;
  }
}

// Funciones para cada clase

void IP_C(DIRECCION dir)
{
  if (obten_mascara(dir) < BITS_RED_C || obten_mascara(dir) > BITS_DIR_IP)
  {
    printf("\nERROR: MASCARA INVALIDA");
    exit(1);
  }
  printf("\n\nIP Address: %s", obtenIP(dir));
  asigna_host_sub(dir, obten_mascara(dir), 3);
  printf("\nSubredes: %i", obten_subredes(dir));
  printf("\nHosts: %ix Subred", obten_hosts(dir));
  printf("\nSaltos: %i entre subredes ", obten_salto(dir));
  tabla_rangos(dir);
}

void IP_B(DIRECCION dir)
{
  if (obten_mascara(dir) < BITS_RED_B || obten_mascara(dir) > BITS_DIR_IP)
  {
    printf("\nERROR: MASCARA INVALIDA, MENOR O MAYOR");
    exit(1);
  }
  printf("\n\nIP Address: %s", obtenIP(dir));
  // printf("\nNetmask: %i", obten_mascara(dir));
  asigna_host_sub(dir, obten_mascara(dir), 2);
  printf("\nSubredes: %i", obten_subredes(dir));
  printf("\nHosts: %ix Subred", obten_hosts(dir));
  printf("\nSaltos: %i entre subredes ", obten_salto(dir));
  tabla_rangos(dir);
}

void IP_A(DIRECCION dir)
{
  if (obten_mascara(dir) < BITS_RED_A || obten_mascara(dir) > BITS_DIR_IP)
  {
    printf("\nERROR: MASCARA INVALIDA");
    exit(1);
  }
  printf("\n\nIP Address: %s", obtenIP(dir));
  // printf("\nNetmask: %i", obten_mascara(dir));
  asigna_host_sub(dir, obten_mascara(dir), 1);
  printf("\nSubredes: %i", obten_subredes(dir));
  printf("\nHosts: %ix Subred", obten_hosts(dir));
  printf("\nSaltos: %i entre subredes ", obten_salto(dir));
  tabla_rangos(dir);
}

// Función que genera los rangos en un archivo de texto plano
void tabla_rangos(DIRECCION dir)
{
  FILE *fp;
  fp = fopen("TABLA DE RANGOS.txt", "w+t");
  int limite = obten_subredes(dir);
  if (obten_subredes(dir) > 100)
  {
    limite = 100;
  }
  fprintf(fp, "\n\tTabla de rangos\n");
  fprintf(fp, "\nIP Address: %s", obtenIP(dir));
  fprintf(fp, "\nMascara: %i.%i.%i.%i = %i", dir->dat.mascara_subred[0], dir->dat.mascara_subred[1], dir->dat.mascara_subred[2], dir->dat.mascara_subred[3], obten_mascara(dir));
  fprintf(fp, "\nDir Red: %i.%i.%i.%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3]);
  fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
  fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
  fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
  fprintf(fp, "\nSubredes: %i", obten_subredes(dir));
  fprintf(fp, "\nHosts: %ix Subred", obten_hosts(dir));
  fprintf(fp, "\nHosts/net: %i\n\n", obten_hosts(dir) * obten_subredes(dir));
  if (obten_clase(dir) == 1)
  {
    fprintf(fp, "\nClase A");
    if (obten_mascara(dir) <= 16)
    {

      dir->dat.host_max[1] = obten_salto(dir) - 1;

      dir->dat.dir_broadcast[1] = obten_salto(dir) - 1;

      for (int i = 0; i < limite; i++)
      {

        fprintf(fp, "\n\n------------------------------");
        fprintf(fp, "\n[%i]", i + 1);
        fprintf(fp, "\nNetwork: %i.%i.%i.%i/%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3], obten_mascara(dir));
        fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
        fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
        fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
        dir->dat.dir_red[1] += obten_salto(dir);
        dir->dat.host_min[1] += obten_salto(dir);
        dir->dat.host_max[1] += obten_salto(dir);
        dir->dat.dir_broadcast[1] += obten_salto(dir);
      }
    }
    else if (obten_mascara(dir) <= 24)
    {
      dir->dat.host_max[1] = 0;
      dir->dat.host_max[2] = obten_salto(dir) - 1;

      dir->dat.dir_broadcast[1] = 0;
      dir->dat.dir_broadcast[2] = obten_salto(dir) - 1;
      int aux = 256 / obten_salto(dir);
      for (int i = 0, contador = 1; i < limite; i++)
      {

        for (int j = 0; j < aux; j++)
        {
          fprintf(fp, "\n\n------------------------------");
          fprintf(fp, "\n[%i]", contador);
          fprintf(fp, "\nNetwork: %i.%i.%i.%i/%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3], obten_mascara(dir));
          fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
          fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
          fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
          dir->dat.dir_red[2] += obten_salto(dir);
          dir->dat.host_min[2] += obten_salto(dir);
          dir->dat.host_max[2] += obten_salto(dir);
          dir->dat.dir_broadcast[2] += obten_salto(dir);
          contador++;
        }
        dir->dat.dir_red[1] += 1;
        dir->dat.host_min[1] += 1;
        dir->dat.host_max[1] += 1;
        dir->dat.dir_broadcast[1] += 1;

        dir->dat.dir_red[2] = 0;
        dir->dat.host_min[2] = 0;
        dir->dat.host_max[2] = obten_salto(dir) - 1;
        dir->dat.dir_broadcast[2] = obten_salto(dir) - 1;
      }
    }

    else if (obten_mascara(dir) <= 32)
    {
      dir->dat.host_max[1] = 0;
      dir->dat.host_max[2] = 0;
      dir->dat.host_max[3] = obten_salto(dir) - 2;

      dir->dat.dir_broadcast[1] = 0;
      dir->dat.dir_broadcast[2] = 0;
      dir->dat.dir_broadcast[3] = obten_salto(dir) - 1;
      int aux = 256 / obten_salto(dir);
      for (int i = 0, contador = 1; i < limite; i++)
      {

        for (int j = 0; j < aux; j++)
        {
          fprintf(fp, "\n\n------------------------------");
          fprintf(fp, "\n[%i]", contador);
          fprintf(fp, "\nNetwork: %i.%i.%i.%i/%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3], obten_mascara(dir));
          fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
          fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
          fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
          dir->dat.dir_red[3] += obten_salto(dir);
          dir->dat.host_min[3] += obten_salto(dir);
          dir->dat.host_max[3] += obten_salto(dir);
          dir->dat.dir_broadcast[3] += obten_salto(dir);
          contador++;
        }
        dir->dat.dir_red[2] += 1;
        dir->dat.host_min[2] += 1;
        dir->dat.host_max[2] += 1;
        dir->dat.dir_broadcast[2] += 1;

        dir->dat.dir_red[3] = 0;
        dir->dat.host_min[3] = 1;
        dir->dat.host_max[3] = obten_salto(dir) - 2;
        dir->dat.dir_broadcast[3] = obten_salto(dir) - 1;
      }
      // printf("\nNum_veces_sub: %i", aux);
      // printf("\nNum_veces aux: %i", 256 / aux);
    }
  }

  else if (obten_clase(dir) == 2)
  {
    fprintf(fp, "\nClase B");
    if (obten_mascara(dir) <= 24)
    {

      dir->dat.host_max[2] = obten_salto(dir) - 1;

      dir->dat.dir_broadcast[2] = obten_salto(dir) - 1;

      for (int i = 0; i < limite; i++)
      {

        fprintf(fp, "\n\n------------------------------");
        fprintf(fp, "\n[%i]", i + 1);
        fprintf(fp, "\nNetwork: %i.%i.%i.%i/%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3], obten_mascara(dir));
        fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
        fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
        fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
        dir->dat.dir_red[2] += obten_salto(dir);
        dir->dat.host_min[2] += obten_salto(dir);
        dir->dat.host_max[2] += obten_salto(dir);
        dir->dat.dir_broadcast[2] += obten_salto(dir);
      }
    }
    else if (obten_mascara(dir) < 32)
    {
      dir->dat.host_max[2] = 0;
      dir->dat.host_max[3] = obten_salto(dir) - 2;

      dir->dat.dir_broadcast[2] = 0;
      dir->dat.dir_broadcast[3] = obten_salto(dir) - 1;
      int aux = 256 / obten_salto(dir);
      for (int i = 0, contador = 1; i < limite; i++)
      {

        for (int j = 0; j < aux; j++)
        {
          fprintf(fp, "\n\n------------------------------");
          fprintf(fp, "\n[%i]", contador);
          fprintf(fp, "\nNetwork: %i.%i.%i.%i/%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3], obten_mascara(dir));
          fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
          fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
          fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
          dir->dat.dir_red[3] += obten_salto(dir);
          dir->dat.host_min[3] += obten_salto(dir);
          dir->dat.host_max[3] += obten_salto(dir);
          dir->dat.dir_broadcast[3] += obten_salto(dir);
          contador++;
        }
        dir->dat.dir_red[2] += 1;
        dir->dat.host_min[2] += 1;
        dir->dat.host_max[2] += 1;
        dir->dat.dir_broadcast[2] += 1;

        dir->dat.dir_red[3] = 0;
        dir->dat.host_min[3] = 1;
        dir->dat.host_max[3] = obten_salto(dir) - 2;
        dir->dat.dir_broadcast[3] = obten_salto(dir) - 1;
      }
    }
  }
  else
  {
    fprintf(fp, "\nClase C");
    dir->dat.host_min[3] = 1;
    dir->dat.host_max[3] = obten_salto(dir) - 2;
    dir->dat.dir_broadcast[3] = obten_salto(dir) - 1;

    for (int i = 0; i < limite; i++)
    {

      fprintf(fp, "\n\n------------------------------");
      fprintf(fp, "\n[%i]", i + 1);
      fprintf(fp, "\nNetwork: %i.%i.%i.%i/%i", dir->dat.dir_red[0], dir->dat.dir_red[1], dir->dat.dir_red[2], dir->dat.dir_red[3], obten_mascara(dir));
      fprintf(fp, "\nHost Minimo: %i.%i.%i.%i", dir->dat.host_min[0], dir->dat.host_min[1], dir->dat.host_min[2], dir->dat.host_min[3]);
      fprintf(fp, "\nHost Maximo: %i.%i.%i.%i", dir->dat.host_max[0], dir->dat.host_max[1], dir->dat.host_max[2], dir->dat.host_max[3]);
      fprintf(fp, "\nBroadcast: %i.%i.%i.%i", dir->dat.dir_broadcast[0], dir->dat.dir_broadcast[1], dir->dat.dir_broadcast[2], dir->dat.dir_broadcast[3]);
      dir->dat.dir_red[3] += obten_salto(dir);
      dir->dat.host_min[3] += obten_salto(dir);
      dir->dat.host_max[3] += obten_salto(dir);
      dir->dat.dir_broadcast[3] += obten_salto(dir);
    }
  }
  fclose(fp);
}
