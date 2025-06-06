#include "List.h"
#pragma warning(disable:4996)
using namespace std;

List::List(MemoryManager& mem) : AbstractList(mem) {
	this->head = nullptr;
	this->count = 0;
}

List::~List() {
	this->clear();
}

int List::push_front(void* elem, size_t elemSize) {
	if (elemSize <= 0) { return 1; }

	head = new Node(head);
	if (head) {
		head->data_size = elemSize;
		head->data = _memory.allocMem(elemSize);
		if (head->data) {
			head->data = memcpy(head->data, elem, elemSize);
			count++;
			return 0;
		}
		else {
			throw(Error("It was not allocated memory in List: push front"));
		}
	}

	return 1;
}

void List::pop_front() {
	if (head == NULL) {
		return;
	}
	else {
		Node* tmp = this->head->next;
		_memory.freeMem(head->data);
		_memory.freeMem(head);
		this->head = tmp;
		this->count--;
	}
}

void* List::front(size_t& size) {
	if (head == NULL) {
		return nullptr;
	}

	size = head->data_size;
	return head->data;
}

int List::insert(Container::Iterator* iter, void* elem, size_t elemSize) {
	if (elemSize <= 0) { return 1; }

	ListIterator* iter_l = dynamic_cast<ListIterator*>(iter);
	if (iter) {
		if (iter_l->cur_iter == NULL) { return 1; }

		if (iter_l->cur_iter == head) {
			push_front(elem, elemSize);
			return 0;
		}
		else {
			Node* tmp_node = head;
			while (tmp_node != NULL) {
				if (tmp_node->next == iter_l->cur_iter) {
					Node* newNode = new Node(tmp_node->next);
					if (newNode) {
						newNode->data_size = elemSize;
						newNode->data = _memory.allocMem(elemSize);
						if (newNode->data) {
							newNode->data = memcpy(newNode->data, elem, elemSize);
							tmp_node->next = newNode;
							count++;
							return 0;
						}
						else {
							throw(Error("It was not allocated memory in List: insert"));
						}
					}
					else {
						throw(Error("It was not allocated memory in Node of List: insert"));
					}
				}
				tmp_node = tmp_node->next;
			}
			_memory.freeMem(tmp_node);
		}
	}

	return 1;
}

int List::size() {
	return this->count;
}

size_t List::max_bytes() {
	return _memory.size();
}

List::Iterator* List::find(void* elem, size_t size) {
	if (size <= 0 && head == NULL) { return nullptr; }

	Node* cur_node = head;
	while (cur_node != NULL) {
		if (cur_node->data_size == size) {
			if (memcmp(cur_node->data, elem, size) == 0) {
				ListIterator* iter = new ListIterator(cur_node);
				return iter;
			}
		}
		cur_node = cur_node->next;
	}

	_memory.freeMem(cur_node);
	return nullptr;
}

List::Iterator* List::newIterator() {
	if (head == NULL) { return nullptr; }

	ListIterator* iter = new ListIterator(head);
	if (iter) {
		return iter;
	}
	else {
		throw(Error("It was not allocated memory in List: NewIterator"));
	}
}

void List::remove(Container::Iterator* iter) {
	ListIterator* iter_l = dynamic_cast<ListIterator*>(iter);
	if (iter) {
		if (iter_l->cur_iter == head) {
			Node* tmp = this->head->next;
			_memory.freeMem(head->data);
			_memory.freeMem(head);
			this->head = tmp;
			iter_l->cur_iter = head;
			this->count--;
		}
		else {
			Node* tmp = head;
			while (tmp != NULL) {
				if (tmp->next == iter_l->cur_iter) {
					tmp->next = tmp->next->next;
					_memory.freeMem(iter_l->cur_iter->data);
					_memory.freeMem(iter_l->cur_iter);
					iter_l->cur_iter = NULL;
					iter_l->cur_iter = tmp->next;
					count--;
					return;
				}
				tmp = tmp->next;
			}
			_memory.freeMem(tmp);
		}
	}
}

void List::clear() {
	while (head != NULL) {
		Node* tmp = head->next;
		_memory.freeMem(head->data);
		_memory.freeMem(head);
		head = tmp;
	}
}

bool List::empty() {
	if (count == 0 && head == NULL) {
		return true;
	}
	return false;
}


List::ListIterator::ListIterator(Node* tmp) {
	this->cur_iter = tmp;
}

List::ListIterator::~ListIterator() {
	if (this->cur_iter) {
		this->cur_iter = NULL;
	}
}

void* List::ListIterator::getElement(size_t& size) {
	if (cur_iter == NULL || cur_iter->data == NULL) {
		size = 0;
		return nullptr;
	}

	size = cur_iter->data_size;
	//cout << size << endl;
	return cur_iter->data;
}

bool List::ListIterator::hasNext() {
	if (cur_iter == NULL) { return false; }

	if (cur_iter->next != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void List::ListIterator::goToNext() {
	if (cur_iter == NULL) { return; }

	cur_iter = cur_iter->next;
}

bool List::ListIterator::equals(Container::Iterator* right) {
	ListIterator* tmp_iter = dynamic_cast<ListIterator*>(right);
	if (tmp_iter) {
		if (tmp_iter->cur_iter == this->cur_iter) {
			return true;
		}
	}
	
	return false;
}
