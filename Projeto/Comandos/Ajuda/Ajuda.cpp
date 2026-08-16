#include "Ajuda.h"

CmdAjuda::CmdAjuda(Jardim* j) : Comando("ajuda", j) {}

CmdAjuda::~CmdAjuda() {}

void CmdAjuda::executar(std::string* segs, int n) {
    if (n != 1) {
        std::cout << "[ERRO] Sintaxe: ajuda\n";
        return;
    }
    std::cout << "\n=== LISTA DE COMANDOS ANTES DE CRIAR O JARDIM ===\n";

    std::cout << " jardim <l> <c>       : Cria o jardim (Max 26x26).\n";
    std::cout << " executa <ficheiro>   : Executa comandos de um ficheiro.\n";
    std::cout << "=========================\n";


    std::cout << "\n=== LISTA DE COMANDOS ===\n";

    // GERAIS
    std::cout << " jardim <l> <c>       : Cria o jardim (Max 26x26).\n";
    std::cout << " avanca [n]           : Avanca n instantes.\n";
    std::cout << " fim                  : Sai do programa.\n";
    std::cout << " executa <ficheiro>   : Executa comandos de um ficheiro.\n";

    // JARDINEIRO E ACOES
    std::cout << " -- Acoes do Jardineiro --\n";
    std::cout << " c / b / e / d        : Move Cima/Baixo/Esq/Dir.\n";
    std::cout << " entra <l><c>         : Entra no jardim.\n";
    std::cout << " sai                  : Sai do jardim.\n";
    std::cout << " planta <l><c> <tipo> : Planta (c, r, e, x).\n";
    std::cout << " colhe <l><c>         : Colhe planta.\n";
    std::cout << " compra <tipo>        : Compra ferramenta (g, a, t, z).\n";
    std::cout << " pega <id>            : Pega ferramenta.\n";
    std::cout << " larga                : Larga ferramenta.\n";

    // INFORMACOES
    std::cout << " -- Informacoes --\n";
    std::cout << " larea                : Mostra o jardim.\n";
    std::cout << " lplantas             : Lista plantas.\n";
    std::cout << " lplanta <l><c>       : Detalhes da planta.\n";
    std::cout << " lsolo <l><c> [n]     : Detalhes do solo.\n";
    std::cout << " lferr                : Lista ferramentas.\n";

    std::cout << "=========================\n";
}
