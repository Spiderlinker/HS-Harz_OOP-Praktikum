//------------------------------------------------------------------------------
// Datei: Sekr.h
//
// Klasse zur Verwaltung eines Sekretärs
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 24.11.2019
// -----------------------------------------------------------------------------
#ifndef _Sekretaer_h
#define _Sekretaer_h

#include "Mitarb.h"
#include <iostream>
using namespace std;

class Sekretaer:public Mitarbeiter{

  public: 
    Sekretaer(unsigned short = 0, unsigned short = 0, const char* = nullptr);

    void fremdspracheAendern(const char*);

    const char* getFremdsprache()const;

    void ausgeben(ostream& = cout) const;

  private:
    static const size_t FREMDSPRACHE_MAX_LEN = 17;
    char fremdsprache[FREMDSPRACHE_MAX_LEN+1];



};

#endif