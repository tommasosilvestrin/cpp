#include "../include/CicloPrefissato.h"
#include "../include/Dispositivo.h"

// Costruttore
CicloPrefissato::CicloPrefissato(std::string n, int indirizzo, double p, int t)
    : Dispositivo{n, indirizzo, p}, durataCiclo{t} {} //sfrutto il costruttore della classe base

void CicloPrefissato::accensione(){
    Dispositivo::accensione();
    resetMinRimanenti();
}
