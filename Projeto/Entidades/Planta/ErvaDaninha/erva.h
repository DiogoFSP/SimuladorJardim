#ifndef ERVA_H
#define ERVA_H
#include "../../../Solo/solo.h"
#include "../planta.h"
#include "../../../Settings/Settings.h"

class Erva_Daninha : public Planta {
private:
    int contadorMultiplicacao;

public:
    Erva_Daninha();

    ~Erva_Daninha();

    //abs
    void absagua(Solo& s);
    void absnutrientes(Solo& s);
    bool morre(Solo& s, Solo* vizinhos[8]);
    void multiplica(Solo& s, Solo* vizinhos[8]);

};
#endif