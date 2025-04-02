#include <iostream>
#include <vector>
using namespace std;

struct Complex_num {
	double real, img;
};

struct Node
{
	Complex_num data;
	int value; Node* link; Node* prev;

	Node(int a) {
		value = a; link = NULL;
	}
};

struct link_list
{
private:
	Node* tail; Node* head;
	int lnght;

public:
	link_list() { tail = nullptr; head = nullptr; lnght = 0; }
	~link_list() { }

	void _push_back(int value) {
		Node* nd = new Node(value);
		if (head == nullptr)
			head = tail = nd;
		else
			tail->link = nd; tail = nd;
		lnght++;
	}
	void _push_front(int value) {
		Node* nd = new Node(value);
		nd->link = head; head = nd;
		if (tail == nullptr)
			tail = head;
		else
			head->link = nd; head = nd;
		lnght++;
	}
	void pop_back() {
		if (head == tail) {
			delete head; head = tail = nullptr;
		}
		else {
			Node* crt = head;
			while (crt ->link != tail) {
				crt = crt->link;
			}
			delete tail; tail = crt; tail->link = nullptr;
		}
		lnght--;
	}
	void pop_front() {
		Node* crt = head;
		head = head->link;
		delete crt;
		lnght--;
		if (head == nullptr)
			tail = nullptr;
	}
	void pop_index(int pos) {
		pos--;
		if ((pos == 0) || (pos >= lnght))
			return;
		else if (pos == 0)
			pop_front();
		else {
			if (pos == lnght - 1)
				pop_back();
			else {
				Node* nd = head;
				for (int i = 0; i < pos - 1;i++)
					nd = nd->link;
				nd->link = nd->link->link;
			}
		}
	}
	void insert(int pos, int val) {
		if (pos == 0) {
			_push_front(val);
		}
		else {
			if (pos == lnght)
				_push_back(val);
			else {
				Node* nd = head;
				for (int i = 0; i < pos - 1; i++)
					nd = nd->link;
				Node* crt = new Node(val);
				crt->link = nd->link;
				nd->link = crt;
				lnght++;
			}
		}
	}
	void print() {
		Node* nd = head;
		for (int i = 0; i < lnght; i++) {
			cout << '{' << nd->value << ',' << nd->link << "} -> ";
			nd = nd->link;
		}
		cout << "nullptr";
	}
	void erase() {
		if (head == nullptr)
			return;
		else {
			Node* nd = head;
			while (head != nullptr) {
				nd=head->link;
				delete head; head = nd->link;
			}

			head = nullptr;
		}
	}
	void clear() {
		if (head == NULL)
			return;
		while (lnght != 0)
			pop_front();
	}
	int get_index(int pos) {
		if ((pos < 0) || (pos >= lnght))
			return 0;
		else {
			Node* nd = head;
			for (int i = 0; i < pos; i++)
				nd = nd->link;
			return nd->value;
		}
	}

};

int main() // 2-3, 3-4, 4-5, 5-6... второе число - ссылка. первое сущее. Попробывать сделать через хранение в массиве.
{
	link_list lst;
	srand(time(0));
	for (int i = 0; i < 4; i++)
		lst._push_back(rand() % 100);
	lst.print();
	lst.insert(2, 777);
	lst.print();
	cout << lst.get_index(2);
}
