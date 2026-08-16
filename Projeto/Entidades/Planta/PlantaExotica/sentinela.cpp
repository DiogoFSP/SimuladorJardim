#include "sentinela.h"
#include "../../../Solo/solo.h"
#include "../../../Settings/Settings.h"

Sentinela::Sentinela() : Planta(
        Settings::Sentinela::inicial_agua,
        Settings::Sentinela::inicial_nutrientes,
        "bonita",
        'x') {

    this->contadorAbates = 0;
    std::cout << "A construir planta sentinela "<< std::endl;
}

Sentinela::~Sentinela() {
    std::cout << "A destruir sentinela..\n" << std::endl;
}

void Sentinela::absagua(Solo &s) {
    float aguaSolo = s.getAgua();
    float qtdabs = Settings::Sentinela::absorcao_agua;
    if (aguaSolo > qtdabs) {
        s.rmvagua(qtdabs);
        addagua(qtdabs);
    }
}

void Sentinela::absnutrientes(Solo &s) {
     float nutriSolo = s.getNutrientes();
    float qtdabs = Settings::Sentinela::absorcao_nutrientes;
    if (nutriSolo > qtdabs) {
        s.rmvnutrientes(qtdabs);
        addnutrientes(qtdabs);
    }
}

void Sentinela::processa(Solo& s, Solo* vizinhos[8]) {
    for (int i = 0; i < 8; i++) {
        if (vizinhos[i] != nullptr && vizinhos[i]->getPlanta() != nullptr) {
            if (vizinhos[i]->getPlanta()->getSimbolo() == 'e') {
                vizinhos[i]->removerPlanta();
                this->contadorAbates++;
            }
        }
    }
    rmvagua(Settings::Sentinela::perde_agua);
    rmvnutrientes(Settings::Sentinela::perde_nutri);
    Planta::processa(s, vizinhos); // chama o processa da classe base
}

bool Sentinela::morre(Solo &s, Solo *vizinhos[8]) {
    if (getNutrientes() <= Settings::Sentinela::morre_fome || getIdade() >= Settings::Sentinela::morre_idade) {
        s.addnutrientes(getNutrientes() / 2);
        s.removerPlanta();
        return true;
    }
    return false;
}

void Sentinela::multiplica(Solo& s, Solo* vizinhos[8]) {
    if (this->contadorAbates < Settings::Sentinela::abates_para_reproducao) {
        return;
    }

    if (getNutrientes() >= Settings::Sentinela::multiplica_custo) {
        for (int i = 0; i < 8; i++) {
            if (vizinhos[i] != nullptr && vizinhos[i]->getPlanta() == nullptr) {

                Planta* nova = new Sentinela();
                nova->setNascagr(true);

                nova->setNutri(Settings::Sentinela::nova_planta_nutri);
                nova->setAgua(getAgua() / 2);

                rmvnutrientes(Settings::Sentinela::nova_planta_nutri);
                rmvagua(getAgua() / 2);

                this->contadorAbates -= Settings::Sentinela::abates_para_reproducao;

                vizinhos[i]->setPlanta(nova);
                return;
            }
        }
    }
}