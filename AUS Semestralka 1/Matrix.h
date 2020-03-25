#pragma once
using namespace std;
class Matrix 
{
public:
	Matrix() {
	};
	virtual int get(int indexR, int indexS) = 0;
	virtual void set(int indexR, int indexS , int data) = 0;
	virtual size_t riadkySize() = 0;
	virtual size_t stlpceSize() = 0;
};

