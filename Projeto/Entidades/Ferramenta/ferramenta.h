#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include <string>
#include "../../Solo/solo.h"
#include "../../Settings/Settings.h"

class Solo;

class Ferramenta {
private:
    static int contador;   // contador global para gerar nº de serie unico
    int nserie;
    char simbolo;
    std::string nome;
    bool ausar;
    int capacidade;

public:
    Ferramenta(std::string nome, char simbolo, int capacidade);

    virtual ~Ferramenta();

    int getNumeroSerie() const;
    char getSimbolo() const;
    std::string getNome() const;
    bool getAusar() const;

    int getCapacidade() const;
    void rmvCapacidade(int qtd);

    bool setAusar(bool ausar);

    virtual bool usar(Solo &s) = 0; // como a funcao é igualada a 0 é orbigada a ser subescrita pela subclasse

    virtual std::string info() const; //info -> retornar str com info sobre ferramenta

    virtual bool verfCap() const = 0;

    static void atualizarContador(int novoValor);

    static void resetContador(int n);

    void setNumeroSerie(int id);

};

#endif