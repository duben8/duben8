#pragma once
#include "structures/list/list.h"
#include "structures/ds_routines.h"
namespace structures
{
	template<typename T>
	class TwoLinkedListItem : public DataItem<T>
	{
	public:
		TwoLinkedListItem(T data);

		TwoLinkedListItem(const TwoLinkedListItem<T>& other);

		~TwoLinkedListItem();

		void setNext(TwoLinkedListItem<T>* next);
		void setPrevious(TwoLinkedListItem<T>* previous);
		TwoLinkedListItem<T>* getPrevious();
		TwoLinkedListItem<T>* getNext();
	private:
		TwoLinkedListItem<T>* previous_;
		CyclicTwosidedLinkedList<T>* next_;
	};

	template<typename T>
	class CyclicTwosidedLinkedList : public List<T>
	{
	public:
		CyclicTwosidedLinkedList();
		CyclicTwosidedLinkedList(const CyclicTwosidedLinkedList<T>& other);
		~CyclicTwosidedLinkedList();
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		CyclicTwosidedLinkedList<T>& operator=(const CyclicTwosidedLinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;
		void add(const T& data) override;
		void insert(const T& data, const int index) override;
		bool tryRemove(const T& data) override;
		T removeAt(const int index) override;
		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;
		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;
	private:
		TwoLinkedListItem<T>* first_;
		TwoLinkedListItem<T>* last_;
		size_t size_;
	private:
		TwoLinkedListItem<T>* getItemAtIndex(int index) const;
	};

	template<typename T>
	inline TwoLinkedListItem<T>::TwoLinkedListItem(T data) :
		DataItem(data)
	{
		next_ = nullptr;
		previous_ = nullptr;
	}
	template<typename T>
	inline TwoLinkedListItem<T>::TwoLinkedListItem(const TwoLinkedListItem<T>& other)
		: DataItem(other)
	{
		next_ = other.next_;
		previous_ = other.previous_;
	}
	template<typename T>
	inline TwoLinkedListItem<T>::~TwoLinkedListItem()
	{
		next_ = nullptr;
		previous_ = nullptr;
	}
	template<typename T>
	inline void TwoLinkedListItem<T>::setNext(TwoLinkedListItem<T>* next)
	{
		next_ = next;
	}
	template<typename T>
	inline void TwoLinkedListItem<T>::setPrevious(TwoLinkedListItem<T>* previous)
	{
		previous_ = previous;
	}
	template<typename T>
	inline TwoLinkedListItem<T>* TwoLinkedListItem<T>::getPrevious()
	{
		return previous_;
	}
	template<typename T>
	inline TwoLinkedListItem<T>* TwoLinkedListItem<T>::getNext()
	{
		return next_;
	}
	template<typename T>
	inline CyclicTwosidedLinkedList<T>::CyclicTwosidedLinkedList() :
		List<T>::List(), first_(nullptr) , last_(nullptr)
	{
	}

	template<typename T>
	inline CyclicTwosidedLinkedList<T>::CyclicTwosidedLinkedList(const CyclicTwosidedLinkedList<T>& other):
		CyclicTwosidedLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline CyclicTwosidedLinkedList<T>::~CyclicTwosidedLinkedList()
	{
		this->clear();
	}

	template<typename T>
	inline Structure* CyclicTwosidedLinkedList<T>::clone() const
	{
		return new CyclicTwosidedLinkedList(*this);
	}

	template<typename T>
	inline size_t CyclicTwosidedLinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& CyclicTwosidedLinkedList<T>::operator=(const List<T>& other)
	{
		if (*this != other) {
			*this = dynamic_cast<const CyclicTwosidedLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline CyclicTwosidedLinkedList<T>& CyclicTwosidedLinkedList<T>::operator=(const CyclicTwosidedLinkedList<T>& other)
	{
		if (this != &other)
		{
			clear();
			for (T item : other) {
				add(item);
			}
		}
		return *this;
	}

	template<typename T>
	inline T& CyclicTwosidedLinkedList<T>::operator[](const int index)
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T CyclicTwosidedLinkedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void CyclicTwosidedLinkedList<T>::add(const T& data)
	{
		TwoLinkedListItem<T>* item = new TwoLinkedListItem<T>(data);
		if (size_ == 0) {
			first_ = item;
			last_ = item;
			item->setNext(item);
			item->setPrevious(item);
		}
		else {
			last_->setNext(item);
			item->setNext(first_);
			last_ = item;
		}
		size_++;
	}

	template<typename T>
	inline void CyclicTwosidedLinkedList<T>::insert(const T& data, const int index)
	{
		TwoLinkedListItem<T>* pridavany = new TwoLinkedListItem<T>(data);
		TwoLinkedListItem<T>* item = getItemAtIndex(index);
		item->getPrevious()->setNext(pridavany);
		pridavany->setPrevious(item->getPrevious());
		item->setPrevious(pridavany);
		pridavany->setNext(item);
		size_++;
	}

	template<typename T>
	inline bool CyclicTwosidedLinkedList<T>::tryRemove(const T& data)
	{
		int i = getIndexOf(data);
		if (i != -1) {
			removeAt(i);
			return true;
		}
		else {
			return false;
		}
		
	}

	template<typename T>
	inline T CyclicTwosidedLinkedList<T>::removeAt(const int index)
	{
		TwoLinkedListItem<T>* item = getItemAtIndex(index);
		T data = item->accessData();
		item->getPrevious()->setNext(item->getNext);
		item->getNext()->setPrevious(item->getPrevious);
		delete item;
		return data;
	}

	template<typename T>
	inline int CyclicTwosidedLinkedList<T>::getIndexOf(const T& data)
	{
		TwoLinkedListItem<T>* prvok = first_;
		int index = 0;
		while (prvok != nullptr) {
			if (prvok->accessData() == data) {
				return index;
			}
			index++;
			prvok = prvok->getNext();
		}
		return -1;
	}

	template<typename T>
	inline void CyclicTwosidedLinkedList<T>::clear()
	{
		while (first_ != nullptr) {
			TwoLinkedListItem<T>* item = first_->getNext();
			delete first_;
			first_ = item;
		}
		size_ = 0;
		last_ = nullptr;
	}

	template<typename T>
	inline TwoLinkedListItem<T>* CyclicTwosidedLinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index at CyclicTwosidedLinkedList<T>::getItemAtIndex");
		TwoLinkedListItem<T>* item = first_;
		int indexh = 0;
		while (indexh != index) {
			item = item->getNext();
			indexh++;
		}
		return item;
	}

}