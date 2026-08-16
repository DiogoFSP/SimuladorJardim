#include "jardim.h"

#include "../Entidades/Ferramenta/EnxadaRotativa/enxadarotativa.h"
#include "../Entidades/Ferramenta/PacoteAdubo/adubo.h"
#include "../Entidades/Ferramenta/Regador/regador.h"
#include "../Entidades/Ferramenta/TesouraPoda/tesoura.h"
#include "../Entidades/Planta/Cacto/cacto.h"
#include "../Entidades/Planta/Roseira/roseira.h"
#include "../Entidades/Planta/ErvaDaninha/erva.h"
#include "../Entidades/Planta/PlantaExotica/sentinela.h"
#include "../utilidades.h"
#include "../Entidades/Ferramenta/EnxadaRotativa/enxadarotativa.h"

Jardim::Jardim(int l, int c)
    : linhas(l), colunas(c), jardineiroPresente(false) {
    this->jardineiro = new Jardineiro();
    solos = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i) {
        solos[i] = new Solo[colunas];
    }

    for (int i = 0; i < 3; i++) {
        gerarFerramentaAleatoria();
    }
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; ++i) {
        delete[] solos[i];
    }
    delete[] solos;

    if (jardineiro != nullptr) {
        delete jardineiro;
        jardineiro = nullptr;
    }
}

// Getters básicos
int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }

// Posição do jardineiro
int Jardim::getlinhaJardineiro() const {
    if (jardineiro == nullptr) return -1;
    return jardineiro->getlinha();
}

int Jardim::getcolunaJardineiro() const {
    if (jardineiro == nullptr) return -1;
    return jardineiro->getcoluna();
}

// Acesso ao solo
Solo& Jardim::getSolo(int l, int c) {
    return solos[l][c];
}

const Solo& Jardim::getSolo(int l, int c) const {
    return solos[l][c];
}

// Jardineiro
void Jardim::setJardineiro(Jardineiro* j) {
    jardineiro = j;
}
Jardineiro* Jardim::getJardineiro() const { return jardineiro; }

bool Jardim::getJardineiroPresente() const { return jardineiroPresente; }

void Jardim::saiJardineiro(Jardineiro* j, int linha, int coluna) {

    if (j != nullptr && j->jaSaiuNesteTurno()) {
        std::cout << "[ERRO] Ja saiu 1x do jardim neste turno.\n";
        return;
    }

    jardineiroPresente = false;
    if (j != nullptr) {
        j->setlinha(-1);
        j->setcoluna(-1);
        j->marcaSaida();
    }
    std::cout << "O jardineiro saiu do jardim...\n";
}

// Impressão do jardim
void Jardim::imprimir() const {
    std::cout << "    ";
    for (int c = 0; c < colunas; ++c) {
        char letra = 'A' + c;
        std::cout << " " << letra << " ";
    }
    std::cout << "\n";

    std::cout << "   +" << std::string(colunas * 3, '-') << "+\n";

    for (int l = 0; l < linhas; ++l) {
        char letraLinha = 'A' + l;
        std::cout << " " << letraLinha << " |";

        for (int c = 0; c < colunas; ++c) {

            if (jardineiroPresente && jardineiro != nullptr &&
                jardineiro->getlinha() == l && jardineiro->getcoluna() == c) {

                std::cout << " " << jardineiro->getSimbolo() << " ";
                }
            else {
                std::cout << " " << getSolo(l, c).getSimbolo() << " ";
            }
        }
        std::cout << "|\n";
    }
    std::cout << "   +" << std::string(colunas * 3, '-') << "+\n\n";
}

bool Jardim::verpos(const std::string &pos, int& linhaDest, int& colunaDest) const{
    if (pos.size() != 2 || pos[0] < 'a' || pos[0] > 'z' || pos[1] < 'a' || pos[1] > 'z') {
        std::cout << "[ERRO] Posicao invalida. Usa formato <linha><coluna> (ex: ab)\n";
        return false;
    }

    linhaDest = std::tolower(pos[0]) - 'a';
    colunaDest = std::tolower(pos[1]) - 'a';

    if (linhaDest < 0 || linhaDest >= linhas ||
        colunaDest < 0 || colunaDest >= colunas) {
        std::cout << "[ERRO] Posicao fora dos limites do jardim.\n";
        return false;
        }

    return true;
}

// funcoes para comandos

bool Jardim::entraJardineiro(int linha, int coluna) {

    if (jardineiro == nullptr) {
        jardineiro = new Jardineiro();
    }

    if (linha < 0 || linha >= linhas || coluna < 0 || coluna >= colunas) {
        std::cout << "[ERRO] Posicao de entrada invalida.\n";
        return false;
    }

    if (jardineiro->jaEntrouNesteTurno()) {
        std::cout << "O jardineiro ja entrou neste turno.\n";
        std::cout << "Avance 1 ou mais instantes para entrar novamente no jardim.\n";
        return false;
    }

    jardineiro->setlinha(linha);
    jardineiro->setcoluna(coluna);
    jardineiroPresente = true;

    verfFerramentanoSolo(linha, coluna);
    jardineiro->marcaEntrada();

    return true;
}

bool Jardim::plantarPlanta(int linha, int coluna, char tipo) const{

    if (solos[linha][coluna].getPlanta() != nullptr) {
        std::cout << "[ERRO] Ja existe uma planta nessa posicao.\n";
        return false;
    }

    if (!jardineiro->podePlantar()) {
        std::cout << "[ERRO]: Limite de plantacoes por turno atingido.\n";
        return false;
    }

    Planta* nova = nullptr;

    switch (tipo) {
        case 'c':
            nova = new Cacto();
            break;
        case 'r':
            nova = new Roseira();
            break;
        case 'e':
            nova = new Erva_Daninha();
            break;
        case 'x':
            nova = new Sentinela();
            break;
        default:
            std::cout << "[ERRO] Tipo de planta invalido.\n";
            return false;
    }

    solos[linha][coluna].setPlanta(nova);

    jardineiro->RegistarPlantacao();

    return true;
}

bool Jardim::colhePlanta(int linha, int coluna) const{
    if (solos[linha][coluna].getPlanta() == nullptr) {
        std::cout << "[ERRO] Nao existe planta nessa posicao.\n";
        return false;
    }

    if (!jardineiro->podeColher()) {
        std::cout << "O jardineiro ja atingiu o limite de colheitas neste turno!\n";
        return false;
    }
    jardineiro->RegistarColheita();

    solos[linha][coluna].removerPlanta();

    return true;
}

void Jardim::larea() const {
    bool encontrou = false;
    Jardineiro* jardi = getJardineiro();
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            Solo& s = solos[i][j];

            bool temJardineiroAqui = false;
            if (jardineiroPresente && jardi != nullptr) {
                if (jardi->getlinha() == i && jardi->getcoluna() == j) {
                    temJardineiroAqui = true;
                }
            }

            bool temAlgo = (s.getPlanta() != nullptr) ||
                (s.getFerramenta() != nullptr) ||
                temJardineiroAqui;

            if (temAlgo) {
                encontrou = true;
                std::cout << "Posicao "
                          << static_cast<char>('a' + i)
                          << static_cast<char>('a' + j)
                          << " || Solo(Agua=" << solos[i][j].getAgua()
                          << ", Nutrientes=" << solos[i][j].getNutrientes()
                          << ")";

                if (solos[i][j].getPlanta() != nullptr) {
                    Planta* p = solos[i][j].getPlanta();
                    std::cout << " | Planta " << p->getSimbolo()
                              << " (Beleza=" << p->getBeleza()
                              << ", Agua=" << p->getAgua()
                              << ", Nutrientes=" << p->getNutrientes()
                              << ")";
                }

                if (s.getFerramenta() != nullptr) {
                    std::cout << " | Ferramenta "
                              << s.getFerramenta()->getSimbolo();
                }

                if (temJardineiroAqui) {
                    std::cout << " | Jardineiro";
                }

                std::cout << "\n";
            }
        }
    }

    if (!encontrou)
        std::cout << "[ERRO] Nenhuma posicao ocupada no jardim.\n";

}

void Jardim::lferr() const {
    jardineiro->listarFerramentas();
}

bool Jardim::infoPlanta(int l, int c) {
    Planta *p  = solos[l][c].getPlanta();
    if (p == nullptr) {return false;}
    std::string pos;

    pos = 'a' + l;
    pos += 'a' + c;

    std::cout << "Planta em " << pos
    << " | Tipo=" << p->getSimbolo()
    << " | Beleza=" << p->getBeleza()
    << " | Agua=" << p->getAgua()
    << " | Nutrientes=" << p->getNutrientes()
    << " || Solo(Agua=" << solos[l][c].getAgua()
    << ", Nutr=" << solos[l][c].getNutrientes()
    << ")\n";
    return true;
}

bool Jardim::infoSolo(int l, int c) {
    std::string pos;

    pos = 'a' + l;
    pos += 'a' + c;

    std::cout << "Posicao " << pos
        << " || Solo(Agua=" << solos[l][c].getAgua()
        << ", Nutr=" << solos[l][c].getNutrientes()
        << ")";

    if (solos[l][c].getPlanta() != nullptr) {
        Planta* p = solos[l][c].getPlanta();
        std::cout << " | Planta " << p->getSimbolo()
                  << " (Beleza=" << p->getBeleza()
                  << ", Agua=" << p->getAgua()
                  << ", Nutr=" << p->getNutrientes()
                  << ")";
    }

    if (solos[l][c].getFerramenta() != nullptr) {
        std::cout << " | Ferramenta=" << solos[l][c].getFerramenta()->getSimbolo();
    }

    if (jardineiroPresente) {
        std::cout << " | Jardineiro presente";
    }

    std::cout << "\n";
    return true;
}

void Jardim::avancaInstantes(int n) {
    for (int i=0; i < n; i++) {

        //resetar a flag de nascida agr
        for (int l = 0; l < linhas; l++) {
            for (int c = 0; c < colunas; c++) {
                Planta* p = solos[l][c].getPlanta();
                if (p != nullptr) {
                    p->setNascagr(false);
                }
            }
        }

        if (jardineiroPresente && jardineiro != nullptr) {
            //coordenadas atuais
            int jL = jardineiro->getlinha();
            int jC = jardineiro->getcoluna();

            if (jL >= 0 && jL < linhas && jC >= 0 && jC < colunas ) {
                Solo& soloAtual = getSolo(jL, jC);

                jardineiro->atuar(soloAtual);
            }
        }

        for (int l = 0; l < linhas; l++) {
            for (int c = 0; c < colunas; c++) {
                Solo& s = solos[l][c];
                Planta* p = s.getPlanta();

                if (p != nullptr && !p->nasceuAgora()) {
                    Solo* vizinhos[8];
                    for(int v=0; v<8; v++) vizinhos[v] = nullptr;

                    // Cima, Baixo, Esq, Dir, CimaEsq, CimaDir, BaixoEsq, BaixoDir
                    int dL[] = {-1, 1,  0, 0, -1, -1,  1, 1};
                    int dC[] = { 0, 0, -1, 1, -1,  1, -1, 1};

                    for(int v=0; v<8; v++) {
                        int vizL = l + dL[v];
                        int vizC = c + dC[v];

                        if(vizL >= 0 && vizL < linhas && vizC >= 0 && vizC < colunas) {
                            vizinhos[v] = &solos[vizL][vizC];
                        }
                    }
                    p->processa(s, vizinhos);
                }
            }
        }
    }

    if (jardineiro != nullptr) {
        jardineiro->resetQuantidadesPorInstante();
    }
}

bool Jardim::compraFerramenta(char tipo) {

    Ferramenta* novaFerramenta = nullptr;

    switch (tipo) {
        case 'g':
            novaFerramenta = new Regador();
            break;
        case 'a':
            novaFerramenta = new PacoteDeAdubo();
            break;
        case 't':
            novaFerramenta = new TesouraPoda();
            break;
        case 'z':
            novaFerramenta = new Enxada_Rotativa();
            break;
        default:
            return false;
    }

    if (novaFerramenta != nullptr) {
        jardineiro->adicionaFerramenta(novaFerramenta);
        return true;
    }

    return false;
}

void Jardim::gerarFerramentaAleatoria() {

    bool noJardim = false;

    while (!noJardim) {
        int rL = Utilidades::obterValorAleatorio(0, linhas-1);
        int rC = Utilidades::obterValorAleatorio(0, colunas-1);

        //verf se a posicao n tem ferramenta
        if (solos[rL][rC].getFerramenta() == nullptr) {
            int tipoFerramenta = Utilidades::obterValorAleatorio(0, 3);

            Ferramenta* novaF = nullptr;

            switch (tipoFerramenta) {
                case 0: novaF = new Enxada_Rotativa(); break;
                case 1: novaF = new PacoteDeAdubo(); break;
                case 2: novaF = new Regador(); break;
                case 3: novaF = new TesouraPoda(); break;
            }

            if (novaF != nullptr) {
                solos[rL][rC].setFerramenta(novaF);
                noJardim = true;
            }
        }
    }
}

void Jardim::verfFerramentanoSolo(int l, int c) {
    Ferramenta* f = solos[l][c].getFerramenta();

    if (f != nullptr) {
        jardineiro->adicionaFerramenta(f); //se naquela posição exister uma ferramenta add ao invent

        solos[l][c].setFerramenta(nullptr);

        std::cout << "O jardineiro apanhou uma " << f->getNome() << "!\n";
        gerarFerramentaAleatoria();
    }
}

void Jardim::moverJardineiro(int dL, int dC) {
    if (!jardineiroPresente || jardineiro == nullptr) {
        return;
    }

    if (!jardineiro->podeMover()) {
        std::cout << "[ERRO]: Limite de movimentos por instante atingido (10)\n";
        return;
    }

    int linhaAtual = jardineiro->getlinha();
    int colunaAtual = jardineiro->getcoluna();
    int novaL = jardineiro->getlinha() + dL;
    int novaC = jardineiro->getcoluna() + dC;

    //verf limites
    if (novaL < 0 || novaL >= linhas || novaC < 0 || novaC >= colunas) {
        std::cout << "[ERRO] Movimento invalido: fora do jardim.\n";
        return;
    }

    verfFerramentanoSolo(novaL, novaC);

    //atualizar coordenadas internas
    jardineiro->setlinha(novaL);
    jardineiro->setcoluna(novaC);

    jardineiro->RegistarMovimento();
    std::cout << "[OK] O jardineiro moveu-se para " <<(char)('a' + novaL) << (char)('a' + novaC) << " ("
        <<  novaL << "," << novaC <<")\n";
}


