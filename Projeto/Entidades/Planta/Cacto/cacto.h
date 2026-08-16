#include "../planta.h"
#include "../../../Solo/solo.h"

class Cacto: public Planta {
private:

public:
    Cacto();

    ~Cacto();

    //absorve
    void absagua(Solo& s);
    void absnutrientes(Solo& s);
    bool morre(Solo& s, Solo* vizinhos[8]);
    void multiplica(Solo& s, Solo* vizinhos[8]);



};