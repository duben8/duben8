#include "Scenar.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace structures;
Scenar::Scenar(EnumScenar type, size_t pocet)
	
{
	if (pocet % 100 != 0) { throw std::invalid_argument("Musis zadat stovkovy nasobok"); }
	pocet_ = pocet;
	this->typ = type;
	pomery = new Array<short int>(100);
	switch (typ) {
	case A_List :
		for (int i = 0; i < 15; i++) {
			(*pomery)[i] = std::rand() % 3;
		}
		for (int i = 15; i < 30; i++) {
			(*pomery)[i] = std::rand() % 3 + 3;
		}
		for (int i = 30; i < 90; i++) {
			(*pomery)[i] = std::rand() % 2 + 6;
		}
		for (int i = 90; i < 100; i++) {
			(*pomery)[i] = 8;
		}
		break;
	case B_List :
		for (int i = 0; i < 30; i++) {
			(*pomery)[i] = std::rand() % 2;
		}
		for (int i = 30; i < 60; i++) {
			(*pomery)[i] = std::rand() % 2 + 3;
		}
		for (int i = 60; i < 90; i++) {
			(*pomery)[i] = std::rand() % 1 + 5;
		}
		for (int i = 90; i < 100; i++) {
			(*pomery)[i] = 8;
		}
		break;
	case C_List:
		for (int i = 0; i < 30; i++) {
			(*pomery)[i] = std::rand() % 2;
		}
		for (int i = 30; i < 60; i++) {
			(*pomery)[i] = std::rand() % 2 + 3;
		}
		for (int i = 60; i < 90; i++) {
			(*pomery)[i] = std::rand() % 1 + 5;
		}
		for (int i = 90; i < 100; i++) {
			(*pomery)[i] = 8;
		}
		break;
	case A_Queue: 
		for (int i = 0; i < 45; i++) {
			(*pomery)[i] = 0;
		}
		for (int i = 45; i < 90; i++) {
			(*pomery)[i] = 1;
		}
		for (int i = 90; i < 100; i++) {
			(*pomery)[i] = 2;
		}
		break;
	case B_Queue:
		for (int i = 0; i < 50; i++) {
			(*pomery)[i] = 0;
		}
		for (int i = 50; i < 75; i++) {
			(*pomery)[i] = 1;
		}
		for (int i = 75; i < 100; i++) {
			(*pomery)[i] = 2;
		}
		break;
	case A_Matrix:
		for (int i = 0; i < 75; i++) {
			(*pomery)[i] = 0;
		}
		for (int i = 75; i < 100; i++) {
			(*pomery)[i] = 1;
		}
		break;
	case B_Matrix:
		for (int i = 0; i < 25; i++) {
			(*pomery)[i] = 0;
		}
		for (int i = 25; i < 100; i++) {
			(*pomery)[i] = 1;
		}
		break;
	case Custom: 
		throw std::invalid_argument("Nie je znamy ziaden default scenar pre Custom");
	}


}

Scenar::Scenar(Array<short int>* ratio)
{
	if (ratio->size() != 100) { throw std::invalid_argument("Pomery musia byt udane 100 prvkovym polom!"); }
	pomery = new Array<short int>(*ratio);
	this->typ = Custom;
}

void Scenar::nezamiesanyScenar()
{
	scenar = new Array<short int>(pocet_);
	scenar->copy(*pomery, 0, *scenar, 0, 99);
	for (int i = 1; i < (static_cast<int>(pocet_))/100; i++) {
		Array<short int>::copy(*scenar, 0, *scenar, 100 * i - 1 , 99);
	}
}

void Scenar::zamiesaj()
{
	std::random_shuffle(&(*scenar)[0], &(*scenar)[pocet_ - 1]);

}

Array<short int>* Scenar::akePomery()
{
	return pomery;
}

Array<short int>* Scenar::celyScenar()
{
	return scenar;
}

short int Scenar::operator[](int index)
{
	return (*scenar)[index];
}

EnumScenar Scenar::getTyp()
{
	return typ;
}

size_t Scenar::getPocet()
{
	return pocet_;
}

Scenar::~Scenar()
{
	delete pomery;
	pomery = nullptr;
	delete scenar;
	scenar = nullptr;
}
