InfluxDB wrapper for Arduino
===============

Let your Arduino post data to InfluxDB.
Assuming your Arduino has an Ethernet shield which is connected to a network that can reach your InfluxDB server at a given IP address.
Also it is assumed your InfluxDB server is listening to the default port. The wrapper will use the standard TCP (HTTP POST) protocol.

Oh, InfluxDB is a nice time series database. Typically a database you want when you store time stamped measurement data for example. The Influx query language is very suited for this. For example "group by 5m" will group the data by 5 minute chunks.
On top of InfluxDB you might want to install Grafana, letting you make pretty time series graphs from data collected by your Arduino.

This library currently works on InfluxDB 0.9. It has not been tried on any other version.

Install
--------
cd /your/arduino/libraries/folder
git clone https://github.com/jstelwag/InfuxDB.git

Usage
--------
  #include <Ethernet.h>
  #include <EEPROM.h>
  #include <InfluxDB.h>
  
  const byte romPosition = 0; // set to 0 if you are not using eeprom memory
  InfluxDB influx(romPosition);
  
  void setup() {
  
    // Below is a one off, once the eeprom is filled up, remove this
    IPAddress influxServerIP(11,22,33,44);
    InfluxProperties influxProp = {
      { 0x00, 0xA0, 0x11, 0xED, 0x8E, 0x18 },
      influxServerIP,
      "database name",
      "user name",
      "password"
    };
	
    EEPROM.put(romPosition, influxProp);

	// Start the wrapper (this will initialize the Ethernet shield)
	influx.setup();
  }
  
  void loop() {
    influx.post("temperature,type=arduino_sample value=22.9", F("My user agent"));
	delay(10000);
  }
  
  See the influxdb manual for the line protocol. Arduino's have been sending millions of datapoints so far with this code, so consider it stable.