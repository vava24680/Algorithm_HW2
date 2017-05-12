#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
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
	tree[1] = 0;
	tree[2] = 1;
	tree[3] = 3;
	tree[4] = 1;
	tree[5] = 1;
	tree[6] = 1;
	tree[7] = 1;
	tree[8] = 1;
	tree[9] = 1;
	tree[0] = full_size*3+1;
	Insert(tree, 74);
	Insert(tree, 11);
	Insert(tree, 25);
	Insert(tree, 16);
	Insert(tree, 67);
	Insert(tree, 2);
	Insert(tree, 15);
	Insert(tree, 37);
	Insert(tree, 44);
	Insert(tree, 83);
	Insert(tree, 100);
	Insert(tree, 95);
	for (int i = 1,j=1; i <= 188; i = i + 3,j++)
	{
		cout << "(" << j << ", " << tree[i] << ", " << tree[i + 1] << ", " << tree[i + 2] << ")" << endl;
	}
	cout << "Insertion Done" << endl;
	Delete(tree, 4);
	Delete(tree, 2);
	Delete(tree, 37);
	Delete(tree, 25);
	for (int i = 1,j=1; i <= 188; i = i + 3,j++)
	{
		cout << "(" << j << ", " << tree[i] << ", " << tree[i + 1] << ", " << tree[i + 2] << ")" << endl;
	}
	cout << "number 67's rank is :" << Rank(tree, 95) << endl;
	cout << "The number whose rank is 5 :" << Select(tree, 10) << endl;
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