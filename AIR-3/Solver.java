import java.io.*;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.*;

public class Solver{	
	static int num = 3;
	static int[] steps_x = {0,1,-1,0}; // Down Right Left Up
	static int[] steps_y = {1,0,0,-1};
	//static int zero_x;
	//static int zero_y;
	
	public static void solve(int[][] init , int[][] goal , int x , int y){
	
		PriorityQueue<Node> pq = new PriorityQueue<Node>(1000 , (a,b) -> (a.cost) - (b.cost));
		
		Node root = new Node(init ,  1 , x , y, x  ,y , null );
		Node temp = root;
		
		int d = 0;		
		temp.cost = calcCost(root , goal);
		temp.h = temp.cost - temp.g;
		root.cost = temp.cost;
		
		pq.add(root);	
		print_matrix(temp);
				
		while(temp.h != 0){
			for(int i = 0 ; i < 4 ; i ++){			//MOVES	 
				x = temp.x;
				y = temp.y;			
				if((y + steps_y[i] >= 0) && (x + steps_x[i] >= 0 )  && (y + steps_y[i] < num ) && (x + steps_x[i] < num )){
					Node new_node = new Node(temp.matrix ,temp.g , x , y , x + steps_x[i] , y + steps_y[i] , temp );
					new_node.cost = calcCost(new_node , goal);
					pq.add(new_node);
					d = d + 1;
					//print_matrix(new_node);
					//System.out.println("Cost: : " + new_node.cost);
				}
			}
		temp = pq.poll();
		//print_matrix(temp);
		//if(d > 10){break;}		
		}
		print(temp);	
		//print_matrix(temp);		
	}
	public static void print_matrix(Node inp){
		for(int i = 0 ; i<num ; i++){
			for(int j = 0 ; j<num ; j++){
				System.out.print(inp.matrix[i][j] + " ");
			}
			System.out.println(" ");
		}
		System.out.println(inp.cost);
		System.out.println(" ");
	}
	public static int calcCost(Node inp , int[][] goal){	
		int cnt = 0;
		for(int i = 0 ; i< num ; i++){
			for(int j = 0 ; j< num ; j++){
				
				if(inp.matrix[i][j] != goal[i][j]){
					cnt++;						
				}
			}
		}
		System.out.println("Inside : " + cnt + inp.g );
		inp.h = cnt;
	return cnt + inp.g;
	}
	public static void print(Node inp ){	
		int cnt = 0;
		
		while(inp != null){
		print_matrix(inp);
		inp = inp.parent;
		
		}
	}
	public static void main(String args[]){		
		int[][] matrix = new int[num][num];
		int[][] goal = new int[num][num];
		int x = 0,y = 0;
		Scanner sc = new Scanner(System.in);
		
		for (int i = 0 ; i < num ; i++){
			for (int j = 0 ; j < num ; j++){
				matrix[i][j] = sc.nextInt();
				
				if(matrix[i][j] == 0){
					x = i;
					y = j;
				}
			
			}
		}			
		for (int i = 0 ; i < num ; i++){
			for (int j = 0 ; j < num ; j++){
				goal[i][j] = sc.nextInt();
			}
		}					
		solve(matrix,goal,x,y);
	}
};
