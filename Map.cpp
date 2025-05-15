#include <iostream>
#include <clocale>
#include <Windows.h>
#include <string>

using namespace std;

struct object{
	int x, y;
	string name;
	object* next;
};

object* create_head() {
	object* head = new object;
	head->x = head->y = 0;
	head->name = "";
	head->next = nullptr;
	return head;
}

void add_start(object* head, int p_x, int p_y, const string& p_name) {
	object* new_object = new object; 
	new_object->x = p_x;
	new_object->y = p_y;
	new_object->name = p_name;

	new_object->next = head->next;
	head->next = new_object;

	cout << "����� ������ ������� ��������." << endl;
}

void delete_object(object* head, int number) {

	if (number < 1) {
		cout << "uncorrect number\n";
		return;
	}
	object* prev = head;
	object* cur = head->next;
	for (int i = 1; i < number; i++) {
		if (!cur) {
			cout << "� ������ ��� �������� � �������� �������. " << endl;
			return;
		}
		prev = prev->next;
		cur = cur->next;
	}

	prev->next = cur->next;
	delete cur;
}

void delete_all(object* head) {
	//object* temp = head;
	object * current = head->next; 
	while (current) {
		head->next = current->next;
		delete current;
		current = head->next;
	};
	delete head;
}

void print_map_objects(object* head) {
	object* temp = head->next;
	int i = 1;
	cout << endl;
	if (!temp) {
		cout << "��� ������ ����." << endl;
		return;
	}
	while (temp) {
		cout << i << ". Name: " << temp->name << "; x: " << temp->x << "; y: " << temp->y << ";" << endl;
		temp = temp->next;
		i++;
	}
}

int count_objects(object* head) {
	object* temp = head->next;
	int i = 0;
	while (temp) {
		i++;
		temp = temp->next;
	}
	return i;
}

void delete_in_rect(object* head, int min_x, int max_x, int min_y, int max_y) {
	object* temp = head;
	object* cur = head->next;

	while (cur && temp) {
		if ((cur->x >= min_x) && (cur->x <= max_x) && (cur->y >= min_y) && (cur->y <= max_y)) {
			temp->next = cur->next;
			delete cur;
			cur = temp->next;
		}
		else {
			temp = cur;
			cur = cur->next;
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	int a;
	a = 0;

	cout << "�������� ��������: \n1. ������� ������.\n2. ����� �� ���������.\n"; 
	cin >> a;
	
	if (a == 1) {
		object* head = create_head();
			while (a != 100) {
				cout << "�������� ��������:" << endl;
				cout << "1 - �������� ������." << endl;
				cout << "2 - ������� ������ ��������." << endl;
				cout << "3 - ������� ���������� �������� ������." << endl;
				cout << "4 - ������� ��������� ������." << endl;
				cout << "5 - ������� ������ �� ������������� �������." << endl;
				cout << "100 - ������� ������ � ����� �� ���������." << endl;
				cin >> a;
				
				switch (a) {
				case 1: {
					cout << "������� ������:\n";
					int x, y;
					string n_name;
					cout << "��������: ";
					cin >> n_name;
					cout << "x: ";
					cin >> x;
					cout << "y: ";
					cin >> y;
					add_start(head, x, y, n_name);
					break;
				}
				case 2: {
					print_map_objects(head);
					break;
				}
				case 3: {
					int c = count_objects(head);
					cout << c << endl;
					break;
				}
				case 4: {
					int n;
					cout << "������� ����� ���������� ��������: ";
					cin >> n;
					delete_object(head, n);
					break;
				}
				case 5: {
					cout << "������� ������:\n";
					int min_x, max_x,  min_y, max_y;
					string n_name;
					cout << "��������� x: ";
					cin >> min_x;
					cout << "�������� x: ";
					cin >> max_x;
					cout << "��������� y: ";
					cin >> min_y;
					cout << "�������� y: ";
					cin >> max_y;
					delete_in_rect(head, min_x, max_x, min_y, max_y);
					break;
				}
				case 100: 
					break;
				default:
					break;
				}
			}
			cout << "������ ������, ��������� �������.\n";
	}
	else {
		cout << "��������� �������";
	}
	return 0;
}