#include <iostream>
#include <fstream>
#include <regex>

enum tokens_identificadores {
    LETRA,
    DIGITO,
    SIMBOLO_ESPECIAL,
    COMPOSTO_ESPECIAL,
    KEYWORD
};

int main(int argc, char *argv[])
{
    std::regex regex("\\(\\*.*\\*\\)");
    //Arquivos
    std::string file_pascal = argv[1];
    std::ifstream input_compilador(file_pascal);
    std::string arquivo_inteiro;
    if (input_compilador.is_open())
    {
        std::string linha;
        while (std::getline(input_compilador, linha))
        {
            arquivo_inteiro += linha;
        }
    input_compilador.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }

    std::string linha_formatado = std::regex_replace(arquivo_inteiro, regex, "");
    std::cout << linha_formatado << std::endl;

    return 0;
}