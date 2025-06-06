#pragma once
#include "Container.h"
#include "List.h"
#define BASE 65521 
using namespace std;
// Базовый класс для некоторой группы абстрактных контейнеров
class GroupContainer : public Container
{
protected:
    List** arr_list;
    size_t count_elem;
    size_t Setsize;
public:
    GroupContainer(MemoryManager& mem);

    size_t hash_func(void* key, size_t keySize);

    int size() override;
    size_t max_bytes() override;

    void clear() override;
    bool empty() override;
};
