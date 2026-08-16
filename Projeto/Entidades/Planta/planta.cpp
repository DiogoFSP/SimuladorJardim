#include "planta.h"
#include "../../Solo/solo.h"
#include "Cacto/cacto.h"

Planta::Planta(int aguaInicial, int nutrientesInicial, const std::string &beleza, char simbolo)
        : beleza(beleza), simbolo(simbolo), agua(aguaInicial), nutrientes(nutrientesInicial) {
    this->idade = 0;
}

Planta::~Planta() {
}

float Planta::getAgua() const {
    return agua;
}

int Planta::getNutrientes() const {
    return nutrientes;
}

char Planta::getSimbolo() const {
    return simbolo;
}

std::string Planta::getBeleza() const {
    return beleza;
}

void Planta::addagua(float qtd) {
    agua += qtd;
}

void Planta::rmvagua(float qtd) {
    agua -= qtd;
    if (agua < 0) {
        agua = 0;
    }
}

void Planta::setAgua(float agua) {
    this->agua = agua;
}

void Planta::addnutrientes(float qtd) {
    nutrientes += qtd;
}

void Planta::rmvnutrientes(float qtd) {
    nutrientes -= qtd;
    if (nutrientes < 0) {
        nutrientes = 0;
    }
}

void Planta::setNutri (float nutrientes) {
    this->nutrientes = nutrientes;
}

bool Planta::nasceuAgora() const {
    return nascagr;
}

void Planta::setNascagr(bool nascagr) {
    this->nascagr = nascagr;
}

int Planta::getIdade() const {
    return idade;
}


void Planta::processa(Solo& s, Solo* vizinhos[8]) {
    idade++;

    absagua(s);
    absnutrientes(s);

    bool morreu = morre(s, vizinhos);
    if (morreu) {
        return;
    }

    multiplica(s, vizinhos);
}




