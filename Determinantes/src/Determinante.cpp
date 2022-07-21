#include "Determinante.h"

Determinante::Determinante(int ngrau)
{
    setgrau(ngrau);
    set_resultado(1);
}

Determinante::Determinante()
{
    set_resultado(1);
}

Determinante::~Determinante()
{
}

void Determinante::setgrau(int ngrau)
{
    grau = ngrau;
}

int Determinante::getgrau()
{
    return grau;
}

void Determinante::set_resultado(float nresultado)
{
    resultado = nresultado;
}

float Determinante::get_resultado()
{
    return resultado;
}

void Determinante::set_linha()
{
    numero.push_back(std::vector<float>());
}

void Determinante::destruir_linha(int j)
{
    numero[j].clear();
}

void Determinante::set_elemento(int j, float num)
{
    numero[j].push_back(num);
}

float Determinante::get_elemento(int j, int i)
{
    return numero[j][i];
}

void Determinante::destruir_elemento(int j)
{
    if(!numero[j].empty())
    {
        numero[j].pop_back();
    }
}

double Determinante::multiplicador(float elemento1, float elemento2)
{
    double multiplicador = (double)(elemento1)/(elemento2);
    return multiplicador;
}

void Determinante::trocar_linhas(int linha1, int linha2)
{
    float aux;
    for(int k = 0; k < getgrau(); k++)
    {
        aux = numero[linha1][k];
        numero[linha1][k] = numero[linha2][k];
        numero[linha2][k] = aux;
        numero[linha1][k] *= -1;
    }
}

void Determinante::operacao_entre_linhas(int linha_multiplicada, double multiplicador, int linha_transformada)
{
    for(int COLUNA = 0; COLUNA < getgrau(); COLUNA++)
    {
        numero[linha_transformada][COLUNA] = -multiplicador*numero[linha_multiplicada][COLUNA] + numero[linha_transformada][COLUNA];
    }
    if(numero[linha_transformada][linha_transformada] == 0)
    {
        escalonar();
    }
}

int Determinante::achar_linha(int COLUNA)
{
    int LINHA;
    for(LINHA = 0; LINHA < getgrau(); LINHA++)
    {
        if(numero[LINHA][COLUNA] != 0)
        {
            if(numero[COLUNA][LINHA] != 0)
            {
                break;
            }
        }
    }
    if(LINHA == getgrau())
    {
        LINHA = -1;
    }
    return LINHA;
}

void Determinante::escalonar_coluna(int COLUNA)
{
    if(numero[COLUNA][COLUNA] == 0)
    {
        int LINHA = achar_linha(COLUNA);
        if(LINHA != -1)
        {
            trocar_linhas(COLUNA, LINHA);
        }
        else
        {
            set_resultado(0);
        }
    }
}

void Determinante::escalonar()
{
    for(int COLUNA = 0; COLUNA < getgrau(); COLUNA++)
    {
        escalonar_coluna(COLUNA);
        if(get_resultado() == 0)
        {
            goto fim;
        }
    }
    for(int i = 0; i < getgrau() - 1; i++)
    {
        for(int j = i + 1; j < getgrau(); j++)
        {
            if(numero[j][i] != 0)
            {
                double multiplo;
                multiplo = multiplicador(numero[j][i], numero[i][i]);
                operacao_entre_linhas(i, multiplo, j);
            }
            if(get_resultado() == 0)
            {
                goto fim;
            }
        }
    }
fim: /*continue */
    ;
}

void Determinante::calcular_diagonal()
{
    if(get_resultado() != 0)
    {
        float resultado = 1;
        for(int i = 0; i < getgrau(); i++)
        {
            resultado *=  numero[i][i];
            set_resultado(resultado);
        }
    }
}

