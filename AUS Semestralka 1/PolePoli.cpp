#include "PolePoli.h"

PolePoli::PolePoli(int pocetR, int pocetS) :
	Matrix::Matrix()
{
	riadky = pocetR;
	stlpce = pocetS;
	pole = new structures::Array< structures::Array<int>*>(pocetR);
	for (int i = 0; i < static_cast<int>(pole->size()); i++) {
		(*pole)[i] = new structures::Array<int>(pocetS);
	}
}

int PolePoli::get(int indexR, int indexS)
{
	structures::DSRoutines::rangeCheckExcept(indexR, pole->size(), "Neplatny index riadku v PolePoli::get index: " + indexR);
	structures::Array<int>* riadok = (*pole)[indexR];
	structures::DSRoutines::rangeCheckExcept(indexS, riadok->size(), "Neplatny index stlpca v PolePoli::get index: " + indexS);
	return (*riadok)[indexS];
}

void PolePoli::set(int indexR, int indexS, int data)
{
	structures::DSRoutines::rangeCheckExcept(indexR, pole->size(), "Neplatny index riadku v PolePoli::get index: " + indexR);
	structures::Array<int>* riadok = (*pole)[indexR];
	structures::DSRoutines::rangeCheckExcept(indexS, riadok->size(), "Neplatny index stlpca v PolePoli::get index: " + indexS);
	(*riadok)[indexS] = data;
}

size_t PolePoli::riadkySize()
{
	return riadky;
}

size_t PolePoli::stlpceSize()
{
	return stlpce;
}

PolePoli::~PolePoli()
{
	for (int i = 0; i < static_cast<int>(pole->size()); i++) {
		delete (*pole)[i];
	}
	delete pole;
}
