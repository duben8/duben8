#pragma once
#include "Matrix.h"
#include "structures/array/array.h"
#include "structures/ds_routines.h"
class JednoPoleMatrix : public Matrix
{
private:
	structures::Array<int>* pole;
	size_t riadky;
	size_t stlpce;
	
public:
	JednoPoleMatrix(size_t pocetRiadkov, size_t pocetStlpcov);
	int get(int indexR, int indexS);
	void set(int indexR, int indexS , int data);
	size_t riadkySize();
	size_t stlpceSize();
	~JednoPoleMatrix();
};

