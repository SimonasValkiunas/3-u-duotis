#include "StudentoKlase.h"
#include "mVector.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>

    //Set'erei

    void zmogus::setVardas (std::string x){vardas = x;}
    void zmogus::setPavarde (std::string x) {pavarde = x;}
    void studentas::setEgzpazymys (double x) {egzaminoPazymys = x;}
    void studentas::setNd (int x){nd.push_back(x);}
    void studentas::setGalutinis(){
        galutinisBalas = (egzaminoPazymys*0.6)+(vidurkis()*0.4);
    }
    //Get'erei

    std::string zmogus::getVardas (){return vardas;}
    std::string zmogus::getPavarde (){return pavarde;}
    double studentas::getEgzPazymys () {return egzaminoPazymys;}
    int studentas::getNd (int i){return nd[i];}
    double studentas::getGalutinis(){return galutinisBalas;}

    //Funkcijos
    float studentas::vidurkis()
{
    return (float)std::accumulate(nd.begin(),nd.end(),0)/(float)nd.size();
}

bool Nuskaityti(std::vector<studentas> &stud, std::string failas) {
  std::ifstream fin;
  try {
    std::string input;
    fin.open (failas, std::ios::in | std::ios::binary);
    if( !fin )throw std::ios::failure( "Error opening file!");

    getline(fin, input);
    while(fin >> input) {
      studentas temp;
      int paz;
      temp.setVardas(input);
      fin >> input;
        temp.setPavarde(input);
      for(int i = 0; i < 5; i++) {
        fin >> paz;
          temp.setNd(paz);
      }
      fin >> paz;
        temp.setEgzpazymys(paz);
        temp.setGalutinis();
      stud.push_back(temp);
    }
  } catch (const std::ifstream::failure &e) {
    std::cout << e.what() << std::endl;
      return 0;
  }
  fin.close();
  return 1;
}

void Spausdinimas1 (std::vector<studentas> &kietiakai, std::vector<studentas> &vargsiukai, std::string file) {
  std::ofstream fout(file);
  fout << "Kietiakai:" << std::endl;
  fout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis-vidurkis" << std::endl;
  for(auto &k: kietiakai)
    fout << k;
  fout << "Vargsiukai:" << std::endl;
  fout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis-vidurkis"  << std::endl;
  for(auto &v: vargsiukai)
    fout << v;
  fout.close();
}

void Spausdinimas2 (std::vector<studentas> &kietiakai, std::vector<studentas>::iterator bound, std::string file) {
  std::ofstream fout(file);
  fout << "Kietiakai:" << std::endl;
  fout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis-vidurkis"  << std::endl;
  for (std::vector<studentas>::iterator it=bound; it!=kietiakai.end(); ++it)
    fout << *it;
  fout << "Vargsiukai:" << std::endl;
  fout << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis-vidurkis" << std::endl;
  for (std::vector<studentas>::iterator it=kietiakai.begin(); it != bound; ++it)
    fout << *it;
  fout.close();
}

//Operatoriai

std::ostream& operator <<(std::ostream& out, const studentas& a) {
  out << std::left << std::setprecision(2) << std::fixed << std::setw(15) << a.pavarde << std::setw(15) << a.vardas << std::setw(20) << a.galutinisBalas << std::endl;
  return out;
}

 bool zmogus::operator< (const zmogus& b) {
  return vardas < b.vardas;

}

bool zmogus::operator==(const zmogus &b) {
  return vardas == b.vardas && pavarde == b.pavarde;
}

bool zmogus::operator!=(const zmogus &b) {
  return !operator==(b);
}


bool zmogus::operator> (const zmogus& b) {
  return vardas > b.vardas;
}

//Strategijos ir matavimas

#include <chrono>

void pirmaStrategija (std::string file) {
  auto t1 = std::chrono::high_resolution_clock::now();
  std::vector<studentas> stud;
  std::vector<studentas> vargsiukai;
  std::vector<studentas> kietiakai;
  Nuskaityti(stud, file + ".txt");
  for(auto &item: stud) {
    if(item.getGalutinis() < 6) vargsiukai.push_back(item);
    else kietiakai.push_back(item);
  }
  std::sort(stud.begin(), stud.end());
  std::sort(vargsiukai.begin(), vargsiukai.end());
  std::sort(kietiakai.begin(), kietiakai.end());
  Spausdinimas1(kietiakai, vargsiukai, file + "-rezultatai.txt");
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = t2 - t1;
  std::cout << "Duomenu kiekis -  " << std::setw(6) << file << " Pirma Strategija - " << elapsed.count() << "s"<< std::endl;
  stud.clear();
}

bool jeiVargsiukas (studentas& x){ return x.galutinisBalas < 6.0;}


void antraStrategija(std::string file) {
  auto t1 = std::chrono::high_resolution_clock::now();
  std::vector<studentas> stud;
  Nuskaityti(stud, file + ".txt");
  std::sort(stud.begin(), stud.end());
  std::vector<studentas>::iterator it = stable_partition(stud.begin(), stud.end(), jeiVargsiukas);
  Spausdinimas2(stud, it, file + "-rezultatai.txt");
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = t2 - t1;
  std::cout << "Duomenu kiekis - " << std::setw(6) << file << " Antra Strategija -  " << elapsed.count() << "s"<< std::endl;
  stud.clear();
}


