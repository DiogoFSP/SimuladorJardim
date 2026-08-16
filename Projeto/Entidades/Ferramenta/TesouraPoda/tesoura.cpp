#include "tesoura.h"

TesouraPoda::TesouraPoda()
        : Ferramenta("Tesoura de Poda", 't', -1) {
    std::cout << "A construir Tesoura Poda...\n";
}

TesouraPoda::~TesouraPoda() {
    std::cout << "A destruir Tesoura de Poda...\n";
}

bool TesouraPoda::usar(Solo &s){
    if (s.getPlanta()) {
        if (s.getPlanta()->getBeleza() == "feia") {
            std::cout << "Tesoura de poda: A remover planta feia...\n";
            s.setPlanta(nullptr);
            return true;
        } else {
            std::cout << "Tesoura de poda: nada para cortar aqui.\n";
        }
    }
    return false;
}

std::string TesouraPoda::info() const {
    return "Tesoura de Poda (n " + std::to_string(getNumeroSerie()) +
           ") - nunca se desgasta.";
}

bool TesouraPoda::verfCap() const {
    return true;
}