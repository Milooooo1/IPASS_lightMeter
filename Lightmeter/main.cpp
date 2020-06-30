#include "hwlib.hpp"
#include "lightmeter.hpp"

bool displayed = false;
int ISO = 0;
int realShutterspeed = 0;                             
float Aperture = 0;

// Reverste a char* str with given length int len
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

// int x is the integer you want to convert to char str[]
// the integer will be stored in char str[]
// int d are the amount of 0's added at the beginning
// if x is greater than d
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

// float n is the variable you want to convert to an array
// char* res is the array where the variable n will be stored in
// aterpoint is the amount of digits you want to save after the point
void floatToArray(float n, char* res, int afterpoint){
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = intToString(ipart, res, 0);
    if (afterpoint != 0 ){
        res[i] = '.';
        fpart = fpart * pow(10, afterpoint);
        intToString((int)fpart, res + i + 1, afterpoint);
    }

}

// This function clears the screen
void clearScreen(hwlib::terminal_from & display, hwlib::terminal_from & header){
    display << "\f" << hwlib::flush;
    header << "\f" << hwlib::flush;
}

// This function shows the settings menu, manipulates the 
// ISO, aperture and shutterspeed and calculates the missing value
void showSettingsMenu(hwlib::terminal_from & display, hwlib::terminal_from & headerDisplay, lightmeter & meter,
                      hwlib::target::pin_in & sw1, hwlib::target::pin_in & sw2, hwlib::target::pin_in & sw3,
                      hwlib::target::pin_in & sw4){


    int ISOArray[25]  = { 0, 100, 125, 160, 200, 250, 320, 400, 500, 640, 800, 1000, 1250,
                          1600, 2000, 2500, 3200, 4000, 5000, 6400 };                           //Possible photography ISO values
    float ApArray[15] = { 0, 1.1, 1.2, 1.4, 1.8, 2.0, 2.8, 4.0, 5.6, 6.3, 8.0, 11, 16, 22 };    //Possible photography aperature values
    int ssArray[35]   = { 0, 8000, 6400, 4000, 3200, 2500, 2000, 1600, 1250, 1000, 800, 
                          640, 500, 400, 320, 250, 200, 160, 125, 100, 80, 60, 50, 40, 
                          30, 25, 20, 15, 13, 10, 8, 6, 5, 4 };                                 //Possible photography shutterspeed values
    int ISOcounter = 0;
    int APcounter = 0;
    int SScounter = 0;
    clearScreen(display, headerDisplay);
    headerDisplay << " Settings menu" << hwlib::flush;
    displayed = false;
    bool calculated = false;
    char ap[10];

    for(;;){

        floatToArray(Aperture, ap, 1);
        if (!displayed){
            display << "\f" << hwlib::flush;
            display << "\n"
                << "ISO: "  << ISO      << "\n"
                << "t: 1/"  << realShutterspeed << "\n"
                << "f/"     << ap << hwlib::flush; 
        }
        displayed = true;
        sw1.refresh(); sw2.refresh(); sw3.refresh(); sw4.refresh();
        hwlib::wait_ms(10);

        // This if statement checks the input
        // Switch 1 calculates or returns to the main menu.
        // it only returns to the menu if it already 
        // calculated a value.
        // Switch 2 increases the ISO
        // Switch 3 increases the aperature
        // Switch 4 increases the shutterspeed
        if (sw1.read() == 0 && calculated){
            displayed = false;
            return;
        } else if (sw2.read() == 0 && sw1.read() == 1 && sw3.read() == 1 && sw4.read() == 1){           // Increase IOS
            ISO = ISOArray[ISOcounter];
            if (ISOcounter > 20){
                ISOcounter = 0;
            } else {
                ISOcounter++;
            }
            displayed = false;
            continue;
        } else if (sw4.read() == 0 && sw2.read() == 1 && sw1.read() == 1 && sw3.read() == 1){           // Increase aperture
            Aperture = ApArray[APcounter];
            if (APcounter > 15){
                APcounter = 0;
            } else {
                APcounter++;
            }
            displayed = false;
            continue;
        } else if (sw3.read() == 0 && sw2.read() == 1 && sw4.read() == 1 && sw1.read() == 1){           // Increase shutterspeed
            realShutterspeed = ssArray[SScounter];
            if (SScounter > 35){
                SScounter = 0;
            } else {
                SScounter++;
            }
            displayed = false;
            continue;
        } else if (sw1.read() == 0 && sw2.read() == 1 && sw3.read() == 1 && sw4.read() == 1){
            if (ISO == 0 && realShutterspeed != 0 && Aperture != 0){                                  // Calculate ISO
                ISO = meter.getISO((float)Aperture, 1 / realShutterspeed);
                displayed = false;
                calculated = true;
            } else if (realShutterspeed == 0 && ISO != 0 && Aperture != 0){                           // Calculate shutterspeed
                realShutterspeed = meter.getShutterspeed((float)Aperture, ISO);
                displayed = false;
                calculated = true;
            } else if (Aperture == 0 && realShutterspeed != 0 && ISO != 0){                           // Calculate aperture
                Aperture = meter.getAperture(ISO, 1 / realShutterspeed);
                displayed = false;
                calculated = true;
            } else {                                                                                    // Invalid entry
                display << "\f" << hwlib::flush;
                display << "\n Invalid entry \n Values reset"<< hwlib::flush;
                realShutterspeed = 0;
                ISO = 0;
                Aperture = 0;
                displayed = false;
                calculated = false;
                hwlib::wait_ms(1000);
            }
        }
    }
}

// This function shows the lux meter which is updated live
void LuxEvMeter(hwlib::terminal_from & display, hwlib::terminal_from & headerDisplay,
                BH1750 & sensor, lightmeter & meter, hwlib::target::pin_in & back){

    clearScreen(display, headerDisplay);
    int ExposureValue = 0;
    int Lux = 0;
    headerDisplay << " Lux & EV meter" << hwlib::flush;
    for(;;){
        display << "\f" << hwlib::flush;
        Lux = sensor.getLightIntensity();
        ExposureValue = meter.getEv();
        display << "\nEV: " << ExposureValue << "\n"
                << "Lux: " << Lux << hwlib::flush;
        
        displayed = false;
        back.refresh();
        if (back.read() == 0){
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
        if (!displayed){
            clearScreen(display, headerDisplay);
            headerDisplay   << "  Enter input" << hwlib::flush;
            display         << "\n s: Settings"
                            << "\n m: Live Meter" 
                            << hwlib::flush;
        } 
        displayed = true;
       

        sw1.refresh();
        sw2.refresh();
        if (sw1.read() == 0 && sw2.read() == 1){
            showSettingsMenu(display, headerDisplay, meter, sw1, sw2, sw3, sw4);
        } else if (sw2.read() == 0 && sw1.read() == 1){
            LuxEvMeter(display, headerDisplay, sensor, meter, sw2);
        }
    }
}