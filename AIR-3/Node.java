import java.io.*;



public class Node{

	Node parent;
	int num = 3;
	int matrix[][];
	int cost;
	int g = 0;
	int h;
	int x;
	int y;

	Node(int matrix[][] , int step, int prev_x, int prev_y , int new_x , int new_y , Node parent ){
	
		this.matrix = new int[num][num];
	
		for(int i = 0 ;  i < 3 ; i++ ){
		
			for(int j = 0; j < 3 ; j++){
				this.matrix[i][j] = matrix[i][j];
			}
		}
		
		int temp = this.matrix[new_x][new_y];
		this.matrix[new_x][new_y] = this.matrix[prev_x][prev_y];
		this.matrix[prev_x][prev_y] = temp;
		
		this.x = new_x;
		this.y = new_y;
		
		this.g = this.g + step;
		this.parent = parent;
		

	}

};
