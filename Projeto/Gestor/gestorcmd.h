#ifndef GESTORCMD_H
#define GESTORCMD_H

#include "../Comandos/comandos.h"
#include "../Jardim/jardim.h"

class GestorCmd {
private:
    Comando** comandos;
    int capacidade;
    int quantidade;
    bool terminar = false;

    void expandir();

public:
    GestorCmd();

    ~GestorCmd();

    void registar(Comando* cmd);

    void interpretar(const std::string& linha);

    void pedirTermino() { terminar = true; }
    bool deveTerminar() const { return terminar; }

    int getNumeroComandos();
    Comando* getComando(int i);

    void prepararComandosJogo(Jardim** jardimRef, bool* terminarPtr);
};

#endif