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
#pragma omp section
			{
				parallelDfs(root->right);
			}
		}
	}
}

int main()
{
	node *root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->left->right = new node(5);

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
