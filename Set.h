#pragma once
#include "List.h"
#include "SetAbstract.h"
#include "MemoryManager.h"
using namespace std;

class Set : public AbstractSet {
public:
    class Set_iterator : public Container::Iterator
    {
    private:
        Set* set;
        List::ListIterator* iter_l;
        size_t index_lst_iter;
    public:
        friend class Set;

        Set_iterator(Set* set, int index);
        Set_iterator(Set* set, int cur_index, List::ListIterator* iter);

        ~Set_iterator();

        size_t get_index();

        void* getElement(size_t& size) override; 
        bool hasNext() override;
        void goToNext() override; 
        bool equals(Iterator* right) override;
    };
    friend class Set_Test;

    Set(MemoryManager& mem) : AbstractSet(mem) {}
    ~Set();

    //my method
    void rehash_func();

    //AbstractSet
    int insert(void* elem, size_t size) override;

    //Container
    Iterator* find(void* elem, size_t size) override;
    Iterator* newIterator() override; 
    void remove(Iterator* iter) override;
};
