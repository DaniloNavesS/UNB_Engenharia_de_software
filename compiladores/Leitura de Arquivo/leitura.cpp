#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    std::string file_pascal = argv[1];

    std::ifstream input_compilador(file_pascal);

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