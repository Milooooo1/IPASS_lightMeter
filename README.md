![test](images/logo.png?raw=true "Logo")

This is a project for a class at the Hogeschool Utrecht, Technische-Informatica. 

This project includes a libary for the BH1750 lightintensity sensor and an test application showing that the libary works. 
This project also contains a lightmeter application which uses the [hwlib](https://github.com/wovo/hwlib "Hwlib by wovo") and my BH1750 library. It also includes a library for a camera lightmeter application. This library uses the BH1750 library and calculates the ISO, Aperature and Shutterspeed for a correctly exposed image. 
If you wish to build the full lightmeter application follow this schematic made with [Frizting](https://fritzing.org/download/ "Fritzing")
If the schematic is build correctly you can run the `test_app.cpp` as an example. 

![test](images/Fitzing_schematic.jpg?raw=true "Schematic")
[GY-302](https://github.com/nkolban/fritzing "GY-302 Model")
[SSD1306](https://forum.fritzing.org/t/oled-128x64-i2c-monochrome-display-ssd1306-created/1202 "SSD1306 Model")

Generate documentation with the following command:

`doxygen BH1750/Doxyfile`

And for the camera application:

`doxygen Lightmeter/Doxyfile`

--------------------------------------------------------------------------------------------
                          Copyright Milo Beliën 2020 - 2021.
              Distributed under the Boost Software License, Version 1.0. 
  (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
