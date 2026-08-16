#include "Backup.h"

std::map<std::string, CopiaJardim*> Backup::memorias;

void Backup::guardar(const std::string& nome, CopiaJardim* dados) {
    if (existe(nome)) {
        delete memorias[nome];
    }
    memorias[nome] = dados;
}

CopiaJardim* Backup::recuperar(const std::string& nome) {
    if (existe(nome)) {
        CopiaJardim* dados = memorias[nome];

        memorias.erase(nome);

        return dados;
    }
    return nullptr;
}

bool Backup::existe(const std::string& nome) {
    return memorias.find(nome) != memorias.end();
}

bool Backup::apagar(const std::string& nome) {
    if (existe(nome)) {
        delete memorias[nome];
        memorias.erase(nome);
        return true;
    }
    return false;
}

void Backup::limparTudo() {
    for (auto& par : memorias) {
        delete par.second;
    }
    memorias.clear();
}