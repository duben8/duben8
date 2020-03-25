// AUS Semestralka 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "structures/list/array_list.h"
#include "structures/list/list.h"
#include "structures/list/linked_list.h"
#include "Scenar.h"
#include "EnumScenar.h"
#include "structures/heap_monitor.h"
#include "Testovanie.h"
#include "structures/priority_queue/priority_queue.h"
#include "structures/priority_queue/priority_queue_linked_list.h"
#include "structures/priority_queue/heap.h"
#include "Matrix.h"
#include "PolePoli.h"
#include "JednoPoleMatrix.h"
#include "Matrix.h"
#define GLOBAL_POCET_OPERACII 10000
using namespace structures;
using namespace std;
EnumScenar dajScenare(int i);
void vypisMenu();
int main()
{
    int volba;
    do {
        do {
            vypisMenu();
            cin >> volba;
            if (!(volba > -1 && volba < 5)) { cout << "Napisal si nespravnu volbu."; }
        } while (!(volba > -1 && volba < 5));


        switch (volba) {
        case 0:
            cout << "Koniec programu." << endl;
            break;
        case 1: {
            const char* suborArrayList = "suborArrayList.csv";
            const char* suborLinkedList = "suborLinkedList.csv";
            cout << "Zadaj pociatocny pocet prvkov v Listoch" << endl;
            int pocet;
            cin >> pocet;
            if (pocet < 0) { pocet = 0; }
            ArrayList<int>* al = new ArrayList<int>();
            LinkedList<int>* ll = new LinkedList<int>();
            for (int i = 0; i < pocet; i++) {
                al->add(rand() % pocet);
                ll->add(rand() % pocet);
            }
            bool spravnaVolbaScenara = true;
            EnumScenar sc;
            do {
                try {

                    sc = dajScenare(0);
                }
                catch (logic_error) {
                    cout << "Nespravna volba scenara , skus znova!" << endl;
                    spravnaVolbaScenara = false;
                }
            } while (!spravnaVolbaScenara);
            size_t pno;
            pno = Testovanie::ListTest(dynamic_cast<List<int>*> (al), dynamic_cast<List<int>*>(ll), suborArrayList, suborLinkedList, sc, GLOBAL_POCET_OPERACII);
            delete al;
            delete ll;
            
            cout << "Test prebehol uspesne , udaje pre arraylist boli ulozene v: " << suborArrayList << endl;
            cout << "Udaje pre linkedlist boli ulozene v: " << suborLinkedList << endl;
            cout << "Pocet neplatnych operacii je: " << pno << endl;
            delete suborArrayList;
            delete suborLinkedList;
            break;
        }

        case 2: {
            bool spravnaVolbaScenara = true;
            EnumScenar sc;
            do {
                try {

                    sc = dajScenare(1);
                }
                catch (logic_error) {
                    cout << "Nespravna volba scenara , skus znova!" << endl;
                    spravnaVolbaScenara = false;
                }
            } while (!spravnaVolbaScenara);
            const char* suborHeap = "suborHeap.csv";
            const char* suborLinkedList = "suborLinkedListQueue.csv";
            cout << "Zadaj pociatocny pocet prvkov v Listoch" << endl;
            int pocet;
            cin >> pocet;
            if (pocet < 0) { pocet = 0; }
            Heap<int>* heap = new Heap<int>();
            PriorityQueueLinkedList<int>* heapLL = new PriorityQueueLinkedList<int>();
            for (int i = 0; i < pocet; i++) {
                heap->push(rand() % pocet, rand() % pocet);
                heapLL->push(rand() % pocet, rand() % pocet);
            }
            size_t pno;
            pno = Testovanie::PriorityQueueTest(heap, heapLL, suborHeap, suborLinkedList, A_Queue, GLOBAL_POCET_OPERACII);
            delete heap;
            delete heapLL;
            delete suborHeap;
            delete suborLinkedList;
            cout << "Test prebehol uspesne , udaje pre heap boli ulozene v: " << suborHeap << endl;
            cout << "udaje pre linkedlist boli ulozene v: " << suborLinkedList << endl;
            cout << "Pocet neplatnych operacii: " << pno << endl;
            break; }
        case 3: {
            cout << "Zadaj rozmery matice , prve riadky ,druhe stlpce" << endl;
            int riadky;
            cin >> riadky;
            int stlpce;
            cin >> stlpce;
            cout << "Zadaj scenar matice";
            EnumScenar esc = dajScenare(2);
            PolePoli* polePoli = new PolePoli(riadky, stlpce);
            JednoPoleMatrix* jednoPoleMatica = new JednoPoleMatrix(riadky, stlpce);
            const char* suborPolePoli = "suborPolePoli.csv";
            const char* suborImplicitnaMatica = "suborImplicitnaMatica.csv";
            Testovanie::MatrixTest(dynamic_cast<Matrix*>(polePoli), dynamic_cast<Matrix*>(jednoPoleMatica), suborPolePoli, suborImplicitnaMatica, esc, GLOBAL_POCET_OPERACII);
            delete polePoli;
            delete jednoPoleMatica;
            break; }
        }
    } while (volba != 0);

    

    return 0;
}
void vypisMenu() {
    cout << "Napis 0 pre ukoncenie programu." << endl
        << "Napis 1 pre otestovanie zoznamov ArrayList a LinkedList." << endl
        << "Napis 2 pre otestovanie prioritneho frontu implementovaneho Lavostrannou haldou a LinkedListom." << endl
        << "Napis 3 pre otestovanie matice implementovanej jednym polom a polom poli." << endl
        << "Napis 4 pre otestovanie mnoziny" << endl;
}
EnumScenar dajScenare(int i) {
    bool spravna = true;
    do {
        cout << "Napis cislo poradia scenara" << endl
            << "Scenare su: 1 A_List , 2 B_List , 3 C_List ," << endl
            << "4 A_Queue, 5 B_Queue," << endl
            << "6 A_Matrix, 7 B_Matrix" << endl
            << "8 Custom" << endl;
        int volba;
        cin >> volba;
        switch (volba)
        {
        case 1:
            if (i == 0) {
                return A_List;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 2:
            if (i == 0) {
                return B_List;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 3:
            if (i == 0) {
                return C_List;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 4:
            if (i == 1) {
                return A_Queue;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 5:
            if (i == 1) {
                return B_Queue;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 6:
            if (i == 2) {
                return A_Matrix;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 7:
            if (i == 2) {
                return B_Matrix;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        case 8:
            if (i == 3) {
                return Custom;
            }
            else {
                cout << "Nemozes pouzit tu tento scenar" << endl;
                spravna = false;
            }
            break;
        default:
            cout << "Neznama volba scenara!";
            spravna = false;
            break;
        }
    } while (!spravna);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
