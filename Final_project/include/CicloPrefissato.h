#ifndef CICLOPREFISSATO_H
#define CICLOPREFISSATO_H

#include "Dispositivo.h"
#include <string>

class CicloPrefissato:public Dispositivo{
        private:
            int durataCiclo; //durata del ciclo in minuti
			int minRimanenti; //minuti rimanenti al termine del ciclo, e quindi allo spegnimento del dispositivo

	public:
		CicloPrefissato(std::string n, int indirizzo, double p, int t); //costruttore
		void accensione();
		void decreaseMinRimanenti() {minRimanenti--;} //abbassa di 1 i minuti rimanenti al termine del ciclo
		void resetMinRimanenti() {minRimanenti=durataCiclo;} //resetta i minuti mancanti alla fine del ciclo, questa funzione verrà chiamata ad ogni accensione del dispositivo CP
		int getMinRimanenti() const{return minRimanenti;} //ritorna i minuti rimanenti al termine del ciclo
		int getDurataCiclo() const{return durataCiclo;} //ritorna la durata del ciclo in minuti
};

#endif
