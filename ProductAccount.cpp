#include <iostream>
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

int _menu;

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

class Data
{
private:
	Product product;

public:

	string GetProduct() {
		return product.name + "\n" +
			product.articul + "\n" +
			product.color + "\n" +
			product.sostav + "\n" +
			product.strana_proizvoditel + "\n" +
			product.barcode;
	};

	Data()
	{
		product.articul = "";
		product.barcode = "";
		product.color = "";
		product.name = "";
		product.sostav = "";
		product.strana_proizvoditel = "";
	}

	Data(Product _product)
	{
		product.articul = _product.articul;
		product.barcode = _product.barcode;
		product.color = _product.color;
		product.name = _product.name;
		product.sostav = _product.sostav;
		product.strana_proizvoditel = _product.strana_proizvoditel;
	}

	~Data()
	{
	}

	void Print()
	{
		cout << "Наименование: " << product.name << endl;
		cout << "Артикул: " << product.articul << endl;
		cout << "Цвет: " << product.color << endl;
		cout << "Состав: " << product.sostav << endl;
		cout << "Страна-производитель: " << product.strana_proizvoditel << endl;
		cout << "Штрихкод: " << product.barcode << endl;
	}

	void DataEntry(Product _product)
	{
		product.articul = _product.articul;
		product.barcode = _product.barcode;
		product.color = _product.color;
		product.name = _product.name;
		product.sostav = _product.sostav;
		product.strana_proizvoditel = _product.strana_proizvoditel;
	}
};

// Ввод данных
void DataEntry(Data* (&d), int& n)
{
	// временные переменные
	Product product;
	string t;

	cout << "Введите размер массива: ";
	cin >> n;

	// выделяем память под наш массив
	d = new Data[n];

	for (int i = 0; i < n; i++) {
		getline(cin, t);
		cout << "Введите наименование: ";
		getline(cin, product.name);
		cout << "Введите артикул: ";
		getline(cin, product.articul);
		cout << "Введите цвет: ";
		getline(cin, product.color);
		cout << "Введите состав: ";
		getline(cin, product.sostav);
		cout << "Введите страну-производитель: ";
		getline(cin, product.strana_proizvoditel);
		cout << "Введите штрих-код: ";
		cin >> product.barcode;

		// добавляем новые данные в элемент массива объект класса
		d[i].DataEntry(product);

		cout << "________________________________________\n";
	}
}

// Чтение данных из файла
void DataReading(Data* (&d), int& n, string filename)
{
	//создаем поток для чтения
	ifstream reading(filename);

	if (reading) {
		// временные переменные
		Product product;
		string t;

		reading >> n;

		// выделяем память для массива данных
		d = new Data[n];

		// считываем
		for (int i = 0; i < n; i++) {
			getline(reading, t);
			getline(reading, product.name);
			getline(reading, product.articul);
			getline(reading, product.color);
			getline(reading, product.sostav);
			getline(reading, product.strana_proizvoditel);
			reading >> product.barcode;

			// добавляем новые данные в элемент массива объект класса
			d[i].DataEntry(product);
		}

		cout << "Данные считаны!" << endl;
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}

	reading.close();
}

// Вывод данных на экран
void Print(Data* (&d), int& n)
{
	for (int i = 0; i < n; i++) {
		cout << "Карточка товара №" << i + 1 << endl;

		d[i].Print();
		cout << "________________________________________\n";
	}
}

// Изменение записи
void DataChange(Data* (&d), int& n)
{
	// временные переменные
	Product product;
	int _n;
	string t;

	cout << "Введите номер редактируемой записи (от 1 до " << n << "): ";
	cin >> _n;
	_n--;

	if (_n >= 0 && _n < n) {
		getline(cin, t);
		cout << "Введите новое наименование: ";
		getline(cin, product.name);
		cout << "Введите новый артикул: ";
		getline(cin, product.articul);
		cout << "Введите новый цвет: ";
		getline(cin, product.color);
		cout << "Введите новый состав: ";
		getline(cin, product.sostav);
		cout << "Введите новую страну-производитель: ";
		getline(cin, product.strana_proizvoditel);
		cout << "Введите новый штрих-код: ";
		cin >> product.barcode;

		// добавляем новые данные в элемент массива объект класса
		d[_n].DataEntry(product);
	}
	else {
		cout << "Номер записи введен неверно!" << endl;
	}
}

// Копирование записи
void Copy(Data* d_n, Data* d_o, int& n)
{
	for (int i = 0; i < n; i++) {
		d_n[i] = d_o[i];
	}
}

// Добавление записи
void AddData(Data* (&d), int& n)
{
	// временные переменные
	Product product;
	Data* buf = new Data[n];
	int size = n, new_size = ++n;
	string t;

	Copy(buf, d, size);

	d = new Data[new_size];

	Copy(d, buf, size);

	getline(cin, t);
	cout << "Введите новое наименование: ";
	getline(cin, product.name);
	cout << "Введите новый артикул: ";
	getline(cin, product.articul);
	cout << "Введите новый цвет: ";
	getline(cin, product.color);
	cout << "Введите новый состав: ";
	getline(cin, product.sostav);
	cout << "Введите новую страну-производитель: ";
	getline(cin, product.strana_proizvoditel);
	cout << "Введите новый штрих-код: ";
	cin >> product.barcode;

	// добавляем новые данные в элемент массива объект класса
	d[size].DataEntry(product);

	cout << "Данные добавлены!" << endl;

	delete[] buf;
}

// Удаление записи
void DeleteData(Data* (&d), int& n)
{
	// временные переменные
	int _n;
	Data* buf = new Data[n];

	cout << "Введите номер удаляемой записи (от 1 до " << n << "): ";
	cin >> _n;
	_n--;

	if (_n >= 0 && _n < n) {
		Copy(buf, d, n);
		int q = 0;
		n--;

		// выделяем новую память
		d = new Data[n];

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
void SaveData(Data* (&d), int& n, string filename)
{
	// создать поток для записи в файл
	ofstream record(filename);

	if (record) {
		record << n << endl;

		for (int i = 0; i < n; i++) {
			record << d[i].GetProduct();

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
	setlocale(LC_CTYPE, "rus");

	Menu();
	int _actions; // действие
	string filename;

	int _size = 0; // количество данных
	Data* d = new Data[_size]; // массив данных

	while (_menu != 0)
	{
		switch (_menu)
		{
		case 1:
			system("cls"); // очистка экрана

			cout << "Ввести данные о продукции вручную (1) или считать из файла (2)?: ";
			cin >> _actions;

			system("cls");

			if (_actions == 1) {
				DataEntry(d, _size);
			}
			else {
				DataReading(d, _size, "input.txt");
			}

			system("pause");
			system("cls");
			Menu();
			break;
		case 2:
			system("cls");

			if (_size > 0)
				Print(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case 3:
			system("cls");

			if (_size > 0)
				AddData(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");

			if (_size > 0)
				DataChange(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case 5:
			system("cls");

			if (_size > 0)
				DeleteData(d, _size);
			else
				cout << "Данные отсутствуют!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;
		case 6:
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
			system("cls");
			Menu();
			break;
		}
	}

	system("cls");
	cout << "Работа с программой завершена!" << endl;
	system("pause");
}
