#include "cacto.h"
#include "../../../Solo/solo.h"
#include "../../../Settings/Settings.h"
#include "../../../utilidades.h"

Cacto::Cacto() : Planta(0,0,"neutra",'c') {
    std::cout << "A construir Cacto...\n" << std::endl;
}

Cacto::~Cacto() {
    std::cout << "A destruir Cacto...\n" << std::endl;
}

void Cacto::absagua(Solo& s) {
    // Absorve 25% da água do solo
    float aguaSolo = s.getAgua();
    float qtdabs = aguaSolo * (Settings::Cacto::absorcao_agua_percentagem / 100.0);
    addagua(qtdabs);
    s.rmvagua(qtdabs);
}

void Cacto::absnutrientes(Solo& s) {
    float nutriSolo = s.getNutrientes();
    float qtdabs = static_cast<float>(Utilidades::obterValorAleatorio(0, Settings::Cacto::absorcao_nutrientes));
    if (nutriSolo >= qtdabs) {
        addnutrientes(qtdabs);
        s.rmvnutrientes(qtdabs);
    }
}

bool Cacto::morre(Solo& s, Solo* vizinhos[8]) {
    if (s.getAgua() > Settings::Cacto::morre_agua_solo_maior) {
        s.incinstexagua();
    } else {
        s.zerainstexagua();
    }

    if (s.getNutrientes() <= Settings::Cacto::morre_nutrientes_solo_menor) {
        s.incinstsnutriente();
    } else {
        s.zerainstsnutriente();
    }

    bool morreAgua = s.getInstexagua() >= Settings::Cacto::morre_agua_solo_instantes;

    bool morreNutri = s.getInstsnutriente() > Settings::Cacto::morre_nutrientes_solo_instantes;

    if (morreAgua || morreNutri) {
        s.addnutrientes(this->getNutrientes());

        s.removerPlanta();
        return true;
    }

    return false;
}

void Cacto::multiplica(Solo& s, Solo* vizinhos[8]) {
    if (this->getNutrientes() > Settings::Cacto::multiplica_nutrientes_maior &&
        this->getAgua() > Settings::Cacto::multiplica_agua_maior) {

        for (int i = 0; i < 8; i++) {
            Solo* viz = vizinhos[i];

            if (viz != nullptr && viz->getPlanta() == nullptr) {

                Planta* nova = new Cacto();
                nova->setNascagr(true);

                float metadeAgua = this->getAgua() / 2.0f;
                float metadeNutri = this->getNutrientes() / 2.0f;

                this->rmvagua(metadeAgua);
                this->rmvnutrientes(metadeNutri);

                nova->addagua(metadeAgua);
                nova->addnutrientes(metadeNutri);

                viz->setPlanta(nova);
                break;
            }
        }
    }
}


