#ifndef STUDENTOKLASE_H_INCLUDED
#define STUDENTOKLASE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "mVector.h"


class zmogus{
protected:
    std::string vardas;
    std::string pavarde;
public:

    void setVardas (std::string ); //set'eriai
    void setPavarde (std::string );  //set'eriai

    std::string getVardas ();  //get'eriai
    std::string getPavarde (); //get'eriai

    virtual float vidurkis() =0;


     bool operator< (const zmogus& b);

     bool operator> (const zmogus& b);

     bool operator== (const zmogus& b);

    bool operator!= (const zmogus& b);

};

class studentas: public zmogus {

protected:
    double egzaminoPazymys;
    std::vector<int> nd;
public:
    studentas(): egzaminoPazymys(0) {} // konstruktorius
    double galutinisBalas;
    void setEgzpazymys (double );  //set'eriai
    void setNd (int );  //set'eriai
    void setGalutinis ();  //set'eriai
    double getEgzPazymys ();  //get'eriai
    int getNd (int);   //get'eriai
    double getGalutinis ();   //get'eriai
    // Funkcijos

    float vidurkis();

    friend std::ostream& operator<<(std::ostream&, const studentas&);
};

// Funkciju deklaravimas

void Generuoti(int);
bool Nuskaityti(std::vector<studentas>&, std::string);
void Spausdinimas1(std::vector<studentas>&,std::vector<studentas>&,std::string );
void Spausdinimas2(std::vector<studentas>&, std::vector<studentas>::iterator,std::string );
void pirmaStrategija (std::string );
void antraStrategija(std::string );
bool jeiVargsiukas (studentas& );

#endif // STUDENTOKLASE_H_INCLUDED
