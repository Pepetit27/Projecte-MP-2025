#pragma once
#include "Posicio.h"
class Moviment
{
public:
	Moviment();
	Moviment(const Posicio& origen, const Posicio& desti);
	Moviment(const Moviment& moviment);
	~Moviment();
	const Posicio& getOrigen() const;
	const Posicio& getDesti() const;
	bool esValid() const;
	void setOrigen(const Posicio& origen);
	void setDesti(const Posicio& desti);
	void setValid(bool valid);
	Moviment& operator=(const Moviment& moviment);
private:
	Posicio m_origen;
	Posicio m_desti;
};

