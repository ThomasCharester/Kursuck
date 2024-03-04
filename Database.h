#pragma once
#ifndef DATABASE
#define DATABASE

#include <fstream>
#include <vector>

#include "Choice.h"
#include "Participant.h"

class Database {
public:
	Database(UI<Database>& ui) {
		this->ui = &ui;

		switch (readOrNew()) {
		case 'Y':
		case 'y':
			readFile();
			break;
		case 'N':
		case 'n':

			break;
		}
	}
	char readOrNew() {
		char ch = ui->input<char>("Will you edit existing database? (Y/N)");

		return ch;
	}
	int addParticipant() {
		std::string FIO = ui->input<std::string>("Participant FIO");
		int playerID = ui->input<int>("Participant player ID");
		std::string teamName = ui->input<std::string>("Participant team name");
		std::string country = ui->input<std::string>("Participant country");
		int age = ui->input<int>("Participant age");
		float weight = ui->input<float>("Participant wieght");
		float height = ui->input<float>("Participant height");

		participants.push_back(Participant(FIO, country, teamName, weight, height, playerID, age));
		return 1;
	}
	int removeParticipant() {
		system("cls");
		if(participants.empty()) return 1;
		showParticipants();
		int id = ui->input<int>("Participant to remove id");

		participants.erase(participants.begin() + id);

		ui->pressAnyButton();
		return 1;
	}
	int showParticipants() {
		system("cls");
		for (int i = 0; i < participants.size(); i++)
			ui->print<std::string>(participants.at(i).print());
		ui->pressAnyButton();
		return 1;
	}
	int specialTask() {

		return 1;
	}
	int sort() {

		return 1;
	}
	int findLinear() {
		system("cls");

		int key = ui->input<int>("Enter key");

		for (int i = 0; i < participants.size(); i++)
			if ((int)participants.at(i) == key)
				ui->print<std::string>(participants.at(i).print());

		ui->pressAnyButton();
		return 1;
	}
	void enterFileName() {
		system("cls");
		fileName = ui->input<std::string>("Text file name without .txt format");
		fileName += ".txt";
	}
	int writeFile() {
		//Создаём поток чтения файла
		std::ofstream file;

		if (fileName.empty()) enterFileName();
		//Открываем для чтения
		file.open(fileName);
		//Проверка на то, открыт ли файл
		if (file.is_open()) {
			//Записываем все данные о Box-ах в файл, функция printBox() - вернёт строку со всеми данными
			for (int i = 0; i < participants.size(); i++) {
				file << participants.at(i) << '\n';
			}
			//закрываем файл
			file.close();
		}
		//Если файл не открыт, то ошибка
		else std::cout << "Oshibka otkritiya fila";
		return 1;
	}
	int readFile() {
		//Строчка файла
		std::string line;
		//Проверка, указано ли имя файла, вынес в переменную
		if (fileName.empty()) enterFileName();
		//Создаём чтения потока
		std::ifstream file;
		//Открываем для чтения
		file.open(fileName);
		//Проверка на то, открыт ли файл
		if (file.is_open()) {
			//Читаем из файла, пока не конец строки
			while (!file.eof()) {
				//Читаем строку
				std::getline(file, line);
				//Число переменных класса Participant, у меня их 4
				int dataCount = 7;
				//Массив из строк данных
				std::string data[7];
				//Смотрим не конец ли это файла, если что - разрываем
				if (line.empty())
					break;
				//Записываем в базу данных слова, размещённые через пробелы
				for (int i = 0; dataCount > 0; i++) {
					//Проверяем на пробельный символ и уменьшаем количество оставшихся переменных для записи
					if (line[i] == ' ')
						dataCount--;
					//Добавляем в строку по символу
					else
						data[dataCount - 1] += line[i];
				}
				//Создаём Participant, которому указываем параметрами характеристики прочитанные из файла
				participants.push_back(Participant(Participant(
					data[5],
					data[4],
					data[3],
					std::stof(data[2]),
					std::stof(data[1]),
					std::stoi(data[6]),
					std::stoi(data[0]))));
			}
			//закрываем файл
			file.close();
		}
		//Если файл не открыт, то ошибка
		else std::cout << "Oshibka otkritiya fila";

		return 1;
	}
private:
	std::string fileName;
	std::vector<Participant> participants;
	UI<Database>* ui;
};





#endif // !DATABASE
