#pragma once
#include "Matrix.h"
#include "structures/array/array.h"
#include "structures/ds_routines.h"
class PolePoli : public Matrix
{
private:
	structures::Array<structures::Array<int>*>* pole;
	size_t riadky;
	size_t stlpce;
public:
	PolePoli(int pocetR , int pocetS);
	int get(int indexR, int indexS);
	void set(int indexR, int indexS, int data);
	size_t riadkySize();
	size_t stlpceSize();
	~PolePoli();
};

