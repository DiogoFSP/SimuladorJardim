#ifndef SENTINELA_H
#define SENTINELA_H
#include "../../../Solo/solo.h"
#include "../planta.h"
#include "../../../Settings/Settings.h"

class Sentinela : public Planta{
private:
    int contadorAbates;

public:
    Sentinela();

    ~Sentinela();

    void absagua(Solo &s);
    void absnutrientes(Solo &s);
    void processa(Solo& s, Solo* vizinhos[8]) override;
    bool morre(Solo& s, Solo* vizinhos[8]);
    void multiplica(Solo& s, Solo* vizinhos[8]);

};

#endif