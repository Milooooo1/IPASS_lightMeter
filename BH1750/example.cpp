#include "hwlib.hpp"
#include "BH1750.hpp"
#include "BH1750_Average.hpp"

int main(void){
    
    auto sensor = BH1750();
    auto averageOfSensor = BH1750_Average(sensor);
    sensor.Configure(sensor.CONTINUOUSLY_H_RES);

    for(;;){
        sensor.ConfigureMTREG(sensor.MIN_MTREG);
        hwlib::cout << "MIN_Sensitivity: \t Light: " << sensor.GetLightIntensity() << " LUX \n";
        hwlib::wait_ms(80);
        sensor.ConfigureMTREG(sensor.DEFAULT_MTREG);
        hwlib::cout << "DEFAULT_Sensitivity: \t Light: " << sensor.GetLightIntensity() << " LUX \n";
        hwlib::wait_ms(80);
        sensor.ConfigureMTREG(sensor.MAX_MTREG);
        hwlib::cout << "MAX_Sensitivity: \t Light: " << sensor.GetLightIntensity() << " LUX \n";
        hwlib::wait_ms(80);
        sensor.ConfigureMTREG(sensor.DEFAULT_MTREG);
        hwlib::cout << "AVG_Sensitivity: \t Light: " << averageOfSensor.GetAverageLightIntensity() << " LUX \n";
        hwlib::wait_ms(80);
        hwlib::cout << "-----------------------------------------------\n";
        hwlib::wait_ms(400);
    }
}