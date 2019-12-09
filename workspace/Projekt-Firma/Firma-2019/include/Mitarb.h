//------------------------------------------------------------------------------
// Datei: Mitarb.h
//
// Klasse zur Verwaltung eines Mitarbeiters
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 28.11.2019
// -----------------------------------------------------------------------------

#ifndef _Mitarb_h
#define _Mitarb_h

#include <iostream>
using namespace std;

class Mitarbeiter{
  public:
	  //Default Konstruktor
	  Mitarbeiter(unsigned short = 0, unsigned short = 0);

    //Aus- und Eingabe
    virtual void ausgeben(ostream& = cout) const;

    //Operator Überladung
    void operator += (short);

    //Getter Methoden
    unsigned short getGehalt() const;
    unsigned short persNr() const;

    //Setter Methoden
    void persNrAendern(unsigned short);


  protected:
    unsigned short personalNr;
    unsigned short gehalt;
    

};

//Global Überladener Ausgabeoperator
ostream& operator << (ostream&, const Mitarbeiter&);


#endif

