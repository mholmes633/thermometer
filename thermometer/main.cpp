#include <iostream>
#include "dht22.h"
#include <wiringPi.h>
#include "lidarLiteV3.h"


int main()
{
    int del = 1000; // lidar lite delay (ms)
    int fd, res;
    unsigned char st;

    dht22* pDHT22 = new dht22();
    lidarLiteV3* pLLV3 = new lidarLiteV3();

    if (wiringPiSetup() == -1)
        exit(EXIT_FAILURE);

    fd = pLLV3->lidar_init(false);

    if (fd == -1) {
        printf("lidar lite initialization error\n");
    }
    res = pLLV3->lidar_read(fd);
    st = pLLV3->lidar_status(fd);
    //ver = lidar_version(fd);

    printf("%3.0d cm \n", res);
    pLLV3->lidar_status_print(st);

    delay(del);


    std::cout << "hello from thermometer bob!" << std::endl;

    int cnt = 0;
    int err;
    while (cnt < 10) {
        res = pLLV3->lidar_read(fd);
        st = pLLV3->lidar_status(fd);
        

        printf("%3.0d cm \n", res);
        pLLV3->lidar_status_print(st);

        delay(del);
        if (res < 100) {
            err = pDHT22->readDHT22();

            if (err == 0) {
                std::cout << "temperature = " << pDHT22->getTemperature() << std::endl;
                std::cout << "   humidity = " << pDHT22->getHumidity() << std::endl;
                cnt++;
            }
            else {
                std::cout << "error " << std::endl;
            }
        }
        
        
    }

   delete pDHT22;
   delete pLLV3;

 
    return 0;
} 