#include <iostream>
#include <fstream>
#include <regex>

int main(int argc, char *argv[]) {
    std::regex regex("(\\(\\*.*\\*\\))");
    std::regex regex_quebraLinha("(\n)|(\t)|(\\s+)");

    std::string file_pascal = argv[1];

    std::ifstream input_compilador(file_pascal);
    std::string arquivo_completo = "";

    if (input_compilador.is_open()) {
        std::string linha;

        while (std::getline(input_compilador, linha)) {
            arquivo_completo += linha + '\n';
        }

        input_compilador.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return 0;
    }
    
    arquivo_completo = std::regex_replace(arquivo_completo, regex_quebraLinha, "");
    arquivo_completo = std::regex_replace(arquivo_completo, regex, "");
    std::cout << arquivo_completo << std::endl;

    return 0;
}
