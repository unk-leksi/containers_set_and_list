#include "Set.h"
#include "Mem.h"
#pragma warning(disable:4996)
using namespace std;


void Set::rehash_func() {
	Setsize = Setsize * 2;
	List** new_arr_list = (List**)_memory.allocMem(sizeof(List*) * Setsize);
	if (new_arr_list) {
		for (int i = 0; i < Setsize; i++) {
			new_arr_list[i] = nullptr;
		}
	}
	else {
		Setsize = Setsize / 2;
		throw(Error("There was not rehash"));
		return;
	}

	for (int i = 0; i < Setsize / 2; i++) {
		if (arr_list[i] != nullptr && arr_list[i]->empty() == false) {
			List::ListIterator* lst_iter = dynamic_cast<List::ListIterator*>(arr_list[i]->newIterator());
			if (lst_iter) {
				for (int j = 0; j < arr_list[i]->size(); j++) {
					size_t elemsize;
					void* elem = lst_iter->getElement(elemsize);
					size_t hash = hash_func(elem, elemsize) % Setsize;
					if (new_arr_list[hash] == nullptr) {
						new_arr_list[hash] = new List(_memory);
						if (!new_arr_list[hash]) {
							throw(Error("Error with memory in Rehash:new array of list"));
						}
					}
					int result = new_arr_list[hash]->push_front(elem, elemsize);
					if (result != 0) {
						throw(Error("Error with push_front in rehash"));
					}

					if (lst_iter->hasNext() == true) {
						lst_iter->goToNext();
					}
				}

				_memory.freeMem(lst_iter);
			}
			else {
				throw (Error("Error with iterator in Rehash"));
			}

			arr_list[i]->clear();
			_memory.freeMem(arr_list[i]);
		}
	}
	
	_memory.freeMem(arr_list);
	arr_list = new_arr_list;
}


Set::~Set() {
	cout << "~SET." << endl;
	this->clear();

	for (int i = 0; i < Setsize; i++) {
		_memory.freeMem(arr_list[i]);
		arr_list[i] = nullptr;
	}
	_memory.freeMem(arr_list);
	Setsize = 0;
}

int Set::insert(void* elem, size_t size) {
	if (size == 0 || elem == nullptr) {
		return 2;
	}

	size_t cur_index = (hash_func(elem, size)) % Setsize;

	if (arr_list[cur_index] == nullptr) {
		arr_list[cur_index] = new List(_memory);
		if (!arr_list[cur_index]) {
			throw(Error("Error with memory in insert:array list"));
		}
	}

	if (arr_list[cur_index]->size() >= 50) {
		cout << "ReHash." << endl;
		rehash_func();
		cur_index = (hash_func(elem, size)) % Setsize;
	}

	List::ListIterator* founded_iter = dynamic_cast<List::ListIterator*>(arr_list[cur_index]->find(elem, size));

	if (founded_iter != nullptr) {
		_memory.freeMem(founded_iter);
		return 1; //repetition
	}
	else {
		int res = arr_list[cur_index]->push_front(elem, size);
		if (res != 0) {
			throw(Error("Error with push_front in list"));
		}
		this->count_elem++;
		return 0; //success
	}

	return 2; //ostalnoy sluchai
}


Set::Set_iterator::Set_iterator(Set* set, int index) {
	this->set = set;
	this->iter_l = dynamic_cast<List::ListIterator*>(set->arr_list[index]->newIterator());
	if (!this->iter_l) {
		throw(Error("Error with memory Set_iterator in constructor"));
	}
	this->index_lst_iter = index;
}

Set::Set_iterator::Set_iterator(Set* set, int cur_index, List::ListIterator* l_iter) {
	this->set = set;
	this->iter_l = l_iter;
	this->index_lst_iter = cur_index;
}

size_t Set::Set_iterator::get_index() {
	size_t elem_size;
	void* elem = static_cast<void*>(iter_l->getElement(elem_size));

	size_t index_current = set->hash_func(elem, elem_size) % set->Setsize;

	return index_current;
}

void* Set::Set_iterator::getElement(size_t& size) {
	if (set->empty() == true) {
		size = 0;
		return nullptr;
	}

	if (iter_l != nullptr) {
		return iter_l->getElement(size);
	}
	return nullptr;
}

bool Set::Set_iterator::hasNext() {
	if (set->empty() == true) { return false; }

	if (iter_l != nullptr) {
		if (iter_l->hasNext() == true) {
			return true;
		}
		int i = index_lst_iter + 1;
		while (i < set->Setsize) {
			if (set->arr_list[i] != nullptr) {
				return true;
			}
			else {
				i++;
			}
		}
	}
	return false;
}

void Set::Set_iterator::goToNext() {
	if (iter_l != nullptr) {
		if (iter_l->hasNext() == true) {
			iter_l->goToNext();
			return;
		}
		int i = index_lst_iter + 1;
		while (i < set->Setsize) {
			if (set->arr_list[i] != nullptr && set->arr_list[i]->empty() == false) {
				iter_l = dynamic_cast<List::ListIterator*>(set->arr_list[i]->newIterator());
				if (iter_l) {
					index_lst_iter = i;
					return;
				}
			}
			else {
				i++;
			}
		}
		iter_l = nullptr;
	}
}

bool Set::Set_iterator::equals(Iterator* right) {
	return iter_l->equals(right);
}

Set::Set_iterator::~Set_iterator() {
	if (iter_l) {
		set->_memory.freeMem(iter_l);
	}
}


Set::Iterator* Set::find(void* elem, size_t size) {
	if (count_elem == 0 || this->empty() || elem == nullptr || size == 0) { return nullptr; }

	int cur_index = (hash_func(elem, size)) % Setsize;

	if (arr_list[cur_index] && !arr_list[cur_index]->empty()) {
		List::ListIterator* l_iter = dynamic_cast<List::ListIterator*>(arr_list[cur_index]->newIterator());
		if (l_iter) {
			size_t founded_size;
			while (l_iter->hasNext() == true) {
				void* finded_elem = l_iter->getElement(founded_size);
				if (size == founded_size) {
					if (memcmp(elem, finded_elem, size) == 0) {
						List::ListIterator* f_iter = dynamic_cast<List::ListIterator*>(arr_list[cur_index]->find(elem, size));
						_memory.freeMem(l_iter);
						return new Set_iterator(this, cur_index, f_iter);
					}
				}
				l_iter->goToNext();
			}

			void* finded_elem = l_iter->getElement(founded_size);
			if (size == founded_size) {
				if (memcmp(elem, finded_elem, size) == 0) {
					List::ListIterator* f_iter = dynamic_cast<List::ListIterator*>(arr_list[cur_index]->find(elem, size));
					_memory.freeMem(l_iter);
					return new Set_iterator(this, cur_index, f_iter);
				}
			}
		}
		_memory.freeMem(l_iter);
	}

	return nullptr;
}

Set::Iterator* Set::newIterator() {
	if (this->empty()) {
		return nullptr;
	}

	for (int i = 0; i < Setsize; i++) {
		if (arr_list[i] && !arr_list[i]->empty()) {
			Set_iterator* iter = new Set_iterator(this, i);
			return iter;
		}
	}
	return nullptr;
}

void Set::remove(Iterator* iter) {
	if (count_elem == 0 && this->empty()) { return; }

	Set_iterator* it = dynamic_cast<Set_iterator*>(iter);
	if (it) {
		size_t elem_size;
		void* elem = static_cast<void*>(it->getElement(elem_size));

		if (elem == NULL) { return; }

		Set_iterator* iterCop = new Set_iterator(this, it->index_lst_iter, it->iter_l);
		if (iterCop) {
			bool flag = it->iter_l->hasNext();
			if (flag == false) {
				it->goToNext();
			}

			arr_list[iterCop->get_index()]->remove(iterCop->iter_l);

			if (flag == false) {
				_memory.freeMem(iterCop->iter_l);
			}

			count_elem--;
		}
		else {
			throw(Error("Error with memory in remove"));
		}
		//_memory.freeMem(iterCop->iter_l);
		_memory.freeMem(iterCop);
	}
}
