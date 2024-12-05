#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <cmath>

#include "LidarDriver.h"

std::vector<double> print_scan(double min, double max, int n); // genera array di numeri casuali in un intervallo specificato
std::ostream &operator<<(std::ostream &os, const std::vector<double> array); // overload dell'operator per facilitare la fase di testing

int main(int argc, char *argv[])
{
    // creazione di un oggetto LidarDriver
    LidarDriver default_lidar;
    LidarDriver second_lidar(0.5);
    LidarDriver third_lidar(0.7);

    // LANCIA STD::INVALID_ARGUMENT
    // LidarDriver error_lidar(1.1);

    // chiamata a get_scan() ma il buffer è vuoto, LANCIA STD::INVALID_ARGUMENT
    // std::vector<double> empty_buffer = default_lidar.get_scan();

    // stampa di un oggetto di tipo LidarDriver vuoto, LANCIA STD::BAD_ALLOC
    // std::cout << default_lidar << std::endl;

    // riempimento del buffer di default_lidar
    for (int i = 0; i < 10; i++)
        default_lidar.new_scan(print_scan(0.0, 2.0, (180.0 / default_lidar.angular_resolution()) + 1));

    // riempimento del buffer di second_lidar
    for (int i = 0; i < 10; i++)
        second_lidar.new_scan(print_scan(0.0, 1.0, (180.0 / second_lidar.angular_resolution()) + 1));

    // riempimento del buffer di third_lidar
    for (int i = 0; i < 10; i++)
        third_lidar.new_scan(print_scan(0.0, 1.5, (180.0 / third_lidar.angular_resolution()) + 1));

    // recupero della distanza ad un angolo errato, LANCIA STD::INVALID_ARGUMENT
    // std::cout << "\ndistanza a " << 181.0 << "°: " << default_lidar.get_distance(181.0) << "m" << std::endl;

    // ------------------------ BLOCCO TEST 1 ------------------------
    
    // recupero e stampa della scansione più vecchia di default_lidar
    std::vector<double> oldest_scan_1 = default_lidar.get_scan();
    std::cout << "scansione più vecchia di default_lidar: \n" << oldest_scan_1 << std::endl;

    // recupero e stampa della scansione più vecchia di second_lidar
    std::vector<double> oldest_scan_2 = second_lidar.get_scan();
    std::cout << "scansione più vecchia di second_lidar: \n" << oldest_scan_2 << std::endl;

    // recupero e stampa della scansione più vecchia di third_lidar
    std::vector<double> oldest_scan_3 = third_lidar.get_scan();
    std::cout << "scansione più vecchia di third_lidar: \n" << oldest_scan_3 << std::endl;

    // test funzione circolare del buffer
    default_lidar.new_scan(print_scan(0.0, 2.0, (180 / default_lidar.angular_resolution()) + 1));

    // recupero e stampa della scansione più vecchia post buffer-testing
    std::vector<double> oldest_scan_4 = default_lidar.get_scan();
    std::cout << "scansione più vecchia post buffer-testing: \n" << oldest_scan_4 << std::endl;

    // recupero della distanza ad un angolo specifico di default_lidar
    std::cout << "distanza a " << 10.3 << "° di default_lidar: " << default_lidar.get_distance(10.3) << " m" << std::endl;
    std::cout << "distanza a " << 10.6 << "° di default_lidar: " << default_lidar.get_distance(10.6) << " m" << std::endl;

    // recupero della distanza ad un angolo specifico di second_lidar
    std::cout << "distanza a " << 10.1 << "° di second_lidar: " << second_lidar.get_distance(10.1) << " m" << std::endl;
    std::cout << "distanza a " << 10.3 << "° di second_lidar: " << second_lidar.get_distance(10.3) << " m" << std::endl;
    
    // ------------------------ BLOCCO TEST 2 ------------------------
    
    /* // pulizia del buffer
    default_lidar.clear_buffer();
    std::cout << "buffer pulito" << std::endl;

    // inserimento di una nuova scansione dopo la pulizia del buffer
    std::vector<double> post_clear_scan = print_scan(0.0, 2.0, (180 / default_lidar.angular_resolution()) + 1);
    default_lidar.new_scan(post_clear_scan);
    std::cout << "\ninserimento di una nuova scansione dopo la pulizia del buffer: \n" << post_clear_scan << std::endl;
    
    // stampa di un oggetto di tipo LidarDriver
    std::cout << "stampa di un oggetto di tipo LidarDriver: \n" << default_lidar << std::endl;

    // prova di eliminazione dello scan inserito post buffer clear
    std::vector<double> oldest_post_clear_scan = default_lidar.get_scan();
    std::cout << "prova di eliminazione della scansione inserita post buffer-clear: \n" << oldest_post_clear_scan << std::endl; */

    // ------------------------ BLOCCO TEST 3 ------------------------
    
    /* // caso in cui scan contiene meno valori del dovuto
    std::vector<double> incomplete_scan = print_scan(0.0, 2.0, 134);
    std::cout << "vector sotto-dimensionato: \n" << incomplete_scan << std::endl;
    LidarDriver blocco3_lidar;
    blocco3_lidar.new_scan(incomplete_scan);
    std::cout << "caso con scansione sotto-dimensionata: \n" << blocco3_lidar << std::endl;

    // caso in cui scan contiene più valori del dovuto
    std::vector<double> too_much_value = print_scan(0.0, 2.0, 201);
    std::cout << "vector sovra-dimensionato: \n" << too_much_value << std::endl;
    LidarDriver blocco4_lidar;
    blocco4_lidar.new_scan(too_much_value);
    std::cout << "caso con scansione sovra-dimensionata: \n" << blocco4_lidar << std::endl; */

    // ------------------------ BLOCCO TEST 4 ------------------------
    
    /* // caso in cui scan contiene anche valori negativi
    default_lidar.clear_buffer();
    int count_negative_value = 0;
    std::vector<double> negative_value = print_scan(-0.5, 2.0, (180.0 / default_lidar.angular_resolution()) + 1);
    for (int i = 0; i < negative_value.size(); i++)
        if (negative_value[i] < 0)
            count_negative_value++;

    std::cout << "vector con " << count_negative_value << " valori negativi: \n" << negative_value << std::endl;
    default_lidar.new_scan(negative_value);
    std::cout << "caso con scansione con valori negativi: \n" << default_lidar << std::endl; */

    // ------------------------ FINE TEST ------------------------
    
    return 0;
}

// genera array di numeri casuali in un intervallo specificato
std::vector<double> print_scan(double min, double max, int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> intervallo(min, max);
    std::vector<double> random_numbers;

    for (int i = 0; i < n; ++i)
    {
        double n = intervallo(gen);
        n = std::round(n * 100.0) / 100.0;
        random_numbers.push_back(n);
    }
    return random_numbers;
}
 
// overload dell'operator per facilitare la fase di testing
std::ostream &operator<<(std::ostream &os, const std::vector<double> array)
{
    int size = array.size();
    int numbers = static_cast<int>(std::log10(std::abs(size))) + 1;
    for (int i = 0; i < array.size(); ++i)
    {
        os << "[" << std::setw(numbers) << i << "] = "
            << std::fixed << std::setprecision(2)
            << std::setw(4) << array[i]
            << std::endl;
    }
    return os;
}