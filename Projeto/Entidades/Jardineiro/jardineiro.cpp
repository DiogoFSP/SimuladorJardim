#include "jardineiro.h"
#include "../Ferramenta/ferramenta.h"
#include <iostream>
#include "../../Settings/Settings.h"

Jardineiro::Jardineiro()
    : linha(-1), coluna(-1), dentroDoJardim(false),
        movimentosNoTurno(0),
        colheitaTurno(0),
        plantacaoTurno(0),
        ferramentaNaMao(nullptr),
        entrouNesteTurno(false),
        saiuNesteTurno(false)
{
}

Jardineiro::~Jardineiro() {
    for (Ferramenta* f : inventario) {
        delete f;
    }
    inventario.clear();
}

void Jardineiro::adicionaFerramenta(Ferramenta* f) {
    if (f == nullptr) return;

    inventario.push_back(f);
    std::cout << "Ferramenta " << f->getNome() << " guardada na mochila.\n";
}

void Jardineiro::setlinha(int l) { linha = l; }
void Jardineiro::setcoluna(int c) { coluna = c; }
int Jardineiro::getlinha() const { return linha; }
int Jardineiro::getcoluna() const { return coluna; }

bool Jardineiro::estaDentro() const {
    return dentroDoJardim;
}

char Jardineiro::getSimbolo() {
    return '*';
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramentaNaMao;
}

// --- Gestão de entradas/saídas ---
bool Jardineiro::jaEntrouNesteTurno() const { return entrouNesteTurno; }
bool Jardineiro::jaSaiuNesteTurno() const { return saiuNesteTurno; }
void Jardineiro::marcaEntrada() { entrouNesteTurno = true; }
void Jardineiro::marcaSaida() { saiuNesteTurno = true; }

void Jardineiro::listarFerramentas() const {

    if (inventario.empty() && ferramentaNaMao == nullptr) {
        std::cout << "Mochila vazia.\n";
        return;
    }

    std::cout << "=== Ferramentas do jardineiro Inventario ===\n";

    for (size_t i = 0; i < inventario.size(); ++i) {
        Ferramenta* f = inventario[i];
        std::cout << "ID=" << f->getNumeroSerie()
                  << " | Tipo=" << f->getNome()
                  << " | " << f->info();

        if (f == ferramentaNaMao) std::cout << " [NA MAO]";

        std::cout << "\n";
    }

    std::cout << "=== Ferramenta na Mao ===\n";
    if (ferramentaNaMao == nullptr) {
        std::cout << "Maos vazias\n";
    } else {
        std::cout << "ID=" << ferramentaNaMao->getNumeroSerie()
                  << " | " << ferramentaNaMao->getNome()
                  << " | " << ferramentaNaMao->info() << "\n";
    }

}

int Jardineiro::getQuantidadeFerramentas() const { return quantidade; }

Ferramenta* Jardineiro::getFerramentaNoInventario(int i) const {
    if (i < 0 || i >= inventario.size()) {
        return nullptr;
    }
    return inventario[i];
}

void Jardineiro::atuar(Solo& s) {
    if (ferramentaNaMao != nullptr) {
        bool validoParaUso = ferramentaNaMao->usar(s); //chama o usar() da ferramenta que tem em mao
        bool capacidade = ferramentaNaMao->verfCap();
        if (!validoParaUso || !capacidade) {
            delete ferramentaNaMao; //libertar espaço
            ferramentaNaMao = nullptr;

            std::cout << "A ferramenta que estava na mao do jardineiro foi descartada.\n";
        }
    }
}

bool Jardineiro::pegarFerramenta(int nSerie) {
    if (ferramentaNaMao != nullptr) {
        return false;
    }

    for (int i = 0; i < inventario.size(); i++) {

        if (inventario[i]->getNumeroSerie() == nSerie) {

            ferramentaNaMao = inventario[i];

            inventario.erase(inventario.begin() + i); // so remove, nao da delete

            std::cout << "O jardineiro pegou na ferramenta: " << ferramentaNaMao->getNome() << "\n";
            return true;
        }
    }

    return false;
}

void Jardineiro::largarFerramenta() {
    if (ferramentaNaMao == nullptr) {
        return;
    }

    inventario.push_back(ferramentaNaMao);

    std::cout << "O jardineiro guardou o(a) " << ferramentaNaMao->getNome()
              << " na mochila.\n";

    ferramentaNaMao = nullptr;
}


// --- Gestão de movimentos ---
bool Jardineiro::podeMover() const {
    return movimentosNoTurno < Settings::Jardineiro::max_movimentos; //true se ainda nao atingiu o limite
}
void Jardineiro::RegistarMovimento() {
    if (movimentosNoTurno < Settings::Jardineiro::max_movimentos) {
        movimentosNoTurno++;
    }
}
int Jardineiro::getMovimentosRestantes() const {
    return Settings::Jardineiro::max_movimentos - movimentosNoTurno;
}


// --- gestao de colheitas
bool Jardineiro::podeColher() const {
    return colheitaTurno < Settings::Jardineiro::max_colheitas;
}
void Jardineiro::RegistarColheita() {
    if (colheitaTurno < Settings::Jardineiro::max_colheitas) {
        colheitaTurno++;
    }
}
int Jardineiro::getColheitasRestantes() const {
    return Settings::Jardineiro::max_colheitas - colheitaTurno;
}

// ---  gestao de plantacoes
bool Jardineiro::podePlantar() const {
    return plantacaoTurno < Settings::Jardineiro::max_plantacoes;
}
void Jardineiro::RegistarPlantacao() {
    if (plantacaoTurno < Settings::Jardineiro::max_plantacoes) {
        plantacaoTurno++;
    }
}
int Jardineiro::getPlantacaoRestantes() const {
    return Settings::Jardineiro::max_plantacoes - plantacaoTurno;
}


//reset das var's de limite por instante
void Jardineiro::resetQuantidadesPorInstante() {
    movimentosNoTurno = 0;
    colheitaTurno = 0;
    plantacaoTurno = 0;
    saiuNesteTurno = false;
    entrouNesteTurno = false;
}

std::vector<Ferramenta *> Jardineiro::getInventario() {
    return inventario;
}
