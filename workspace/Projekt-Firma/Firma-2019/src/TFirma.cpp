//------------------------------------------------------------------------------
// Datei: tfirma.cpp
//
// Test der Klasse zur Verwaltung der Mitarbeiter einer Abteilung
//
// Autor: Bernhard Zimmermann
// Version 1.0: 19.06.1997
// Änderung:    08.10.1997
//   Anpassungen für Visual C++ 5
// Änderung:    26.05.2007
//   Anpassungen für Visual C++ 2005
// Änderung:    23.06.2008
//   Anpassungen bezüglich der nach Berufsgruppen sortierten Ausgabe 
//   der Abteilungsmitarbeiter 
// Änderung:    29.06.2009
//   Abteilungsbezeichnung mit beliebiger Länge 
// Änderung:	26.11.2016
//	- Abgeleitete Abteilung 'TAbteil' testet nun Member auf virtual
//	- Test auf versteckten CCTOR hinzugefügt (analog zu ASSIGN manuell zu prüfen)
//	- assertions für Abteilungsnamen hinzugefügt
//	- Test auf Nullzeiger-Zeichenketten für 'bezeichnung' hinzugefügt
//  - Rückgabeadressen einfuegen/loeschen werden durch assertions überprüft
//	- Test auf Korrektheit "Löschen nicht vorhandener MA" hinzugefügt
// Änderung:	26.11.2016 (K. Ludwig)
//	- Adresskomponenten entfernt
// -----------------------------------------------------------------------------

// Muss ggf. lokal installiert werden: (https://vld.codeplex.com/)
//#include <C:\Program Files (x86)\Visual Leak Detector\include\vld.h> 
#include <cassert>
#include "Abteil.h"

int main(void)
{
	Sekretaer
		sekr1(7, 1750, "Spanisch");
	Sekretaer
		sekr2(8, 1800, "Englisch");
	Chefin chefin1(sekr1, 17, 4700, "Vertrieb");
	Chefin chefin2(18, 4300, "Einkauf");

	{
		Abteilung s(0);
		assert(! strcmp(s.getBezeichnung(), ""));
		s.ausgeben(std::cout); std::cout << std::endl;
	}

	// Test der beliebig langen Abteilungsbezeichnung
	Abteilung s0;
	assert(! strcmp(s0.getBezeichnung(), ""));
	s0.bezeichnungAendern(0);
	assert(! strcmp(s0.getBezeichnung(), ""));
	std::cout << s0 << std::endl;
	
	Abteilung s1("Abteilung S1");
	std::cout << s1 << std::endl;
	{
		s0.bezeichnungAendern("Die Abteilung S0");
		assert(! strcmp(s0.getBezeichnung(), "Die Abteilung S0"));
		std::cout << s0 << std::endl;
		s1.bezeichnungAendern("S1");
		std::cout << s1 << std::endl;
		Abteilung s2("S2 Abteilung");
		std::cout << s2 << std::endl;
	}
	std::cout << s0 << std::endl;
	std::cout << s1 << std::endl;

	Abteilung s3("S3");
	Abteilung s6("S6");
	
	//s3 = s6; // nicht erlaubt
	//Abteilung s7(s3); // nicht erlaubt
	{
		Mitarbeiter mit1(1, 3200);
		Mitarbeiter mit2(2, 3350);
		Mitarbeiter mit3(3, 3120);

		std::cout << s6 << std::endl;
		assert(s6.loeschen(8888) == 0);	// nicht vorhandenen loeschen
		assert(s6.einfuegen(mit1) == &mit1);             // Abteilung s6 aufbauen
		assert(s6.einfuegen(mit1) == 0);
		assert(s6.einfuegen(chefin1) == &chefin1);
		assert(s6.einfuegen(mit1) == 0);
		assert(s6.einfuegen(sekr1) == &sekr1);
		assert(s6.einfuegen(mit2) == &mit2);
		assert(s6.einfuegen(sekr2) == &sekr2);
		assert(s6.einfuegen(chefin2) == &chefin2);
		assert(s6.einfuegen(mit3) == &mit3);
		assert(s6.einfuegen(mit3) == 0);
		assert(s6.einfuegen(mit3) == 0);
		std::cout << s6 << std::endl;

		assert(s6.loeschen(3) == &mit3);                 // Ersten Mitarbeiter loeschen
		std::cout << s6 << std::endl;
		assert(s6.loeschen(1) == &mit1);                 // Letzten Mitarbeiter loeschen
		std::cout << s6 << std::endl;
		sekr1.persNrAendern(47);
		assert(s3.einfuegen(*s6.loeschen(47)) == &sekr1); // Sekretaer wechselt die Abteilung
		std::cout << s3 << std::endl;
		std::cout << s6 << std::endl;
		assert(s6.loeschen(17) == &chefin1);                // Die Chefinnen verlassen das sinkende Schiff
		assert(s6.loeschen(17) == 0);  
		assert(s6.loeschen(18) == &chefin2);  
		std::cout << s3 << std::endl;
		std::cout << s6 << std::endl;
		assert(s3.einfuegen(*s6.loeschen(8)) == &sekr2);  // Nach dem Aufräumen wechselt der letzte Sekretaer und
		assert(s3.einfuegen(*s6.loeschen(2)) == &mit2);  // der letzte gemeine Mitarbeiter die Abteilung
		std::cout << s3 << std::endl;
		std::cout << s6 << std::endl;
		assert(s3.loeschen(2) == &mit2);    
		std::cout << s3 << std::endl;
		std::cout << s6 << std::endl;
	}

	std::cout << s3 << std::endl; 
	std::cout << s6 << std::endl;

	return 0; 
}


