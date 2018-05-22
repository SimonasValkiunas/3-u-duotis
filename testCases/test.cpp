#define CATCH_CONFIG_MAIN

#include "../StudentoKlase.h"
#include "catch.hpp"



TEST_CASE( "/*VIDURKIS TESTAVIMAS*/" ) {
    SECTION(" Vidurkio skaiciavimas, kai vidurkis - turi 1 reiksme "){
        studentas stud;
        stud.setNd(1);
        REQUIRE(stud.vidurkis() == 1);
    }
    SECTION(" Vidurkio skaiciavimas, kai vidurkis - turi daug reiksme "){
        studentas stud;
        for (int i =1; i<101; i++){stud.setNd(i);}
        REQUIRE(stud.vidurkis() == 50.5);
    }
    SECTION(" Vidurkio skaiciavimas, kai vidurkis - turi 0 reiksme "){
        studentas stud;
        stud.setNd(0);
        REQUIRE(stud.vidurkis() == 0);
    }

}



TEST_CASE( "/*STRING TESTAVIMAS*/" ) {

    SECTION(" (Vardas ir pavarde testavimas, kai turi verte "){
        std::string x = "Vardas1";
        std::string y = "Pavarde1";
        studentas stud;
        stud.setVardas(x);
        stud.setPavarde(y);
        REQUIRE( stud.getVardas() == "Vardas1" );
        REQUIRE( stud.getPavarde() == "Pavarde1" );
    }
    SECTION(" (Vardas ir pavarde testavimas, kai neturi vertes "){
        studentas stud;
        REQUIRE( stud.getVardas() == "" );
        REQUIRE( stud.getPavarde() == "" );
    }

}

TEST_CASE( "/*FAILU TESTAVIMAS*/" ) {
    std::vector<studentas> stud;
    SECTION(" KAI FAILO NERA "){
        REQUIRE( Nuskaityti(stud, "tikrai_tokio_nera.txt") == 0 );
    }
    SECTION(" KAI FAILAS TUSCIAS "){
        Nuskaityti(stud, "tuscias.txt");
        REQUIRE( stud.size() == 0 );
    }
    SECTION(" KAI FAILAS NE TUSCIAS "){
        int i =100;
        Generuoti(i);
        Nuskaityti(stud, "100.txt");
        REQUIRE( stud.size() == i );
    }

}
