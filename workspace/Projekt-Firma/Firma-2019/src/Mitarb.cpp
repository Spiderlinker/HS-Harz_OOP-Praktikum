//------------------------------------------------------------------------------
// Datei: Mitarb.cpp
//
// Implementierung der Klasse zur Verwaltung eines Mitarbeiters
//
// Autoren: Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 28.11.2019
// -----------------------------------------------------------------------------

#include "Mitarb.h"

//Konstruktor mit Default Werten definiert 
Mitarbeiter::Mitarbeiter(unsigned short personalNr, unsigned short gehalt)
{
    this->personalNr = personalNr;
    this->gehalt = gehalt;
}

//Getter Methoden
unsigned short Mitarbeiter::getGehalt() const
{
  return gehalt;
}

unsigned short Mitarbeiter::persNr() const
{
  return personalNr;
}

//Setter Methode
void Mitarbeiter::persNrAendern(unsigned short personalNr)
{
  this->personalNr = personalNr;
}

void Mitarbeiter::operator += (short gehalt)
{
  // Berechnung von neuem Gehalt
  short tempGehalt = this->gehalt + gehalt;
  // Prüfen, ob neues Gehalt gültig ist
  if(tempGehalt >= 0)
  {
    // Neues Gehalt setzen
    this->gehalt = tempGehalt;
  }else{
    // Neues Gehalt ist ungültig, Fehler ausgeben
     cerr<<"Fehler: Falscher Aenderungswert fuer das Gehalt"<<endl;
  }
}

//Überladenen Standard Ausgabe operator
ostream& operator << (ostream& strm, const Mitarbeiter& ma)
{
  ma.ausgeben(strm);
  return strm;
}

void Mitarbeiter::ausgeben(ostream& strm) const
{
  strm << "PNr: " << personalNr << ", Gehalt: "<<gehalt;
}