﻿#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Product {
	string name,
		color,
		articul,
		sostav,
		barcode,
		strana_proizvoditel;
};

// глобальная переменная, 
// в которой находится введенный номер меню
char _menu;

void Menu() {
	cout << "Выберите действие: " << endl
		<< "(0) Выход из программы" << endl
		<< "(1) Ввод данных" << endl
		<< "(2) Вывод данных" << endl
		<< "(3) Добавление данных" << endl
		<< "(4) Изменение данных" << endl
		<< "(5) Удаление данных" << endl
		<< "(6) Сохранение данных" << endl
		<< "Ваш выбор: ";
	cin >> _menu;
}

// Ввод данных
void DataEntry(Product* (&d), int& n)
{
	// временные переменные
	string t;

	cout << "Введите размер массива: ";
	cin >> n;

	// выделяем память под наш массив
	d = new Product[n];

	// добавляем новые данные в элементы массива
	for (int i = 0; i < n; i++) {
		getline(cin, t);
		cout << "Введите наименование: ";
		getline(cin, d[i].name);
		cout << "Введите артикул: ";
		getline(cin, d[i].articul);
		cout << "Введите цвет: ";
		getline(cin, d[i].color);
		cout << "Введите состав: ";
		getline(cin, d[i].sostav);
		cout << "Введите страну-производитель: ";
		getline(cin, d[i].strana_proizvoditel);
		cout << "Введите штрих-код: ";
		cin >> d[i].barcode;

		cout << "________________________________________\n";
	}
}

// Чтение данных из файла
void DataReading(Product* (&d), int& n, string filename)
{
	//создаем поток для чтения
	ifstream reading(filename);

	if (reading) {
		// временные переменные
		string t;

		reading >> n;

		// выделяем память для массива данных
		d = new Product[n];

		// считываем
		// добавляем новые данные в элемент массива
		for (int i = 0; i < n; i++) {
			getline(reading, t);
			getline(reading, d[i].name);
			getline(reading, d[i].articul);
			getline(reading, d[i].color);
			getline(reading, d[i].sostav);
			getline(reading, d[i].strana_proizvoditel);
			reading >> d[i].barcode;
		}

		cout << "Данные считаны!" << endl;
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}

	reading.close();
}

// Вывод данных на экран
void Print(Product d[], int n)
{
	for (int i = 0; i < n; i++) {
		cout << "Карточка товара №" << i + 1 << endl;
		cout << "Наименование: " << d[i].name << endl;
		cout << "Артикул: " << d[i].articul << endl;
		cout << "Цвет: " << d[i].color << endl;
		cout << "Состав: " << d[i].sostav << endl;
		cout << "Страна-производитель: " << d[i].strana_proizvoditel << endl;
		cout << "Штрихкод: " << d[i].barcode << endl;
		cout << "________________________________________\n";
	}
}

// Изменение записи
void DataChange(Product* (&d), int& n)
{
	// временные переменные
	int _n;
	string t;

	cout << "Введите номер редактируемой записи (от 1 до " << n << "): ";
	cin >> _n;
	_n--;

	// если номер записи есть в массиве, то изменяем данные в элементе массива
	if (_n >= 0 && _n < n) {
		getline(cin, t);
		cout << "Введите новое наименование: ";
		getline(cin, d[_n].name);
		cout << "Введите новый артикул: ";
		getline(cin, d[_n].articul);
		cout << "Введите новый цвет: ";
		getline(cin, d[_n].color);
		cout << "Введите новый состав: ";
		getline(cin, d[_n].sostav);
		cout << "Введите новую страну-производитель: ";
		getline(cin, d[_n].strana_proizvoditel);
		cout << "Введите новый штрих-код: ";
		cin >> d[_n].barcode;
	}
	else {
		cout << "Номер записи введен неверно!" << endl;
	}
}

// Копирование записи
void Copy(Product* d_n, Product* d_o, int n)
{
	for (int i = 0; i < n; i++) {
		d_n[i] = d_o[i];
	}
}

// Добавление записи
void AddData(Product* (&d), int& n)
{
	// временные переменные
	Product* buf = new Product[n];
	int size = n, new_size = ++n;
	string t;

	Copy(buf, d, size);

	d = new Product[new_size];

	Copy(d, buf, size);

	// добавляем новые данные в элемент массива
	getline(cin, t);
	cout << "Введите новое наименование: ";
	getline(cin, d[size].name);
	cout << "Введите новый артикул: ";
	getline(cin, d[size].articul);
	cout << "Введите новый цвет: ";
	getline(cin, d[size].color);
	cout << "Введите новый состав: ";
	getline(cin, d[size].sostav);
	cout << "Введите новую страну-производитель: ";
	getline(cin, d[size].strana_proizvoditel);
	cout << "Введите новый штрих-код: ";
	cin >> d[size].barcode;

	cout << "Данные добавлены!" << endl;

	delete[] buf;
}

// Удаление записи
void DeleteData(Product* (&d), int& n)
{
	// временные переменные
	int _n;
	Product* buf = new Product[n];

	cout << "Введите номер удаляемой записи (от 1 до " << n << "): ";
	cin >> _n;
	_n--;

	if (_n >= 0 && _n < n) {
		Copy(buf, d, n);
		int q = 0;
		n--;

		// выделяем новую память
		d = new Product[n];

		for (int i = 0; i <= n; i++) {
			if (i != _n) {
				d[q] = buf[i];
				q++;
			}
		}

		cout << "Запись удалена!" << endl;
	}
	else {
		cout << "Номер записи введен неверно!" << endl;
	}

	delete[] buf;
}

// Сохранение массива данных в файл
void SaveData(Product d[], int n, string filename)
{
	// создать поток для записи в файл
	ofstream record(filename);

	if (record) {
		record << n << endl;

		for (int i = 0; i < n; i++) {
			record << d[i].name << endl;
			record << d[i].articul << endl;
			record << d[i].color << endl;
			record << d[i].sostav << endl;
			record << d[i].strana_proizvoditel << endl;
			record << d[i].barcode;

			if (i < n - 1)
				record << endl;
		}

		record.close();

		cout << "Данные сохранены!" << endl;
	}
	else {
		cout << "Ошибка записи в файл!" << endl;
	}
}

int main()
{
	// руссификация ввода/вывода
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "rus");

	Menu();

	int _actions; // действие
	int _size = 0; // количество данных
	Product* d = new Product[_size]; // массив данных

	while (_menu != '0')
	{
		switch (_menu)
		{
		case '1':
			system("cls"); // очистка экрана

			cout << "Ввести данные о продукции вручную (1) или считать из файла (2)?: ";
			cin >> _actions;

			system("cls");

			if (_actions == 1) {
				DataEntry(d, _size);
			}
			else if (_actions == 2) {
				DataReading(d, _size, "input.txt");
			}

			system("pause");
			system("cls");
			Menu();
			break;
		case '2':
			system("cls");

			if (_size > 0)
				Print(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case '3':
			system("cls");

			if (_size > 0)
				AddData(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case '4':
			system("cls");

			if (_size > 0)
				DataChange(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case '5':
			system("cls");

			if (_size > 0)
				DeleteData(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case '6':
			system("cls");

			if (_size > 0)
				SaveData(d, _size, "out.txt");
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		default:
			cout << "Пункт меню введен неверно!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		}
	}

	system("cls");
	cout << "Работа с программой завершена!" << endl;
	system("pause");
}
