//------------------------------------------------------------------------------
// Datei: tsc.cpp
//
// Test der Klassen zur Verwaltung der Daten von Sekretaer und Chefin
//
// Autor: Bernhard Zimmermann
// Version 1.0: 14.06.1997
// Änderung:    08.10.1997
//   Anpassungen für Visual C++ 5
// Änderung:    26.05.2007
//   Anpassungen für Visual C++ 2005
// Änderung:    30.05.2014
//   Anpassungen bezüglich geänderten Spezifikation von Sekretaer und Chefin
// Änderung:    26.04.2015
//   Test des Virtuellen Destruktors von Mitarbeiter hinsichlich eines
//   Mitarbeiter-Zeigers auf ein Chefin-Objekt
// Änderung:	22.11.2016 ( K. Ludwig)
//	- Tests systematisiert und durch assertions automatisiert
// Änderung:	26.11.2016 (K. Ludwig)
//	- Adresskomponenten und Einlesetests entfernt
// Änderung:	27.11.2016 (K. Ludwig)
//	- Chefin und Sekretaer werden separat inkludiert
//	  -> Sekretaer kann ohne Fertigstellung Chefin hier "optisch" überprüft werden
//	- Test auf Parametrierungsvarianten ausgeben() eingefügt
//	- Test Selbstapplikation Zuweisung Chefin eingefügt
// -----------------------------------------------------------------------------

#include <cassert>
#include "Sekr.h"
#include "Chefin.h"

int main(void) {
	/* SEKRETAER */
	{ // Defaults
		Sekretaer s;
		assert(! strcmp(s.getFremdsprache(), ""));
		std::cout << s << std::endl;
		s.fremdspracheAendern("Kantonesisch");
		assert(! strcmp(s.getFremdsprache(), "Kantonesisch"));
		s.fremdspracheAendern(0);
		assert(! strcmp(s.getFremdsprache(), ""));
		s.fremdspracheAendern("");
		assert(! strcmp(s.getFremdsprache(), ""));
		assert(s.getGehalt() == 0);
		assert(s.persNr() == 0);
		s.ausgeben();
		std::cout << std::endl;
	}
	{ // Parametriert
		Sekretaer s(17, 3890, "Latein");
		assert(! strcmp(s.getFremdsprache(), "Latein"));
		assert(s.getGehalt() == 3890);
		assert(s.persNr() == 17);
		s.ausgeben(std::cout); std::cout << std::endl;
	}
	/* CHEFIN */
	{ // Defaults
		const Chefin c;
		assert(! strcmp(c.getBereich(), ""));
		assert(c.getGehalt() == 0);
		assert(c.persNr() == 0);
		c.ausgeben(std::cout); std::cout << std::endl;
	}

	{ // CCTOR
		Sekretaer s(17, 3890, "Latein");
		Chefin c1(s, 21, 9500, "EDV");
		Chefin c2(c1);
		c1.bereichAendern("Buchhaltung");
		assert(! strcmp(c1.getBereich(), "Buchhaltung"));
		assert(! strcmp(c2.getBereich(), "EDV"));
		assert(c1.persNr() == c2.persNr());
		std::cout << "c1: " << c1 << std::endl
			<< "c2: " << c2 << std::endl;
	}
	{ // ASSIGNMENT
		Sekretaer s(17, 3890, "Latein");
		Chefin c1(s, 21, 9500, "EDV");
		c1 = c1; // Selbstapplikation
		{
			// Polymorphie
			Mitarbeiter* c2 = new Chefin(s, 15, 8000, "Verwaltung");
			assert(! strcmp(c1.getBereich(), "EDV"));
			Chefin& c2_ref = dynamic_cast<Chefin&>(*c2);
			c2_ref = c1;
			c1.bereichAendern("IT-Services");
			assert(! strcmp(c2_ref.getBereich(), "EDV"));
			assert(c1.persNr() == c2->persNr());
			std::cout << "c2: " << *c2 << std::endl;
			// virtueller Mitarbeiter::DTOR
			delete c2;
		}
		assert(! strcmp(c1.getBereich(), "IT-Services"));
		std::cout << "c1: " << c1 << std::endl;
	}
	{ // CTOR parametriert
		Sekretaer s;
		Chefin c(s = Sekretaer(14, 1200, 0), 2, 5000, "Sales");
		std::cout << c << std::endl;
    Sekretaer s1(78, 980, "Polnisch");
    c.sekretaerAendern(s1);
    std::cout << c << std::endl;
    c.sekretaerAendern();
    std::cout << c << std::endl;
	}
	{ // Manuell überprüfen durch durch wechselseitiges umkommentieren (const) char* bereich
		const Chefin c(66, 4500, "EDV");
		const char* bereich = c. getBereich();
		// zu erwartender Fehler: error C2440: 'Initialisierung': 'const char *' kann nicht in 'char *' konvertiert werden
		//char* bereich = c.getBereich(); 
		assert(! strcmp(bereich, "EDV"));		
		assert(! strcmp(c.getBereich(), "EDV"));
		std::cout << c << std::endl;
	}
	/* Nullzeiger in neuen Zeichenketten (Segfault/korrekte Defaults?" */	
	{ // 1.) setzen per Memberfunktion
		const Sekretaer s(7, 3000, "Englisch");
		Chefin c(s, 17, 6700, "Vertrieb");
		assert(! strcmp(c.getBereich(), "Vertrieb"));
		c.bereichAendern(0);
		assert(! strcmp(c.getBereich(), ""));
		std::cout << c << std::endl;
	}
	{ // 2.) setzen per CTOR
		const Sekretaer s(7, 3000, 0);
		Chefin c(s, 17, 6700, 0);
		assert(! strcmp(s.getFremdsprache(), ""));
		assert(! strcmp(c.getBereich(), ""));
		std::cout << c << std::endl;
	}
	/* DEFEKTE */
	{ // Absturz (Sekretaer entlassen, Chefin weiss von "nichts")
		//	const Sekretaer* s = new Sekretaer();
		//	Chefin c(*s);
		//	delete s;
		//	std::cout << c << std::endl;
	}

	return 0;
}

