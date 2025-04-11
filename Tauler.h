#pragma once
#include "Fitxa.h"
#include <iostream>
#include <fstream>
#include <string>

#define N_FILES 8
#define N_COLUMNES 8
using namespace std;

class Tauler
{
public:

	Tauler();
	~Tauler();
	int lletraToIndex(char LletraCol);
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	string toString() const;
private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
	int m_numFitxesBlanc;
	int m_numFitxesNegre;
	bool m_torn;
};

