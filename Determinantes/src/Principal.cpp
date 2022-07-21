#include "Principal.h"

Principal::Principal()
{
    menu();
}

Principal::~Principal()
{
}

void Principal::menu()
{
    int ngrau;
    setlocale(LC_ALL, "Portuguese");
    Interface usuario;
    do
    {
        system("cls");
        usuario.receber(&ngrau);
        if(ngrau == 1)
        {
            usuario.instrucoes();
            menu();
        }
        if(ngrau == 2)
        {
            exit(0);
        }
    }
    while(ngrau < 3 || ngrau > 10);

    Determinante det(ngrau);

    Interface teste(det);

    teste.receber_numeros();
    teste.printar_determinante();

    std::string digito;
    std::cout << "Aperte S para sair, V para voltar: ";
    std::cin >> digito;

    if(digito == "V" || digito == "v")
    {
        menu();
    }

    if(digito == "S" || digito == "s")
    {
        exit(0);
    }
}
