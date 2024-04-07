#pragma once
#ifndef DATABASE
#define DATABASE

#include <fstream>
#include <vector>
#include <tuple>
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
		ui->printMinecraft("&1Will &4you &2edit &5existing &6database? &0(&2Y&0/&3N&0) ");
		char ch = (char)(ui->inputInstant("", false, 122, 65));

		return ch;
	}
	int editDatabase() {
		UI<Database>::Choice taskChoices[2]{
			UI<Database>::Choice(this, &Database::addParticipant, "Add participant"),
			UI<Database>::Choice(this, &Database::removeParticipant, "Remove participant")
		};

		return ui->choose(taskChoices, 2, "Choose option", false);
	}
	int search() {
		UI<Database>::Choice taskChoices[2]{
			UI<Database>::Choice(this,&Database::findLinear,"Find linear"),
			UI<Database>::Choice(this,&Database::findBinary,"Find binary")
		};

		return ui->choose(taskChoices, 2, "Choose type of sort", false);
	}
	int file() {
		UI<Database>::Choice taskChoices[3]{
			UI<Database>::Choice(this,&Database::writeFile,"Rewrite file"),
			UI<Database>::Choice(this,&Database::addFromFile,"Add from file"),
			UI<Database>::Choice(this,&Database::readFile,"Read file")
		};

		return ui->choose(taskChoices, 3, "File", false);
	}
	int addParticipant() {
		std::string FIO = ui->input<std::string>("Participant &2FIO");
		int playerID = ui->input<int>("Participant &2player ID");
		std::string teamName = ui->input<std::string>("Participant &2team name");
		std::string country = ui->input<std::string>("Participant &2country");
		int age = ui->input<int>("Participant &2age");
		float weight = ui->input<float>("Participant &2weight");
		float height = ui->input<float>("Participant &2height");

		participants.push_back(new Participant(FIO, country, teamName, weight, height, playerID, age));

		addTeamMember(participants.size() - 1);

		return 1;
	}
	void addTeamMember(int i) {
		bool found = false;
		for (int j = 0; j < teams.size() && !found; j++) {
			if (std::string(*participants.at(i)) == std::get<0>(teams.at(j))) {
				std::get<1>(teams.at(j)) = (std::get<1>(teams.at(j)) * std::get<2>(teams.at(j)) + int(*participants.at(i)));
				std::get<2>(teams.at(j))++;
				std::get<1>(teams.at(j)) /= std::get<2>(teams.at(j));
				found = true;
			}
		}
		if (!found || teams.empty()) {
			teams.push_back(std::make_tuple<std::string, int, int>(std::string(*participants.at(i)), int(*participants.at(i)), 1));
		}
	}
	void removeTeamMember(int i) {
		for (int j = 0; j < teams.size(); j++) {
			if (std::string(*participants.at(i)) == std::get<0>(teams.at(j))) {
				std::get<1>(teams.at(j)) = (std::get<1>(teams.at(j)) * std::get<2>(teams.at(j)) - int(*participants.at(i)));
				std::get<2>(teams.at(j))--;
				std::get<1>(teams.at(j)) /= std::get<2>(teams.at(j));
			}
		}
	}
	int removeParticipant() {
		system("cls");
		if (participants.empty()) ui->printMinecraft("&1Nothing to delete ");
		else {
			showParticipants();
			int id = ui->input<int>("Participant to &1remove &0id");
			removeTeamMember(id);
			participants.erase(participants.begin() + id);
		}
		ui->pressAnyButton();
		return 1;
	}
	int showTeams() {
		system("cls");
		if (teams.empty()) ui->printMinecraft("&1Nothing to output ");
		else {
			ui->printMinecraft("&3Teams: ");
			for (size_t j = 0; j < teams.size(); j++) {
				ui->print<std::string>(std::get<0>(teams.at(j)));
				for (size_t i = 0; i < participants.size(); i++) {
					if (std::string(*participants.at(i)) == std::get<0>(teams.at(j)))ui->print<std::string>(participants.at(i)->print());
				}
				std::cout << '\n';
			}
		}
		ui->pressAnyButton();
		return 1;
	}
	int showParticipants() {
		system("cls");
		if (participants.empty()) ui->printMinecraft("&1Nothing to output ");
		else {
			for (int i = 0; i < participants.size(); i++) {
				ui->print<std::string>(participants.at(i)->print());
			}
		}
		ui->pressAnyButton();
		return 1;
	}
	int specialTask() {
		// Имя команды/Возраст общий/Кол-во участников
		std::vector<std::tuple<std::string, int, int>> teams = this->teams;

		for (size_t j = 0; j < teams.size() - 1; j++) {
			if (std::get<1>(teams.at(j + 1)) > std::get<1>(teams.at(j))) {
				teams.erase(teams.begin() + j + 1);
				j--;
			}
			else if (std::get<1>(teams.at(j + 1)) < std::get<1>(teams.at(j))) {
				for (int i = j; i > 0; i--) {
					teams.erase(teams.begin() + i);
					j = 0;
				}
			}
		}
		system("cls");
		ui->printMinecraft("&3Youngest &0teams is: ");
		for (size_t j = 0; j < teams.size(); j++) {
			ui->print<std::string>(std::get<0>(teams.at(j)));
			for (size_t i = 0; i < participants.size(); i++) {
				if (std::string(*participants.at(i)) == std::get<0>(teams.at(j)))ui->print<std::string>(participants.at(i)->print());
			}
			std::cout << '\n';
		}
		ui->pressAnyButton();
		return 1;
	}
	int sort() {
		if (teams.empty()) ui->printMinecraft("&1Nothing to sort ");
		else {
			UI<Database>::Choice taskChoices[4]{
				UI<Database>::Choice(this,&Database::quickSort,"Quick"),
				UI<Database>::Choice(this,&Database::shellSort,"Shell"),
				UI<Database>::Choice(this,&Database::pigeonholeSort,"Pigeonhole"),
				UI<Database>::Choice(this,&Database::bubbleSort,"Bubble")
			};

			return ui->choose(taskChoices, 4, "Sort", false);
		}
		return 1;
	}
	int quickSort() {
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
			if (f <= l) 
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
	int shellSort() {
		int i, j, step;
		Participant* tmp;
		for (step = participants.size() / 2; step > 0; step /= 2)
			for (i = step; i < participants.size(); i++)
			{
				tmp = participants[i];
				for (j = i; j >= step; j -= step)
				{
					if (*tmp < *participants[j - step])
						participants[j] = participants[j - step];
					else
						break;
				}
				participants[j] = tmp;
			}
		return 1;
	}
	int pigeonholeSort() {
		Participant* min = participants[0], * max = participants[0];
		for (int i = 1; i < participants.size(); i++) {
			if (*participants[i] < *min)
				min = participants[i];
			if (*participants[i] > *max)
				max = participants[i];
		}
		int range = (int)(*max) - (int)(*min) + 1;

		std::vector<Participant*>* holes = new std::vector<Participant*>[range];

		for (int i = 0; i < participants.size(); i++)
			holes[(int)(*participants[i]) - (int)(*min)].push_back(participants[i]);

		int index = 0;
		for (int i = 0; i < range; i++) {
			std::vector<Participant*>::iterator it;
			for (it = holes[i].begin(); it != holes[i].end(); ++it)
				participants[index++] = *it;
		}
		return 1;
	}
	int bubbleSort() {
		for (int step = 0; step < participants.size(); ++step) {
			for (int i = 0; i < participants.size() - step - 1; i++) {
				if (*participants[i] > *participants[i + 1]) {
					Participant* temp = participants[i];
					participants[i] = participants[i + 1];
					participants[i + 1] = temp;
				}
			}
		}
		return 1;
	}
	int findLinear() {
		system("cls");

		int key = ui->input<int>("Enter key");
		bool found = false;
		for (int i = 0; i < participants.size(); i++)
			if (int(*participants.at(i)) == key)
			{
				found = true;
				ui->print<std::string>(participants.at(i)->print());
			}
		if (!found)ui->printMinecraft("&1Not found");
		ui->pressAnyButton();
		return 2;
	}
	int findBinary() {
		system("cls");

		int key = ui->input<int>("Enter key");

		size_t mid = (participants.size() - 1) / 2, dist;
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
			ui->printMinecraft("&1Not Found");

		ui->pressAnyButton();
		return 2;
	}
	void enterFileName(std::string& fileName) {
		system("cls");
		fileName = ui->input<std::string>("Text file name without .format, then press enter");
		fileName += ".ednach";
	}
	int writeFile() {
		std::ofstream file;

		if (fileName.empty()) enterFileName(fileName);
		file.open(fileName);
		if (file.is_open()) {
			for (int i = 0; i < participants.size(); i++) {
				file << *participants.at(i) << '\n';
			}
			file.close();
		}
		else ui->printMinecraft("&1File open error");
		return 2;
	}
	int readFile(bool extendedFile) {
		std::string line;
		if (extendedFile)
		{
			participants.clear();
			std::string fileName;
			enterFileName(fileName);
		}
		else if (fileName.empty()) enterFileName(fileName);
		std::ifstream file;
		file.open(fileName);
		if (file.is_open()) {
			while (!file.eof()) {
				std::getline(file, line);
				int dataCount = 7;
				std::string data[7];
				if (line.empty())
					break;
				for (int i = 0; dataCount > 0; i++) {
					if (line[i] == ' ')
						dataCount--;
					else
						data[dataCount - 1] += line[i];
				}
				participants.push_back(new Participant(Participant(
					data[5],
					data[4],
					data[3],
					std::stof(data[2]),
					std::stof(data[1]),
					std::stoi(data[6]),
					std::stoi(data[0]))));

				addTeamMember(participants.size() - 1);
			}
			file.close();
		}
		else ui->printMinecraft("&1File open error");

		return 2;
	}
	int readFile() { return readFile(false); }
	int addFromFile() { return readFile(true); }
private:
	std::string fileName;
	std::vector<Participant*> participants;
	UI<Database>* ui;
	// Содержит информацию о командах в порядке Имя команды/Возраст общий/Кол-во участников
	std::vector<std::tuple<std::string, int, int>> teams;
};





#endif // !DATABASE
