//------------------------------------------------------------------------------
// Datei: Sekr.cpp
//
// Implementierung der Klasse zur Verwaltung eines Sekretärs
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 24.11.2019
// -----------------------------------------------------------------------------

#include "Sekr.h"

Sekretaer::Sekretaer(unsigned short personalNr, unsigned short gehalt, const char* fremdsprache):Mitarbeiter(personalNr, gehalt)
{
  fremdspracheAendern(fremdsprache);
  //strncpy(this->fremdsprache, fremdsprache, FREMDSPRACHE_MAX_LEN);
}

void Sekretaer::fremdspracheAendern(const char* fremdsprache)
{
  if(fremdsprache == nullptr){
    this->fremdsprache[0] = '\0';
  }
  else{
    strncpy(this->fremdsprache, fremdsprache, FREMDSPRACHE_MAX_LEN);
    this->fremdsprache[FREMDSPRACHE_MAX_LEN] = '\0';
  }
}


const char* Sekretaer::getFremdsprache()const
{
  return this->fremdsprache;
}


void Sekretaer::ausgeben(ostream& strm)const
{
  Mitarbeiter::ausgeben(strm);
  strm << ", Fremdspr: "<< fremdsprache;
}