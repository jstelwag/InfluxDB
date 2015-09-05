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
#ifndef InfluxDB_h
#define InfluxDB_h
#include <Ethernet.h>

struct InfluxProperties {
	uint8_t macAddress[6];
	IPAddress influxIP;
	char influxDB[11];
	char influxUser[7];
	char influxPassword[15];
};

class InfluxDB {
  public:
    InfluxDB(byte romPosition);
    void setup();
	boolean post(String &data, String userAgent);
  private:
	byte _romPosition;

};

#endif

