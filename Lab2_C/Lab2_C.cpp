//Створити файл зі списком справ на поточний день: умовна назва, час початку, передбачувана тривалість. Визначити,
//яка справа за списком наступна (найближча до поточного часу). Створити файл з інформацією про вільний час у другій половині дня (після 13:00):
//початок та закінчення тимчасового проміжку та його тривалість (розрахувати)
#include "Header.h"
int main() {
	string name_outF;  //ім'я файлу
	cout << "Enter the name of a file to write schedule in: ";
	cin >> name_outF;
	int n = 0;
	schedule m[20];
	make_schedule(name_outF);  //створення файлу з розкладом
	print_schedule(name_outF, m, n); //виведення вмісту файлу для користувача
	now(name_outF, m, n); //наступне для даного часу діло
	string name2;  //ім'я файлу для запису вільних проміжків після обіду
	cout << "Enter the name of a file to write spaces in: ";
	cin >> name2;
	spaces(name_outF, name2, m, n);  //створення файлу з проміжками 
	return 0;
}