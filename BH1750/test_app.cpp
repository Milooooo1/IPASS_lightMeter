#include "hwlib.hpp"
#include "BH1750.hpp"
#include "BH1750_Average.hpp"

//  This is a test application for the BH1750 library
//  Wave your hand over the sensor for the best visualization
//


int main(void){
    
    auto sensor = BH1750();
    unsigned int x = 0;
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
        switch (x)
        {
        case 4:
            hwlib::cout <<"######################################################## \n" 
                        <<"Sensor powered down should return latest measured value. \n"
                        <<"######################################################## \n";
            sensor.PowerDown();
            break;
        case 8:
            hwlib::cout<<"############################################################ \n" 
                        <<"Sensor powered back up should return new measuredes values. \n"
                        <<"########################################################### \n";
            sensor.PowerOn();
            sensor.Configure(sensor.CONTINUOUSLY_H_RES);
            break;

        }
        hwlib::wait_ms(400);
        x++;
    }
}