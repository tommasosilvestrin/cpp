#include "../include/Dispositivo.h"

// Costruttore della classe base Dispositivo
Dispositivo::Dispositivo(std::string n, int indirizzo, double p)
    : nome{n}, id{indirizzo}, potenza{p}, energia{0}, stato{false}, timerAccensione{-1} {}

void Dispositivo::increaseEnergia(){ //questa funzione verrà chiamata ad ogni passaggio di minuto, se il dispositivo è acceso
    if(potenza > 0){
        energia += potenza/60; //energia prodotta in 1 minuto
    }
    else{
        energia += (-potenza)/60; //energia consumata in 1 minuto
    }
}
