#include "StudentoKlase.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>

    //Set'erei

    void studentas::setVardas (std::string x){vardas = x;}
    void studentas::setPavarde (std::string x) {pavarde = x;}
    void studentas::setEgzpazymys (double x) {egzaminoPazymys = x;}
    void studentas::setNd (int x){nd.push_back(x);}
    void studentas::setGalutinis(){
        galutinisBalas = (egzaminoPazymys*0.6)+(vidurkis()*0.4);
    }
    //Get'erei

    std::string studentas::getVardas (){return vardas;}
    std::string studentas::getPavarde (){return pavarde;}
    double studentas::getEgzPazymys () {return egzaminoPazymys;}
    int studentas::getNd (int i){return nd[i];}
    double studentas::getGalutinis(){return galutinisBalas;}

    // Velnais žino kas
    float studentas::vidurkis()
{
    return (float)std::accumulate(nd.begin(),nd.end(),0)/(float)nd.size();
}

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

std::ostream& operator<<(std::ostream& out, const studentas& a) {
  out << std::left << std::setprecision(2) << std::fixed << std::setw(15) << a.pavarde << std::setw(15) << a.vardas << std::setw(20) << a.galutinisBalas << std::endl;
  return out;
}

bool studentas::operator< (const studentas& b) {
  return vardas < b.vardas;
}


//Strategijos ir matavimas

#include <chrono>

void pirmaStrategija (std::string file) {
  auto start = std::chrono::high_resolution_clock::now();
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
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Duomenu kiekis: " << std::setw(6) << file << " [Vector 1 strategija] Time taken: " << elapsed.count() << " s\n";
  stud.clear();
}

bool jeiVargsiukas (studentas& x){ return x.galutinisBalas < 6.0;}

 void antraStrategija (std::string file) {
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<studentas> stud;
  std::vector<studentas> vargsiukai;
  Nuskaityti(stud, file + ".txt");
  std::sort(stud.begin(), stud.end());
  std::sort(vargsiukai.begin(), vargsiukai.end());
  copy_if(stud.begin(), stud.end(), back_inserter(vargsiukai), jeiVargsiukas );
  stud.erase(remove_if(stud.begin(), stud.end(), jeiVargsiukas), stud.end());
  Spausdinimas1(stud, vargsiukai, file + "-rezultatai.txt");
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Duomenu kiekis: " << std::setw(6) << file << " [Vector 2 strategija] Time taken: " << elapsed.count() << " s\n";
  stud.clear();
}

void stablePartition (std::string file) {
  auto start = std::chrono::high_resolution_clock::now();
  std::vector<studentas> stud;
  Nuskaityti(stud, file + ".txt");
  std::sort(stud.begin(), stud.end());
  std::vector<studentas>::iterator bound = stable_partition(stud.begin(), stud.end(), jeiVargsiukas);
  Spausdinimas2(stud, bound, file + "-rezultatai.txt");
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  std::cout << "Duomenu kiekis: " << std::setw(6) << file << " [stable_partition()] Time taken: " << elapsed.count() << " s\n";
  stud.clear();
}


