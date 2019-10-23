#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>

using namespace std;

class backtracking{
    int dimen;
    bool** board;
    bool* checkrow;

    bool checkSafe(int row, int column){

        if(checkrow[row]) return false;

        for(int i=0; i<=column; i+=1){
            if(board[row][i])
                return false;
        }
        for(int i=row, j=column; i>=0 && j>=0; i-=1, j-=1){
            if(board[i][j])
                return false;
        }
        for(int i=row, j=column; i<dimen && j>=0; i+=1, j-=1){
            if(board[i][j])
                return false;
        }
        return true;
    }
    bool init(int column){
        bool flag = true;
        int temp;
        for(int i=0; i<dimen; i+=1){
            if(checkrow[i]==false){
                flag = false;
                break;
            }
        }
        if(flag==true) return true;

        for(int row=0; row<dimen; row+=1){
            if(checkSafe(row, column)){
                board[row][column] = true;
                checkrow[row] = true;
            
                if(init((column+1)%dimen)) return true;
                else{
                    board[row][column] = false;
                    checkrow[row] = false;
                }
            }
        }
        return false;
    }

public:
    backtracking(int d){
        dimen = d;
        board = (bool**) malloc(dimen * sizeof(bool*));
        checkrow = (bool*) calloc(dimen, sizeof(bool));

        for(int i=0; i<dimen; i+=1){
            board[i] = (bool*) calloc(dimen, sizeof(bool));
        }

        srand(time(0));
        init(rand()%dimen);

        for(int i=0; i<dimen; i+=1){
            for(int j=0; j<dimen; j+=1){
                if(board[i][j]){
                    printf("Q ");
                    continue;
                }
                printf("_ ");
            }
            printf("\n");
        }
    }
};

class branchnbound{
    int dimen;
    bool** board;
    bool* majorDiagonal;
    bool* minorDiagonal;
    bool* checkRow;
    
    bool checkSafe(int row, int column){
    	if(checkRow[row]==true) return false;
    	else if(majorDiagonal[row-column+dimen-1]==true) return false;
    	else if(minorDiagonal[row + column]==true) return false;
    	
    	return true;
    }
    
    bool init(int column){
    	bool flag = true;  	
    	for(int i=0; i<dimen; i+=1){
    		if(checkRow[i]==false){
    			flag = false;
    			break;
    		}
    	}	
    	if(flag==true) return true;
    	
    	for(int row=0; row<dimen; row+=1){
    		if(checkSafe(row, column)==true){
    			checkRow[row] = true;
    			board[row][column] = true;
    			majorDiagonal[row-column+dimen-1] = true;
    			minorDiagonal[row + column] = true;
    			
    			if(init((column+1)%dimen)) return true;
    			
    			checkRow[row] = false;
    			board[row][column] = false;
    			majorDiagonal[row-column+dimen-1] = false;
    			minorDiagonal[row + column] = false;
    		}
    	}	
    	return false;
    }
    
public:
	branchnbound(int d){
		dimen = d;
		
		board = (bool**) calloc(dimen, sizeof(bool*));
		majorDiagonal = (bool*) calloc(2*dimen - 1, sizeof(bool));
		minorDiagonal = (bool*) calloc(2*dimen - 1, sizeof(bool));
		checkRow = (bool*) calloc(dimen, sizeof(bool));
	
		for(int i=0; i<dimen; i+=1){
			board[i] = (bool*) calloc(dimen, sizeof(bool));
		}
		
		srand(time(0));
        init(rand()%dimen);

        for(int i=0; i<dimen; i+=1){
            for(int j=0; j<dimen; j+=1){
                if(board[i][j]){
                    printf("Q ");
                    continue;
                }
                printf("_ ");
            }
            printf("\n");
        }
	}
};

int main(int argc, char** argv){
    int dimen, choice;
    sscanf(argv[1], "%d", &dimen);
    sscanf(argv[2], "%d", &choice);
    
    if(choice==1)
    	backtracking b(dimen);
    else if(choice==2)
    	branchnbound b(dimen);
    return 0;
}
