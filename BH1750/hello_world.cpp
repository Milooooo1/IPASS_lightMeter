#include "hwlib.hpp"

int main( void ){
auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

auto bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

uint8_t address = 0x23; //0x5C or 0x23
uint8_t result[2];
uint16_t poort_value = 0;

enum MODES
{
	POWER_DOWN = 0x00,
	POWER_UP = 0x01,
	RESET = 0x07,
	CONTINUOUSLY_H_RES = 0x10,
	CONTINUOUSLY_H_RES2 = 0x11,
	CONTINUOUSLY_L_RES = 0x13,
	ONE_TIME_H_RES = 0x20,
	ONE_TIME_H_RES2	= 0x21,
	ONE_TIME_L_RES = 0x23
};

while(1){
	{
		auto writetr = ((hwlib::i2c_bus*)(&bus))->write(address);
   		writetr.write(ONE_TIME_H_RES);
	}
	{
		auto readtr = ((hwlib::i2c_bus*)(&bus))->read(address);
		readtr.read(result, 2);
	}
	poort_value = result[0] + result[1];
	//poort_value = poort_value / 1.2;
	hwlib::cout << "Light: " << poort_value << " Lux \n";
	hwlib::wait_ms(400);
}

}
