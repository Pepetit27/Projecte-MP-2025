#ifndef TAULER_H
#define TAULER_H
#include <iostream>     // per cout, cerr
#include <fstream>      // per ifstream
#include <sstream>      // per istringstream
#include <string>
#include "Fitxa.h"
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
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;
	void fitxesEliminades(const Posicio& origen, const Posicio& desti);
private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
	int m_numFitxesBlanc;
	int m_numFitxesNegre;
	bool m_torn;
}; 
#endif // TAULER_H

Tauler::Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = Fitxa(COLOR_NEGRE, TIPUS_EMPTY, Posicio(i, j));

			if ((i == 0 || i == 2) && ((j % 2) == 0))
			{
				m_tauler[i][j] = Fitxa(COLOR_BLANC, TIPUS_NORMAL, Posicio(i, j));
			}
			else
				if ((i == 1) && ((j % 2) == 1))
				{
					m_tauler[i][j] = Fitxa(COLOR_BLANC, TIPUS_NORMAL, Posicio(i, j));
				}

			if ((i == 7 || i == 5) && ((j % 2) == 0))
			{
				m_tauler[i][j] = Fitxa(COLOR_NEGRE, TIPUS_NORMAL, Posicio(i, j));
			}
			else
				if ((i == 6) && ((j % 2) == 1))
				{
					m_tauler[i][j] = Fitxa(COLOR_NEGRE, TIPUS_NORMAL, Posicio(i, j));
				}

		}
	}

	m_numFitxesBlanc = 12;
	m_numFitxesNegre = 12;
	m_torn = true; // Blanc comença
}
Tauler::~Tauler()
{

}
int Tauler::lletraToIndex(char LletraCol)
{
	switch (LletraCol)
	{
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	default:
		cout << "Error: lletra de columna no valida" << endl;
		return -1;
	}
	return 0;
}

void Tauler::inicialitza(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);
	if (!fitxer.is_open())
	{
		cerr << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
		return;
	}

	string linia;
	while (getline(fitxer, linia))
	{
		// Ignora línies buides o comentaris
		if (linia.empty() || linia[0] == '#')
			continue;

		istringstream iss(linia);
		char tipus, LletraCol;
		int fila;

		if (!(iss >> tipus >> LletraCol >> fila))
		{
			cerr << "Error: Format de línia incorrecte -> " << linia << endl;
			continue;
		}

		int columna = lletraToIndex(LletraCol);
		fila -= 1; // Convertim a índex base 0

		// Comprovació de límits del tauler
		if (fila < 0 || fila >= N_FILES-1 || columna < 0 || columna >= N_COLUMNES-1)
		{
			cerr << "Error: Coordenades fora de rang -> " << linia << endl;
			continue;
		}

		Posicio posicio(fila, columna);

		switch (tipus)
		{
		case 'X':
			m_tauler[fila][columna] = Fitxa(COLOR_NEGRE, TIPUS_NORMAL, posicio);
			break;
		case 'O':
			m_tauler[fila][columna] = Fitxa(COLOR_BLANC, TIPUS_NORMAL, posicio);
			break;
		case 'D':
			m_tauler[fila][columna] = Fitxa(COLOR_BLANC, TIPUS_DAMA, posicio);
			break;
		case 'R':
			m_tauler[fila][columna] = Fitxa(COLOR_NEGRE, TIPUS_DAMA, posicio);
			break;
		default:
			cerr << "Error: Tipus de fitxa desconegut -> " << tipus << endl;
			break;
		}
	}

	fitxer.close();
}

void Tauler::actualitzaMovimentsValids()
{
	if (m_torn)
	{
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				if (m_tauler[i][j].getColor() == COLOR_BLANC)
				{
					Posicio posicionsPossibles[MAX_POSICIONS_POSSIBLES];
					int nPosicions = 0;
					getPosicionsPossibles(Posicio(i, j), nPosicions, posicionsPossibles);
					for (int i = 0; i < nPosicions; i++)
					{
						m_tauler[i][i].afegirMoviment(posicionsPossibles[i]);
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				if (m_tauler[i][j].getColor() == COLOR_NEGRE)
				{
					Posicio posicionsPossibles[MAX_POSICIONS_POSSIBLES];
					int nPosicions = 0;
					getPosicionsPossibles(Posicio(i, j), nPosicions, posicionsPossibles);
					for (int i = 0; i < nPosicions; i++)
					{
						m_tauler[i][i].afegirMoviment(posicionsPossibles[i]);
					}
				}
			}
		}
	}
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	actualitzaMovimentsValids();
	int filaOrigen = origen.getFila();
	int columnaOrigen = origen.getColumna();
	int filaDesti = desti.getFila();
	int columnaDesti = desti.getColumna();
	int i = 0;
	bool trobat = false;
	while (i < m_tauler[filaOrigen][columnaOrigen].getnMoviments() && !trobat)
	{
		if (m_tauler[filaOrigen][columnaOrigen].getMoviment(i).getDesti() == desti)
		{
			trobat = true;
		}
		else
			i++;
	}
	if (trobat)
	{
		m_tauler[filaDesti][columnaDesti] = m_tauler[filaOrigen][columnaOrigen];
		m_tauler[filaOrigen][columnaOrigen] = Fitxa(COLOR_NEGRE, TIPUS_EMPTY, Posicio(filaOrigen, columnaOrigen));
		if(columnaDesti == 7 || columnaDesti == 0)
		{
			if (m_tauler[filaDesti][columnaDesti].getColor() == COLOR_BLANC)
				m_tauler[filaDesti][columnaDesti] = Fitxa(COLOR_BLANC, TIPUS_DAMA, Posicio(filaDesti, columnaDesti));
			else
				m_tauler[filaDesti][columnaDesti] = Fitxa(COLOR_NEGRE, TIPUS_DAMA, Posicio(filaDesti, columnaDesti));
		}
		return true;
	}
}

string Tauler::toString() const
{
	string taulerString;
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				if (m_tauler[i][j].getColor() == COLOR_BLANC && m_tauler[i][j].getTipus() == TIPUS_NORMAL)
					taulerString += 'O';
				else if (m_tauler[i][j].getColor() == COLOR_NEGRE && m_tauler[i][j].getTipus() == TIPUS_NORMAL)
					taulerString += 'X';
				else if (m_tauler[i][j].getTipus() == TIPUS_DAMA && m_tauler[i][j].getColor() == COLOR_NEGRE)
					taulerString += 'R';
				else if (m_tauler[i][j].getTipus() == TIPUS_DAMA && m_tauler[i][j].getColor() == COLOR_BLANC)
					taulerString += 'D';
				else
					taulerString += '_';
			}
			taulerString += '\n';
		}
}



void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
	nPosicions = 0;
	int fila = origen.getFila();
	int columna = origen.getColumna();
	// Comprovar si la fitxa és blanca o negra
	ColorFitxa colorFitxa = m_tauler[fila][columna].getColor();
	TipusFitxa tipusFitxa = m_tauler[fila][columna].getTipus();
	// Comprovar si la fitxa és dama
	if (tipusFitxa == TIPUS_DAMA)
	{
		if (m_tauler[fila + 1][columna - 1].getTipus() == TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila + 1, columna - 1);
			nPosicions++;
		}
		if (m_tauler[fila + 1][columna + 1].getTipus() == TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila + 1, columna + 1);
			nPosicions++;
		}
		if (m_tauler[fila - 1][columna - 1].getTipus() == TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila - 1, columna - 1);
			nPosicions++;
		}
		if (m_tauler[fila - 1][columna + 1].getTipus() == TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila - 1, columna + 1);
			nPosicions++;
		}

		if (m_tauler[fila + 2][columna - 2].getTipus() == TIPUS_EMPTY && m_tauler[fila + 1][columna - 1].getTipus() != TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila + 2, columna - 2);
			nPosicions++;
			getPosicionsPossibles(Posicio(fila + 2, columna - 2), nPosicions, posicionsPossibles);

		}
		if (m_tauler[fila + 2][columna + 2].getTipus() == TIPUS_EMPTY && m_tauler[fila + 1][columna + 1].getTipus() != TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila + 2, columna + 2);
			nPosicions++;
			getPosicionsPossibles(Posicio(fila + 2, columna + 2), nPosicions, posicionsPossibles);
		}
		if (m_tauler[fila - 2][columna - 2].getTipus() == TIPUS_EMPTY && m_tauler[fila - 1][columna - 1].getTipus() != TIPUS_EMPTY )
		{
			posicionsPossibles[nPosicions] = Posicio(fila - 2, columna - 2);
			nPosicions++;
			getPosicionsPossibles(Posicio(fila - 2, columna - 2), nPosicions, posicionsPossibles);
		}
		if (m_tauler[fila - 2][columna + 2].getTipus() == TIPUS_EMPTY && m_tauler[fila - 1][columna + 1].getTipus() != TIPUS_EMPTY)
		{
			posicionsPossibles[nPosicions] = Posicio(fila - 2, columna + 2);
			nPosicions++;
			getPosicionsPossibles(Posicio(fila - 2, columna + 2), nPosicions, posicionsPossibles);
		}
	}
	else
	{
		if (colorFitxa == COLOR_BLANC)// Afegir moviments possibles per a la fitxa blanca
		{
			if (m_tauler[fila + 1][columna - 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPosicions] = Posicio(fila + 1, columna - 1);
				nPosicions++;
			}
			if (m_tauler[fila + 1][columna + 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPosicions] = Posicio(fila + 1, columna + 1);
				nPosicions++;
			}
			if (m_tauler[fila + 2][columna - 2].getTipus() == TIPUS_EMPTY && m_tauler[fila + 1][columna - 1].getTipus() == TIPUS_EMPTY && m_tauler[fila + 1][columna - 1].getColor() == COLOR_NEGRE)
			{
				posicionsPossibles[nPosicions] = Posicio(fila + 2, columna - 2);
				nPosicions++;
				getPosicionsPossibles(Posicio(fila + 2, columna - 2), nPosicions, posicionsPossibles);
			}
			if (m_tauler[fila + 2][columna + 2].getTipus() == TIPUS_EMPTY && m_tauler[fila + 1][columna + 1].getTipus() != TIPUS_EMPTY && m_tauler[fila + 1][columna - 1].getColor() == COLOR_NEGRE)
			{
				posicionsPossibles[nPosicions] = Posicio(fila + 2, columna + 2);
				nPosicions++;
				getPosicionsPossibles(Posicio(fila + 2, columna + 2), nPosicions, posicionsPossibles);
			}
			
		}
		else// Afegir moviments possibles per a la fitxa negra
		{
			if (m_tauler[fila - 1][columna - 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPosicions] = Posicio(fila - 1, columna - 1);
				nPosicions++;
			}
			if (m_tauler[fila - 1][columna + 1].getTipus() == TIPUS_EMPTY)
			{
				posicionsPossibles[nPosicions] = Posicio(fila - 1, columna + 1);
				nPosicions++;
			}
			if (m_tauler[fila - 2][columna - 2].getTipus() == TIPUS_EMPTY && m_tauler[fila - 1][columna - 1].getTipus() != TIPUS_EMPTY && m_tauler[fila + 1][columna - 1].getColor() == COLOR_BLANC)
			{
				posicionsPossibles[nPosicions] = Posicio(fila - 2, columna - 2);
				fitxesEliminades(origen,posicionsPossibles[nPosicions]);
				nPosicions++;
				
				getPosicionsPossibles(Posicio(fila - 2, columna - 2), nPosicions, posicionsPossibles);
			}
			if (m_tauler[fila - 2][columna + 2].getTipus() == TIPUS_EMPTY && m_tauler[fila - 1][columna + 1].getTipus() != TIPUS_EMPTY && m_tauler[fila + 1][columna - 1].getColor() == COLOR_BLANC)
			{
				posicionsPossibles[nPosicions] = Posicio(fila - 2, columna + 2);
				nPosicions++;
				getPosicionsPossibles(Posicio(fila - 2, columna + 2), nPosicions, posicionsPossibles);
			}
		}
	}
}

void Tauler::fitxesEliminades(const Posicio& origen, const Posicio& desti)
{
	   
}
