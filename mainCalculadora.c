/**
 * @file mainCalculadora.c
 * @author {Rubio Haro Diego} ({rubiodiego001@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 Archivo Principal main
 */

//Librerias
#include<stdio.h>
#include"calcu.h"

int main(int argc, char *arvg[])
{
    DIRECCION dir=crearStruct(arvg[1]);
    validarIP(dir);
    
    return 0;
    
}