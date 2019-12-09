//------------------------------------------------------------------------------
// Datei: Chefin.h
//
// Klasse zur Verwaltung einer Chefin
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 24.11.2019
// -----------------------------------------------------------------------------
#ifndef _Chefin_h
#define _Chefin_h

#include "Mitarb.h"
#include "Sekr.h"
#include <iostream>
using namespace std;

class Chefin:public Mitarbeiter{
    
  public:

    Chefin(unsigned short = 0, unsigned short = 0, const char* = nullptr);

    Chefin(const Sekretaer&, unsigned short = 0, unsigned short = 0, const char* = nullptr);

    Chefin(const Chefin&);

    void ausgeben(ostream& = cout) const;

    void bereichAendern(const char* = nullptr);

    void sekretaerAendern(const Sekretaer& = NULL);

    const char* getBereich()const;

    ~Chefin();

    const Chefin& operator = (const Chefin&);

  private:
    const Sekretaer* sekretaer;
    char* bereich;

};

#endif