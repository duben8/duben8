#pragma once
#include "structures/array/array.h"
#include "EnumScenar.h"
#include <algorithm>
#include <cstdlib>
using namespace structures;
class Scenar
{
private : 
	Array<short int>* pomery;
	Array<short int>* scenar;
	EnumScenar typ;
	size_t pocet_;
public:
	Scenar(EnumScenar type, size_t pocet);
	Scenar(Array<short int>* ratio);
	void nezamiesanyScenar();
	void zamiesaj();
	Array<short int>* akePomery();
	Array<short int>* celyScenar();
	short int operator[](int index);
	EnumScenar getTyp();
	size_t getPocet();
	~Scenar();
};

