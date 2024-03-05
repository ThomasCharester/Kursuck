#pragma once
#ifndef CHOICE
#define CHOICE

#include <iostream>
#include <string>
#include <conio.h>

template<typename T>
class UI {
public:
	enum exitValues : int {
		exitChoice = 0,
		continueChoice = 1,
		exitAndContinueChoice = 2,
		shutdown = 3
	};
	struct Choice {
		T* funcOwner;
		int (T::* func)();
		std::string choiceName;
		Choice() {
			funcOwner = nullptr;
			func = nullptr;
			choiceName = "Bruh";
		}
		Choice(T* funcOwner, int (T::* func)(), std::string choiceName) {
			this->funcOwner = funcOwner;
			this->func = func;
			this->choiceName = choiceName;
		}
	};
	int pressAnyButton() {
		std::cout << "\nPress any button ";
		
		return _getch();
	}
	int choose(Choice* choices, int choiceCount, std::string name, bool lethalExit = true) {

		std::string* names = new std::string[choiceCount];
		for (int i = 0; i < choiceCount; i++) {
			names[i] = choices[i].choiceName;
		}


		exitValues state = exitValues::continueChoice;
		while (state == exitValues::continueChoice) {
			system("cls");

			std::string name2 = name;

			printInFrame(names, name2, choiceCount, 1);

			int input = inputInstant("Your choice", 48 + choiceCount);

			if (input) {
				state = static_cast<UI<T>::exitValues>(((choices[input - 1].funcOwner)->*(choices[input - 1].func))());
				if (state == exitValues::exitAndContinueChoice) state = exitValues::continueChoice;
			}
			else
				state = (lethalExit) ? exitValues::exitChoice : exitValues::exitAndContinueChoice;
		}
		return state;
	}
	template<typename T1>
	T1 input(std::string text) {
		T1 input;
		while (true) {
			std::cout << '\n' << text << " : ";
			std::cin >> input;
			if (std::cin.fail()) {
				std::cout << "WRONG INPUT!!!";
				std::cin.clear();
				std::cin.ignore();
			}
			else {
				return input;
			}
		}
	}
	int inputInstant(std::string text, int less = 57, int bigger = 48) {
		int input;
		while (true) {
			std::cout << '\n' << text << " : ";
			input = _getch();
			if ((input > less || input < bigger)) {
				std::cout << "WRONG INPUT!!!";
				std::cin.clear();
			}
			else {
				return input - 48;
			}
		}
	}
	void printInFrame(std::string* strings, std::string name, int stringCount, int padding)
	{
		padding++;
		int width = 10 + padding * 2;
		for (size_t i = 0; i < stringCount; i++)
			width += (int)(strings[i].length()) + 5;
		std::cout << '\n';
		for (int i = 0; i < (width - name.length() - 2) / 2; i++)
			std::cout << '#';

		std::cout << ' ' << name << ' ';

		for (int i = 0; i < (width - name.length()) / 2; i++)
			std::cout << '#';

		for (int i = padding - 1; i > 0; i--)
		{
			std::cout << '\n';
			std::cout << '#';
			for (int j = 0; j < width - 2; j++)
				std::cout << ' ';
			std::cout << '#';
		}

		std::cout << "\n#";

		for (int i = padding; i > 0; i--)
			std::cout << ' ';

		std::cout << "Exit - 0";

		for (size_t i = 0; i < stringCount; i++)
			std::cout << ' ' << strings[i] << " - " << i + 1;

		for (int i = padding; i > 0; i--)
			std::cout << ' ';

		std::cout << '#';

		for (int i = padding - 1; i > 0; i--)
		{
			std::cout << '\n';
			std::cout << '#';
			for (int j = 0; j < width - 2; j++)
				std::cout << ' ';
			std::cout << '#';
		}

		std::cout << '\n';

		for (int i = 0; i < width; i++)
			std::cout << '#';

		std::cout << '\n';
	}

	template <typename T1>
	void print(T1 data) {
		std::cout << '\n' << data;
	}
};
#endif