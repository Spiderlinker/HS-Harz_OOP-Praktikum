//------------------------------------------------------------------------------
// Datei: Abteil.cpp
//
// Implementierung der Klasse zur Verwaltung der Mitarbeiter einer Abteilung
//
// Autoren:Oliver Lindemann (u33873), Robin Kopitz (u33874)
// Version 1.0: 24.11.2019
// -----------------------------------------------------------------------------

#include "Abteil.h"


Abteilung::Abteilung(const char* bezeichnung) : bezeichnung(nullptr), first(nullptr) {
  //Call Bezeichnung zum einfügen der Bezeichnung
  bezeichnungAendern(bezeichnung);
}

Abteilung::~Abteilung(){  
  cout << "Destruktor von Abteilung called" << endl;
  //Prüfe ob es sich um einen Nullptr handelt wenn nein lösche das dynamische Feld
  delete[] this->bezeichnung;
  delete first;
}

void Abteilung::bezeichnungAendern(const char* bezeichnung){
    //Prüfe ob es sich um einen Nullptr handelt wenn nein lösche das dynamische Feld
    //um Datenmüll zu vermeiden
    delete[] this->bezeichnung;

    //Falls nichts übergeben wird erstelle ein dynamisches Feld und initialisiere es mit /0
    if(bezeichnung == nullptr){
      this->bezeichnung = new char[1];
      this->bezeichnung[0] = '\0';
    }
    else
    {
      //Falls etwas übergeben wird erzeuge das dynmische Feld mit der Stringlänge +1 und kopiere
      //den String
      this->bezeichnung = new char[strlen(bezeichnung) + 1];
      strcpy(this->bezeichnung, bezeichnung);
    }
}

Mitarbeiter* Abteilung::einfuegen(Mitarbeiter& mitarbeiter){

   for(Listnode* current = first; current != nullptr; current = current->next){
    // Prüfen, ob der aktuelle Listenknoten 
    // den gesuchten Mitarbeiter enthält
    if(current->val->persNr() == mitarbeiter.persNr()){
      // Mitarbeiter gefunden und Speicheradresse zurückgeben
      return 0; // 0 = nullptr
    }
  }

  // Mitarbeiter einfügen und zurückgeben
  first = new Listnode(first, mitarbeiter);
  return first->val;
}

Mitarbeiter* Abteilung::loeschen(unsigned short persNr){
  Mitarbeiter* geloeschterMitarbeiter = nullptr;

  Listnode* pred = nullptr;
  for(Listnode* current = first; current != nullptr; current = current->next){

    // Prüfen, ob der aktuelle Listenknoten 
    // den gesuchten Mitarbeiter enthält
    if(current->val->persNr() == persNr){
      
      if(pred != nullptr) {
        // Vorgänger dieses Knotens soll auf nächsten Knoten zeigen
        pred->next = current->next;
      }else{
        // Der gesuchte Knoten ist der Erste in der Liste
        // Ersten Knoten neu setzen auf den nächsten des gelöschten Knotens
        first = current->next;
      }
      
      geloeschterMitarbeiter = current->val;

      // current->next auf null setzen,
      // damit der Destruktor des current-Listnodes 
      // nicht die nachfolgenden Elemente löscht
      current->next = nullptr;
      delete current;

      // Listknoten gefunden und gelöscht
      break;
    }

    pred = current;
  }

  return geloeschterMitarbeiter;
}

void Abteilung::ausgeben(ostream& strm) const {
  strm << "Abteilung: " << this->bezeichnung << endl;
  
  strm << "\tChefinnen: " << endl;
  for(Listnode* current = first; current != nullptr; current = current->next){

    // Prüfen, ob der aktuelle Listenknoten 
    // den gesuchten Mitarbeiter enthält
    if(dynamic_cast<Chefin*> (current->val)){
      strm << "\t" << *current->val << endl;
    }
  }

  strm << "\tSekretaere: " << endl;
  for(Listnode* current = first; current != nullptr; current = current->next){
    // Prüfen, ob der aktuelle Listenknoten 
    // den gesuchten Mitarbeiter enthält
    if(dynamic_cast<Sekretaer*> (current->val)){
      strm << "\t" << *current->val << endl;
    }
  }

  strm << "\tMitarbeiter: " << endl;
  for(Listnode* current = first; current != nullptr; current = current->next){
    // Prüfen, ob der aktuelle Listenknoten 
    // den gesuchten Mitarbeiter enthält
    if(!(dynamic_cast<Chefin*> (current->val)) && !(dynamic_cast<Sekretaer*> (current->val))){
      strm << "\t" << *current->val << endl;
    }
  }
}

const char* Abteilung::getBezeichnung() const {
  return bezeichnung;
}

ostream& operator << (ostream& strm, const Abteilung& abteilung){
  abteilung.ausgeben(strm);
  return strm;
}

// ----- Listnode

Abteilung::Listnode::Listnode(Listnode* next, Mitarbeiter& val) : next(next), val(&val) {
}

//Rekursiver Aufruf zum Löschen aller Listenknoten
Abteilung::Listnode::~Listnode(){
  delete next;
}
