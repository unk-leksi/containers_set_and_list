#include "SetTest.h"
#include <chrono>
#include <string>
#pragma warning(disable:4996)
using namespace std;


Set_Test::Set_Test(size_t size) {
	this->_memory = new Mem(size);
	this->main_set = new Set(*this->_memory);
}

Set_Test::~Set_Test() {
    cout << "~Set Test." << endl;
    
    delete this->main_set;
    delete this->_memory;

    _CrtDumpMemoryLeaks();
}


void Set_Test::fill_array(size_t count_elem) {
    try {
        cout << "Заполняет массив на " << count_elem << " элементов." << endl;
        for (int i = 1; i <= count_elem; i++) {
            int result = main_set->insert(&i, sizeof(i));
            if (result != 0) {
                throw(Container::Error("Error with insert"));
            }

            result = check_insert(i); //i+1
            if (result == 1) {
                throw(Container::Error("Element not found in Container"));
            }
        }
        //print_elements();
    }
    catch (Container::Error err) {
        cout << err.msg << endl;
    }
}

int Set_Test::check_insert(int index) {
    Set::Set_iterator* iter = dynamic_cast<Set::Set_iterator*>(main_set->find(&index, sizeof(index)));
    if (iter) {
        size_t elem_size;
        int* elem = static_cast<int*>(iter->getElement(elem_size));
        if (*elem != index) {
            delete iter;
            return 1;
        }

        delete iter;
        return 0;
    }
    else {
        throw(Container::Error("Error with insert"));
    }

    return 1;
}

void Set_Test::print_elements() {
    cout << "Print all elements: ";

    Set::Set_iterator* it = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());

    if (it) {
        for (int i = 0; i < main_set->size(); i++) {
            size_t size;
            int* elem = static_cast<int*>(it->getElement(size));
            cout << *elem << " ";

            it->goToNext();
        }
        cout << endl;
        delete it;
    }
}


void Set_Test::test_remove_find(size_t count_elem) {
    cout << "Testing remove." << endl;

    auto start = std::chrono::high_resolution_clock::now();

    fill_array(count_elem);

    if (main_set->size() != count_elem) {
        throw(Container::Error("Error: size of elements != count_elem in Testing remove"));
    }

    Set::Set_iterator* it = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());

    if (it) {
        for (int i = 0; i < count_elem; i++) {
            size_t size;
            int* elem = static_cast<int*>(it->getElement(size));
            int tmp_elem = *elem;
            if (*elem % 2 == 0) {
                main_set->remove(it);
                Set::Set_iterator* tmp = dynamic_cast<Set::Set_iterator*>(main_set->find(&tmp_elem, sizeof(tmp_elem)));
                if (tmp) {
                    delete tmp;
                    throw(Container::Error("Odd element is not deleted in Container"));
                }
            }
            else {
                Set::Set_iterator* tmp = dynamic_cast<Set::Set_iterator*>(main_set->find(elem, size));
                if (!tmp && (*elem % 2 != 0)) {
                    throw(Container::Error("There is not even element in Container"));
                }
                delete tmp;
                it->goToNext();
            }
        }
        //for
        delete it;
    }
    else {
        throw(Container::Error("Error with function of newIterator in testing of remove_and_find"));
    }

    if (main_set->size() != count_elem / 2) {
        throw(Container::Error("Error with odd element in testing of remove_and_find"));
    }
    //print_elements();

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << "Время выполнения: " << elapsed.count() << " мс.\n";
  
    main_set->clear();
}

void Set_Test::test_removing_all_elem(size_t count_elem) {
    cout << "Testing removing all elements." << endl;

    auto start = std::chrono::high_resolution_clock::now();

   fill_array(count_elem);

   if (main_set->size() != count_elem) {
       throw(Container::Error("Error: size of elements != count_elem in Testing removing all elements"));
   }

   Set::Set_iterator* it = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());

   if (it) {
       for (int i = 0; i < count_elem; i++) {
           size_t size;
           int* elem = static_cast<int*>(it->getElement(size));
           int tmp_elem = *elem;

           main_set->remove(it);
           //cout << tmp_elem << endl;

           Set::Set_iterator* tmp = dynamic_cast<Set::Set_iterator*>(main_set->find(&tmp_elem, sizeof(tmp_elem)));
           if (tmp) {
               delete tmp;
               throw(Container::Error("Element is not deleted in Container"));
           }
       }
       delete it;
   }
   else {
       throw(Container::Error("Error with function of newIterator in removing all elem"));
   }

   if (main_set->size() != 0) {
       throw(Container::Error("Error with removing: size != 0"));
   }

   if (main_set->empty()) {
       cout << "Множество пусто после удаления всех элементов" << endl;
   }

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << "Время выполнения: " << elapsed.count() << " мс.\n";

    main_set->clear();
}

//int Set_Test::Test_two_Iterators(size_t count_elem) {
//    cout << "Testing 2 iterators" << endl;
//
//    fill_array(count_elem);
//
//    Set::Set_iterator* iter1 = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());
//    Set::Set_iterator* iter2 = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());
//
//    size_t size;
//    int* elem = static_cast<int*>(iter1->getElement(size));
//    int tmp_elem = *elem;
//
//    if (iter1) {
//        main_set->remove(iter1);
//        Set::Set_iterator* tmp = dynamic_cast<Set::Set_iterator*>(main_set->find(&tmp_elem, sizeof(tmp_elem)));
//        if (tmp) {
//            delete tmp;
//            throw(Container::Error("Odd element is not deleted in Container"));
//        }
//    }
//    else {
//        cout << "Iter1 not finded" << endl;
//        return 1;
//    }
//
//    if (iter2) {
//      //  main_set->remove(iter2);
//    }
//
//    if (main_set->size() != count_elem - 1) {
//        throw(Container::Error("Error with remove in Testing 2 iterators"));
//    }
//
//    delete iter1;
//    delete iter2;
//    main_set->clear();
//	return 0;
//}

void Set_Test::Test_void_insert() {
    cout << "Testing void insert" << endl;

    typedef struct Point{
        double x, y;
    }Point;

    Point pair;
    pair.x = 10.5;
    pair.y = 12.8;


    try {
        size_t founded_size;

        int result = main_set->insert(&pair, sizeof(Point));
        if (result != 0) {
            throw(Container::Error("Error with insert pair"));
        }
        Set::Set_iterator* iter1 = dynamic_cast<Set::Set_iterator*>(main_set->find(&pair, sizeof(pair)));
        if (!iter1) {
            throw(Container::Error("Pair was not added"));
        }

        Point* elem = static_cast<Point*>(iter1->getElement(founded_size));
        if ((pair.x == elem->x) && (pair.y == elem->y) && sizeof(pair) == founded_size) {
            cout << "Соответствует точке" << endl;
        }
        else {
            cout << "Не соответствует точке" << endl;
        }

        main_set->remove(iter1);
        Set::Set_iterator* tmp_it = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());
        if (tmp_it) {
            delete tmp_it;
            throw(Container::Error("Pair was not deleted"));
        }
        delete iter1;


        double arr[] = {2, 3};
        result = main_set->insert(&arr, sizeof(arr));
        if (result != 0) {
            throw(Container::Error("Error with insert double array"));
        }
        Set::Set_iterator* iter2 = dynamic_cast<Set::Set_iterator*>(main_set->find(&arr, sizeof(arr)));
        if (!iter2) {
            throw(Container::Error("Double array was not added"));
        }

        double* elem2 = static_cast<double*>(iter2->getElement(founded_size));
        if ((arr[0] == elem2[0]) && (arr[1] == elem2[1]) && sizeof(double) * 2 == founded_size) {
            cout << "Соответствует array: {2, 3}" << endl;
        }
        else {
            cout << "Не соответствует array: {2, 3}" << endl;
        }

        main_set->remove(iter2);
        tmp_it = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());
        if (tmp_it) {
            delete tmp_it;
            throw(Container::Error("Pair was not deleted"));
        }
        delete iter2;


        string new_n = "Hello";
        result = main_set->insert(&new_n, sizeof(new_n));
        if (result != 0) {
            throw(Container::Error("Error with insert string"));
        }
        Set::Set_iterator* iter3 = dynamic_cast<Set::Set_iterator*>(main_set->find(&new_n, sizeof(new_n)));
        if (!iter3) {
            throw(Container::Error("String was not added"));
        }

        string* el1 = static_cast<string*>(iter3->getElement(founded_size));
        if (new_n == *el1 && sizeof(new_n) == founded_size) {
            cout << "Соответствует: " << new_n << endl;
        }
        else {
            cout << "Не соответствует: " << new_n << endl;
        }

        //Repeat insert
        result = main_set->insert(&new_n, sizeof(new_n));
        if (result != 0) {
            cout << "Error with repeat insert str" << endl;
        }

        main_set->remove(iter3);
        tmp_it = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());
        if (tmp_it) {
            delete tmp_it;
            throw(Container::Error("Pair was not deleted"));
        }
        delete iter3;
    }
    catch (Container::Error err) {
        cout << err.msg << endl;
    }


    if (main_set->size() != 0) {
        throw(Container::Error("Container is not empty"));
    }
  
    main_set->clear();
}

void Set_Test::Test_rehash_function(size_t count_elem) {
    //изменить в GroupContainer Setsize на 100

    cout << "Testing rehash function." << endl;

    auto start = std::chrono::high_resolution_clock::now();

    fill_array(count_elem);

    if (count_elem == main_set->size()) {
        cout << "Количество элементов: " << main_set->size() << endl;
    }
    else {
        throw(Container::Error("Количество элементов не совпадает с count_elem"));
    }

    cout << "Старый SetSize: 100. " << "Текущий Setsize: " << main_set->Setsize << endl;


    Set::Set_iterator* iter = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());
    size_t founded_size;
    int* elem = static_cast<int*>(iter->getElement(founded_size));
    int tmp_elem = *elem;
    if (iter) {
        main_set->remove(iter);
    }
    delete iter;

    Set::Set_iterator* tmp = dynamic_cast<Set::Set_iterator*>(main_set->find(&tmp_elem, sizeof(tmp_elem)));
    if (tmp) {
        delete tmp;
        throw(Container::Error("Element is not deleted in Container"));
    }

    if (main_set->size() == count_elem - 1) {
        cout << "All good" << endl;
    }
    else {
        cout << "Bad" << endl;
    }

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << "Время выполнения: " << elapsed.count() << " мс.\n";

    main_set->clear();


    Set::Set_iterator* iter7 = dynamic_cast<Set::Set_iterator*>(main_set->newIterator());

    if (main_set->empty() == true && iter7 == NULL) {
        cout << "Success" << endl;
    }
    else {
        cout << "Unsuccess" << endl;
    }
}
