#include "../include/Manuale.h"

// Costruttore, dispositivo manuale, l'ora di spegnimento viene impostata a 23.59 in minuti
Manuale::Manuale(std::string n, int indirizzo, double p)
    : Dispositivo{n, indirizzo, p} {} //sfrutto il costruttore della classe base
