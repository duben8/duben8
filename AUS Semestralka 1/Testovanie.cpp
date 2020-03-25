#include "Testovanie.h"
#include <fstream>
#include <iostream>
#include <chrono>

size_t Testovanie::ListTest(List<int>* list_1, List<int>* list_2, const char* suborList_1, const char* suborList_2, EnumScenar sc, size_t pocet)
{
	Scenar* listSc = new Scenar(sc, pocet);
	size_t pocetnepl;
	pocetnepl = Testovanie::ListTest(list_1,list_2, suborList_1, suborList_2, listSc);
	delete listSc;
	return pocetnepl;
}

size_t Testovanie::ListTest(List<int>* list_1, List<int>* list_2, const char* suborList_1, const char* suborList_2, Scenar* listSc)
{
	if (!(listSc->getTyp() == A_List || listSc->getTyp() == B_List || listSc->getTyp() == C_List || listSc->getTyp() == Custom)) {
		throw std::logic_error("Typ Scenaru musi byt A_List , B_List , C_List alebo Custom!");
	}
	listSc->nezamiesanyScenar();
	listSc->zamiesaj();
	std::ofstream outfile;
	outfile.open(suborList_1);
	if (!outfile.is_open()) {
		throw std::exception("Chyba pri otvarani suboru pre list_1");
	}
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	size_t pocetNeplatnychOperacii = 0;
	for (size_t i = 0; i < listSc->getPocet() ; i++) {
		if ((*listSc)[static_cast<int>(i)] == 8) {
			if (list_1->size() != 0) {
				int data = (*list_1)[rand() % (list_1->size())];
				begin = std::chrono::steady_clock::now();
				list_1->getIndexOf(data);
				end = std::chrono::steady_clock::now();
			}
			else {
				pocetNeplatnychOperacii++;
			}
		}
		else {
			begin = std::chrono::steady_clock::now();
			if (!ListOperacia((*listSc)[static_cast<int>(i)], list_1)) { pocetNeplatnychOperacii++; };
			end = std::chrono::steady_clock::now();
		}
		
		outfile << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " , " << (*listSc)[static_cast<int>(i)] << " , " << i << " ," << endl;
	}
	outfile.close();
	outfile.open(suborList_2);
	for (size_t i = 0; i < listSc->getPocet(); i++) {
		if ((*listSc)[static_cast<int>(i)] == 8) {
			if (list_2->size() != 0) {
				int data = (*list_2)[rand() % (list_2->size())];
				begin = std::chrono::steady_clock::now();
				list_2->getIndexOf(data);
				end = std::chrono::steady_clock::now();
			}
			else {
				pocetNeplatnychOperacii++;
			}
		}
		else {
			begin = std::chrono::steady_clock::now();
			if (!ListOperacia((*listSc)[static_cast<int>(i)], list_2)) { pocetNeplatnychOperacii++; };
			end = std::chrono::steady_clock::now();
		}
		outfile << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " , " << (*listSc)[static_cast<int>(i)] << " , " << i << " ," << endl;
	}
	outfile.close();
	return pocetNeplatnychOperacii;
}

bool Testovanie::ListOperacia(short int operacia, List<int>* list)
{
	switch (operacia) {
	case 0:
		try {
			list->insert(rand() % 1000000, 0);
		}
		catch (out_of_range) {
			return false;
		}
		break;
	case 1:
		try {
			if (list->size() - 1 != 0) {
				list->insert(rand() % 1000000, rand() % (list->size() - 1) );
			}
		}
		catch (out_of_range) {
			return false;
		}
		break;
	case 2:
		list->add(5);
		break;
	case 3:
		try {
			list->removeAt(0);
		}
		catch (out_of_range) {
			return false;
		}
		break;
	case 4:
		try {
			list->removeAt(static_cast<int>(list->size()) - 1);
		}
		catch (out_of_range) {
			return false;
		}
		break;
	case 5:
		try {
			if (list->size() != 0) {
				list->removeAt(rand() % static_cast<int>(list->size()));
				return true;
			}
			else {
				return false;
			}
			
		}
		catch (out_of_range) {
			return false;
		}
		break;
	case 6:
		try {
			if (list->size() == 0) {
				return false;
			}
			if (list->size() == 1) {
				(*list)[0];
				return true;
			}
			(*list)[rand() % list->size() - 1];
			return true;
		}
		catch (out_of_range) {
			return false;
		}
		break;
	case 7:
		try {
			if (list->size() == 0) { return false; }
			if (list->size() == 1) { (*list)[0] = rand() % 1000000; }
			(*list)[rand() % list->size() - 1] = rand() % 1000000;
		}
		catch (out_of_range) {
			return false;
		}
		break;
	default:
		throw std::logic_error("Neplatna operacia v Testovanie::ListOperacia() kod operacie:" + operacia);
	}
	
	return true;
}

size_t Testovanie::PriorityQueueTest(PriorityQueue<int>* queue1, PriorityQueue<int>* queue2, const char* suborQueue_1, const char* suborQueue_2, EnumScenar scenar, size_t pocetOperacii)
{
	Scenar* sc = new Scenar(scenar, pocetOperacii);
	size_t pno;
	sc->nezamiesanyScenar();
	sc->zamiesaj();
	pno = PriorityQueueTest(queue1, queue2, suborQueue_1, suborQueue_2, sc);
	delete sc;
	return pno;
}

size_t Testovanie::PriorityQueueTest(PriorityQueue<int>* queue1, PriorityQueue<int>* queue2, const char* suborQueue_1, const char* suborQueue_2, Scenar* scenar)
{
	if (!(scenar->getTyp() == A_Queue || scenar->getTyp() == B_Queue ||scenar->getTyp() == Custom)) {
		throw std::logic_error("Typ Scenaru musi byt A_Queue , B_Queue alebo Custom!");
	}
	scenar->nezamiesanyScenar();
	scenar->zamiesaj();
	std::ofstream outfile;
	outfile.open(suborQueue_1);
	if (!outfile.is_open()) {
		throw std::exception("Chyba pri otvarani suboru pre queue_1");
	}
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	size_t pno = 0;
	for (size_t i = 0; i < scenar->getPocet(); i++) {
		begin = std::chrono::steady_clock::now();
		if (!QueueOperacia((*scenar)[static_cast<int>(i)], queue1)) { pno++; }
		end = std::chrono::steady_clock::now();
		outfile << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " , " << (*scenar)[static_cast<int>(i)] << " , " << i << " ," << endl;
	}
	outfile.close();
	outfile.open(suborQueue_2);
	for (size_t i = 0; i < scenar->getPocet(); i++) {
		begin = std::chrono::steady_clock::now();
		if (!QueueOperacia((*scenar)[static_cast<int>(i)], queue2)) { pno++; }
		end = std::chrono::steady_clock::now();
		outfile << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " , " << (*scenar)[static_cast<int>(i)] << " , " << i << " ," << endl;
	}
	outfile.close();
	return pno;
}

bool Testovanie::QueueOperacia(short int operacia, PriorityQueue<int>* queue)
{
	switch (operacia)
	{
	case 0:
		queue->push(rand() % 10001, 5);
		return true;
		break;
	case 1:
		try {
			queue->pop();
		}
		catch (logic_error) {
			return false;
		}
		return true;
		break;
	case 2:
		try {
			queue->peek();
		}
		catch (logic_error) {
			return false;
		}
		return true;
		break;
	default:
		throw std::logic_error("Neplatna operacia v Testovanie::QueueOperacia , kod operacie: " + operacia);
	}
}

void Testovanie::MatrixTest(Matrix* matica1, Matrix* matica2, const char* suborMatrix_1, const char* suborMatrix_2, Scenar* matrixSc)
{
	if (!(matrixSc->getTyp() == A_Matrix || matrixSc->getTyp() == B_Matrix || matrixSc->getTyp() == Custom)) {
		throw std::logic_error("Typ Scenaru musi byt A_Matrix , B_Matrix alebo Custom!");
	}
	matrixSc->nezamiesanyScenar();
	matrixSc->zamiesaj();
	std::ofstream outfile;
	outfile.open(suborMatrix_1);
	if (!outfile.is_open()) {
		throw std::exception("Chyba pri otvarani suboru pre maticu_1");
	}
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	for (size_t i = 0; i < matrixSc->getPocet(); i++) {
		begin = std::chrono::steady_clock::now();
		MatrixOperacia((*matrixSc)[static_cast<int>(i)], matica1);
		end = std::chrono::steady_clock::now();
		outfile << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " , " << (*matrixSc)[static_cast<int>(i)] << " , " << i << " ," << endl;
	}
	outfile.close();
	outfile.open(suborMatrix_2);
	for (size_t i = 0; i < matrixSc->getPocet(); i++) {
		begin = std::chrono::steady_clock::now();
		MatrixOperacia((*matrixSc)[static_cast<int>(i)], matica2);
		end = std::chrono::steady_clock::now();
		outfile << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " , " << (*matrixSc)[static_cast<int>(i)] << " , " << i << " ," << endl;
	}
	outfile.close();
}

void Testovanie::MatrixTest(Matrix* matica1, Matrix* matica2, const char* suborMatrix_1, const char* suborMatrix_2, EnumScenar sc , size_t pocetOperacii)
{
	Scenar* scenar = new Scenar(sc, pocetOperacii);
	MatrixTest(matica1, matica2, suborMatrix_1, suborMatrix_2, scenar);
	delete scenar;
}

bool Testovanie::MatrixOperacia(short int operacia, Matrix* matica)
{
	switch (operacia) {
	case 0:
		matica->get(rand() % matica->riadkySize(), rand() % matica->stlpceSize());
		return true;
		break;
	case 1:
		matica->set(rand() % matica->riadkySize(), rand() % matica->stlpceSize(), 10);
		return true;
		break;
	default:
		throw std::logic_error("Neplatna operacia v Testovanie::MatrixOperacia index operacie: " + operacia);
		break;
	}
}
