#include <iostream>
#include "SetTest.h"
#include "Mem.h"
#include "MemoryManager.h"
#include "List.h"
#include "Set.h"
#include <chrono>
using namespace std;

 #define __CRTDBG_MAP_ALLOC
 #include <crtdbg.h>
 #define DEBUG_NEW new_1(_NORMAL_BLOCK, FILE, LINE)
 #define new_1 DEBUG_NEW


int main() {
    setlocale(LC_ALL, "Russian");

    size_t size1 = 100;

    Set_Test set_st(size1);
 
    try {
        set_st.test_remove_find(100);
        cout << endl;

        //set_st.test_removing_all_elem(10000);
        //cout << endl;

        //set_st.Test_void_insert();
        //cout << endl;

        //изменить в GroupContainer Setsize на 100
        //set_st.Test_rehash_function(10000);
        //cout << endl;
    }
    catch (Container::Error err) {
        cout << err.msg << endl;
    }

    return 0;
}
