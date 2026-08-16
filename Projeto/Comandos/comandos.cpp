#include "comandos.h"


Comando::Comando(const std::string& n, Jardim* j)
    : nome(n), jardim(j) {}

Comando::~Comando() = default;


std::string Comando::getNome() const { return nome; }
