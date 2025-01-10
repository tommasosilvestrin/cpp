#ifndef CASA_H
#define CASA_H

#include <vector>
#include <memory>
#include <string>
#include "Manuale.h"
#include "CicloPrefissato.h"


class Casa{

    private:
        static const int FINE = 1439; //rappresenta l'ora 23:59 in minuti passati dalle 00:00, ultimo minuto utile della giornata
        double potenzaMax; //(in kW) limite della potenza del sistema (inizialmente 3,5 kW)
        double potenzaInUso; //(in kW) somma delle potenze dei dispositivi accesi
        std::vector<std::shared_ptr<Dispositivo>> vetDispositivi; //vettore di dispositivi
        std::vector<std::shared_ptr<Dispositivo>> dispAccesi; //contiene i dispositivi accesi in ordine di accensione, dal meno recente al più recente
        int orario; //l'ora del giorno rappresentata in minuti passati dalle 00:00

    public:

        Casa(double p); //costruttore
        std::string const getOrario(); //restituisce il log da stampare all'inizio dell'esecuzione di ogni comando
        std::string resetOrario(); //esegue comando "reset time"
        void accendiDispositivo(std::string n); //esegue comando "set ${DEVICENAME} on"
        void spegniDispositivo(std::string n); //esegue comando "set ${DEVICENAME} off"
        std::string impostaTimer(std::string n, int s); //esegue comando "set ${DEVICENAME} ${START}"
        std::string impostaTimer(std::string n, int s, int e); //(solo per dispositivi manuali) esegue comando "set ${DEVICENAME} ${START} ${STOP}"
        std::string rmTimer(std::string n); //esegue comando "rm ${DEVICENAME}"
        std::string consumoDispositivo(std::string n); //esegue comando "show ${DEVICENAME}"
        void allConsumi(); //esegue comando "show"
        void setOrario(int x); //esegue comando "set time ${TIME}"
        std::string resetTimers(); //esegue comando "reset timers"
        void resetAll(); //esegue comando "reset all"

};

std::string intToOrario(int x); //trasforma il numero di minuti passati dalle 00:00 in formato hh:mm

#endif
