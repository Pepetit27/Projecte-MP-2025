#include "Fitxa.h"

Fitxa::Fitxa()
{
	m_color = COLOR_NEGRE;
	m_tipus = TIPUS_NORMAL;
	m_numMoviments = 0;
}
Fitxa::Fitxa(ColorFitxa color, TipusFitxa tipus, Posicio posicioFitxa)
{
	m_color = color;
	m_tipus = tipus;
	m_posicio = posicioFitxa;
	m_numMoviments = 0;
}
ColorFitxa Fitxa::getColor() const
{
	return m_color;
}
TipusFitxa Fitxa::getTipus() const
{
	return m_tipus;
}
Posicio Fitxa::getPosicio() const
{
	return m_posicio;
}

void Fitxa::afegirMoviment(const Posicio& moviment)
{
	m_moviments[m_numMoviments].setOrigen(m_posicio);
	m_moviments[m_numMoviments].setDesti(moviment);
	m_numMoviments++;
}
Moviment Fitxa::getMoviment(int i) const
{
	return m_moviments[i];
}
