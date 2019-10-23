import java.io.*;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.*;

class Node{
	Node parent;
	int matrix[][];
	int h;
	int depth;
	int cost;
	int x;
	int y;

	Node(int matrix[][],int curr_depth,int prev_x,int prev_y,int new_x,int new_y, Node parent){
		this.matrix = new int[3][3];
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				this.matrix[i][j] = matrix[i][j];
			}
		}
		int temp=this.matrix[new_x][new_y];
		this.matrix[new_x][new_y]= this.matrix[prev_x][prev_y];
		this.matrix[prev_x][prev_y]=temp;

		this.x=new_x;
		this.y=new_y;

		this.depth=this.depth+curr_depth;
		this.parent = parent;
	}
};



public class puzzle{
	static int[] steps_x={0,1,-1,0};
	static int[] steps_y={1,0,0,-1};

	public static void solve(int[][] init,int[][] goal,int x,int y){

		PriorityQueue<Node> q = new PriorityQueue<Node>(1000, (a,b)-> (a.cost)-(b.cost));

		Node root = new Node(init ,  1 , x , y, x  ,y , null);
		Node temp = root;

		temp.cost=Cost(root,goal);
		temp.h=temp.cost-temp.depth;
		root.cost=temp.cost;

		q.add(root);
		//print_matrix(temp);

		while(temp.h!=0){
			for(int i=0;i<4;i++){
				x=temp.x;
				y=temp.y;
				if((y+steps_y[i]>=0) && (x+steps_x[i]>=0) && (y+steps_y[i]<3) && (x+steps_x[i]<3)){
					Node new_node = new Node(temp.matrix,temp.depth+1,x,y,x+steps_x[i],y+steps_y[i],temp);
					new_node.cost=Cost(new_node,goal);
					q.add(new_node);
				}
			}
			temp=q.poll();
		}
		print(temp);
	}

	public static int Cost(Node n,int[][] goal){
		int count=0;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(n.matrix[i][j]!=goal[i][j])
					count++;
			}
		}
		n.h=count;
		return count+n.depth;
	}

	public static void print_matrix(Node n){
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				System.out.print(n.matrix[i][j] + " ");
			}
			System.out.println();
		}
		//System.out.println(n.cost);
		System.out.println();
	}

	public static void print(Node n){
		int count=0;
		Stack<Node> s = new Stack<Node>(); 
		while(n!=null){
			s.push(n);
			n=n.parent;
		}
		System.out.println("No. of Iterations =" + (s.size()-1) + "\n");
		while(!s.empty()){
			print_matrix(s.peek());
			s.pop();
		}
	}

	public static void main(String[] args) {
		int[][] matrix = new int[3][3];
		int[][] goal = new int[3][3];
		int x=0,y=0;
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Initial Configuration : ");
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				matrix[i][j]=sc.nextInt();
				if(matrix[i][j]==0){
					x=i;y=j;
				}
			}
		}
		System.out.println("Enter Goal Configuration : ");
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				goal[i][j]=sc.nextInt();
			}
		}
		solve(matrix,goal,x,y);
	}
}