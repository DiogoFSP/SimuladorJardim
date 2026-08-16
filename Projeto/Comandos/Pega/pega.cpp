#include "pega.h"
#include "../../Entidades/Jardineiro/jardineiro.h"
#include "../../Entidades/Ferramenta/ferramenta.h"
#include "../../utilidades.h"

CmdPega::CmdPega(Jardim* j) : Comando("pega", j) {}

CmdPega::~CmdPega() {
}

void CmdPega::executar(std::string* seg, int n) {
    if (n != 2) {
        std::cout << "[ERRO] Sintaxe: pega <nserie>\n";
        return;
    }
    if (!Utilidades::soDigitos(seg[1])) {
        std::cout << "[ERRO] O parametro deve ser um numero inteiro positivo.\n";
        return;
    }

    int nserie = std::stoi(seg[1]);
    Jardineiro* jard = jardim->getJardineiro();

    if (jard == nullptr) {
        std::cout << "[ERRO] Nao ha jardineiro no jardim.\n";
        return;
    }

    if (jard->getFerramentaNaMao() != nullptr) {
        std::cout << "[ERRO] O jardineiro ja tem uma ferramenta na mao ("
                  << jard->getFerramentaNaMao()->getNome()
                  << "). Use 'larga' primeiro.\n";
        return;
    }

    bool sucesso = jard->pegarFerramenta(nserie);

    if (sucesso) {
        std::cout << "[OK] Ferramenta " << nserie << " colocada na mao.\n";
    } else {
        std::cout << "[ERRO] Ferramenta com ID " << nserie << " nao encontrada no inventario.\n";
    }
}