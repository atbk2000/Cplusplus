#ifndef DETERMINANTE_H
#define DETERMINANTE_H
#include <vector>

class Determinante
{
    int grau;
    std::vector<std::vector<float>> numero;
    float resultado;

    public:

    Determinante(int ngrau);
    Determinante();
    ~Determinante();

    void setgrau(int nlinhas);
    int getgrau();
    void set_resultado(float nresultado);
    float get_resultado();
    void set_linha();
    void destruir_linha(int j);
    void set_elemento(int j, float num);
    float get_elemento(int j, int i);
    void destruir_elemento(int j);
    double multiplicador(float elemento1, float elemento2);
    void trocar_linhas(int linha1, int linha2);
    void operacao_entre_linhas(int linha_multiplicada, double multiplicador, int linha_transformada);
    int achar_linha(int coluna);
    void escalonar_coluna(int i);
    void escalonar();
    void calcular_diagonal();

};

#endif // DETERMINANTE_H
