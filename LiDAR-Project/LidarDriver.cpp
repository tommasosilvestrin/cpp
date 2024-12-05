#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>
#include <cmath>

#include "LidarDriver.h"

// CONSTRUCTOR
LidarDriver::LidarDriver(double resolution)
    : angular_resolution_{resolution}, buffer_(BUFFER_DIM, std::vector<double>(static_cast<int>(RANGE / angular_resolution_ + 1)))
{
    if (angular_resolution_ < 0.1 || angular_resolution_ > 1.0)
        throw std::invalid_argument("angular resolution must be [0.1°, 1.0°]");
    // std::cout << "angular resolution set to: " << angular_resolution_ << "°" << std::endl;
}

// MEMBER FUNCTIONS
void LidarDriver::new_scan(std::vector<double> scan)
{
    // controllo il numero di valori negativi nella scansione
    int count_errors = 0;
    for (int i = 0; i < scan.size(); i++)
    {
        if (scan[i] < 0.0)
        {
            scan[i] = 0.0; // imposto a 0 il valore negativo
            count_errors++;
        }
    }
    
    // se gli errori di rilevamento sono troppi invalido la scansione
    if (count_errors > (RANGE / angular_resolution_) / 4)
        throw std::invalid_argument("too many incorrect values, invalid scan");

    // altrimenti gestisco le posizioni e ...
    if (last_position_ != -1 && update_position(last_position_) == oldest_position_)
        oldest_position_ = update_position(oldest_position_);
    last_position_ = update_position(last_position_);

    // ... controllo il numero di valore contenuti nella scansione
    if (scan.size() < (RANGE / angular_resolution_) + 1)
    {
        int i = 0;
        while (i < scan.size())
        {
            buffer_[last_position_][i] = scan[i];
            i++;
        }
        while (i < (RANGE / angular_resolution_) + 1)
        {
            buffer_[last_position_][i] = 0;
            i++;
        }
    }
    else if (scan.size() > (RANGE / angular_resolution_) + 1)
        for (int i = 0; i < (RANGE / angular_resolution_) + 1; i++)
            buffer_[last_position_][i] = scan[i];
    else
        buffer_[last_position_] = scan;
}

std::vector<double> LidarDriver::get_scan(void)
{
    if (last_position_ == -1)
        throw std::invalid_argument("the buffer is empty");

    std::vector<double> oldest_scan = buffer_[oldest_position_];
    buffer_[oldest_position_].clear();
    oldest_position_ = update_position(oldest_position_);
    return oldest_scan;
}

void LidarDriver::clear_buffer(void)
{
    for (int i = 0; i < BUFFER_DIM; i++)
        buffer_[i].clear();

    // reset variabili per gestione posizione
    last_position_ = -1;
    oldest_position_ = 0;
}

double LidarDriver::get_distance(double angle)
{
    if (angle < 0 || angle > 180)
        throw std::invalid_argument("angle must be [0°, 180°]");

    return buffer_[last_position_][round_angle(angle) * (1 / angular_resolution_)];
}

// PRIVATE FUNCTIONS
int LidarDriver::count_numbers(void) {
    return static_cast<int>(std::log10(std::abs((RANGE / angular_resolution_) + 1))) + 1;
}

int LidarDriver::update_position(int position)
{
    (position == (BUFFER_DIM - 1)) ? position = 0 : position++;
    return position;
}

double LidarDriver::round_angle(double angle)
{
    double closest_angle = 0.0;
    double min_diff = 1.0;

    for (double i = 0; i <= RANGE; i += angular_resolution_)
    {
        double diff = std::abs(i - angle);
        if (diff < min_diff)
        {
            min_diff = diff;
            closest_angle = i;
        }
    }
    return closest_angle;
}

// HELPER FUNCTIONS
std::ostream &operator<<(std::ostream &os, LidarDriver obj)
{
    try
    {
        std::vector<double> scan = obj.buffer(obj.last_position());
        for (int i = 0; i < scan.size(); ++i)
        {
            os << "[" << std::setw(obj.count_numbers()) << i << "] = "
                << std::fixed << std::setprecision(2)
                << std::setw(4) << scan[i]
                << std::endl;
        }
        return os;
    } 
    catch(std::bad_alloc e)
    {
        return os << "the buffer is empty" << std::endl;
    }
}