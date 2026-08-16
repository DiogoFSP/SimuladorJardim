#include "compra.h"

CmdCompra::CmdCompra(Jardim* j): Comando("compra", j) {}

CmdCompra::~CmdCompra() {
}

void CmdCompra::executar(std::string *seg, int n) {
    //verificar tam
    if (n != 2 || seg[1].size() != 1) {
        std::cout << "[ERRO] Sintaxe: compra <c>\n";
        return;
    }
    char tipo = seg[1][0];

    if (tipo != 'g' && tipo != 'a' && tipo != 't' && tipo != 'z') {
        std::cout << "[ERRO]: Tipo de ferramenta desconhecido.\n"
            << " g: Regador\n a: Adubo\n t: Tesoura\n z: Enxada Rotativa\n";
        return;
    }

    bool sucesso = jardim->compraFerramenta(tipo);

    if (sucesso) {
        std::cout << "[OK] Ferramenta do tipo "<< tipo << " comprada e adicionada ao inventario \n";
    } else {
        std::cout << "[ERRO]: Nao foi possivel efetuar a compra\n Possiveis causas: Jardineiro ausente?\n";
    }
}

