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
		//������ ����� ������ �����
		std::ofstream file;

		if (fileName.empty()) enterFileName();
		//��������� ��� ������
		file.open(fileName);
		//�������� �� ��, ������ �� ����
		if (file.is_open()) {
			//���������� ��� ������ � Box-�� � ����, ������� printBox() - ����� ������ �� ����� �������
			for (int i = 0; i < participants.size(); i++) {
				file << participants.at(i) << '\n';
			}
			//��������� ����
			file.close();
		}
		//���� ���� �� ������, �� ������
		else std::cout << "Oshibka otkritiya fila";
		return 1;
	}
	int readFile() {
		//������� �����
		std::string line;
		//��������, ������� �� ��� �����, ����� � ����������
		if (fileName.empty()) enterFileName();
		//������ ������ ������
		std::ifstream file;
		//��������� ��� ������
		file.open(fileName);
		//�������� �� ��, ������ �� ����
		if (file.is_open()) {
			//������ �� �����, ���� �� ����� ������
			while (!file.eof()) {
				//������ ������
				std::getline(file, line);
				//����� ���������� ������ Participant, � ���� �� 4
				int dataCount = 7;
				//������ �� ����� ������
				std::string data[7];
				//������� �� ����� �� ��� �����, ���� ��� - ���������
				if (line.empty())
					break;
				//���������� � ���� ������ �����, ����������� ����� �������
				for (int i = 0; dataCount > 0; i++) {
					//��������� �� ���������� ������ � ��������� ���������� ���������� ���������� ��� ������
					if (line[i] == ' ')
						dataCount--;
					//��������� � ������ �� �������
					else
						data[dataCount - 1] += line[i];
				}
				//������ Participant, �������� ��������� ����������� �������������� ����������� �� �����
				participants.push_back(Participant(Participant(
					data[5],
					data[4],
					data[3],
					std::stof(data[2]),
					std::stof(data[1]),
					std::stoi(data[6]),
					std::stoi(data[0]))));
			}
			//��������� ����
			file.close();
		}
		//���� ���� �� ������, �� ������
		else std::cout << "Oshibka otkritiya fila";

		return 1;
	}
private:
	std::string fileName;
	std::vector<Participant> participants;
	UI<Database>* ui;
};





#endif // !DATABASE
