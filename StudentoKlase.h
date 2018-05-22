#ifndef STUDENTOKLASE_H_INCLUDED
#define STUDENTOKLASE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>



class studentas {

private:
    std::string vardas;
    std::string pavarde;
    double egzaminoPazymys;
    std::vector<int> nd;
public:
    studentas(): egzaminoPazymys(0) {} // konstruktorius
     double galutinisBalas;

    void setVardas (std::string ); //set'eriai
    void setPavarde (std::string );  //set'eriai
    void setEgzpazymys (double );  //set'eriai
    void setNd (int );  //set'eriai
    void setGalutinis ();  //set'eriai

    std::string getVardas ();  //get'eriai
    std::string getPavarde (); //get'eriai
    double getEgzPazymys ();  //get'eriai
    int getNd (int);   //get'eriai
    double getGalutinis ();   //get'eriai


    // Operatoriai
    friend std::ostream& operator<<(std::ostream&, const studentas&);
    bool operator< (const studentas& b);

    bool operator> (const studentas& b);

    bool operator== (const studentas& b);

    bool operator!= (const studentas& b);


    // Funkcijos

    float vidurkis();
};

// Funkciju deklaravimas

void Generuoti(int);
bool Nuskaityti(std::vector<studentas>&, std::string);
void Spausdinimas1(std::vector<studentas>&,std::vector<studentas>&,std::string );
void Spausdinimas2(std::vector<studentas>&, std::vector<studentas>::iterator,std::string );
void pirmaStrategija (std::string );
void antraStrategija(std::string );
bool jeiVargsiukas (studentas& );
void stablePartition(std::string);

#endif // STUDENTOKLASE_H_INCLUDED
