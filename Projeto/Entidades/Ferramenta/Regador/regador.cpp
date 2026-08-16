#include "regador.h"
#include "../../../Solo/solo.h"   // aqui precisamos do Solo para chamar addagua()
#include "../ferramenta.h"
#include "../../../Settings/Settings.h"

Regador::Regador(): Ferramenta("Regador", 'g', Settings::Regador::capacidade) {
    std::cout << "A construir Regador com capacidade" << Settings::Regador::capacidade <<"\n";
}

Regador::~Regador() {
    std::cout << "A destruir regador..." << std::endl;
}

bool Regador::usar(Solo &s) {
    if (verfCap()) {
        s.addagua(Settings::Regador::dose);

        rmvCapacidade(Settings::Regador::dose);

        std::cout << "Regador usado! Capacidade restante: "
                  << getCapacidade() << "\n";
        return true;
    } else {
        std::cout << "O regador ja nao tem agua! e foi descartado\n";
    }
    return false;
}

std::string Regador::info() const {
    return getNome() + " (n " + std::to_string(getNumeroSerie()) +
           ") - Capacidade: " + std::to_string(getCapacidade());
}

bool Regador::verfCap() const {
    return getCapacidade() >= Settings::Regador::dose;
}