// identifier final state machine class header file
#include <iostream>
#include <string>

class Machine {

private:

	States* currentState;

public:

	void switchStates(string* identifier) {
		for (int i; i < len(identifier); i++) {
			if (i == char) {
				changeState(2);		//letter
			}
			else if (i == int) {
				changeState(3);		//digit
			}
			else {
				changeState(5);		//neither letter nor digit (invalid state)
			}
		}
		//end of parsing, check last state
		if (*state == 4) {
			//valid
			token = *identifier;
		}
		else {
			//invalid
			//MAKE ERROR STATEMENT
		}
	}
};

class States {

private:

	Machine* _currentFSM;

public:

	void changeState(int stateChangeTo) {
		//delete current state
		if (currentState) {
			delete currentState;
			currentState = stateChangeTo;
			cout << *currentState << endl;
		}
		//set new state to stateChangeTo
	}
};