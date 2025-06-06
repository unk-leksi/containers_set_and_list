#pragma once
#include "ListAbstract.h"
#pragma warning(disable:4996)
using namespace std;

class List : public AbstractList {
private:
	class Node {
	public:
		Node* next;
		void* data;
		size_t data_size;

		Node(Node* next) {
			this->next = next;
			this->data = NULL;
			this->data_size = 0;
		}
	};
	Node* head;
	int count;

public:
	class ListIterator : public Container::Iterator {
	private:
		Node* cur_iter;
	public:
		friend class List;

		ListIterator(Node* tmp);
		~ListIterator();

		void* getElement(size_t& size) override;
		bool hasNext() override;
		void goToNext() override;
		bool equals(Container::Iterator* right) override;
	};

	List(MemoryManager& mem);
	~List();

	//Abstract List
	int push_front(void* elem, size_t elemSize) override;
	void pop_front() override;
	void* front(size_t& size)override;
	int insert(Container::Iterator* iter, void* elem, size_t elemSize) override;

	//Container
	int size() override;
	size_t max_bytes() override;
	Iterator* find(void* elem, size_t size) override;
	Iterator* newIterator() override;
	void remove(Container::Iterator* iter) override;
	void clear() override;
	bool empty() override;
};
