#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include "../Ferramenta/ferramenta.h"
#include "../../Settings/Settings.h"
#include "../../Solo/solo.h"
#include <vector>


class Ferramenta;
class Solo;

class Jardineiro {
private:
    int linha;
    int coluna;
    bool dentroDoJardim;
    int movimentosNoTurno;
    int colheitaTurno;
    int plantacaoTurno;

    std::vector<Ferramenta*> inventario;
    //int capacidade;
    int quantidade;
    Ferramenta* ferramentaNaMao;

    bool entrouNesteTurno;
    bool saiuNesteTurno;

public:
    Jardineiro();
    ~Jardineiro();

    void adicionaFerramenta(Ferramenta* f);
    void pegaFerramenta(int numeroSerie);
    void largaFerramenta();
    void compraFerramenta(char tipo);
    void listarFerramentas() const;

    void expandir();

    //movimentos por instante (maz 10)
    bool podeMover() const;
    void RegistarMovimento();
    int getMovimentosRestantes() const;

    //colheira por instante
    bool podeColher() const;
    void RegistarColheita();
    int getColheitasRestantes() const;

    //plantação
    bool podePlantar() const;
    void RegistarPlantacao();
    int getPlantacaoRestantes() const;

    //reset dos limites após avancar instantes
    void resetQuantidadesPorInstante();

    void setlinha(int l);
    void setcoluna(int c);
    int getlinha() const;
    int getcoluna() const;

    bool estaDentro() const;
    char getSimbolo();
    Ferramenta* getFerramentaNaMao() const;

    int getQuantidadeFerramentas() const;
    Ferramenta* getFerramentaNoInventario(int nserie) const;

    // --- Gestão de entradas/saídas ---
    bool jaEntrouNesteTurno() const;
    bool jaSaiuNesteTurno() const;
    void marcaEntrada();
    void marcaSaida();
    void resetEntradasSaidas();


    //usar ferramenta
    void atuar(Solo& s);
    bool pegarFerramenta(int nSerie);
    void largarFerramenta();

    std::vector<Ferramenta *> getInventario();
};

#endif