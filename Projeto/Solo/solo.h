#ifndef SOLO_H
#define SOLO_H
#include <iostream>
#include <ostream>

#include "../Entidades/Ferramenta/ferramenta.h"
#include "../Entidades/Planta/planta.h"
class Planta;
class Ferramenta;
class Jardineiro;

class Solo {
private:
    float agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

    int instexagua; //Instantes com excesso de agua
    int instsnutri; //Instantes sem nutrientes

public:
    Solo();
    ~Solo();

    float getAgua() const;
    int getNutrientes() const;
    Planta* getPlanta() const;
    Ferramenta* getFerramenta() const;
    char getSimbolo() const;
    int getInstexagua() const;
    int getInstsnutriente() const;


    void addagua(float qtd); //adicionar agua por 'instante'
    void rmvagua(float qtd); //remover agua por 'instante'
    void addnutrientes(float qtd); //adicionar nutrientes por 'instante'
    void rmvnutrientes(float qtd); //remover nutrientes por 'instante'

    void incinstexagua(); //incremento de  n instantes excesso agua
    void zerainstexagua(); //zerar instantes com excesso de agua
    void incinstsnutriente();
    void zerainstsnutriente(); //semalhante a cima mas com 0

    void setPlanta(Planta* planta); //definir pos planta
    void removerPlanta();
    void setFerramenta(Ferramenta* ferramenta); //definir pos ferramenta;

    char getSimblo() const;
    void setJardineiro(Jardineiro* j, int linha, int coluna);

    void setAgua(float agua);
    void setNutri(float nutrientes);
};

#endif
