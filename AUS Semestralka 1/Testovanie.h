#pragma once
#include "EnumScenar.h"
#include "Scenar.h"
#include "structures/list/list.h"
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/priority_queue/priority_queue.h"
#include "Matrix.h"
using namespace std;
using namespace structures;
class Testovanie
{
public:
	static size_t ListTest(List<int>* list_1, List<int>* list_2, const char* suborList_1, const char* suborList_2, EnumScenar scenar, size_t pocetOperacii);
	static size_t ListTest(List<int>* list_1, List<int>* list_2, const char* suborList_1, const char* suborList_2, Scenar* listSc);
	static bool ListOperacia(short int operacia, List<int>* list);
	static size_t PriorityQueueTest(PriorityQueue<int>* queue1, PriorityQueue<int>* queue2 , const char* suborQueue_1 , const char* suborQueue_2, EnumScenar scenar, size_t PocetOperacii);
	static size_t PriorityQueueTest(PriorityQueue<int>* queue1, PriorityQueue<int>* queue2, const char* suborQueue_1, const char* suborQueue_2, Scenar* scenar);
	static bool QueueOperacia(short int operacia, PriorityQueue<int>* queue);
	static void MatrixTest(Matrix* matica1, Matrix* matica2, const char* suborMatrix_1, const char* suborMatrix_2, Scenar* matrixSc);
	static void MatrixTest(Matrix* matica1, Matrix* matica2, const char* suborMatrix_1, const char* suborMatrix_2, EnumScenar sc, size_t pocetOperacii);
	static bool MatrixOperacia(short int operacia, Matrix* matica);

};

