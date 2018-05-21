#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include "StudentoKlase.h"

void Nuskaityti(std::vector<studentas> &stud, std::string failas) {
  std::ifstream fin;
  try {
    std::string input;
    fin.open (failas, std::ios::in | std::ios::binary);
    if( !fin ) throw std::ios::failure( "Error opening file!");
    getline(fin, input);
    while(fin >> input) {
      studentas placeholder;
      double paz;
      placeholder.setVardas(input);
      fin >> input;
      placeholder.setPavarde(input);
      for(int i = 0; i < 5; i++) {
        fin >> paz;
        placeholder.setNd(paz);
      }
      fin >> paz;
      placeholder.setEgzpazymys(paz);
      placeholder.setGalutinis();
      stud.push_back(placeholder);
    }
  } catch (const std::ifstream::failure &e) {
    std::cout << e.what() << std::endl;
  }
  fin.close();
}

