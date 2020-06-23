#include "hwlib.hpp"
#include "lightmeter.hpp"
#include <string>

int ExposureValue = 0;
int Lux = 0;
int ISO = 0;
int shutterSpeed = 0;
int Apperature = 0;                              //Supposed to be a float but gives problems

// auto sw1  = hwlib::target::pin_in( hwlib::target::pins::d2 );
// auto sw2  = hwlib::target::pin_in( hwlib::target::pins::d3 );
// auto sw3  = hwlib::target::pin_in( hwlib::target::pins::d4 );
// auto sw4  = hwlib::target::pin_in( hwlib::target::pins::d5 );

void showSettingsMenu(hwlib::terminal_from & display, hwlib::terminal_from & headerDisplay, lightmeter & meter){
    int realShutterspeed = 1 / shutterSpeed;
    char s;
    int ISOcounter, APcounter, SScounter = 0;
    headerDisplay << "\f" << hwlib::flush;
    headerDisplay << " Settings menu" << hwlib::flush;
    for(;;){
        display << "\f" << hwlib::flush;
        display << "\n"
            << "ISO: " << ISO           << "\n"
            << "t: 1/" << shutterSpeed  << "\n"
            << "f/" << Apperature       << hwlib::flush; 
        hwlib::cin >> s;
        if(s == 'e'){
            return;
        } else if (s == 'i'){ //ISO
            switch (ISOcounter) {
                case 0: ISO = 0; break;
                case 1: ISO = 100; break;
                case 2: ISO = 125; break;
                case 3: ISO = 160; break;
                case 4: ISO = 200; break;
                case 5: ISO = 250; break;
                case 6: ISO = 320; break;
                case 7: ISO = 400; break;
                case 8: ISO = 500; break;
                case 9: ISO = 640; break;
                case 10: ISO = 800; break;
                case 11: ISO = 1000; break;
                case 12: ISO = 1250; break;
                case 13: ISO = 1600; break;
                case 14: ISO = 2000; break;
                case 15: ISO = 2500; break;
                case 16: ISO = 3200; break;
                case 17: ISO = 4000; break;
                case 18: ISO = 5000; break;
                case 19: ISO = 6400; break;
                default: ISOcounter = 0; break;
            }
            ISOcounter++;
            continue;
        } else if (s == 'a'){ //Aperature
            switch (APcounter) {
                case 0: Apperature = 0; break;
                case 1: Apperature = 1.1; break;
                case 2: Apperature = 1.2; break;
                case 3: Apperature = 1.4; break;
                case 4: Apperature = 1.8; break;
                case 5: Apperature = 2.0; break;
                case 6: Apperature = 2.8; break;
                case 7: Apperature = 4.0; break;
                case 8: Apperature = 5.6; break;
                case 9: Apperature = 6.3; break;
                case 10: Apperature = 8.0; break;
                case 11: Apperature = 11; break;
                case 12: Apperature = 16; break;
                case 13: Apperature = 22; break;
                default: APcounter = 0; break;
            }
            APcounter++;
            continue;
        } else if (s == 's'){ //Shutterspeed
            switch (SScounter) {
                case 0: shutterSpeed = 0; break;
                case 1: shutterSpeed = 8000; break;
                case 2: shutterSpeed = 6400; break;
                case 3: shutterSpeed = 5000; break;
                case 4: shutterSpeed = 4000; break;
                case 5: shutterSpeed = 3200; break;
                case 6: shutterSpeed = 2500; break;
                case 7: shutterSpeed = 2000; break;
                case 8: shutterSpeed = 1600; break;
                case 9: shutterSpeed = 1250; break;
                case 10: shutterSpeed = 1000; break;
                case 11: shutterSpeed = 800; break;
                case 12: shutterSpeed = 640; break;
                case 13: shutterSpeed = 500; break;
                case 14: shutterSpeed = 400; break;
                case 15: shutterSpeed = 320; break;
                case 16: shutterSpeed = 250; break;
                case 17: shutterSpeed = 200; break;
                case 18: shutterSpeed = 160; break;
                case 19: shutterSpeed = 125; break;
                case 20: shutterSpeed = 100; break;
                case 21: shutterSpeed = 80; break;
                case 22: shutterSpeed = 60; break;
                case 23: shutterSpeed = 50; break;
                case 24: shutterSpeed = 40; break;
                case 25: shutterSpeed = 30; break;
                case 26: shutterSpeed = 25; break;
                case 27: shutterSpeed = 20; break;
                case 28: shutterSpeed = 15; break;
                case 29: shutterSpeed = 13; break;
                case 30: shutterSpeed = 10; break;
                case 31: shutterSpeed = 8; break;
                case 32: shutterSpeed = 6; break;
                case 33: shutterSpeed = 5; break;
                case 34: shutterSpeed = 4; break;
                default: SScounter = 0; break;
        }
            SScounter++;
            continue;
        } else if (s == 'c'){
            if(ISO == 0){
                ISO = meter.getISO((float)Apperature, realShutterspeed);
                display << "\f" << hwlib::flush;
                display << "ISO: " << ISO << hwlib::flush;
                hwlib::cout << "ISO: " << ISO << "\n";
                hwlib::cin >> s;
                if(s == 'e'){
                    continue;
                }
            } else if(shutterSpeed == 0){
                shutterSpeed = meter.getShutterspeed((float)Apperature, ISO);
                display << "\f" << hwlib::flush;
                display << "Shutterspeed: " << shutterSpeed << hwlib::flush;
                hwlib::cout << "Shutterspeed: " << realShutterspeed << "\n";
                hwlib::cin >> s;
                if(s == 'e'){
                    continue;
                }
            } else if(Apperature == 0){
                Apperature = meter.getApperature(ISO, realShutterspeed);
                display << "\f" << hwlib::flush;
                display << "Apperature: f/" << Apperature << hwlib::flush;
                hwlib::cout << "Apperature: " << Apperature << "\n";
                hwlib::cin >> s;
                if(s == 'e'){
                    continue;
                }
            } else {
                display << "\f" << hwlib::flush;
                display << "\nInvalid entry"<< hwlib::flush;
                hwlib::cin >> s;
                if(s == 'e'){
                    continue;
                }
            }
        }
    }
}

void LuxEvMeter(hwlib::terminal_from & display, hwlib::terminal_from & headerDisplay,
                BH1750 & sensor, lightmeter & meter){
    char s;
    display << "\f" << hwlib::flush;
    headerDisplay << "\f" << hwlib::flush;
    headerDisplay << " Lux & EV meter" << hwlib::flush;
    for(;;){
        display << "\f" << hwlib::flush;
        Lux = sensor.GetLightIntensity();
        ExposureValue = meter.getEv();
        display << "\nEV: " << ExposureValue << "\n"
                << "Lux: " << Lux << hwlib::flush;
        hwlib::cin >> s;
        if(s == 'e'){
            return;
        } else if (s == 'c'){
            continue;
        }
    } 
}

int main(void){

    BH1750 sensor = BH1750();
    lightmeter meter = lightmeter(sensor);

    auto font8x8 = hwlib::font_default_8x8();

    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );

    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    auto header = hwlib::part(
        oled,
        hwlib::xy( 0, 0 ),
        hwlib::xy( 128, 9 )
    );
    auto headerDisplay = hwlib::terminal_from( header, font8x8 );
    auto mainscreen = hwlib::part(
        oled,
        hwlib::xy( 0, 9 ),
        hwlib::xy( 128, 64)
    );
    auto display = hwlib::terminal_from( mainscreen, font8x8 );

    meter.configMeasurement(sensor.CONTINUOUSLY_H_RES);
    sensor.Configure(sensor.CONTINUOUSLY_H_RES);
    
    display << "\f" << hwlib::flush;
    headerDisplay << "\f" << hwlib::flush;

    char s;
    for(;;){
        headerDisplay << "\f" << hwlib::flush;
        display << "\f" << hwlib::flush;
        headerDisplay << "  Enter input" << hwlib::flush;
        display << "\n s: Settings"
            << "\n m: Live Meter" 
            << hwlib::flush;
        hwlib::cin >> s;
        if(s == 's'){
            showSettingsMenu(display, headerDisplay, meter);
        } else if(s == 'm'){
            LuxEvMeter(display, headerDisplay, sensor, meter);
        }
    }
}