#include <iostream>
using namespace std;

// инакпсуляция для параноиков: засунуть класс в приватную зону класса.
// вложенные классы работают только с статическим разрешением переменных - методов.
//class ListNode {
//public:
//
//	class Node {
//	public:
//		int value;
//		Node* link;
//
//		Node(int v): value(v), link(NULL){}
//	};
//
//	Node* head;
//	ListNode() : head(NULL) {}
//
//	void add(int data) {
//		Node* new_node = new Node(data);
//		if (!head) {
//			head = new_node; return;
//		}
//		else {
//			Node* emp_node = head;
//			while (emp_node->link) {
//				emp_node = emp_node->link;
//				cout << "Next: " << emp_node;
//			}
//			emp_node->link = new_node;
//			cout << "End: " << new_node;
//		}
//	}
//};

class Account {
private:
	class Login {
		string login;
	public:
		Login(string stroka){
			if ((size(stroka) > 0) and (size(stroka) < 65535)) {
				login = stroka;
			}
		}
		string get_log() {
			return login;
		}
	};
	class Password {
		string pass;
	public:
		Password(string p) {
			if ((size(p) > 0) and (size(p) < 65535)) {
				pass = p;
			}
		}
		string get_pass() {
			return pass;
		}
	};
	Login login; Password password;
public:
	Account(string f, string s) : login(f), password(s) {
		cout << "Логин: " << login.get_log()<< "\npassword: ";
		if (size(password.get_pass())>0) {
			cout << ".hide user password.";
		}
		else {
			cout << ".didnt has password |warning|";
		}
	}
};

int main()
{
	setlocale(LC_ALL, "");
	Account("Kasey", "");
}
