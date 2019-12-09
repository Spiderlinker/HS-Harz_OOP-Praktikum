//------------------------------------------------------------------------------
// Datei: Chefin.cpp
//
// Implementierung der Klasse zur Verwaltung einer Chefin
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 24.11.2019
// -----------------------------------------------------------------------------

#include "Chefin.h"
#include "Sekr.h"

    
Chefin::Chefin(unsigned short personalNr, unsigned short gehalt, const char* bereich) : Mitarbeiter(personalNr, gehalt), sekretaer(nullptr), bereich(nullptr)
{
    bereichAendern(bereich);
}

Chefin::Chefin(const Sekretaer& sekretaer, unsigned short personalNr, unsigned short gehalt, const char* bereich) : Mitarbeiter(personalNr, gehalt), sekretaer(&sekretaer), bereich(nullptr)
{
    bereichAendern(bereich);
}

Chefin::Chefin(const Chefin& c) : Mitarbeiter(c.personalNr, c.gehalt), sekretaer(nullptr), bereich(nullptr)
{
  bereichAendern(c.getBereich());
}

void Chefin::bereichAendern(const char* bereich)
{

    if(this->bereich != nullptr){ 
     delete[] this->bereich;
    }

    if(bereich == nullptr){
      this->bereich = new char[1];
      this->bereich[0] = '\0';
    }else
    {
      this->bereich = new char[strlen(bereich) + 1];
      strcpy(this->bereich, bereich);
    }
}

void Chefin::sekretaerAendern(const Sekretaer& sekretaer)
{
    this->sekretaer = &sekretaer;
}

const char* Chefin::getBereich()const {
  return this->bereich;
}

Chefin::~Chefin(){
  cout << "Destruktor called: Chefin to destroy: "; 
  ausgeben();
  cout << endl;

  this->sekretaer = nullptr;
  if(this->bereich != nullptr){
    delete []bereich;
  }
}

const Chefin& Chefin::operator = (const Chefin& c){
  
  if(&c != this) {
    this->gehalt = c.gehalt;
    this->personalNr = c.personalNr;

    this->sekretaer = nullptr;
    bereichAendern(c.getBereich());
  }

  return *this;
}

void Chefin::ausgeben(ostream& strm) const{
  Mitarbeiter::ausgeben(strm);
  strm << ", Bereich: "<< bereich<<endl;
  if(this->sekretaer == nullptr){
    strm << "\tKein Sekretaer";
  }else {
    strm << "\tMein Sekretaer: [";
    this->sekretaer->ausgeben(strm);
    strm << "]";
  }
}