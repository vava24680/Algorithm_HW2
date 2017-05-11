#include <iostream>
#include <cstring>
#include <cstdlib>
#include "algo_hw2.hpp"
using namespace std;
int main(void)
{
	int delete_num = -1;
	const int full_size = 63;
	/*int* tree=0;
	tree = new int[3*full_size+1];*/
	int tree[3 * full_size + 1];
	//memset(tree, -1, full_size*3+1);
	for (int i = 1; i < 3 * full_size + 1; i++)
	{
		tree[i] = -1;
	}
	tree[0] = full_size*3+1;
	Insert(tree, 1);
	Insert(tree, 4);
	Insert(tree, 9);
	Insert(tree, 8);
	Insert(tree, 2);
	Insert(tree, 15);
	Insert(tree, 6);
	Insert(tree, 99);
	Insert(tree, 88);
	Insert(tree, 6);
	Insert(tree, 7);
	Insert(tree, 10);
	for (int i = 1,j=1; i <= 188; i = i + 3,j++)
	{
		cout << "(" << j << ", " << tree[i] << ", " << tree[i + 1] << ", " << tree[i + 2] << ")" << endl;
	}
	cout << "Insertion Done" << endl;
	Delete(tree, 4);
	Delete(tree, 9);
	Delete(tree, 6);
	for (int i = 1,j=1; i <= 188; i = i + 3,j++)
	{
		cout << "(" << j << ", " << tree[i] << ", " << tree[i + 1] << ", " << tree[i + 2] << ")" << endl;
	}
	//cout << "What you want to delete :";
	//cin >> delete_num;
	/*while (delete_num >= 0)
	{
		Delete(tree ,delete_num);
	}
	*/
	system("pause");
	return 0;
}