#include "Posicio.h"


Posicio::Posicio()
{
	m_fila = 0;
	m_columna = 0;
}

Posicio::Posicio(int fila, int columna)
{
	m_fila = fila;
	m_columna = columna;
}

Posicio::Posicio(const Posicio& posicio)
{
	m_fila = posicio.m_fila;
	m_columna = posicio.m_columna;
}

Posicio::~Posicio()
{// Destructor
}
int Posicio::getFila() const
{
	return m_fila;
}
int Posicio::getColumna() const
{
	return m_columna;
}
void Posicio::setFila(int fila)
{
	m_fila = fila;
}
void Posicio::setColumna(int columna)
{
	m_columna = columna;
}

bool Posicio::operator==(const Posicio& posicio) const
{
	return (m_fila == posicio.m_fila && m_columna == posicio.m_columna);
}

ostream& operator<<(ostream& os, const Posicio& posicio)
{
	os << "(" << posicio.getFila() << ", " << posicio.getColumna() << ")";
	return os;
	// TODO: insert return statement here
}


/*
bool Posicio::operator!=(const Posicio& posicio) const
{
	return (m_fila != posicio.m_fila || m_columna != posicio.m_columna);
}
Posicio& Posicio::operator=(const Posicio& posicio)
{
	if (this != &posicio)
	{
		m_fila = posicio.m_fila;
		m_columna = posicio.m_columna;
	}
	return *this;
}
*/
