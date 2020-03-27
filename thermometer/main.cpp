#include <iostream>
#include "dht22.h"
#include <wiringPi.h>

int main()
{
    dht22* pDHT22 = new dht22();
    if (wiringPiSetup() == -1)
        exit(EXIT_FAILURE);

    std::cout << "hello from thermometer bob!" << std::endl;

    int cnt = 0;
    int err;
    while (cnt < 10) {
        err = pDHT22->readDHT22();

        if (err == 0) {
            std::cout << "temperature = " << pDHT22->getTemperature() << std::endl;
            std::cout << "   humidity = " << pDHT22->getHumidity() << std::endl;
            cnt++;
        }
        
    }

   delete pDHT22;
 
    return 0;
} 