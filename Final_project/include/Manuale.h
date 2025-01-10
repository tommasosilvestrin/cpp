#ifndef MANUALE_H
#define MANUALE_H

#include "Dispositivo.h"
#include <string>

class Manuale:public Dispositivo{
    private:
		int timerSpegnimento; //orario programmato di spegnimento

	public:
		Manuale(std::string n, int indirizzo, double p);//costruttore 
		void setTimerSpegnimento(int e){timerSpegnimento = e;} //setta un orario di spegnimento
		int getTimerSpegnimento() const{return timerSpegnimento;} //restituisce l'orario programmato di spegnimento
};

#endif
