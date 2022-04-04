#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct schedule {  //структура для запису кожного запису
	int beg_m = 0, end_m = 0;
	char name[20];
};
struct space_struct { // структура для запису вільного часу
	int beg, end;
};
char yes_or_no(string); //продовження введення
void now(string, schedule*, int);  //даний час
void spaces(string, string, schedule*, int);  //проміжки після обіду
void make_schedule(string);  //створення розкладу
void print_schedule(string, schedule*, int&);  //друкування розкладу
void print_spaces(string);  //друкування проміжків
void sort(schedule*, int);
char yes_or_no(string ask) {
	bool fail = true;
	string ch;
	while (fail) {
		cout << ask;
		cin >> ch;
		if (ch == "Y" || ch == "y" || ch == "N" || ch == "n")
			fail = false;
	}
	char answer = ch[0];
	return answer;
}
void now(string name, schedule* mass, int n) {
	ifstream inFile(name, ios::binary);
	schedule sched;
	int hours, minutes, time;
	cout << "What time is it now?(hours and minutes with a space between them): ";
	cin >> hours >> minutes;
	time = hours * 60 + minutes;
	int next_time = 24 * 60;
	string next = "Nothing";
	for (int i = 0; i < n; i++) {
		sched = *(mass + i);
		if (sched.beg_m > time && sched.beg_m <= next_time) { //пошук найближчого до поставленого часу
			next_time = sched.beg_m;
			next = sched.name;
		}
	}
	cout << "Next is " << next << endl;
	inFile.close();
}
void make_schedule(string name) {
	ofstream outFile(name, ios::binary | ios::app);
	schedule FirstSched;
	int hours_b, minutes_b, hours_e, minutes_e;
	bool contin = true;
	char ch;
	while (contin) {
		cin.ignore();
		cout << "Enter the name of the act: ";
		cin.getline(FirstSched.name, 20);
		cout << "Enter the beginning (hours and minutes with a space between them): ";
		cin >> hours_b >> minutes_b;
		FirstSched.beg_m = hours_b * 60 + minutes_b;
		cout << "Enter the end (hours and minutes with a space between them): ";
		cin >> hours_e >> minutes_e;
		FirstSched.end_m = hours_e * 60 + minutes_e;
		outFile.write((char*)&FirstSched, sizeof(schedule));
		ch = yes_or_no("Do you want to continue ? (Y / N) ");
		if (ch == 'Y' || ch == 'y')
			contin = true;
		else
			contin = false;
	}
	outFile.close();
}
void print_schedule(string name, schedule* mass, int& n) {
	schedule print_sched;
	ifstream inFile(name, ios::binary);
	cout << "Your schedule is:\n";
	int dur;
	while (inFile.read((char*)&print_sched, sizeof(schedule)))
	{
		*(mass + n) = print_sched;
		n++;
	}
	sort(mass, n);
	for (int i = 0; i < n; i++) {
		printf("Name %20s  Time from %02d:%02d till %02d:%02d\t", mass[i].name, mass[i].beg_m / 60,
			mass[i].beg_m % 60, mass[i].end_m / 60, mass[i].end_m % 60);
		dur = mass[i].end_m - mass[i].beg_m;
		cout << "Duration: " << dur / 60 << "h " << dur % 60 << "m" << endl;
	}
	inFile.close();
}
void spaces(string file, string name2, schedule* mass, int n) {
	ifstream inFile(file, ios::binary);
	ofstream outFile(name2, ios::binary);
	schedule sched;
	space_struct sp;
	int time = 13 * 60;
	for (int i = 0; i < n; i++) {
		sched = *(mass + i);
		if (sched.beg_m<time && sched.end_m>time)
			time = sched.end_m;
		if (sched.beg_m > time && sched.end_m > time) {
			sp.beg = time;
			sp.end = sched.beg_m;
			time = sched.end_m;
			outFile.write((char*)&sp, sizeof(space_struct));
		}
	}
	sp.beg = time;
	sp.end = 24 * 60;
	outFile.write((char*)&sp, sizeof(space_struct));
	outFile.close();
	inFile.close();
	print_spaces(name2);
}
void print_spaces(string name) {
	ifstream inFile(name, ios::binary);
	space_struct sp;
	int dur;
	while (inFile.read((char*)&sp, sizeof(space_struct))) {
		printf("Space from %02d:%02d till %02d:%02d\t", sp.beg / 60, sp.beg % 60, sp.end / 60, sp.end % 60);
		dur = sp.end - sp.beg;
		cout << "Duration: " << dur / 60 << "h " << dur % 60 << "m" << endl;
	}
}
void sort(schedule* mass, int n) {
	schedule extra;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (mass[j].beg_m > mass[j + 1].beg_m) {
				extra = mass[j];
				mass[j] = mass[j + 1];
				mass[j + 1] = extra;
			}
		}
	}
}
