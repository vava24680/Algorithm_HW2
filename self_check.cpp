#include <iostream>
#include <cstring>
#include <cstdlib>
#include "algo_hw2.hpp"
using namespace std;
int main(void)
{
	const int full_size = 63;
	int* tree=0;
	tree = new int[3*full_size+1];
	memset(tree, -1, full_size*3+1);
	tree[0] = full_size*3+1;
	Insert(tree, 5);
	Insert(tree, 6);
	Insert(tree, 7);
	Insert(tree, 8);
	for(int i=1;i<=30;i=i+3)
	{
		cout << "(" << tree[i] << ", " << tree[i+1] << ", " << tree[i+2] << ")" << endl;
	}
	system("pause");
	return 0;
}