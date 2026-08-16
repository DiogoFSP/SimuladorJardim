#include "../planta.h"
#include "../../../Settings/Settings.h"
#include "../../../Solo/solo.h"
#include "../../../Settings/Settings.h"

class Roseira: public Planta {

public:
    Roseira();

    ~Roseira();

    //absorção
    void absagua(Solo& s);
    void absnutrientes(Solo& s);
    bool morre(Solo& s, Solo* vizinhos[8]) override;
    void multiplica(Solo& s, Solo* vizinhos[8]) override;
};