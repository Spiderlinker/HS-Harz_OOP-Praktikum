//------------------------------------------------------------------------------
// Datei: Abteil.h
//
// Klasse zur Verwaltung der Mitarbeiter einer Abteilung
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 24.11.2019
// -----------------------------------------------------------------------------

#ifndef _Abteil_h
#define _Abteil_h

#include "Chefin.h"
#include <iostream>

using namespace std;


class Abteilung {

public:

  //Konstruktor mit default argumenten
  Abteilung(const char* bezeichnung = nullptr);

  //Destruktor
  ~Abteilung();

  //Setter Bezeichnung
  void bezeichnungAendern(const char* bezeichnung = nullptr);

  //Setter Mitarbeiter
  Mitarbeiter* einfuegen(Mitarbeiter& mitarbeiter);

  //Löschen eines vorhanden Mitarbeiters
  Mitarbeiter* loeschen(unsigned short persNr);

  void ausgeben(ostream& = cout) const;

  //Getter Bezeichnung
  const char* getBezeichnung() const;

private:
  //Predeklaration 
  class Listnode;

  //Klassenvariablen
  char* bezeichnung;
  Listnode* first;

  // Methoden sollen nicht aufgerufen werden können
  const Abteilung& operator = (const Abteilung&){}
  Abteilung(const Abteilung&){}

  //Klasse zur Erstellung der Mitarbeiter List einer Abteilung mit privatem Zugriff
  class Listnode {

    public:
      Listnode(Listnode* next, Mitarbeiter& val);
      ~Listnode();

      //Arbeitsvariablen
      Listnode* next;
      Mitarbeiter* val;
    };
};

//Global Überladener Ausgabeoperator
ostream& operator << (ostream&, const Abteilung&);

#endif
