/*
Copyright 2015 Jaap Stelwagen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <DallasTemperature.h>

#include "InfluxDB.h"
#include "Ethernet.h"
#include "EEPROM.h"

InfluxDB::InfluxDB(byte romPosition) {
	_romPosition = romPosition;
}

void InfluxDB::setup() {
	Serial.print(F("Connecting to network... "));
	InfluxProperties prop;
	EEPROM.get(_romPosition, prop);
	delay(1000); // give the ethernet module time to boot up
	if (Ethernet.begin(prop.macAddress) == 0) {
		Serial.println(F("failed to configure Ethernet using DHCP"));
		//Further on it will try to connect at every post
	}
	else {
		Serial.print(F("success! My IP is now "));
		Serial.println(Ethernet.localIP());
	}
}


boolean InfluxDB::post(String &data, String userAgent) {
	EthernetClient client;
	InfluxProperties prop;
	EEPROM.get(_romPosition, prop);
	Serial.print(F("@"));
	Serial.print(prop.influxIP);
	if (client.connect(prop.influxIP, 8086)) {
		client.print(F("POST /write?db="));
		client.print(prop.influxDB);
		client.print(F("&precision=s&u="));
		client.print(prop.influxUser);
		client.print(F("&p="));
		client.print(prop.influxPassword);
		client.println(F(" HTTP/1.1"));
		client.print(F("User-Agent: "));
		client.println(userAgent);
		client.println(F("Connection: close"));
		client.print(F("Content-length: "));
		client.println(data.length());
		client.println();
		client.print(data);

		if (client.connected()) {
			client.stop();
			return true;
		}
		Ethernet.maintain();
		client.stop();
		return false;
	} else {
		//TODO go into failure thingies
		client.stop();
		setup();
		return false;
	}
}

