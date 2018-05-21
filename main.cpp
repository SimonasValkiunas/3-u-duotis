#include <iostream>
#include "StudentoKlase.h"

std::vector<studentas> stud;
std::vector<studentas> vargsiukai;
std::vector<studentas> kietiakai;

int main()
{

    for (int i = 10; i<=100000; i*=10){
    Generuoti(i);
    pirmaStrategija(std::to_string(i));
    antraStrategija(std::to_string(i));
    stablePartition(std::to_string(i));
    }


    return 0;
}
