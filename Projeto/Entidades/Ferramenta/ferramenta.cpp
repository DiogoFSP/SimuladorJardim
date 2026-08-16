#include "ferramenta.h"

Ferramenta::Ferramenta(std::string nome, char simbolo, int capacidade)
    : nome(nome), nserie(++contador), simbolo(simbolo), ausar(ausar), capacidade(capacidade) {
}

Ferramenta::~Ferramenta() {
}

int Ferramenta::contador = 0;

int Ferramenta::getNumeroSerie() const {
    return nserie;
}

char Ferramenta::getSimbolo() const {
    return simbolo;
}

std::string Ferramenta::getNome() const {
    return nome;
}

int Ferramenta::getCapacidade() const{
    return capacidade;
}

std::string Ferramenta::info() const {
    return nome + " (n " + std::to_string(nserie) + ")";
}

void Ferramenta::rmvCapacidade(int qtd) {
    capacidade -= qtd;
}

void Ferramenta::atualizarContador(int novoValor) {
    if (novoValor > contador) {
        contador = novoValor;
    }
}

void Ferramenta::setNumeroSerie(int id) {
    nserie = id;
}

void Ferramenta::resetContador(int n) {
    contador = n;
}
