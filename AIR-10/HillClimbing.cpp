#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class State {
public:
	int* board;
	int emptySlot;
	int heuristicValue;
	State() {
		board = (int*) malloc(9 * sizeof(int));
		heuristicValue = -1;
	}
	bool input() {
		int value;
		int test = 0;
		for(int i=0; i<9; i+=1) {
			scanf("%d", &value);
			if(value < 0 || value > 8)
				return true;			
			if((test & (1<<value)) != 0)
				return true;			
			test |= (1<<value);		
			if(value == 0) 
				emptySlot = i;
			board[i] = value;
		}
		return false;
	}
	void display() {
		printf("\n");
		for(int i=0; i<9; i+=1) {
			printf("%d ", board[i]);
			if(i == 2 || i == 5 || i == 8)
				printf("\n");
		}
	}
	void equateTo(const State& s) {
		for(int i=0; i<9; i+=1) {
			board[i] = s.board[i];
			if(s.board[i] == 0)
				emptySlot = i;			
			heuristicValue = s.heuristicValue;
		}
	}
	int getHeuristicValue(const State& s) {
		int tempHeuristicValue = 0;
		for(int i=0; i<9; i+=1) {
			if(board[i] != s.board[i] && s.board[i] != 0)
				tempHeuristicValue += 1;
		}
		heuristicValue = tempHeuristicValue;
		return tempHeuristicValue;
	}	
	int getEmptySlot() {
		for(int i=0; i<9; i+=1) {
			if(board[i] == 0)
				emptySlot = i;
				return i;
		}
	}
	bool moveUp() {
		getEmptySlot();
		if(emptySlot < 3)
			return false;			
		board[emptySlot] = board[emptySlot - 3];
		board[emptySlot - 3] = 0;
		return true;
	}
	bool moveDown() {
		getEmptySlot();
		if(emptySlot > 5)
			return false;			
		board[emptySlot] = board[emptySlot + 3];
		board[emptySlot + 3] = 0;
		return true;
	}
	bool moveLeft() {
		getEmptySlot();
		if(emptySlot % 3 == 0)
			return false;		
		board[emptySlot] = board[emptySlot - 1];
		board[emptySlot - 1] = 0;
		return true;
	}
	bool moveRight() {
		getEmptySlot();
		if(emptySlot % 3 == 2) 
			return false;		
		board[emptySlot] = board[emptySlot + 1];
		board[emptySlot + 1] = 0;
		return true;
	}
};

class HillClimbingAlgorithm {
	State initialState;
	State goalState;
	bool gameStatus;
	vector<State> solutionList;
	
public:
	HillClimbingAlgorithm() {
		gameStatus = true;
		solutionList.clear();
		
		bool flag = true;
		printf("Enter the block elements for initial state: : ");
		
		while((flag = initialState.input()) == true) {
			flag = false;
			printf("Error! Invalid Elements.\n");
			printf("Please enter valid elements: : ");
		}
		
		solutionList.push_back(initialState);
		
		printf("Enter the block elements for goal state: : ");
		
		while((flag = goalState.input()) == true) {
			flag = false;
			printf("Error! Invalid Elements.\n");
			printf("Please enter valid elements: : ");
		}
		
		initiateAlgorithm();
	}
	
	bool isSolved(const State& s) {
		for(int i=0; i<9; i+=1) {
			if(goalState.board[i] != s.board[i])
				return false;
		}
		gameStatus = false;
		return true;
	}
	
	int getMinimumHeuristicValue(const State& s) {
		State tempState;
		int values[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
		
		tempState.equateTo(s);
		tempState.moveUp();
		values[0] = tempState.getHeuristicValue(goalState);
		
		tempState.equateTo(s);
		tempState.moveDown();
		values[1] = tempState.getHeuristicValue(goalState);
		
		tempState.equateTo(s);
		tempState.moveLeft();
		values[2] = tempState.getHeuristicValue(goalState);
		
		tempState.equateTo(s);
		tempState.moveRight();
		values[3] = tempState.getHeuristicValue(goalState);
		
		int min = values[0];
		int index = 0;
		
		for(int i=1; i<4; i+=1) {
			if(min > values[i] && values[i] <= s.heuristicValue){
				min = values[i];
				index = i;
			}
		}
		
		return index;
	}
	
	void initiateAlgorithm() {
		State currentState;
		initialState.getHeuristicValue(goalState);
		currentState.equateTo(initialState);
		int index;
		State tempState;
		
		while(!isSolved(currentState)) {
			index = getMinimumHeuristicValue(currentState);
			
			tempState.equateTo(currentState);
			
			switch(index) {
				case 0:
					tempState.moveUp();
					break;
					
				case 1:
					tempState.moveDown();
					break;
					
				case 2:
					tempState.moveLeft();
					break;
					
				case 3:
					tempState.moveRight();
					break;
			}
			
			bool sameState = true;
			for(int i=0; i<9; i+=1){
				if(tempState.board[i] != currentState.board[i])
					sameState = false;
			}
			
			if(sameState) {
				printf("The problem is not solvable at state\n");
				tempState.display();
				break;
			}
			
			solutionList.push_back(tempState);
			currentState.equateTo(tempState);
		};
		
		if(!gameStatus) {
			for(int i=0; i<solutionList.size(); i+=1)
				solutionList[i].display();
			printf("\nReached Goal State\n");
		}
	}
};

int main() {
	HillClimbingAlgorithm h;
	return 0;
}
