#include "adubo.h"
#include "../../../Solo/solo.h"
#include "../ferramenta.h"
#include "../../../Settings/Settings.h"
#include <iostream>

PacoteDeAdubo::PacoteDeAdubo(): Ferramenta("Pacote de Adubo",'a', Settings::Adubo::capacidade) {
    std::cout << "A construir Pacote de Adubo com quantidade" << Settings::Adubo::capacidade << "\n";
}

PacoteDeAdubo::~PacoteDeAdubo() {
    std::cout << "A destruir pacote de adubo..." << std::endl;
}

bool PacoteDeAdubo::usar(Solo &s) {
    if (verfCap()) {
        s.addnutrientes(Settings::Adubo::dose);
        rmvCapacidade(Settings::Adubo::dose);

        std::cout << "Pacote de adubo usado! Quantidade restante: "
                  << getCapacidade() << "\n";
        return true;
    } else {
        std::cout << "O pacote de adubo ja nao tem mais!\n";
    }
    return false;
}

std::string PacoteDeAdubo::info() const {
    return getNome() + " (n " + std::to_string(getNumeroSerie()) +
           ") - Quantidade: " + std::to_string(getCapacidade());
}

bool PacoteDeAdubo::verfCap() const {
    return getCapacidade() >= Settings::Adubo::dose;
}