#include <iostream>
#include <vector>
#include <string>

#include "FiniteStateMachine.h"

unsigned int goback(unsigned int k);

void FSM_abaaba(std::string str, std::vector <char> const& alphabet);

void FSM_char(std::string str, std::vector <char> const& alphabet);

void FSM_uint(std::vector<unsigned int> const& strVect, std::vector <unsigned int> const& alphabet);

void FSM_substr(std::string str, std::string substr, std::vector<char> const& alphabet);

void FSM_ab(std::string str, std::vector<char> const& alphabet);

int main() {

	setlocale(LC_ALL, "RUSSIAN");

	std::cout << "Тесты\n";

	std::cout << "\n1) Первый автомат";
	std::cout << "\nПервый автомат принимает строку, если она оканчивается на 'abaaba'\n";

	std::cout << "\nТест 1.1: строка 'abacbabaaba'; алфавит: 'a', 'b', 'c'";
	FSM_abaaba("abacbabaaba", std::vector<char> {'a', 'b', 'c'});

	std::cout << "\nТест 1.2: строка 'abcbaabcabacb'; алфавит: 'a', 'b', 'c'";
	FSM_abaaba("abcbaabcabacb", std::vector<char> {'a', 'b', 'c'});


	std::cout << "\n\n2) Второй автомат (тип char)";
	std::cout << "\nВторой автомат принимает строку, если её первый символ встречается четное количество раз\n";

	std::cout << "\nТест 2.2: строка 'ababbaaa'; алфавит: 'a', 'b'";
	FSM_char("ababbaaa", std::vector<char> {'a', 'b'});

	std::cout << "\nТест 2.2: строка 'cbaccabc'; алфавит: 'a', 'b', 'c'";
	FSM_char("cbaccabc", std::vector<char> {'a', 'b', 'c'});
	

	std::cout << "\n\n3) Третий автомат (тип unsigned int)";
	std::cout << "\nТретий автомат принимает строку, если её первый символ встречается четное количество раз\n";

	std::cout << "\nТест 3.1: строка '0 1 1 0 0 3'; алфавит: 0, 1, 2, 3";
	FSM_uint(std::vector<unsigned int> {0, 1, 1, 0, 0, 3}, std::vector<unsigned int> {0, 1, 2, 3});
	
	std::cout << "\nТест 3.2: строка '2 1 0 2 1 0'; алфавит: 0, 1, 2";
	FSM_uint(std::vector<unsigned int> {2, 1, 0, 2, 1, 0}, std::vector <unsigned int> {0, 1, 2});
	

	std::cout << "\n\n4) Четвертый автомат (тип char)";
	std::cout << "\nЧетвертый автомат принимает строку p, если она является подстрокой s\n";

	std::cout << "\nТест 4.1: строка s 'abcaabbbaa'; подстрока p 'abbb'; алфавит: 'a', 'b', 'c'";
	FSM_substr("abcaabbbaa", "abbb", std::vector <char>{'a', 'b', 'c'});

	std::cout << "\nТест 4.2: строка s 'aabccbbaad'; подстрока p 'cba'; алфавит: 'a', 'b', 'c', 'd'";
	FSM_substr("aabccbbaad", "cba", std::vector<char>{'a', 'b', 'c', 'd'});


	std::cout << "\n\n\nДополнительный тест \n1) строка s 'cbdddcadebca'; подстрока p 'cadeb'; алфавит: 'a', 'b', 'c', 'd'";
	FSM_substr("cbdddcadebca", "cadeb", std::vector<char>{'a', 'b', 'c', 'd', 'e'});

	std::cout << "\n2) строка s 'cbdddcadebca'; подстрока p 'dddbcab'; алфавит: 'a', 'b', 'c', 'd', 'e'";
	FSM_substr("cbdddcadebca", "dddbcae", std::vector<char> {'a', 'b', 'c', 'd', 'e'});

	std::cout << std::endl << std::endl << std::endl;

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

void FSM_abaaba(std::string str, std::vector<char> const& alphabet)
{
	FiniteStateMachine <unsigned int, char> fsm;

	std::string smallstr = "abaaba";
	std::vector <char> smallstrVect(smallstr.begin(), smallstr.end());

	fsm.setAlphabet(alphabet); // передаем алфавит
	fsm.setInitial(0); // передаем начальное состояние
	fsm.setTerminal(std::vector <unsigned int> {6}); // передаем конечное состояние

	
	std::vector<unsigned int> states(7);
	for (int i = 0; i < 7; i++) {
		states[i] = i;
	}
	fsm.setStates(states); // передаем все состояния

	// вычиляем переходы
	std::map<std::pair<unsigned int, char>, unsigned int> transitions;

	for (auto c : alphabet) {
		if (smallstrVect[0] != c) {
			transitions[{0, c}] = 0;
		}
		else {
			transitions[{0, c}] = 1;
		}
	}
	for (unsigned int i = 1; i <= 5; i++) {
		for (auto c : alphabet) {
			if (smallstrVect[i] != c) {
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
	fsm.setTransitions(transitions); // передаем переходы
	
	if (fsm.isAcceptable(std::vector <char> (str.begin(), str.end()))) {
		std::cout << "\nСтрока " << str << " принята";
	}
	else {
		std::cout << "\nСтрока " << str << " не принята";
	}

}

void FSM_char(std::string str, std::vector<char> const& alphabet)
{
	FiniteStateMachine<int, char> fsm;

	std::vector<char> strVect(str.begin(), str.end());
	fsm.setAlphabet(alphabet); // передаем алфавит
	fsm.setInitial(0);   // передаем начальное состояние
	fsm.setTerminal(std::vector <int> { 0 }); // передаем конечные состояния
	fsm.setStates(std::vector <int> {0, 1}); // передаем все состояния

	// расчитываем переходы
	std::map <std::pair<int, char>, int> transitions;
	transitions[{0, str[0]}] = 1;
	transitions[{1, str[0]}] = 0;
	for (int i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] != str[0]) {
			transitions[{0, alphabet[i]}] = 0;
			transitions[{1, alphabet[i]}] = 1;
		}
	}
	fsm.setTransitions(transitions); // передаем переходы

	if (fsm.isAcceptable(strVect)) {
		std::cout << "\nСтрока " << str <<" принята";
	}
	else {
		std::cout << "\nСтрока " << str << " не принята";
	}

}

void FSM_uint(std::vector<unsigned int> const& strVect, std::vector<unsigned int> const& alphabet)
{
	FiniteStateMachine<int, unsigned int> fsm;

	fsm.setAlphabet(alphabet); // передаем алфавит
	fsm.setInitial(0);  // передаем начальоне состояние
	fsm.setTerminal(std::vector <int> { 0 }); // передаем конечные состояния
	fsm.setStates(std::vector <int> {0, 1}); // передаем все состояния

	// расчитываем переходы
	std::map <std::pair<int, unsigned int>, int> transitions;
	transitions[{0, strVect[0]}] = 1;
	transitions[{1, strVect[0]}] = 0;
	for (int i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] != strVect[0]) {
			transitions[{0, alphabet[i]}] = 0;
			transitions[{1, alphabet[i]}] = 1;
		}
	}
	fsm.setTransitions(transitions); // передаем переходы

	if (fsm.isAcceptable(strVect)) {
		std::cout << "\nСтрока ";
		for (auto s : strVect) {
			std::cout << s << " ";
		}
		std:: cout << "принята";
	}
	else {
		std::cout << "\nСтрока ";
		for (auto s : strVect) {
			std::cout << s << " ";
		}
		std::cout << "не принята";
	}

}

void FSM_substr(std::string str, std::string substr, std::vector<char> const& alphabet)
{
	FiniteStateMachine<int, char> fsm;

	fsm.setAlphabet(alphabet); // передаем алфавит
	fsm.setInitial(0);   // передаем начальное состояние
	int substrLen = (int)substr.length();
	fsm.setTerminal(std::vector <int> { substrLen }); // передаем конечные состояния

	std::vector <int> states(substrLen + 1);
	for (int i = 0; i <= substrLen; i++) {
		states[i] = i;
	}
	fsm.setStates(states); // передаем все состояния

	// расчитываем переходы
	std::map <std::pair<int, char>, int> transitions;

	for (auto cur : states) {
		for (auto c : alphabet) {

			int next = (cur + 1 <= substrLen) ? (cur + 1) : substrLen;
			if (substr[static_cast<int64_t>(next) - 1] != c) {
				next = 0;
			}

			transitions[{cur, c}] = next;
		}
	}

	fsm.setTransitions(transitions); // передаем переходы

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
		std::cout << "\nСтрока " << substr << " принята";
	}
	else {
		std::cout << "\nСтрока " << substr << " не принята";
	}
}

void FSM_ab(std::string str, std::vector<char> const& alphabet)
{
	FiniteStateMachine<int, char> fsm;

	fsm.setAlphabet(alphabet);
	fsm.setInitial(0);
	fsm.setTerminal(std::vector<int>{1, 2});


}
