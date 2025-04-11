#include "Fitxa.h"

Fitxa::Fitxa()
{
	m_color = COLOR_NEGRE;
	m_tipus = TIPUS_NORMAL;
}
Fitxa::Fitxa(ColorFitxa color, TipusFitxa tipus, Posicio posicioFitxa)
{
	m_color = color;
	m_tipus = tipus;
	m_posicio = posicioFitxa;
}
ColorFitxa Fitxa::getColor()
{
	return m_color;
}
TipusFitxa Fitxa::getTipus()
{
	return m_tipus;
}
Posicio Fitxa::getPosicio()
{
	return m_posicio;
}
