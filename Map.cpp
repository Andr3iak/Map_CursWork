#include <iostream>
#include <clocale>
#include <Windows.h>
#include <string>
#include <iomanip>


using namespace std;

struct object{
	double x, y; // x-долгота y-широта
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

void add_start(object* head, double p_y, double p_x, const string& p_name) {

	if (p_x < -180.0 || p_x > 180.0) {
		cout << "Ошибка: долгота должна быть в диапазоне от -180 до 180 градусов." << endl;
		return;
	}

	if (p_y < -90.0 || p_y > 90.0) {
		cout << "Ошибка: широта должна быть в диапазоне от -90 до 90 градусов." << endl;
		return;
	}

	object* new_object = new object;
	new_object->y = p_y;
	new_object->x = p_x;
	new_object->name = p_name;

	new_object->next = head->next;
	head->next = new_object;

	cout << "Новый объект успешно добавлен." << endl;
}


void search_objects(object* head, const string& search_name) {

	object* current = head->next;
	while (current != nullptr) {
		if (current->name == search_name) {
			cout << "Name: " << current->name << "; Широта: " << fixed << setprecision(5) << current->y << "; Долгота: " << current->x << ";" << endl;
			return;
		}
		current = current->next;
	}
	cout << "Объект не найден." << endl;
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
			cout << "В списке нет элемента с заданным номером. " << endl;
			return;
		}
		prev = prev->next;
		cur = cur->next;
	}

	prev->next = cur->next;
	delete cur;
}

void delete_all(object* head) {
	object * current = head->next; 
	while (current) {
		head->next = current->next;
		delete current;
		current = head->next;
	};
	delete head;
}

void print_objects(object* head) {
	object* temp = head->next;
	int i = 1;
	cout << endl;
	if (!temp) {
		cout << "Ваш список пуст." << endl;
		return;
	}
	while (temp) {
		cout << i << ". Name: " << temp->name << "; Широта: " << fixed << setprecision(5) << temp->y << "; Долгота: " << temp->x << ";" << endl;
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

void delete_in_rect(object* head, double min_y, double max_y, double min_x, double max_x) {
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

void print_ascii_map(object* head) {
	object* temp = head->next;

	if (!temp) {
		cout << "Карта пуста." << endl;
		return;
	}

	int min_x = temp->x, max_x = temp->x;
	int min_y = temp->y, max_y = temp->y;

	while (temp) {
		if (temp->x < min_x) min_x = temp->x;
		if (temp->x > max_x) max_x = temp->x;
		if (temp->y < min_y) min_y = temp->y;
		if (temp->y > max_y) max_y = temp->y;
		temp = temp->next;
	}

	min_x = min(min_x, 0);
	max_x = max(max_x, 0);
	min_y = min(min_y, 0);
	max_y = max(max_y, 0);

	min_x -= 2; max_x += 2;
	min_y -= 2; max_y += 2;

	for (int i = min_x; i < 0; i++) {
		cout << " ";
	}
	cout << "0 (Широта)" << endl;


	for (int y = max_y+1; y >= min_y; y--) {
		for (int x = min_x; x <= max_x; x++) {
			bool is_object_here = false;
			object* current = head->next;

			while (current) {
				if (int (current->x )== x && int (current->y) == y) {
					is_object_here = true;
					break;
				}
				current = current->next;
			}

			if (is_object_here) {
				cout << "O";
			}
			else if (x == 0 && y == 0) {
				cout << "+";  
			}
			else if (y == 0) {
				cout << "-";  
				if (x == max_x) {
					cout << " 0 (Долгота)";
				}
			}
			else if (x == 0) {
				cout << "|";
			}
			else {
				cout << "·"; 
			}
		}
		cout << endl;
	}

}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a;
	a = 0;

	cout << "Выберите действие: \n1. Создать список.\n2. Выйти из программы.\n"; 
	cin >> a;
	
	if (a == 1) {
		object* head = create_head();
			while (a != 100) {
				cout << "\nВыберите действие:" << endl;
				cout << "1 - Добавить объект." << endl;
				cout << "2 - Вывести список объектов." << endl;
				cout << "3 - Вывести количество объектов списка." << endl;
				cout << "4 - Найти элемент по его названию." << endl;
				cout << "5 - Удалить выбранный объект." << endl;
				cout << "6 - Удалить объект из прямоугольной области." << endl;
				cout << "7 - Вывести графическую карту." << endl;
				cout << "100 - Удалить список и выйти из программы." << endl;
				cin >> a;
				
				switch (a) {
				case 1: {
					/*cin.ignore();
					cout << "Введите данные:\n";
					double x, y;
					string n_name;
					cout << "Название: ";
					getline(cin, n_name);
					cout << "Широта [-90; 90]: ";
					cin >> y;
					cout << "Долгота [-180; 180]: ";
					cin >> x;
					add_start(head, y, x, n_name);*/
					

					add_start(head, -5.2, 3.9, "Центральный_вокзал");
					add_start(head, -7, -2, "Озеро_Светлое");
					add_start(head, 10.133, 15.6, "Гора_Ветров");
					/*add_start(head, -5, 8, "Музей_Искусств");
					add_start(head, 0, -4, "Городская_библиотека");
					add_start(head, 12, -10, "Маяк_Старого_порта");
					add_start(head, -15, 6, "Ботанический_сад");
					add_start(head, 3, 0, "Парк_Победы");
					add_start(head, 8, -8, "Старый_форт");
					add_start(head, -3, -12, "Рыбацкая_деревня");
					add_start(head, 20, 5, "Аэропорт_Северный");
					add_start(head, -10, -5, "Заповедник_Лесной");
					add_start(head, 7, 9, "Театр_Драмы");
					add_start(head, 0, 0, "Площадь_Звезд");
					add_start(head, 18, -3, "Водопад_Радужный");
					*/

					break;
				}
				case 2: {
					print_objects(head);
					break;
				}
				case 3: {
					int c = count_objects(head);
					cout << c << endl;
					break;
				}
				case 4: {
					string name;
					cout << "Введите название искомого объекта: ";
					cin >> name;
					cout << endl;
					search_objects(head, name);
					break;
				}
				case 5: {
					int n;
					cout << "Введите номер удаляемого элемента: ";
					cin >> n;
					delete_object(head, n);
					break;
				}
				case 6: {
					cout << "Введите данные:\n";

					double min_x, max_x,  min_y, max_y;
					string n_name;

					cout << "Минимальная Широта: ";
					cin >> min_y;
					cout << "Максимальная Широта: ";
					cin >> max_y;
					cout << "Минимальная долгота: ";
					cin >> min_x;
					cout << "Максимальная долгота: ";
					cin >> max_x;

					delete_in_rect(head, min_y, max_y, min_x, max_x);
					cout << "Удаление завершено" << endl;
					break;
				}
				case 7: 
					print_ascii_map(head);
					break;
				case 100: 
					break;
				default:
					break;
				}
			}
			cout << "Список удален, программа закрыта.\n";
	}
	else {
		cout << "Программа закрыта";
	}
	
	return 0;
}