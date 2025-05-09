#include "Moviment.h"

const Posicio& Moviment::getOrigen() const
{
	return m_origen;
}

const Posicio& Moviment::getDesti() const
{
	return m_desti;
}



void Moviment::setOrigen(const Posicio& origen)
{
	m_origen = origen;
}

void Moviment::setDesti(const Posicio& desti)
{
	m_desti = desti;
}



Moviment::Moviment()
{
	m_origen = Posicio();
	m_desti = Posicio();
}

Moviment::Moviment(const Posicio& origen, const Posicio& desti)
{
	m_origen = origen;
	m_desti = desti;
}

Moviment::Moviment(const Moviment& moviment)
{
	m_origen = moviment.m_origen;
	m_desti = moviment.m_desti;
}

Moviment::~Moviment()
{
	// Destructor
}

Moviment& Moviment::operator=(const Moviment& moviment)
{
	if (this != &moviment)
	{
		m_origen = moviment.m_origen;
		m_desti = moviment.m_desti;
	}
	return *this;
}

