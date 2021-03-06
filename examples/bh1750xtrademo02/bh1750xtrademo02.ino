/*

* bh1750xtra - BH1750FVI library for the Arduino exploring all range/sensitivity levels, from 0.11 lx to 100000 lx
* Author: Jose Gama 2015

* demo with default values, checking the I2C address and a few methods with info on the BH1750FVI object

*
* This library is free software; you can redistribute it
* and/or modify it under the terms of the GNU Lesser
* General Public License as published by the Free Software
* Foundation; either version 3 of the License, or (at
* your option) any later version.
*
* This library is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A
* PARTICULAR PURPOSE.  See the GNU Lesser General Public
* License for more details.
*
* You should have received a copy of the GNU Lesser
* General Public License along with this library; if not,
* write to the Free Software Foundation, Inc.,
* 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*
*/
#include <bh1750xtra.h>
#include <Wire.h>

bh1750xtra bhSensor; // instantiate object bh1750xtra

void setup() {
    uint8_t error;
    Serial.begin(9600); // initialize serial com at 9600 bauds
    Wire.begin(); // initialize I2C com
    Serial.println("bh1750xtra");
    
    // idea based on i2c_scanner by unknown author + Krodal +  louarnold + Nick Gammon
    // test to see if the bh1750 I2C Ids are available
    Wire.beginTransmission(35);
    error = Wire.endTransmission();
    if (error == 0) Serial.println("I2C device found at address 0x23"); else Serial.println("I2C device NOT found at address 0x23");
        Wire.beginTransmission(92);
    error = Wire.endTransmission();
    if (error == 0) Serial.println("I2C device found at address 0x5C"); else Serial.println("I2C device NOT found at address 0x5C");
        
    // testing a few methods to get info about the object
    Serial.print("Get_I2C_Slave_Address() = ");
    Serial.println(bhSensor.Get_I2C_Slave_Address()); // get I2C address
    Serial.print("Get_Resolution_Mode() = ");
    Serial.println(bhSensor.Get_Resolution_Mode()); // get resolution mode
    Serial.print("Get_MTreg() = ");
    Serial.println(bhSensor.Get_MTreg()); // get measurement time register
    bhSensor.Power_On(); // power on
    delay(1000);               // wait for a second
}

// the loop routine runs over and over again forever:
void loop() {
    int8_t nBytesRead=bhSensor.Read_I2C_To_Buffer(); // read from sensor to buffer
    if (nBytesRead != 2)  Serial.print("I2C reading error "); else { // error!
        Serial.print(bhSensor.Get_Read_Lux()); Serial.println(" lx "); // read buffer value in Lux
    }
    delay(1000);               // wait for a second
}
