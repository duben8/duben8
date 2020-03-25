#include "JednoPoleMatrix.h"

JednoPoleMatrix::JednoPoleMatrix(size_t pocetRiadkov, size_t pocetStlpcov) :
Matrix::Matrix()
{
	pole = new structures::Array<int>(pocetRiadkov * pocetStlpcov);
	riadky = pocetRiadkov;
	stlpce = pocetStlpcov;
}

int JednoPoleMatrix::get(int indexR, int indexS)
{
	structures::DSRoutines::rangeCheckExcept(indexR, riadky, "Neplatny riadok v JednoPoleMatrix::get index riadku: " + indexR);
	structures::DSRoutines::rangeCheckExcept(indexS, stlpce, "Neplatny stlpec v JednoPoleMatrix::get index stlpca: " + indexS);
	return (*pole)[indexR * static_cast<int>(stlpce) + static_cast<int>(indexS)];
}

void JednoPoleMatrix::set(int indexR, int indexS, int data)
{
	structures::DSRoutines::rangeCheckExcept(indexR, riadky, "Neplatny riadok v JednoPoleMatrix::get index riadku: " + indexR);
	structures::DSRoutines::rangeCheckExcept(indexS, stlpce, "Neplatny stlpec v JednoPoleMatrix::get index stlpca: " + indexS);
	(*pole)[indexR * static_cast<int>(stlpce) + static_cast<int>(indexS)] = data;
}

size_t JednoPoleMatrix::riadkySize()
{
	return riadky;
}

size_t JednoPoleMatrix::stlpceSize()
{
	return stlpce;
}

JednoPoleMatrix::~JednoPoleMatrix()
{
	delete pole;
	riadky = 0;
	stlpce = 0;
}
