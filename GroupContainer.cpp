#include "GroupContainer.h"


GroupContainer::GroupContainer(MemoryManager& mem) : Container(mem) 
{
	Setsize = 1000000;
	arr_list = (List**)_memory.allocMem(sizeof(List*) * Setsize);
	if (arr_list) {
		for (int i = 0; i < Setsize; i++) 
		{
			arr_list[i] = nullptr;
		}
		count_elem = 0;
	}
	else {
		throw(Error("Error with memory in Set Constructor"));
	}
}

size_t d_hash(const void* key, size_t keySize) 
{
    const uint8_t* data = static_cast<const uint8_t*>(key);
    size_t hash = 5381;

    for (size_t i = 0; i < keySize; i++) {
        hash = ((hash << 5) + hash) + data[i];
    }

    return hash;
}

size_t GroupContainer::hash_func(void* key, size_t keySize)
{
    return d_hash(key, keySize);
}

int GroupContainer::size() 
{
	return this->count_elem;
}

size_t GroupContainer::max_bytes() 
{
	return _memory.size();
}

void GroupContainer::clear() 
{
	if (Setsize == 0) {
		return;
	}

	for (int i = 0; i < Setsize; i++) {
		if (arr_list[i] != nullptr && !arr_list[i]->empty()) {
			arr_list[i]->clear();
		}
	}

	count_elem = 0;
}

bool GroupContainer::empty() 
{
	if (count_elem == 0) {
		return true;
	}
	else {
		return false;
	}
}
