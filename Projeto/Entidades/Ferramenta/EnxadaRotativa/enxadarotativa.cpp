#include "enxadarotativa.h"
#include "../../../Solo/solo.h"
#include "../ferramenta.h"
#include "../../../Settings/Settings.h"
#include <iostream>

Enxada_Rotativa::Enxada_Rotativa(): Ferramenta("Enxada Rotativa", 'z', Settings::Enxada_Rotativa::capacidade) {
    std::cout << "A construir Enxada Rotativa\n";
}

Enxada_Rotativa::~Enxada_Rotativa() {
    std::cout << "A destruir a enxada rotativa\n";
};

bool Enxada_Rotativa::usar(Solo &s) {
    if (verfCap()) {

        if (s.getAgua() >= Settings::Enxada_Rotativa::alagado){
            s.rmvagua(Settings::Enxada_Rotativa::perca_agua);
            s.addnutrientes(Settings::Enxada_Rotativa::ganho_nutrientes);
            rmvCapacidade(Settings::Enxada_Rotativa::gasto);

            std::cout << "Enxada Rotativa utilizada! Quantidade Restante: "
                << getCapacidade() << "\n";
        } else {
            std::cout << "O solo nao esta alagado!\n";
        }
        return true;
    }

    std::cout << "A enxada rotativa ja esta desgastada!\n";
    return false;
}

std::string Enxada_Rotativa::info() const {
    return getNome() + " (n " + std::to_string(getNumeroSerie()) +
           ") - Quantidade: " + std::to_string(getCapacidade());
}

bool Enxada_Rotativa::verfCap() const {
    return getCapacidade() >= Settings::Enxada_Rotativa::gasto;
}
