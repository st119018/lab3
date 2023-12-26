#include <iostream>
#include <vector>
#include <string>

#include "FiniteStateMachine.h"

unsigned int goback(unsigned int k);

int main() {

	setlocale(LC_ALL, "RUSSIAN");

	std::string str = "0";

	std::cout << "Первый автомат";
	while (str != "end") {
		FiniteStateMachine <unsigned int, char> fsm;

		std::cout << "\nПервый автомат принимает строку, если она оканчивается на 'abaaba'";
		std::cout << "\n\nВведите количество символов в алфавите(помимо 'a' и 'b'): ";
		int num;
		std::cin >> num;
		std::vector <char> alphabet(num + 2);
		std::cout << "\nВведите через пробел символы(тип char): ";

		alphabet[0] = 'a';
		alphabet[1] = 'b';
		for (int i = 2; i < num + 2; i++) {
			char c;
			std::cin >> c;
			alphabet[i] = c;
		}

		std::cout << "\nВведите строку (минимальной длины 6): ";
		std::cin >> str;

		while (str.size() < 6) {
			std::cout << "\nДлина строки меньше 6; введите ещё раз: ";
			std::cin >> str;
		}

		std::vector <char> strVect(str.begin(), str.end());

		fsm.setAlphabet(alphabet);
		fsm.setInitial(0);
		fsm.setTerminal(std::vector <unsigned int> {6});

		std::vector<unsigned int> states(7);
		for (int i = 0; i < 7; i++) {
			states[i] = i;
		}
		fsm.setStates(states);

		std::map<std::pair<unsigned int, char>, unsigned int> transitions;

		for (auto c : alphabet) {
			if (strVect[0] != c) {
				transitions[{0, c}] = 0;
			}
			else {
				transitions[{0, c}] = 1;
			}
		}
		for (unsigned int i = 1; i <= 5; i++) {
			for (auto c : alphabet) {
				if (strVect[i] != c) {
					transitions[{i, c}] = transitions[{goback(i), c}];
				}
				else {
					transitions[{i, c}] = i + 1;
				}
			}
		}
		for (auto c : alphabet) {
			transitions[{6, c}] = transitions[{goback(6), c}];
		}
		fsm.setTransitions(transitions);

		if (fsm.isAcceptable(strVect)) {
			std::cout << "\nСтрока принята";
		}
		else {
			std::cout << "\nСтрока не принята";
		}

		std::cout << "\n\nЧтобы перейти к следующему автомату, введите end: ";
		std::cin >> str;
	}



	str = "0";
	std::cout << "\n\nВторой автомат (тип char)";
	while (str != "end") {
		FiniteStateMachine<int, char> fsm;

		std::cout << "\nВторой автомат принимает строку, если её первый символ встречается четное количество раз\n";
		std::cout << "\nВведите количество символов в алфавите: ";
		int num;
		std::cin >> num;
		std::vector <char> alphabet(num);
		std::cout << "\nВведите через пробел символы(тип char): ";

		for (int i = 0; i < num; i++) {
			char c;
			std::cin >> c;
			alphabet[i] = c;
		}

		std::cout << "\nВведите строку: ";
		std::cin >> str;
		std::vector<char> strVect(str.begin(), str.end());
		fsm.setAlphabet(alphabet);
		fsm.setInitial(0);
		fsm.setTerminal(std::vector <int> { 0 });
		fsm.setStates(std::vector <int> {0, 1});

		//переходы
		std::map <std::pair<int, char>, int> transitions;
		transitions[{0, str[0]}] = 1;
		transitions[{1, str[0]}] = 0;
		for (int i = 0; i < alphabet.size(); i++) {
			if (alphabet[i] != str[0]) {
				transitions[{0, alphabet[i]}] = 0;
				transitions[{1, alphabet[i]}] = 1;
			}
		}
		fsm.setTransitions(transitions);

		if (fsm.isAcceptable(strVect)) {
			std::cout << "\nСтрока принята";
		}
		else {
			std::cout << "\nСтрока не принята";
		}

		std::cout << "\n\nЧтобы перейти к следующему автомату, введите end: ";
		std::cin >> str;
	}



	str = "0";
	std::cout << "\n\nТретий автомат (тип unsigned int)";
	while (str != "end") {
		FiniteStateMachine<int, unsigned int> fsm;

		std::cout << "\nТретий автомат принимает строку, если её первый символ встречается четное количество раз\n";
		std::cout << "\nВведите количество символов в алфавите: ";
		int num;
		std::cin >> num;
		std::vector <unsigned int> alphabet(num);
		std::cout << "\nВведите через пробел символы алфавита(тип unsigned int): ";

		for (int i = 0; i < num; i++) {
			unsigned int c;
			std::cin >> c;
			alphabet[i] = c;
		}

		std::cout << "\nВведите количество символов в строке: ";
		int n;
		std::cin >> n;
		std::cout << "\nВведите через пробел символы строки(тип unsigned int): ";
		std::vector<unsigned int> strVect(n);
		for (int i = 0; i < n; i++) {
			unsigned int symbol;
			std::cin >> symbol;
			strVect[i] = symbol;
		}

		fsm.setAlphabet(alphabet);
		fsm.setInitial(0);
		fsm.setTerminal(std::vector <int> { 0 });
		fsm.setStates(std::vector <int> {0, 1});

		//переходы
		std::map <std::pair<int, unsigned int>, int> transitions;
		transitions[{0, strVect[0]}] = 1;
		transitions[{1, strVect[0]}] = 0;
		for (int i = 0; i < alphabet.size(); i++) {
			if (alphabet[i] != strVect[0]) {
				transitions[{0, alphabet[i]}] = 0;
				transitions[{1, alphabet[i]}] = 1;
			}
		}
		fsm.setTransitions(transitions);

		if (fsm.isAcceptable(strVect)) {
			std::cout << "\nСтрока принята";
		}
		else {
			std::cout << "\nСтрока не принята";
		}

		std::cout << "\n\nЧтобы перейти к следующему автомату, введите end: ";
		std::cin >> str;
	}

	str = "0";
	std::cout << "\n\nЧетвертый автомат (тип char)";

	while (str != "end") {
		std::cout << "\nЧетвертый автомат проверяет, является ли строка p подстрокой s\n";
		std::cout << "\nВведите количество символов в алфавите: ";
		int num;
		std::cin >> num;
		std::vector <char> alphabet(num);
		std::cout << "\nВведите символы алфавита через пробел(тип char): ";

		for (int i = 0; i < num; i++) {
			char c;
			std::cin >> c;
			alphabet[i] = c;
		}

		std::cout << "\nВведите основную строку (строку s): ";
		std::cin >> str;
		std::cout << "\nВведите подстроку (строку p): ";
		std::string substr;
		std::cin >> substr;

		FiniteStateMachine<int, char> fsm;

		fsm.setAlphabet(alphabet);
		fsm.setInitial(0);
		int substrLen = (int)substr.length();
		std::vector <int> terminalStates{ substrLen };
		fsm.setTerminal(terminalStates);

		std::map <std::pair<int, char>, int> transitions;
		std::vector <int> states(substrLen + 1);
		for (int i = 0; i <= substrLen; i++) {
			states[i] = i;
		}
		fsm.setStates(states);

		for (auto cur : states) {
			for (auto c : alphabet) {

				int next = (cur + 1 <= substrLen) ? (cur + 1) : substrLen;
				if (substr[static_cast<int64_t>(next) - 1] != c) {
					next = 0;
				}

				transitions[{cur, c}] = next;
			}
		}


		fsm.setTransitions(transitions);

		std::vector<char> mainStr(str.begin(), str.end());
		int strLen = (int)str.length();

		bool accepted = false;
		for (int i = 0; i <= strLen - substrLen; ++i) {
			std::vector <char> sub(mainStr.begin() + i, mainStr.begin() + i + substrLen);
			if (fsm.isAcceptable(sub)) {
				accepted = true;
			}
		}
		if (accepted) {
			std::cout << "\nСтрока принята";
		}
		else {
			std::cout << "\nСтрока не принята";
		}
		std::cout << "\n\nЧтобы закончить, введите end: ";
		std::cin >> str;
	}

	return 0;
}

unsigned int goback(unsigned int k)
{
	switch (k) {
	case 1:
		return 0;
	case 2:
		return 0;
	case 3:
		return 1;
	case 4:
		return 1;
	case 5:
		return 2;
	case 6:
		return 3;
	default:
		return 0;
	}
}
