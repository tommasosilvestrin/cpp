#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <iostream>
#include <vector>

class LidarDriver
{

public:
    // CONSTRUCTOR
    LidarDriver(double resolution = DEFAULT_RESOLUTION);

    // MEMBER FUNCTIONS
    /* La funzione new_scan che accetta uno std::vector<double> contenente una
    scansione e lo memorizza nel buffer (sovrascrivendo la scansione meno recente se il buffer è pieno).
    Questa funzione esegue anche il controllo di dimensione: se le letture sono in
    numero minore del previsto, completa i dati mancanti a 0; se sono in numero maggiore, li taglia */
    void new_scan(std::vector<double> scan);  

    /* La funzione get_scan che fornisce in output uno std::vector<double> contenente
    la scansione più vecchia del sensore e la rimuove dal buffer */                           
    std::vector<double> get_scan(void);   

    // La funzione clear_buffer che elimina (senza restituirle) tutte le scansioni salvate                
    void clear_buffer(void);

    /* La funzione get_distance che accetta un angolo espresso in gradi (double) e ritorna la
    lettura corrispondente a tale angolo nella scansione più recente acquisita dal sensore;
    tale scansione non è eliminata dal buffer, e se l’angolo richiesto non è disponibile
    ritorna la lettura relativa al valore di angolo più vicino */
    double get_distance(double angle);  

    // conta le cifre per la stampa delle scansioni
    int count_numbers(void);

    // GETTER FUNCTIONS, in-class implementation                    
    int last_position(void) const { return last_position_; }
    double angular_resolution(void) const { return angular_resolution_; }
    std::vector<double> buffer(int position) const { return buffer_[last_position_]; }

private:
    // CONSTANTS
    static constexpr int RANGE = 180;                 // range massimo del sensore
    static constexpr int BUFFER_DIM = 10;             // dimensione del buffer
    static constexpr double DEFAULT_RESOLUTION = 1.0; // risoluzione di default

    // VARIABLES
    int last_position_{-1};                   // posizione della scansione più recente
    int oldest_position_{0};                  // posizione della scansione più vecchia
    const double angular_resolution_;         // risoluzione angolare del sensore
    std::vector<std::vector<double>> buffer_; // buffer con vector bidimensionale

    // PRIVATE FUNCTIONS
    int update_position(int pos);     // restituisce correttamente la posizione successiva
    double round_angle(double angle); // trova l'angolo più vicino a quello passato come parametro in get_distance
};

// HELPER FUNCTIONS
/* L’overloading dell’operator<< che stampa a schermo l’ultima scansione salvata
(ma non la rimuove dal buffer) */
std::ostream &operator<<(std::ostream &os, const LidarDriver obj);

#endif // LIDARDRIVER_H