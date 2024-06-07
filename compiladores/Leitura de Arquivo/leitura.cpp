#include <iostream>
#include <fstream>

int main()
{
    std::ifstream input_compilador("entrada.pas");

    if (input_compilador.is_open())
    {
        std::string linha;

        while (std::getline(input_compilador, linha))
        {
            std::cout << linha << std::endl;
        }
    input_compilador.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }

    return 0;
}