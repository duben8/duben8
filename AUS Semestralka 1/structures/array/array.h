#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../ds_routines.h"

namespace structures 
{
	
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T> 
	class Array	: public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(const size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(const Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();
		
		/// <summary> Operacia klonovania. Vytvori a vrati duplikat pola. </summary>
		/// <returns> Ukazovatel na vytvoreny klon pola. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Struktura (pole), z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, vstupny parameter nie je Array. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		Structure& operator=(const Structure& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Pole, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa toto pole nachadza po priradeni. </returns>
		Array<T>& operator=(const Array<T>& other);

		/// <summary> Operator porovnania. </summary>
		/// <param name = "other"> Pole, s ktorym sa ma porovnat. </param>
		/// <returns> true, ak su polia rovnake, false inak. </returns>
		bool operator==(const Array<T>& other) const;
		
		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		T& operator[](const int index);

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>  
		const T operator[](const int index) const;

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception> 
		static void copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(const int index) const;
	};

	template<typename T>
	Array<T>::Array(const size_t size) :
		vector_(new Vector(size * sizeof(T))),
		size_(size)
	{
	}

	template<typename T>
	Array<T>::Array(const Array<T>& other) :
		vector_(new Vector(*(other.vector_))), 
		size_(other.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		//TODO 02: Array
		delete this->vector_; // pouzijem delete lebo vector vznikal cez new 
		this->vector_ = nullptr; //nastavim vsetky tieto na nulu
		this->size_ = 0;
	}

	template<typename T>
	Structure* Array<T>::clone() const
	{
		return new Array<T>(*this);
	}

	template<typename T>
	Structure& Array<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Array<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	Array<T>& Array<T>::operator=(const Array<T>& other)
	{
		//TODO 02: Array
		//throw std::exception("Array<T>::operator=: Not implemented yet.");
		if (this != &other) { //porovnam ci neni ten isty
			if (this->size_ == other.size_) { //skontrolujem ci su rovnako velke lebo polia maju cely zivot rovnaku velkost takze nemozem tam dat nejaky s inou velkoustou
				*this->vector_ = *other.vector_; //priradim nasmu vector toho druheho
			}
			else {
				throw std::logic_error("Array<T>::operator=(const Array<T>& other) sizes are different");
			}
		}
		return *this;
	}
	
	template<typename T>
	size_t Array<T>::size() const
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](const int index)
	{
		int vectorIndex = mapFunction(index);
		byte* vectorPointer = vector_->getBytePointer(vectorIndex);
		T* typeVectorPointer = reinterpret_cast<T*>(vectorPointer);
		return *typeVectorPointer;
		//TODO 02: Array
		//throw std::exception("Array<T>::operator[]: Not implemented yet.");
		/*DSRoutines::rangeCheckExcept(index, size_, "Array<T>::operator[] : invalid index"); //zisti ci je to vobec v array
		int vectorIndex = mapFunction(index);

		return *(reinterpret_cast<T*>(vector_->getBytePointer(vectorIndex))); //zoberie z vectora byte pointer a pretypuje ho na T
		*/
	}

	template<typename T>
	const T Array<T>::operator[](const int index) const
	{
		//TODO 02: Array
		//throw std::exception("Array<T>::operator[]: Not implemented yet.");
		DSRoutines::rangeCheckExcept(index, this->size_, "Array<T>::operator[] : invalid index"); //zisti ci je to vobec v array
		int vectorIndex = this->mapFunction(index);

		return *reinterpret_cast<T*>(this->vector_->getBytePointer(vectorIndex)); //zoberie z vectora byte pointer a pretypuje ho na T
	}

	template<typename T>
	inline bool Array<T>::operator==(const Array<T>& other) const
	{
		//TODO 02: Array
		//throw std::exception("Array<T>::operator==: Not implemented yet.");
		return (*this->vector_ == *other.vector_); //porovnam iba ci sa ich vectory rovnaju
	}

	template<typename T>
	void Array<T>::copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length)
	{
		//TODO 02: Array
		//throw std::exception("Array<T>::copy: Not implemented yet.");
		DSRoutines::rangeCheckExcept(srcStartIndex, src.size(), "Invalid srcStartIndex at Array<T>::copy");
		DSRoutines::rangeCheckExcept(destStartIndex, dest.size(), "Invalid destStartIndex at Array<T>::copy");
		DSRoutines::rangeCheckExcept(length, src.size() - srcStartIndex + 1, "Invalid length for src at Array<T>::copy");
		DSRoutines::rangeCheckExcept(length, dest.size() - destStartIndex + 1, "Invalid length for dest at Array<T>::copy");
		Vector::copy(*src.vector_, src.mapFunction(srcStartIndex), *dest.vector_, dest.mapFunction(destStartIndex), dest.mapFunction(length));
	}

	template<typename T>
	inline int Array<T>::mapFunction(const int index) const
	{
		//TODO 02: Array
		//throw std::exception("Array<T>::mapFunction: Not implemented yet.");
		//DSRoutines::rangeCheckExcept(index, size_, "Invalid index in Array! current size: " + size_);
		return index * sizeof(T);
	}
}

