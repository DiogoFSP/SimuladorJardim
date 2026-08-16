#include "erva.h"
#include "../../../Solo/solo.h"
#include "../../../Settings/Settings.h"
#include "../../../utilidades.h"

Erva_Daninha::Erva_Daninha() : Planta(Settings::ErvaDaninha::inicial_agua,Settings::ErvaDaninha::inicial_nutrientes,"feia", 'e') {
    std::cout << "A construir erva daninha...\n" << std::endl;
}

Erva_Daninha::~Erva_Daninha() {
    std::cout << "A destruir erva..\n" << std::endl;
}

void Erva_Daninha::absagua(Solo& s) {
    //Absorve 1u de agua
    float aguaSolo = s.getAgua();
    float qtdabs = Settings::ErvaDaninha::absorcao_agua;
    if (aguaSolo >= qtdabs) {
        s.rmvagua(qtdabs);
        addagua(qtdabs);
    }
}

void Erva_Daninha::absnutrientes(Solo &s) {
    //Absorve 1u de nutrientes
    float nutriSolo = s.getNutrientes();
    float qtdabs = Settings::ErvaDaninha::absorcao_nutrientes;
    if (nutriSolo >= qtdabs) {
        s.rmvnutrientes(qtdabs);
        addnutrientes(qtdabs);
    }
}

bool Erva_Daninha::morre(Solo &s, Solo* vizinhos[8]) {
    if (getIdade() >= Settings::ErvaDaninha::morre_instantes) {
        s.removerPlanta();
        return true;
    }
    return false;
}

void Erva_Daninha::multiplica(Solo& s, Solo* vizinhos[8]) {
    contadorMultiplicacao++;

    if (this->getNutrientes() > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        contadorMultiplicacao >= Settings::ErvaDaninha::multiplica_instantes) {

        Solo* viz = vizinhos[Utilidades::obterValorAleatorio(0,7)];

        if (viz != nullptr) {
            if (viz->getPlanta() != nullptr) {
                viz->removerPlanta();
            }

            Planta* nova = new Erva_Daninha();
            viz->setPlanta(nova);
            nova->setNascagr(true);

            contadorMultiplicacao = 0;
        }
        }
}
