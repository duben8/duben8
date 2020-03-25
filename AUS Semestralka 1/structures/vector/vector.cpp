#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)), //1 kvoli tomu ûe nastavujem bajt
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) : //kopirovaci konötruktor
		Vector(other.size_) //nastavim mu j
	{
		//TODO 01: Vector
		memory_ = memcpy(memory_, other.memory_, other.size_);
	}

	Vector::~Vector()
	{
		free(memory_); //uvolni alokovanu pam‰ù
		memory_ = nullptr; //len aby neukazoval niekam 
		size_ = 0;
		//TODO 01: Vector
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this); //netreba niË iba kopirovacÌ konötruktor s·m na seba

	}

	size_t Vector::size() const //getter
	{
		return size_;
	}

	Structure& Vector::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other); //ötrukt˙ru sk˙sim pretypovaù na vektor ak pojde

		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		//TODO 01: Vector
		if (this != &other) //skontrolujem Ëi neni other rovnaky ako tento
		{
			size_ = other.size_;//priradim mu velkost
			memory_ = realloc(memory_, other.size_);
			memory_ = memcpy(memory_, other.memory_, size_);
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const //porovnavaci operator 
	{
		return size_ == other.size_ && memcmp(memory_, other.memory_, other.size_) == 0; // nepisem v ife lebo takto to bude efektivnejsie a ani to netreba 
	}

	byte& Vector::operator[](const int index) //vrati odkaz
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!"); //skontroluje Ëi je v rozsahu size inak exception
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const //vrati hodnotu akoûe kopiu a je tu const Ëiûe sa nam to nemeni
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!"); //skontroluje Ëi je v rozsahu size inak exception
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest) //skopiruje v this vectore od index count bytov do byte pointeru v dest
	{
		//TODO 01: Vector
		//throw std::exception("Vector::readBytes: Not implemented yet.");
		DSRoutines::rangeCheckExcept(index, this->size_, "Vector::invalid index"); //skontroluje ci index je v rozsahu od zaciatku po size_ ( velkost)
		DSRoutines::rangeCheckExcept(index + count, this->size_ + 1, "Vector::readbytes :: invalid count"); //zisti ci od indexu + kolko chcem readnut je stale v nasej size_ (velkosti)
		if (this->getBytePointer(index + count - 1) < &dest ||    //zistenie prekryvania , prva podmienka je ze ak je koniec source segmentu je pred zaciatkom cieloveho segmentu
			(&dest + count - 1 < this->getBytePointer(index))) { //druha (alebo) podmienka ze ci je zaciatok source segmentu az za koncom dest segmentu
			memcpy(&dest, this->getBytePointer(index), count); // v tomto pripade sa neprekryvaju a mozem memcpy
			
		}
		else {
			memmove(&dest, this->getBytePointer(index), count); //prekryvaju sa a musim memmove
		}
		return dest; // vrati dest
		
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)//DOMA
	{
		//TODO 01: Vector
		//throw std::exception("Vector::copy: Not implemented yet.");
		DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Vector index out of range.");
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Vector index out of range.");
		DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Vector index out of range.");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Vector index out of range.");
		if (&src == &dest &&
			((srcStartIndex <= destStartIndex && srcStartIndex + length > destStartIndex) ||
			(destStartIndex <= srcStartIndex && destStartIndex + length > srcStartIndex))) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		//TODO 01: Vector
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Vector!");
		return reinterpret_cast<byte*>(this->memory_) + index;
	}

}