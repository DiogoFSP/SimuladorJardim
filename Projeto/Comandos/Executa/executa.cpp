#include "executa.h"
#include <fstream>

CmdExecuta::CmdExecuta(Jardim* j, GestorCmd* g) : Comando("executa", j), gestor(g) {}

CmdExecuta::~CmdExecuta() {
}

void CmdExecuta::executar(std::string* seg, int n) {
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: executa <nome_ficheiro>\n";
        return;
    }

    std::string nomeFicheiro = seg[1];
    std::ifstream ficheiro(nomeFicheiro);

    if (!ficheiro.is_open()) {
        std::cout << "[ERRO] Nao foi possivel abrir o ficheiro: " << nomeFicheiro << "\n";
        return;
    }
    std::cout << "---------------------------------------------------\n";
    std::cout << "A iniciar execucao de '" << nomeFicheiro << "'...\n";
    std::cout << "---------------------------------------------------\n";

    std::string linha;
    int contadorLinhas = 0;

    while (std::getline(ficheiro, linha)) {
        if (linha.empty() || linha[0] == '#') continue;

        contadorLinhas++;
        std::cout << "> " << linha << "\n";

        gestor->interpretar(linha);
        if (jardim != nullptr) {
            jardim->imprimir();
        }
    }

    ficheiro.close();
    std::cout << "---------------------------------------------------\n";
    std::cout << "Fim da execucao de '" << nomeFicheiro << "'. (" << contadorLinhas << " comandos lidos)\n";
    std::cout << "---------------------------------------------------\n";

}

void CmdExecuta::setJardim(Jardim* j) {
    this->jardim = j;
}