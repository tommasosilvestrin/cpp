#include "../include/Casa.h"
#include <iostream>
#include <exception>


//inizializzazione del vettore vetDispositivi: un vettore di shared_pointer a Dispositivo, nella pratica ogni elemento del vettore punta a un oggetto Manuale o CP
Casa::Casa(double p)
    : potenzaMax{p}, potenzaInUso{0}, orario{0} {
        std::vector<std::string> nomi{"Impianto fotovoltaico", "Lavatrice", "Lavastoviglie", "Pompa di calore + termostato", "Tapparelle elettriche", "scaldabagno", "Frigorifero", "Forno a microonde", "Asciugatrice", "Televisore"};
        std::vector<double> potenze{1.5, -2, -1.5, -2, -0.3, -1, -0.4, -0.8, -0.5, -0.2};
        std::vector<int> durate{-1, 110, 195, -1, 1, -1, -1, 2, 60, 60};
        for(int i=0; i<nomi.size(); i++){
            if(durate[i]==-1){
                vetDispositivi.push_back(std::make_shared<Manuale>(nomi[i], i, potenze[i]));
            }
            else{
                vetDispositivi.push_back(std::make_shared<CicloPrefissato>(nomi[i], i, potenze[i], durate[i]));
            }
        }
    }

std::string const Casa::getOrario(){ 
    std::string ora = intToOrario(orario); //restituisce una stringa del tipo "15:30"
    std::string s = "[" + ora + "] L'orario attuale è " + ora;
    return s;
}

void Casa::accendiDispositivo(std::string n){
    for(int i=0; i<vetDispositivi.size(); i++){ //questo ciclo scorre tutti i dispositivi
        if((*vetDispositivi[i]).getNome() == n && !(*vetDispositivi[i]).getStato()){ //se il dispositivo è spento...
            (*vetDispositivi[i]).accensione(); //lo accendo (se il dispositivo è CP, verrà chiamata la funzione accensione sovrascritta in CP)
            dispAccesi.push_back(vetDispositivi[i]); //aggiungo il dispositivo alla lista di dispositivi accesi
            std::string s = "[" + intToOrario(orario) + "] Il dispositivo " + (*vetDispositivi[i]).getNome() + "si è acceso"; //log
            std::cout << s << std::endl;
            if((*vetDispositivi[i]).getPotenza() > 0){ //se il dispositivo produce energia (ad es. l'impianto fotovoltaico)...
                potenzaMax += (*vetDispositivi[i]).getPotenza(); //incremento il valore della potenza massima disponibile per il sistema
            }
            else{ //altrimenti (se il dispositivo consuma energia)...
                potenzaInUso += -((*vetDispositivi[i]).getPotenza()); //incremento il valore della potenza utilizzata dal sistema
            }
            if(potenzaInUso > potenzaMax){ //se ho superato la potenza massima accendendo un dispositivo, allora lo spengo, tornando così al di sotto del limite
                spegniDispositivo(n);
            }
        }
    }
    throw std::invalid_argument("Nessun dispositivo con il nome fornito"); //eccezione di elemento non trovato
}

void Casa::spegniDispositivo(std::string n){
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getNome() == n && (*vetDispositivi[i]).getStato()){ //se il dispositivo è acceso...
            (*vetDispositivi[i]).spegnimento(); //lo spengo
            std::string s = "[" + intToOrario(orario) + "] Il dispositivo " + (*vetDispositivi[i]).getNome() + "si è spento"; //log
            std::cout << s << std::endl;
            for(int j=0; j<dispAccesi.size(); j++){ //devo rimuovere il dispositivo appena spento dalla lista dei dispositivi accesi
                if((*vetDispositivi[i]).getNome() == n){
                    //devo mantenere l'ordine di inserimento, quindi sposto di una posizione verso sinistra la porzione del vettore a destra dell'elemento da rimuovere
                    int k = j;
                    while(k < dispAccesi.size()-1){ 
                        dispAccesi[k] = dispAccesi[k++];
                    }
                    dispAccesi.pop_back();
                }
            }
            if((*vetDispositivi[i]).getPotenza() > 0){ //se il dispositivo produce energia (ad es. l'impianto fotovoltaico)...
                potenzaMax -= (*vetDispositivi[i]).getPotenza(); //decremento il valore della potenza massima disponibile per il sistema
                //la potenzaMax è dimnuita e quindi potrei aver sforato con la potenzaInUso. Se così è...
                int l = dispAccesi.size()-1; //spengo i dispositivi partendo da quello acceso per ultimo...
                while(potenzaInUso > potenzaMax){ //fino a quando non ho una potenza utilizzata minore o uguale di quella massima consentita
                    if((*dispAccesi[l]).getPotenza() < 0){ //ATTENZIONE!!! spengo solo i dispositivi che consumano energia, non quelli che la producono
                        spegniDispositivo((*dispAccesi[l]).getNome());
                    }
                    l--;
                }
            }
            else{ //altrimenti (ovvero se il dispositivo consuma energia)...
                potenzaInUso -= -((*vetDispositivi[i]).getPotenza()); //decremento il valore della potenza utilizzata dal sistema
            }
            Manuale* m = dynamic_cast<Manuale*>(vetDispositivi[i].get()); //Nel seguente if si entra solo se il dispositivo è di tipo manuale,
            if(m && (*m).getTimerAccensione()<=orario && (*m).getTimerSpegnimento()>orario){ //se vi è un timer di accensione nel passato e uno di spegnimento nel futuro, allora quest'ultimo viene rimosso
                (*m).setTimerSpegnimento(-1);
            }
        }
    }
    throw std::invalid_argument("Nessun dispositivo con il nome fornito"); //eccezione di elemento non trovato
}

std::string Casa::impostaTimer(std::string n, int s){
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getNome() == n){
            (*vetDispositivi[i]).setTimerAccensione(s); //è possibile farlo sia nei CP che nei manuali
            std::string out = "[" + intToOrario(orario) + "] Impostato un timer per il dispositivo " + (*vetDispositivi[i]).getNome() + " dalle " + intToOrario(s);
            return out;
        }
    }
    throw std::invalid_argument("Nessun dispositivo con il nome fornito"); //eccezione di elemento non trovato
}


std::string Casa::impostaTimer(std::string n, int s, int e){
    if(e<=s){ //non si possono settare timer che prevedono uno spegnimento precedente o uguale all'accensione perchè visto che il log deve essere (da consegna) "dalle .. alle ..", esso perderebbe di senso
        throw std::invalid_argument("L'orario di spegnimento deve essere successivo a quello di accensione"); //eccezione
    }
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getNome() == n){
            Manuale* m = dynamic_cast<Manuale*>(vetDispositivi[i].get());
            if(m){ //questo comando è possibile solo con i dispositivi manuali, come da consegna
                //sovrascrivo entrambi i timer
                (*m).setTimerAccensione(s);
                (*m).setTimerSpegnimento(e);
                std::string out = "[" + intToOrario(orario) + "] Impostato un timer per il dispositivo " + (*vetDispositivi[i]).getNome() + " dalle " + intToOrario(s) + " alle " + intToOrario(e);
                return out; //log
            }
            else{
                throw std::invalid_argument("Questo comando può essere usato solo con i dispositivi manuali"); //eccezione, si sta provando a settare un timer di spegnimento per un dispositivo CP
            }
        }
    }
    throw std::invalid_argument("Nessun dispositivo con il nome fornito"); //eccezione di elemento non trovato
}

std::string Casa::rmTimer(std::string n){
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getNome() == n && (*vetDispositivi[i]).getTimerAccensione()>orario){ //se vi è un timer di accensione nel futuro...
            (*vetDispositivi[i]).setTimerAccensione(-1); //lo rimuovo
            Manuale* m = dynamic_cast<Manuale*>(vetDispositivi[i].get());
            if(m){ //se il dispositivo è manuale, devo rimuovere anche il timer di spegnimento 
                (*m).setTimerSpegnimento(-1);
            }
            std::string out = "[" + intToOrario(orario) + "] Rimosso il timer dal dispositivo " + (*vetDispositivi[i]).getNome(); //log
            return out;
        }
    }
    throw std::invalid_argument("Nessun dispositivo con il nome fornito"); //eccezione di elemento non trovato
}

std::string Casa::consumoDispositivo(std::string n){
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getNome() == n){
            std::string out = "[" + intToOrario(orario) + "] Il dispositivo " + (*vetDispositivi[i]).getNome() + "ha attualmente ";
            //il membro "energia" del dispositivo è sempre positivo, però questa energia è prodotta se il membro potenza del dispositivo nella tabella è positivo, altrimenti è energia consumata
            if((*vetDispositivi[i]).getPotenza()>0){ 
                out += "prodotto ";
            }
            else{
                out += "consumato ";
            }
            out += std::to_string((*vetDispositivi[i]).getEnergia()) + " kWh"; //log
            return out; 
        }
    }
    throw std::invalid_argument("Nessun dispositivo con il nome fornito"); //eccezione di elemento non trovato
}

void Casa::allConsumi(){
    double produzione = 0; //somma dell'energia prodotta da ogni dispositivo della casa
    double consumo = 0; //somma dell'energia consumata da ogni dispositivo della casa
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getPotenza()>0){ //se la varibaile potenza è positiva, l'energia è prodotta
            produzione += (*vetDispositivi[i]).getEnergia(); 
        }
        else{ //se la variabile potenza è negativa, l'energia è consumata
            consumo += (*vetDispositivi[i]).getEnergia();
        }
    }
    std::cout << "[" << intToOrario(orario) << "]" << "Attualmente il sistema ha prodotto " << produzione << " kWh e consumato " << consumo << " kWh. Nello specifico:" << std::endl;
    //A questo punto si potrebbe pensare di chiamare la funzione consumoDispositivo su ogni dispositivo, ma ciò genererebbe un log diverso da quello previsto nella consegna.
    //Infatti quando si usa il comando "show ${DEVICENAME}" vi è la parola attualmente nel log, parola che non deve essere presente nel log del comando "show"
    for(int i=0; i<vetDispositivi.size(); i++){
        if((*vetDispositivi[i]).getPotenza()>0){
            std::cout << " - Il dispositivo " << (*vetDispositivi[i]).getNome() << " ha prodotto " << (*vetDispositivi[i]).getEnergia() << " kWh" << std::endl;
        }
        else{
            std::cout << " - Il dispositivo " << (*vetDispositivi[i]).getNome() << " ha consumato " << (*vetDispositivi[i]).getEnergia() << " kWh" << std::endl;
        }
    }
}

void Casa::setOrario(int x){
    if(x <= orario){ //se imposto un orario nel passato...
        throw std::invalid_argument("L'orario fornito non è valido"); // lancio eccezione
    }
    while(orario < x){
        orario++;
        for(int i=0; i<vetDispositivi.size(); i++){
            if((*vetDispositivi[i]).getStato()){ //se il dispositivo è acceso...
                (*vetDispositivi[i]).increaseEnergia(); //nell'ultimo minuto il dispositivo ha prodotto/consumato energia e quindi vado ad aggiornare il valore
                Manuale* m = dynamic_cast<Manuale*>(vetDispositivi[i].get());
                if(m){ //se il dispositivo è manuale...
                    if((*m).getTimerSpegnimento()==orario){ //se è stato programmato lo spengimento per quest'ora...
                        spegniDispositivo((*m).getNome()); //spengo il dispositivo
                    }
                }
                else{ //se il dispositivo non è manuale, allora è a ciclo prefissato
                    CicloPrefissato* cp = dynamic_cast<CicloPrefissato*>(vetDispositivi[i].get());
                    (*cp).decreaseMinRimanenti(); //è passato un minuto per cui devo diminuire i minuti rimanenti alla fine del ciclo corrente
                    if((*cp).getMinRimanenti() == 0){ //se non vi sono più minuti rimasti al termine del ciclo...
                        spegniDispositivo((*m).getNome()); //spengo il dispositivo
                    }
                }
            }
            else{ //se il dispositivo è spento...
                if((*vetDispositivi[i]).getTimerAccensione() == orario){ //se vi è un'accensione programmata per quest'ora...
                    accendiDispositivo((*vetDispositivi[i]).getNome()); //accendo il dispositivo
                }
            }
        }
        std::cout << getOrario() << std::endl;
    }
}

std::string Casa::resetOrario(){
    orario = 0;
    for(int i=0; i<vetDispositivi.size(); i++){ //riporto i dispositivi al loro stato iniziale(spenti)
        (*vetDispositivi[i]).spegnimento();
    }
    return getOrario(); //log aggiunto da noi
}

std::string Casa::resetTimers(){
    for(int i=0; i<vetDispositivi.size(); i++){ //rimozione dei timer per tutti i dispositivi
        (*vetDispositivi[i]).setTimerAccensione(-1);
        Manuale* m = dynamic_cast<Manuale*>(vetDispositivi[i].get());
        if(m){ //se il dispositivo è manuale, devo rimuovere anche il timer di spegnimento 
            (*m).setTimerSpegnimento(-1);
        }
    }
    return "[" + intToOrario(orario) + "] I timer di tutti i dispositivi sono stati rimossi"; //log aggiunto da noi
}

void Casa::resetAll(){
    //vengono stampati i log delle 2 funzioni precedenti, in quanto il compito di questa funzione è la combinazione di quelli delle funzioni resetOrario e resetTimers
    std::cout << resetOrario() << std::endl;
    std::cout << resetTimers() << std::endl;
}

std::string intToOrario(int x){ 
    int minuti = x%60;
    int ore = x/60;
    std::string s = "";
    if(ore<10){ //se non sono anora le 10:00, non devo stampare, ad es., 9:30, ma 09:30
        s += "0";
    }
    s = s + std::to_string(ore) + ":";
    if(minuti<10){ //vale lo stesso discorso delle ore: devo stampare 09:05 non 09:5
        s+="0";
    }
    s = s + std::to_string(minuti);
    return s;
}
