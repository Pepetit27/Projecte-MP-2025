#include "Tauler.h"

Tauler::Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = Fitxa(COLOR_NEGRE, TIPUS_EMPTY, Posicio(i, j));

			if ((i == 0 || i == 2) && ((j%2)==0))
			{
				m_tauler[i][j] = Fitxa(COLOR_BLANC, TIPUS_NORMAL, Posicio(i, j));
			}else
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
//FOR
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

	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (!fitxer.is_open())
	{
		cerr << "Error: No s'ha pogut obrir el fitxer " << nomFitxer << endl;
		return;
	}
	while (!fitxer.eof())
	{
		Posicio posicio;
		char tipus;
		fitxer >> tipus;
		switch(tipus)
		{
		case('X'):
			
			char LletraCol, int fila, columna;
			fitxer >> LletraCol >> fila;
			columna = lletraToIndex(LletraCol);
			posicio = Posicio(fila - 1, columna);
			m_tauler[fila-1][columna] = Fitxa(COLOR_NEGRE, TIPUS_NORMAL, posicio);
			break;
		case('O'):
			char LletraCol, int fila, columna;
			fitxer >> LletraCol >> fila;
			columna = lletraToIndex(LletraCol);
			posicio = Posicio(fila - 1, columna);
			m_tauler[fila-1][columna] = Fitxa(COLOR_BLANC, TIPUS_NORMAL, posicio);
			break;
		case('D'):
			char LletraCol, int fila, columna;
			fitxer >> LletraCol >> fila;
			columna = lletraToIndex(LletraCol);
			posicio = Posicio(fila - 1, columna);
			m_tauler[fila-1][columna] = Fitxa(COLOR_BLANC, TIPUS_DAMA, posicio);
			break;
		case('R'):
			char LletraCol, int fila, columna;
			fitxer >> LletraCol >> fila;
			columna = lletraToIndex(LletraCol);
			posicio = Posicio(fila - 1, columna);
			m_tauler[fila-1][columna] = Fitxa(COLOR_NEGRE, TIPUS_DAMA, posicio);
			break;
		default:
			cout << "Error: Tipus de fitxa desconegut " << tipus << endl;
			break;
		}
	}
	fitxer.close();
}
void Tauler::actualitzaMovimentsValids()
{
	if(m_torn)
	{
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				if (m_tauler[i][j].getColor() == COLOR_BLANC)
				{
					
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

				}
			}
		}
	}
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	return false;
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
}

string Tauler::toString() const
{
	return string();
}
