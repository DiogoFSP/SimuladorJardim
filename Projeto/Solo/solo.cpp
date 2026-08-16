#include "solo.h"
#include "../utilidades.h"


Solo::Solo()
    : planta(nullptr), ferramenta(nullptr) , instexagua(0), instsnutri(0) {
    agua = static_cast<float>(Utilidades::obterValorAleatorio(80,100)); // converter int para float
    nutrientes = Utilidades::obterValorAleatorio(40,50);
}

Solo::~Solo() {
    if (planta != nullptr) {
        delete planta;
    }
    if (ferramenta != nullptr) {
        delete ferramenta;
    }
}

float Solo::getAgua() const {
    return agua;
}

int Solo::getNutrientes() const {
    return nutrientes;
}


Planta* Solo::getPlanta() const {
    return planta;
}

Ferramenta* Solo::getFerramenta() const {
    return ferramenta;
}

int Solo::getInstexagua() const {
    return instexagua;
}
int Solo::getInstsnutriente() const {
    return instsnutri;
}

char Solo::getSimbolo() const {
    if (planta != nullptr) return planta->getSimbolo();
    if (ferramenta != nullptr) return ferramenta->getSimbolo();
    return  ' ';
}

void Solo::addagua(float qtd) {
    agua += qtd;
}

void Solo::rmvagua(float qtd) {
    agua -= qtd;
    if (agua < 0) {
        agua = 0;
    }
}

void Solo::setAgua(float agua) {
    this->agua = agua;
}

void Solo::addnutrientes(float qtd) {
    nutrientes += qtd;
}

void Solo::rmvnutrientes(float qtd) {
    nutrientes -= qtd;
    if (nutrientes < 0) {
        nutrientes = 0;
    }
}

void Solo::setNutri(float nutrientes) {
    this->nutrientes = nutrientes;
}

void Solo::incinstexagua() {
    instexagua++;
}

void Solo::zerainstexagua() {
    instexagua=0;
}

void Solo::incinstsnutriente() {
    instsnutri++;
}
void Solo::zerainstsnutriente() {
    instsnutri=0;
}

void Solo::setPlanta(Planta* nova) {
    planta = nova;
}

void Solo::removerPlanta() {
    if (planta != nullptr) {
        delete planta;
        planta = nullptr;
    }
}

void Solo::setFerramenta(Ferramenta *ferramenta) {
    this->ferramenta = ferramenta;
}





