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

		participants.push_back(new Participant(FIO, country, teamName, weight, height, playerID, age));
		return 1;
	}
	int removeParticipant() {
		system("cls");
		if (participants.empty()) return 1;
		showParticipants();
		int id = ui->input<int>("Participant to remove id");

		participants.erase(participants.begin() + id);

		ui->pressAnyButton();
		return 1;
	}
	int showParticipants() {
		system("cls");
		for (int i = 0; i < participants.size(); i++) {
			ui->print<std::string>(participants.at(i)->print());
		}
		ui->pressAnyButton();
		return 1;
	}
	int specialTask() {

		return 1;
	}
	int sort() {
		quicksort(0, participants.size() - 1);
		return 1;
	}
	void quicksort(int first, int last)
	{
		int f = first, l = last;
		Participant* mid = participants[(f + l) / 2], * count = participants[f];
		do
		{
			while (*participants[f] < *mid) f++;
			while (*participants[l] > *mid) l--;
			if (f <= l) //������������ ���������
			{
				count = participants[f];
				participants[f] = participants[l];
				participants[l] = count;
				f++;
				l--;
			}
		} while (f < l);
		if (first < l) quicksort(first, l);
		if (f < last) quicksort(f, last);
	}
	int search() {

		UI<Database>::Choice taskChoices[2]{
			UI<Database>::Choice(this,&Database::findLinear,"Find linear"),
			UI<Database>::Choice(this,&Database::findBinary,"Find binary")
		};

		return ui->choose(taskChoices, 2, "Choose type of sort", false);
	}
	int findLinear() {
		system("cls");

		int key = ui->input<int>("Enter key");

		for (int i = 0; i < participants.size(); i++)
			if (int(*participants.at(i)) == key)
				ui->print<std::string>(participants.at(i)->print());

		ui->pressAnyButton();
		return 2;
	}
	int findBinary() {
		system("cls");

		int key = ui->input<int>("Enter key");

		int mid = (participants.size() - 1) / 2, dist;
		bool found = false;
		while (!found) {
			dist = (mid) / 2;

			if (key == int(*participants.at(mid))) found = true;
			if (mid < participants.size() && int(*participants.at(mid)) < key)  mid += dist;
			else if (mid > 0 && int(*participants.at(mid)) > key) mid -= dist;
		}

		if (found) {
			ui->print<std::string>(participants.at(mid)->print());

			dist = 1;
			while (mid + dist < participants.size() && *participants.at(mid) == *participants.at(mid + dist)) {
				ui->print<std::string>(participants.at(mid + dist)->print());
				dist++;
			}
			dist = 1;
			while (mid - dist >= 0 && *participants.at(mid) == *participants.at(mid - dist)) {
				ui->print<std::string>(participants.at(mid - dist)->print());
				dist++;
			}
		}
		else
			ui->print<std::string>("Not found");

		ui->pressAnyButton();
		return 2;
	}
	int file() {
		UI<Database>::Choice taskChoices[2]{
			UI<Database>::Choice(this,&Database::readFile,"Read file"),
			UI<Database>::Choice(this,&Database::writeFile,"Write file")
		};

		return ui->choose(taskChoices, 2, "File", false);
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
				file << *participants.at(i) << '\n';
			}
			//��������� ����
			file.close();
		}
		//���� ���� �� ������, �� ������
		else std::cout << "Oshibka otkritiya fila";
		return 2;
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
				participants.push_back(new Participant(Participant(
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

		return 2;
	}
private:
	std::string fileName;
	std::vector<Participant*> participants;
	UI<Database>* ui;
};





#endif // !DATABASE
