#include "roseira.h"
#include "../../../Solo/solo.h"
#include "../../../Settings//Settings.h"

Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua,Settings::Roseira::inicial_nutrientes,"bonita", 'r') {
    std::cout << "A conctruir Roseira...\n" << std::endl;
}

Roseira::~Roseira() {
    std::cout << "A destruir Roseira...\n" << std::endl;
}

void Roseira::absagua(Solo& s) {
    float aguaSolo = s.getAgua();
    int qtdabs = Settings::Roseira::absorcao_agua;
    if (aguaSolo >= qtdabs) {
        s.rmvagua(qtdabs);
        addagua(qtdabs);
    }
    rmvagua(Settings::Roseira::perda_agua);
}

void Roseira::absnutrientes(Solo& s) {
    float nutriSolo = s.getNutrientes();
    float qtdAbs = Settings::Roseira::absorcao_nutrientes;
    if (nutriSolo >= qtdAbs) {
        s.rmvnutrientes(qtdAbs);
        addnutrientes(qtdAbs);
    }
    rmvnutrientes(Settings::Roseira::perda_nutrientes);
}

bool Roseira::morre(Solo& s, Solo* vizinhos[8]) {
    bool faltaAgua = (getAgua() < Settings::Roseira::morre_agua_menor);
    bool faltaNutrientes = (getNutrientes() < Settings::Roseira::morre_nutrientes_menor);
    bool excessoNutrientes = (getNutrientes() > Settings::Roseira::morre_nutrientes_maior);

    int vizinhosExistentes = 0;
    int vizinhosOcupados = 0;

    for (int i = 0; i < 8; i++) {
        if (vizinhos[i] != nullptr) {
            vizinhosExistentes++;

            if (vizinhos[i]->getPlanta() != nullptr) {
                vizinhosOcupados++;
            }
        }
    }

    bool sufocada = (vizinhosExistentes > 0) && (vizinhosOcupados == vizinhosExistentes);

    if (faltaAgua || faltaNutrientes || excessoNutrientes || sufocada) {
        s.addnutrientes(this->getNutrientes());
        s.addagua(this->getAgua());

        s.removerPlanta();
        return true;
    }

    return false;
}

void Roseira::multiplica(Solo& s, Solo* vizinhos[8]) {
    if (this->getNutrientes() > Settings::Roseira::multiplica_nutrientes_maior) {

        for (int i = 0; i < 8; i++) {
            Solo* viz = vizinhos[i];

            if (viz != nullptr && viz->getPlanta() == nullptr) {

                Planta* nova = new Roseira();
                nova->setNascagr(true);

                float metadeAgua = this->getAgua() / 2.0f;

                nova->rmvnutrientes(nova->getNutrientes());
                nova->addnutrientes(Settings::Roseira::nova_nutrientes);

                nova->rmvagua(nova->getAgua());
                nova->addagua(metadeAgua);

                float excesso = this->getNutrientes() - Settings::Roseira::original_nutrientes;
                if (excesso > 0) {
                    this->rmvnutrientes(excesso);
                }

                this->rmvagua(metadeAgua);

                viz->setPlanta(nova);

                break;
            }
        }
    }
}

