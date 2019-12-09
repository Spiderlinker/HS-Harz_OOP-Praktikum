//------------------------------------------------------------------------------
// Datei: tmitarb.cpp
//
// Test der Klasse zur Verwaltung von Mitarbeiterdaten
//
// Autor: Bernhard Zimmermann
// Version 1.0: 31.05.1997
// Änderung:    01.10.1997
//   Anpassungen für Visual C++ 5
// Änderung:	22.11.2016 (K. Ludwig)
//	- Tests systematisiert und durch assertions automatisiert
//	- Eingabestrom wird aus Dateien (s. Verzeichnis 'Testdateien') gestestet
// Änderung:	26.11.2016 (K. Ludwig)
//	- Adresskomponenten und Einlesetests entfernt
// Änderung:	27.11.2017 (K. Ludwig)
//	- Test auf Parametrierungsvarianten ausgeben() eingefügt
// -----------------------------------------------------------------------------

#include <cassert>
#include "Mitarb.h"

// Precond: Adresse ist vollständig getestet
// => es werden keine Merkmale von Adresse geprüft
int main(void) {
	// Default 
	{
		Mitarbeiter m;
		assert(m.getGehalt() == 0);
		assert(m.persNr() == 0);
		m.ausgeben();
		std::cout << std::endl;
	}
	// implizite Kopie
	{
		const Mitarbeiter m = Mitarbeiter(5, 150);
		assert(m.getGehalt() == 150);
		assert(m.persNr() == 5);
		m.ausgeben(std::cout);
		std::cout << std::endl;
	}
	{ // parametriert (Sunny Day)
		Mitarbeiter m(3, 1000);
		assert(m.getGehalt() == 1000);
		assert(m.persNr() == 3);
		m += 350;
		assert(m.getGehalt() == 1350);
		std::cout << m << std::endl;
	}
	{ // "Anomalien" + const member: ausgeben()/getter-Methoden
		const Mitarbeiter m(42, 65536ui16); // VS-spezifisch
		assert(m.getGehalt() == 0); // Huch? ;-)
		assert(m.persNr() == 42);
		std::cout << m << std::endl; // Compiler?
	}
	{ // Hier bitte visuell prüfen
		Mitarbeiter m;
		m.persNrAendern(14);
		m += -5500; //Meldung?
		assert(m.getGehalt() == 0);
		assert(m.persNr() == 14);
		std::cout << m << std::endl;
	}
	return 0;
}


