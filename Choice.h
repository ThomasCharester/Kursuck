#pragma once
#ifndef CHOICE
#define CHOICE

#include <iostream>
#include <string>
#include <conio.h>
#include "windows.h"
template<typename T>
class UI {
public:
	enum exitValues : int {
		exitChoice = 0,
		continueChoice = 1,
		exitAndContinueChoice = 2,
		shutdown = 3
	};
	enum colors : int {
		White,
		Red,
		Blue,
		Green,
		Orange,
		Pink,
		Yellow
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

			int input = inputInstant("Your choice",true, 48 + choiceCount) - 48;

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
	T1 input(std::string text, bool newLine = true) {
		T1 input;
		while (true) {
			printMinecraft(text + " : ", newLine);
			std::cin >> input;
			if (std::cin.fail()) {
				printMinecraft("&1WRONG INPUT!!!");
				std::cin.clear();
				std::cin.ignore();
			}
			else {
				return input;
			}
		}
	}
	int inputInstant(std::string text,bool newLine = true, int less = 57, int bigger = 48) {
		int input;
		while (true) {
			printMinecraft(text + " : ",newLine);
			input = _getch();
			if ((input > less || input < bigger)) {
				printMinecraft("&1WRONG INPUT!!!");
				std::cin.clear();
			}
			else {
				return input;
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
	void print(T1 data, bool newLine = true) {
		if (newLine) std::cout << '\n';
		std::cout << data;
	}
	void setColor(UI::colors color) {
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (color) {
		case UI::colors::Red:
			SetConsoleTextAttribute(handle, 12);
			break;
		case UI::colors::Green:
			SetConsoleTextAttribute(handle, 10);
			break;
		case UI::colors::Blue:
			SetConsoleTextAttribute(handle, 9);
			break;
		case UI::colors::Yellow:
			SetConsoleTextAttribute(handle, 14);
			break;
		case UI::colors::Orange:
			SetConsoleTextAttribute(handle, 6);
			break;
		case UI::colors::Pink:
			SetConsoleTextAttribute(handle, 13);
			break;
		default:
			SetConsoleTextAttribute(handle, 7);
			break;
		}
	}
	void printMinecraft(std::string str, bool newLine = true) {
		if (newLine) std::cout << '\n';
		bool flag = false;
		for (char ch : str) {
			if (!flag)
				if (ch != '&')
					std::cout << ch;
				else flag = true;
			else {
				setColor(static_cast<UI::colors>((ch - 48)));
				flag = false;
			}
		}
		setColor(White);
	}
};
#endif