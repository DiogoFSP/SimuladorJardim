#ifndef JARDIM_H
#define JARDIM_H

#include <string>
#include <iostream>
#include "../Entidades/Planta/planta.h"
#include "../Entidades/Ferramenta/ferramenta.h"
#include "../Entidades/Jardineiro/jardineiro.h"
#include "../Solo/solo.h"

class Jardim {
private:
    int linhas;
    int colunas;
    Jardineiro* jardineiro;
    bool jardineiroPresente;
    Solo** solos;

public:
    Jardim(int l, int c);

    ~Jardim();


    int getLinhas() const;
    int getColunas() const;

    int getlinhaJardineiro() const;
    int getcolunaJardineiro() const;

    Solo& getSolo(int l, int c);
    const Solo& getSolo(int l, int c) const;

    void setJardineiro(Jardineiro *j);

    Jardineiro* getJardineiro() const;
    bool getJardineiroPresente() const;

    void saiJardineiro(Jardineiro* j, int linha, int coluna);

    bool temJardineiro() const;
    void imprimir() const;

    bool verpos(const std::string &pos, int& linhaDest, int& colunaDest) const;

    //funcoes para comando
    bool entraJardineiro(int linha, int coluna);

    bool plantarPlanta(int linha, int coluna, char tipo) const;
    bool colhePlanta(int linha, int coluna) const;

    void larea() const;

    void lferr() const;

    bool compraFerramenta(char tipo); //compra de x ferramento de tipo y

    bool infoPlanta(int l, int c); //informações da planta

    bool infoSolo(int l, int c); //informações da planta

    void avancaInstantes(int n); //avança n turnos no jardim

    void gerarFerramentaAleatoria();

    void verfFerramentanoSolo(int l, int c);

    void moverJardineiro(int dL, int dC);
};

#endif
