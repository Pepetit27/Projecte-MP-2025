#pragma once
#include <ostream>
using namespace std;
class Posicio
{
public:
	Posicio();
	Posicio(int fila, int columna);
	Posicio(const Posicio& posicio);
	~Posicio();
	int getFila() const;
	int getColumna() const;
	void setFila(int fila);
	void setColumna(int columna);
	
	bool operator==(const Posicio& posicio) const;
	friend ostream& operator<<(ostream& os, const Posicio& posicio);
	/*
	bool operator!=(const Posicio& posicio) const;
	Posicio& operator=(const Posicio& posicio);
	*/
private:
	int m_fila;
	int m_columna;
};

