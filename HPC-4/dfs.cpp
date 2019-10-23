#include<bits/stdc++.h>
using namespace std;
class node
{
public:
	int data;
	node *left,*right;
	node(int d)
	{
		data = d;
		left=right=NULL;
	}
};

void dfs(node *root)
{
	if(root==NULL)
		return;
	dfs(root->left);
	cout<<root->data<<" ";
	dfs(root->right);
}
void parallelDfs(node *root){
	if(root != NULL){
#pragma omp parallel sections
		{
#pragma omp section
			{
				parallelDfs(root->left);
			}
//#pragma omp section
//			{
//				cout << root->data << " ";
//			}
#pragma omp section
			{
				parallelDfs(root->right);
			}
		}
	}
}
// class tree{
// 	public:
//   node *root;

//   tree(){
//     root = NULL;
// 	}

//     node* addNode(node *node,int d)
// 	{
// 	 if (d < node->data) 
//         node->left  = addNode(node->left, d); 
//     else if (d > node->data) 
//         node->right = addNode(node->right, d);
// 	}
//   };

//   void addNode(int d){
//     if(root == NULL){
//       root = new node(d);
//     }
//     else{
//       node *c = root;
//       while(c->left == NULL || c->right != NULL){
// 		if(c->data > d){
// 	  	if(c->left == NULL){
// 	    c->left = new node(d);
// 	  }
// 	  else{
// 	    c = c->left;
// 	  }
// 	}
// 	else{
// 	  if(c->right == NULL){
// 	    c->right = new node(d);
// 	  }
// 	  else{
// 	    c = c->right;
// 	  }
// 	}
//       }
//     }
//   }

//   node* returnRoot(){
//     return root;
//   }
// };
int main()
{
	node *root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->left->right = new node(5);
	//tree t;
  //auto start = chrono::high_resolution_clock::now();
	// node *new1 = new node(3);
	// t.root = new1;

 //  	t.addNode(t.root,10);
 //  	t.addNode(t.root,4);
 //  	t.addNode(t.root,11);
 //  	t.addNode(t.root,14);
 //  	t.addNode(t.root,18);
 //  	t.addNode(t.root,114);
 //  	t.addNode(t.root,109);
 //  	t.addNode(t.root,3);
 //  	t.addNode(t.root,1);
 //  	t.addNode(t.root,198);
 //  	t.addNode(t.root,67);

	cout<<"Inorder traversal\n";
	clock_t timer;
	timer = clock();
	dfs(root);
	cout << "\nTime for serial : " <<(float)(clock() - timer) / CLOCKS_PER_SEC;

    timer = clock();
	parallelDfs(root);
	cout << "\nTime for Parallel : " << (float)(clock() - timer) / CLOCKS_PER_SEC;

	return 0;

}
