#include "Interface.h"

Interface::Interface(Determinante obj)
{
    det = obj;
    setx(0);
    sety(0);
}

Interface::Interface()
{
    setx(0);
    sety(0);
}

Interface::~Interface()
{
}

void Interface::setx(int nx)
{
    x = nx;
}

int Interface::getx()
{
    return x;
}

void Interface::sety(int ny)
{
    y = ny;
}

int Interface::gety()
{
    return y;
}

void Interface::receber(int *num)
{
    float grau;
    std::cout << "Clique 1 para ver as instruções, 2 para sair" << std::endl;
    std::cout << "Qual é o grau do determinante?(de 3 a 10): ";
    std::cin >> grau;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("cls");
        std::cout << "Clique 1 para ver as instruções, 2 para sair" << std::endl;
        std::cout << "Qual é o grau do determinante?(de 3 a 10): ";
        std::cin >> grau;
    }
    *num = int(grau);
    fflush(stdin);
}

void Interface::instrucoes()
{
    system("cls");
    FILE *arq;
    arq = fopen("Instrucoes.txt", "r");
    if(arq == NULL)
    {
        std::cout << "Problemas ao achar o arquivo" << std::endl;
    }
    else
    {
        char c;
        do
        {
            c = getc(arq);
            if(c != '!')
            {
                std::cout << c;
            }
        }
        while(c != '!');
    }
    fclose(arq);
    std::cout << "\n\n\n\n" << "Clique qualquer tecla para voltar ao menu: ";
    getchar();
}

void Interface::posicionar_teclado()
{
    COORD coord;
    coord.X = getx();
    coord.Y = gety();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Interface::apagar_linha()
{
    setx(0);
    posicionar_teclado();
    for(int i = 0; i < 200; i++)
    {
        std::cout << " ";
    }
    setx(0);
    posicionar_teclado();
}

bool Interface::voltar(std::string caracter)
{
    bool retorno = false;
    if((caracter == "E" || caracter == "e"))
    {
        retorno = true;
    }
    if((caracter == "L" || caracter == "l"))
    {
        retorno = true;
    }
    return retorno;
}

void Interface::analisar_volta(int *LINHA, int *COLUNA, std::string caracter)
{
    int auxLINHA = *LINHA;
    int auxCOLUNA = *COLUNA;
    if((caracter == "E" || caracter == "e") && *COLUNA != 0)
    {
        Beep(300, 300);
        sety(gety() - 1);
        apagar_linha();
        auxCOLUNA--;
        det.destruir_elemento(auxLINHA);
        auxCOLUNA--;
    }
    if((caracter == "E" || caracter == "e") && *COLUNA == 0 && *LINHA != 0)
    {
        Beep(300, 300);
        apagar_linha();
        sety(gety() - 2);
        apagar_linha();
        auxLINHA--;
        auxCOLUNA = det.getgrau() - 1;
        det.destruir_elemento(auxLINHA);
        auxCOLUNA--;
    }
    if((caracter == "E" || caracter == "e") && *COLUNA == 0 && *LINHA == 0)
    {
        Beep(300, 300);
        sety(gety() + 1);
        det.set_elemento(auxLINHA, 0);
    }
    if((caracter == "L" || caracter == "l") && *LINHA != 0)
    {
        Beep(300, 300);
        int apagar_linhas = (det.getgrau() + 1) + auxCOLUNA + 1;
        for(int i = 0; i < apagar_linhas; i++)
        {
            apagar_linha();
            sety(gety() - 1);
            posicionar_teclado();
        }
        apagar_linha();
        sety(gety() + 1);
        posicionar_teclado();
        int destruir_elementos = auxCOLUNA + 1;
        for(int i = 0; i < destruir_elementos; i++)
        {
            det.destruir_elemento(auxLINHA);
        }
        auxLINHA--;
        for(int i = 0; i < det.getgrau(); i++)
        {
            det.destruir_elemento(auxLINHA);
        }
        auxCOLUNA = -1;
        det.destruir_linha(auxLINHA);
    }
    if((caracter == "L" || caracter == "l") && *LINHA == 0)
    {
        Beep(300, 300);
        sety(gety() + 1);
        det.set_elemento(auxLINHA, 0);
    }
    *LINHA = auxLINHA;
    *COLUNA = auxCOLUNA;
}

bool Interface::validar_caracter(std::string ndigito)
{
    bool retorno = true;
    unsigned limite_virgula = 0, limite_barra = 0;
    if(ndigito[0] == ',' || ndigito[ndigito.length() - 1] == ',')
    {
        retorno = false;
        goto fim;
    }
    if(ndigito[0] == '.' || ndigito[ndigito.length() - 1] == '.')
    {
        retorno = false;
        goto fim;
    }
    if(ndigito[0] == '/' || ndigito[ndigito.length() - 1] == '/')
    {
        retorno = false;
        goto fim;
    }
    for(unsigned i = 0; i < ndigito.length(); i++)
    {
        if(!(isdigit(ndigito[i])) && ndigito[i] != ',')
        {
            if(ndigito[i] != '/')
            {
                if(!(ndigito[i] == '-' && i == 0))
                {
                    retorno = false;
                    goto fim;
                }
            }
        }
        if(ndigito[i] == ',')
        {
            limite_virgula++;
        }
        if(ndigito[i] == '/')
        {
            limite_barra++;
        }
        if(i - 1 >= 0)
        {
            if((ndigito[i - 1] == '/' || ndigito[i - 1] == ',') && (ndigito[i] == '/' || ndigito[i] == ','))
            {
                retorno = false;
                goto fim;
            }
        }
        if(limite_virgula > 1 && limite_barra == 0)
        {
            retorno = false;
            goto fim;
        }
        if(limite_barra > 1 && limite_virgula == 0)
        {
            retorno = false;
            goto fim;
        }
        if(limite_barra > 2 || limite_virgula > 2)
        {
            retorno = false;
            goto fim;
        }
    }
fim: /* continue */
    return retorno;
}


float Interface::string_to_float(std::string ndigito)
{
    bool divisao = false;
    unsigned i;
    float retorno;
    for(i = 0; i < ndigito.length(); i++)
    {
        if(ndigito[i] == '/')
        {
            divisao = true;
            break;
        }
    }
    if(divisao)
    {
        retorno = (std::stof(ndigito.substr(0, i)))/(std::stof(ndigito.substr(i + 1, ndigito.length() - i - 1)));
    }
    else
    {
        retorno = std::stof(ndigito);
    }
    return retorno;
}

void Interface::receber_numeros()
{
    system("cls");
    sety(1);
    setx(0);
    posicionar_teclado();
    int LINHA, COLUNA;
    float num;
    std::string caracter;
    for(LINHA = 0; LINHA < det.getgrau(); LINHA++)
    {
        det.set_linha();
        for(COLUNA = 0; COLUNA < det.getgrau(); COLUNA++)
        {
            std::cout << "Elemento " << LINHA + 1 << "." << COLUNA + 1 << ": ";
            std::cin >> caracter;
            for(unsigned i = 0; i < caracter.length(); i++)
            {
                if((caracter.compare(i, 1, ".") == 0))
                {
                    caracter.replace(i, 1, ",");
                }
            }
            if(voltar(caracter))
            {
                analisar_volta(&LINHA, &COLUNA, caracter);
            }
            else
            {
                if(validar_caracter(caracter))
                {
                    num = string_to_float(caracter);
                    det.set_elemento(LINHA, num);
                    sety(gety() + 1);
                    posicionar_teclado();
                }
                else
                {
                    det.set_elemento(LINHA, 0);
                    sety(gety() + 1);
                    posicionar_teclado();
                }
            }
        }
        sety(gety() + 1);
        posicionar_teclado();
    }
}

void Interface::printar_determinante()
{
    system("cls");
    sety(0);
    setx(((16*(det.getgrau() - 1) + 2)/2) - 10);
    posicionar_teclado();
    std::cout << "Determinante recebido:";
    sety(2);
    posicionar_teclado();
    for(int LINHA = 0; LINHA < det.getgrau(); LINHA++)
    {
        setx(1);
        posicionar_teclado();
        for(int COLUNA = 0; COLUNA < det.getgrau(); COLUNA++)
        {
            std::cout << det.get_elemento(LINHA, COLUNA);
            setx(getx() + 16);
            posicionar_teclado();
        }
        sety(gety() + 2);
    }
    setx((16*(det.getgrau() - 1) + 2)/2);
    posicionar_teclado();
    std::cout << "=";
    det.escalonar();
    sety(gety() + 2);
    for(int LINHA = 0; LINHA < det.getgrau(); LINHA++)
    {
        setx(1);
        posicionar_teclado();
        for(int COLUNA = 0; COLUNA < det.getgrau(); COLUNA++)
        {
            if(COLUNA >= LINHA)
            {
                std::cout << det.get_elemento(LINHA, COLUNA) + 0.0;
            }
            else
            {
                std::cout << 0;
            }
            setx(getx() + 16);
            posicionar_teclado();
        }
        sety(gety() + 2);
    }
    setx(1);
    posicionar_teclado();
    det.calcular_diagonal();
    std::cout << "Valor do determinante: " << det.get_resultado() + 0.0;
    sety(gety() + 2);
    posicionar_teclado();

    /* LIBERAR MEMÓRIA */
    for(int LINHA = 0; LINHA < det.getgrau(); LINHA++)
    {
        for(int COLUNA = 0; COLUNA < det.getgrau(); COLUNA++)
        {
            det.destruir_elemento(LINHA);
        }
        det.destruir_linha(LINHA);
    }
}


