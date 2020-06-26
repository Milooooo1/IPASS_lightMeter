#include "hwlib.hpp"
#include "lightmeter.hpp"

bool displayed = false;
int ISO = 0;
int realShutterspeed = 0;                             
float Apperature = 0;                              //Supposed to be a float but gives problems

void reverse(char* str, int len){
    int i = 0, j = len - 1, temp;
    while(i < j){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int intToString(int x, char str[], int d){
    int i = 0;
    while(x){
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while(i < d){
        str[i++] = '0';
    }
    reverse(str, i);
    str[i] = '\0';
    return i;
}

void floatToArray(float n, char* res, int afterpoint){
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = intToString(ipart, res, 0);
    if(afterpoint != 0 ){
        res[i] = '.';
        fpart = fpart * pow(10, afterpoint);
        intToString((int)fpart, res + i + 1, afterpoint);
    }

}

void clearScreen(hwlib::terminal_from & display, hwlib::terminal_from & header){
    display << "\f" << hwlib::flush;
    header << "\f" << hwlib::flush;
}

void showSettingsMenu(hwlib::terminal_from & display, hwlib::terminal_from & headerDisplay, lightmeter & meter,
                      hwlib::target::pin_in & sw1, hwlib::target::pin_in & sw2, hwlib::target::pin_in & sw3,
                      hwlib::target::pin_in & sw4){

    int ISOcounter, APcounter, SScounter = 0;
    clearScreen(display, headerDisplay);
    headerDisplay << " Settings menu" << hwlib::flush;
    displayed = false;
    bool calculated = false;
    char ap[10];

    for(;;){

        floatToArray(Apperature, ap, 1);
        if(!displayed){
            display << "\f" << hwlib::flush;
            display << "\n"
                << "ISO: "  << ISO      << "\n"
                << "t: 1/"  << realShutterspeed << "\n"
                << "f/"     << ap << hwlib::flush; 
        }
        displayed = true;

        sw1.refresh(); sw2.refresh(); sw3.refresh(); sw4.refresh();
        hwlib::wait_ms(10);
        if(sw1.read() == 0 && calculated){
            displayed = false;
            return;
        } else if (sw2.read() == 0 && sw1.read() == 1 && sw3.read() == 1 && sw4.read() == 1){ //ISO
            switch (ISOcounter) {
                case 0:  ISO = 0;    break;
                case 1:  ISO = 100;  break;
                case 2:  ISO = 125;  break;
                case 3:  ISO = 160;  break;
                case 4:  ISO = 200;  break;
                case 5:  ISO = 250;  break;
                case 6:  ISO = 320;  break;
                case 7:  ISO = 400;  break;
                case 8:  ISO = 500;  break;
                case 9:  ISO = 640;  break;
                case 10: ISO = 800;  break;
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
            displayed = false;
            continue;
        } else if (sw4.read() == 0 && sw2.read() == 1 && sw1.read() == 1 && sw3.read() == 1){ //Aperature
            switch (APcounter) {
                case 0:  Apperature = 0;   break;
                case 1:  Apperature = 1.1; break;
                case 2:  Apperature = 1.2; break;
                case 3:  Apperature = 1.4; break;
                case 4:  Apperature = 1.8; break;
                case 5:  Apperature = 2.0; break;
                case 6:  Apperature = 2.8; break;
                case 7:  Apperature = 4.0; break;
                case 8:  Apperature = 5.6; break;
                case 9:  Apperature = 6.3; break;
                case 10: Apperature = 8.0; break;
                case 11: Apperature = 11;  break;
                case 12: Apperature = 16;  break;
                case 13: Apperature = 22;  break;
                default: APcounter  = 0;   break;
            }
            APcounter++;
            displayed = false;
            continue;
        } else if (sw3.read() == 0 && sw2.read() == 1 && sw4.read() == 1 && sw1.read() == 1){ //Shutterspeed
            switch (SScounter) {
                case 0:  realShutterspeed = 0;    break;
                case 1:  realShutterspeed = 8000; break;
                case 2:  realShutterspeed = 6400; break;
                case 3:  realShutterspeed = 5000; break;
                case 4:  realShutterspeed = 4000; break;
                case 5:  realShutterspeed = 3200; break;
                case 6:  realShutterspeed = 2500; break;
                case 7:  realShutterspeed = 2000; break;
                case 8:  realShutterspeed = 1600; break;
                case 9:  realShutterspeed = 1250; break;
                case 10: realShutterspeed = 1000; break;
                case 11: realShutterspeed = 800;  break;
                case 12: realShutterspeed = 640;  break;
                case 13: realShutterspeed = 500;  break;
                case 14: realShutterspeed = 400;  break;
                case 15: realShutterspeed = 320;  break;
                case 16: realShutterspeed = 250;  break;
                case 17: realShutterspeed = 200;  break;
                case 18: realShutterspeed = 160;  break;
                case 19: realShutterspeed = 125;  break;
                case 20: realShutterspeed = 100;  break;
                case 21: realShutterspeed = 80;   break;
                case 22: realShutterspeed = 60;   break;
                case 23: realShutterspeed = 50;   break;
                case 24: realShutterspeed = 40;   break;
                case 25: realShutterspeed = 30;   break;
                case 26: realShutterspeed = 25;   break;
                case 27: realShutterspeed = 20;   break;
                case 28: realShutterspeed = 15;   break;
                case 29: realShutterspeed = 13;   break;
                case 30: realShutterspeed = 10;   break;
                case 31: realShutterspeed = 8;    break;
                case 32: realShutterspeed = 6;    break;
                case 33: realShutterspeed = 5;    break;
                case 34: realShutterspeed = 4;    break;
                default: SScounter        = 0;    break;
        }
            SScounter++;
            displayed = false;
            continue;
        } else if (sw1.read() == 0 && sw2.read() == 1 && sw3.read() == 1 && sw4.read() == 1){
            if(ISO == 0 && realShutterspeed != 0 && Apperature != 0){
                ISO = meter.getISO((float)Apperature, 1 / realShutterspeed);
                displayed = false;
                calculated = true;
            } else if(realShutterspeed == 0 && ISO != 0 && Apperature != 0){
                realShutterspeed = meter.getShutterspeed((float)Apperature, ISO);
                displayed = false;
                calculated = true;
            } else if(Apperature == 0 && realShutterspeed != 0 && ISO != 0){
                Apperature = meter.getApperature(ISO, 1 / realShutterspeed);
                displayed = false;
                calculated = true;
            } else {
                display << "\f" << hwlib::flush;
                display << "\n Invalid entry \n Values reset"<< hwlib::flush;
                realShutterspeed = 0;
                ISO = 0;
                Apperature = 0;
                displayed = false;
                calculated = false;
                hwlib::wait_ms(1000);
            }
        }
    }
}

void LuxEvMeter(hwlib::terminal_from & display, hwlib::terminal_from & headerDisplay,
                BH1750 & sensor, lightmeter & meter, hwlib::target::pin_in & back){

    clearScreen(display, headerDisplay);
    int ExposureValue = 0;
    int Lux = 0;
    headerDisplay << " Lux & EV meter" << hwlib::flush;
    for(;;){
        display << "\f" << hwlib::flush;
        Lux = sensor.GetLightIntensity();
        ExposureValue = meter.getEv();
        display << "\nEV: " << ExposureValue << "\n"
                << "Lux: " << Lux << hwlib::flush;
        
        displayed = false;
        back.refresh();
        if(back.read() == 0){
            return;
        } else {
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

    auto sw1  = hwlib::target::pin_in( hwlib::target::pins::d2 );
    auto sw2  = hwlib::target::pin_in( hwlib::target::pins::d3 );
    auto sw3  = hwlib::target::pin_in( hwlib::target::pins::d4 );
    auto sw4  = hwlib::target::pin_in( hwlib::target::pins::d5 );

    meter.configMeasurement(sensor.CONTINUOUSLY_H_RES);

    for(;;){
        if(!displayed){
            clearScreen(display, headerDisplay);
            headerDisplay   << "  Enter input" << hwlib::flush;
            display         << "\n s: Settings"
                            << "\n m: Live Meter" 
                            << hwlib::flush;
        } 
        displayed = true;
       

        sw1.refresh();
        sw2.refresh();
        if(sw1.read() == 0 && sw2.read() == 1){
            showSettingsMenu(display, headerDisplay, meter, sw1, sw2, sw3, sw4);
        } else if(sw2.read() == 0 && sw1.read() == 1){
            LuxEvMeter(display, headerDisplay, sensor, meter, sw2);
        }
    }
}