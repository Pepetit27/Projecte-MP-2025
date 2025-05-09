#pragma once
#include "Moviment.h"
#include <iostream>

#define MAX_MOVIMENTS 100

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
} ColorFitxa;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

class Fitxa  
{  
public:  
   Fitxa();  
   Fitxa(ColorFitxa color, TipusFitxa tipus, Posicio posicioFitxa);  
   ColorFitxa getColor() const; 
   TipusFitxa getTipus() const; 
   Posicio getPosicio() const; 
	int getnMoviments() const { return m_numMoviments; } 
   void afegirMoviment(const Posicio& moviment);
   Moviment getMoviment(int i) const { return m_moviments[i]; }
   

private:  
   ColorFitxa m_color;  
   TipusFitxa m_tipus;  
   Moviment m_moviments[MAX_MOVIMENTS];  
   Posicio m_posicio;
   int m_numMoviments;
};

