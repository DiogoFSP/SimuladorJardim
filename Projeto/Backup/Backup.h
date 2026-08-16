#ifndef BACKUP_H
#define BACKUP_H

#include <map>
#include <string>
#include <vector>

struct DadosSolo {
    int l, c;
    int aguaSolo, nutSolo;

    // Planta
    bool temPlanta;
    char tipoPlanta;
    int aguaPlanta, nutPlanta;

    // Ferramenta no chão
    bool temFerramenta;
    char tipoFerramenta;
    int idFerramenta;
};

struct DadosItem {
    char tipo;
    int id;
};

struct CopiaJardim {
    int linhas, colunas;

    std::vector<DadosSolo> s;

    bool jardineiroPresente;
    int jL, jC;
    std::vector<DadosItem> inv;
};

class Backup {
private:
    static std::map<std::string, CopiaJardim*> memorias;

public:
    static void guardar(const std::string& nome, CopiaJardim* dados);

    static CopiaJardim* recuperar(const std::string& nome);

    static bool existe(const std::string& nome);

    static bool apagar(const std::string& nome);

    static void limparTudo();
};

#endif