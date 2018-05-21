#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include <stdio.h>

int randPazymys() {

    return rand() % 11-0;;
}

void Generuoti (int n) {
    std::ofstream fout(std::to_string(n) + ".txt");
    fout << std::left << std::setprecision(2) << std::fixed << std::setw(15) << "Pavarde" << std::setw(15)  << "Vardas" << std::setw(5) << "ND1" << std::setw(5) << "ND2" << std::setw(5) << "ND3" << std::setw(5) << "ND4" << std::setw(5) << "ND5" << std::setw(9) << "Egzaminas" << std::endl;
    for(int i = 1; i <= n; i++)
      fout << std::left << std::setprecision(2) << std::fixed << "Pavarde" << std::setw(8) << i << "Vardas" << std::setw(9) << i << std::setw(5) << randPazymys() << std::setw(5) << randPazymys() << std::setw(5) << randPazymys() << std::setw(5) << randPazymys() << std::setw(5) << randPazymys() << std::setw(9) << randPazymys() << std::endl;
    fout.close();
}



