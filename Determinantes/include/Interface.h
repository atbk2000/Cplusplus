#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <Windows.h>
#include <string>
#include <locale>
#include <limits>
#include <stdio.h>
#include "Determinante.h"

class Interface
{
    int x;
    int y;
    Determinante det;

public:

    Interface(Determinante obj);
    Interface();
    ~Interface();

    void setx(int nx);
    int getx();
    void sety(int ny);
    int gety();
    void receber(int *num);
    void instrucoes();
    void posicionar_teclado();
    void apagar_linha();
    bool voltar(std::string caracter);
    void analisar_volta(int *LINHA, int *COLUNA, std::string caracter);
    bool validar_caracter(std::string ndigito);
    float string_to_float(std::string ndigito);
    void receber_numeros();
    void printar_determinante();

};

#endif // INTERFACE_H

