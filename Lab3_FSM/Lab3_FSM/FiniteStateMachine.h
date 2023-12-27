#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>

template <typename StateT, typename AlphabetT>

class FiniteStateMachine {
private:

	std::vector <StateT> states_; // вектор всех возможных состояний

	std::vector <AlphabetT> alphabet_; // вектор символов алфавита

	StateT initialState_; // начальное состояние

	std::vector <StateT> terminalStates_; // вектор конечных состояний

	std::map <std::pair <StateT, AlphabetT>, StateT> transitions_; // переходы

public:

	void setStates(std::vector <StateT> const& states) {
		states_ = states;
	}

	void setAlphabet(std::vector <AlphabetT> const& alphabet) {
		alphabet_ = alphabet;
	}

	void setTerminal(std::vector <StateT> const& terminalStates) {
		terminalStates_ = terminalStates;
	}

	void setInitial(StateT const& initialState) {
		initialState_ = initialState;
	}

	void setTransitions(std::map <std::pair<StateT, AlphabetT>, StateT> const& transitions) {
		transitions_ = transitions;
	}

	bool isAcceptable(std::vector <AlphabetT> v);

};

template<typename StateT, typename AlphabetT>
inline bool FiniteStateMachine<StateT, AlphabetT>::isAcceptable(std::vector <AlphabetT> v)
{
	StateT curState = initialState_;
	for (auto c : v) {

		auto it = transitions_.find({ curState, c });

		if (it != transitions_.end()) { // ищем ключ
			curState = it->second; // переходим в новое соответствующее ключу состояние
		}
		else return false;
	}

	//проверяем относится ли последнее состояние к конечным
	for (int i = 0; i < terminalStates_.size(); i++) {
		if (curState == terminalStates_[i]) {
			return true;
		}
	}

	return false;
}