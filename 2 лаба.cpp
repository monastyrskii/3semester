//Монастырский Егор, 18 САИ-1

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;


class phcall
{
public:
	char from[100], to[100];
	int dateandtime, date, time, howlong, ID;
	int days, months, years, hours, minutes;

	//конструктор
	phcall(char from[100], char to[100], int days, int months, int years, int hours, int minutes, int howlong)
	{
		strcpy(this->from, from);
		strcpy(this->to, to);
		this->days = days;
		this->months = months;
		this->years = years;
		this->hours = hours;
		this->minutes = minutes;
		this->howlong = howlong;
		date = days + months * 30 + years * 365;
		time = hours * 60 + minutes;
		dateandtime = time + (date - 1) * 1440;
	}
	void furcout() {
		cout << ID << "   " << from << " " << to << " " << days << "." << months << "." << years << "   " << hours << ":" << minutes << "    " << howlong;
	}
};

int whatdoyouneed() {
	int input;
	cout << "Что вам нужно? \n";
	cout << "1 - вывести полный список звонков \n";
	cout << "2 - добавить по номеру \n";
	cout << "3 - удалить по номеру \n";
	cout << "4 - вывод с даты по дату \n";
	cout << "5 - сортировка по давности \n";
	cout << "6 - сортировка по длительности \n";
	cout << "7 - вывод от конкретного человека \n";
	cout << "8 - вывод к конкретному человеку \n";

	cin >> input;
	return input;
}



int main()
{
	vector<phcall> callbook;
	vector<phcall>::const_iterator it = callbook.begin();

	ifstream inputfile; 	//открываем файл
	inputfile.exceptions(ifstream::badbit | ifstream::failbit);

	int i(1), number, day, month, year, hour, minute, howlong, ID;
	char from[100], to[100];

	try {
		inputfile.open("INPUT.TXT");
		cout << "Файл открыт" << endl;
		while (i) { 		//считываем данные из файла
			inputfile >> number;
			if (number == i) {
				inputfile >> from >> to >> day >> month >> year >> hour >> minute >> howlong;
				phcall addition(from, to, day, month, year, hour, minute, howlong);
				addition.ID = i;
				callbook.push_back(addition);
				i++;
			}
			else i = 0;
		}

	}
	catch (const ifstream::failure & ex) {
		cout << ex.what() << endl;
		cout << ex.code() << endl;
		cout << "Ошибка. Возможно файл был удалён или перемещён" << endl;
	}

	int input = whatdoyouneed();

	if (input == 1) {		// 1. Вывести полный список звонков
		for (i = 0; i < callbook.size(); i++) {
			callbook.at(i).furcout();
		}
		input = whatdoyouneed();
	}

	if (input == 2) { 	// 2. Добавить по номеру
		cout << "Введите номер, который вы хотите добавить \n";
		cin >> input;
		cout << "Введите нужные данные: \n";
		cin >> from >> to >> day >> month >> year >> hour >> minute >> howlong >> ID;
		phcall addition(from, to, day, month, year, hour, minute, howlong);
		addition.ID = ID;
		advance(it, input);
		callbook.insert(it, addition);
		it = callbook.begin();
	}

	else if (input == 3) {	// 3. Удалить по номеру
		cout << "Введите номер, котороый вы хотите удалить \n";
		cin >> input;
		advance(it, input);
		callbook.erase(it);
		it = callbook.begin();
	}

	else if (input == 4) { 	// 4. Вывод с даты по дату
		int mindate, maxdate;
		cout << "Введите минимальную дату (dd mm yy) \n";
		cin >> day >> month >> year;
		mindate = day + month * 30 + year * 365;
		cout << "Введите максимальную дату (dd mm yy) \n";
		cin >> day >> month >> year;
		maxdate = day + month * 30 + year * 365;

		cout << "Результаты отбора по дате \n";
		for (i = 0; i < callbook.size(); i++) {
			if (callbook[i].date >= mindate && callbook[i].date <= maxdate) {
				callbook.at(i).furcout();
			}
		}
	}

	else if (input == 5) { 	// 5. Сортировка по дате и времени
		cout << "Сортировка по дате: \n";
		sort(callbook.begin(), callbook.end(), [](const phcall& a, const phcall& b) {
			return a.date < b.date;
			});
		for (i = 0; i < callbook.size(); i++) {
			callbook.at(i).furcout();
		}
		cout << "\nСортировка по времени: \n";
		sort(callbook.begin(), callbook.end(), [](const phcall& a, const phcall& b) {
			return a.time < b.time;
			});
		for (i = 0; i < callbook.size(); i++) {
			callbook.at(i).furcout();
		}
		cout << "\nСортировка по дате и времени: \n";
		sort(callbook.begin(), callbook.end(), [](const phcall& a, const phcall& b) {
			return a.dateandtime < b.dateandtime;
			});
		for (i = 0; i < callbook.size(); i++) {
			callbook.at(i).furcout();
		}
	}

	else if (input == 6) { 	// 6. Сортировка по длительности
		cout << "\nСортировка по длительности: \n";
		sort(callbook.begin(), callbook.end(), [](const phcall& a, const phcall& b) {
			return a.howlong < b.howlong;
			});
		for (i = 0; i < callbook.size(); i++) {
			callbook.at(i).furcout();
		}
		input = whatdoyouneed();
	}

	else if (input == 7) { 	// 7. Вывод от конкретного человека
		cout << "Введите имя человека для поиска звонков от него \n";
		cin >> from;
		for (i = 0; i < callbook.size(); i++) {
			if (callbook.at(i).from == from) {
				callbook.at(i).furcout();
			}
		}
	}

	else if (input == 8) { 	// 8. вывод к конкретному человеку
		cout << "Введите имя человека для поиска звонков к нему \n";
		cin >> to;
		for (i = 0; i < callbook.size(); i++) {
			if (callbook.at(i).to == to) {
				callbook.at(i).furcout();
			}
		}
	}

	return 0;

}