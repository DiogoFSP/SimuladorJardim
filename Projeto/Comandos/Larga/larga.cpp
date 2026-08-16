#include "larga.h"
#include "../../Entidades/Jardineiro/jardineiro.h"

CmdLarga::CmdLarga(Jardim* j) : Comando("larga", j) {}

CmdLarga::~CmdLarga() {
}

void CmdLarga::executar(std::string* seg, int n) {
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: larga\n";
        return;
    }

    Jardineiro* jard = jardim->getJardineiro();

    if (!jard) {
        std::cout << "[ERRO] O jardineiro nao esta presente.\n";
        return;
    }

    if (jard->getFerramentaNaMao() == nullptr) {
        std::cout << "[ERRO] O jardineiro nao tem nenhuma ferramenta na mao para largar.\n";
        return;
    }

    std::string nomeFerramenta = jard->getFerramentaNaMao()->getNome();

    jard->largarFerramenta();

    std::cout << "[OK] " << nomeFerramenta << " foi guardada no inventario com sucesso.\n";
}