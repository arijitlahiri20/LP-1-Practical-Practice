#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>

using namespace std;

class backtracking{
	int dimen;
	bool **board;
	bool *checkrow;

	bool checksafe(int r, int c){
		if(checkrow[r])
			return false;
		//Check Left Side
		for(int i=0;i<=c;i++){
			if(board[r][i])
				return false;
		}
		//Check Upper Left Diagonal
		for(int i=r,j=c;i>=0 && j>=0;i--,j--){
			if(board[i][j])
				return false;
		}
		//Check Lower Left Diagonal
		for(int i=r,j=c;i<dimen && j>=0;i++,j--){
			if(board[i][j])
				return false;
		}
		return true;
	}
	bool start(int col){
		bool flag = true;
		for(int i=0;i<dimen;i++){
			if(checkrow[i]==false){
				flag=false;
				break;
			}
		}
		if(flag==true)
			return true;
		for(int row=0;row<dimen;row++){
			if(checksafe(row,col))
				board[row][col]=true;
				checkrow[row]=true;
				if(start((col+1)%dimen))
					return true;
				else{
					board[row][col]=false;
					checkrow[row]=false;
				}
		}
		return false;
	}

public:
	backtracking(int d){
		dimen=d;
		board = (bool **)malloc(dimen*sizeof(bool*));
		checkrow = (bool *)calloc(dimen,sizeof(bool));

		for(int i=0;i<dimen;i++){
			board[i]= (bool *)calloc(dimen,sizeof(bool));
		}

		srand(time(0));
		start(rand()%dimen);

		cout<<"Solution to "<<dimen<<" Queens Problem : "<<endl; 
		for(int i=0;i<dimen;i++){
			for(int j=0;j<dimen;j++){
				if(board[i][j])
					cout<<"Q ";
				else
					cout<<"- ";		
			}
			cout<<endl;
		}
	}	

};

int main(int argc, char** argv){
    int dimen, choice;
    sscanf(argv[1], "%d", &dimen);
    sscanf(argv[2], "%d", &choice);
    
    if(choice==1){
    	cout<<"backtracking Selected - "<<endl;
    	backtracking b(dimen);
    }
    else if(choice==2){
    	cout<<"Branch & Bound Selected - "<<endl;
    	//branchnbound b(dimen);
    }
    return 0;
}
