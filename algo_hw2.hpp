#include <iostream>
#include <cstdlib>
#include <cstring>
// change this to your id
static const char* student_id = "0416005" ;

#define RED 1
#define BLACK 0
// do not edit prototype
void Insert(int *, int);
void Delete(int *, int);
int Select(int *, int);
int Rank(int *, int);

// data structure :
// tree is an array with enough space
// tree[0] is the array size
// bundle three attribute as a node data
// First attribute is color, "0" means black, "1" means red , NIL is also "0", "-1" means no data
// Second attribute is key, "0" means NIL, "1"~"999" means data,  "-1" means no data
// Third attribute is size, for Dynamic Order Statistics, "0" means NIL , "-1" means no data
//
// for example,
// if tree[0] is "256" says that the array size is 256
//
// if tree[1] is "1" says that the place of 1 is a red node
//
// if tree[2] is "5" says that the place of 1 is key of 5
//
// if tree[8] is "-1" says that the place of 3 has nothing
//
// if tree[14] is "0" says that the place of 5 is a node of NIL
//
// if tree[19] is "66" says that the place of 7 is key of 66

//
// if there is an ambiguous situation, choose the smaller ( left ) one
//

class node
{
	public:
		node();
		node(int key_value, int size);//For Insertion new node;
		node(int key_value, int color, int size);
		node(int key_value, int color, bool nil_node);
		void initialize_property(node* nil);
		node* get_left(void) const;
		node* get_right(void) const;
		node* get_parent(void) const;
		int get_color(void) const;
		int get_key_value(void) const;
		int get_size(void) const;
		void modify_left(node* n_left);
		void modify_right(node* n_right);
		void modify_parent(node* n_parent);
		void modify_color(int color);
		void modify_key_value(int key_value);
		void modify_size(int size);
		~node();
	private:
		node *left, *right, *parent;
		int key_value;
		bool nil_node;
		int color;//zero(0) means black, one(1) means red.
		int size;
};
node::node()
{
	this->key_value = -111;
	this->color = 2;//Means not exist.
	this->nil_node = 0;
	this->size = 0;
}
node::node(int key_value, int size)
{
	this->key_value = key_value;
	this->color = 1;//New inserted node's color is red;
	this->nil_node = 0;
	this->size = size;
}
node::node(int key_value, int color, int size)
{
	this->key_value = key_value;
	this->color = color;
	this->nil_node = 0;
	this->size = size;
}
node::node(int key_value, int color, bool nil_node)
{
	this->key_value = key_value;
	this->color = color;
	this->nil_node = nil_node;
	this->size = 0;
}
void node::initialize_property(node* nil)
{
	this->left = nil;
	this->right = nil;
	this->color = 1;
}
node* node::get_left(void) const
{
	return this->left;
}
node* node::get_right(void) const
{
	return this->right;
}
node* node::get_parent(void) const
{
	return this->parent;
}
int node::get_color(void) const
{
	return this->color;
}
int node::get_key_value(void) const
{
	return this->key_value;
}
int node::get_size(void) const
{
	return this->size;
}
void node::modify_left(node* n_left)
{
	this->left = n_left;
}
void node::modify_right(node* n_right)
{
	this->right = n_right;
}
void node::modify_parent(node* n_parent)
{
	this->parent = n_parent;
}
void node::modify_color(int color)
{
	this->color = color;
}
void node::modify_key_value(int key_value)
{
	this->key_value = key_value;
}
void node::modify_size(int size)
{
	this->size = size;
}
node::~node()
{}
/*---------------------------------------------------------*/
class RB_tree
{
public:
	RB_tree();
	node* get_root(void) const;
	void left_rotation(node* z);
	void right_rotation(node* z);
	node* left_maximum(node* z);
	void node_insert(int data);
	void node_insert(int data, int color);
	void node_delete(int data);
	void property_fixup(node* z);
	void deletion_fixup(node* z);
	void inorder_travel(int start_index, int* tree,const node* cur_deal_node);
	bool empty_tree();
private:
	node *nil;
	node *root;
};

RB_tree::RB_tree()
{
	nil = new node(-111,0,true);
	//root = nil;
	root = nil;
}

node* RB_tree::get_root(void) const
{
	return this->root;
}
void RB_tree::left_rotation(node* z)
{
	int size_of_z = -2;
	int size_of_tem_z_right_right = -2;
	node* temp_z_right = z->get_right();

	size_of_z = z->get_size();
	size_of_tem_z_right_right = (temp_z_right->get_right())->get_size();

	z->modify_right(temp_z_right->get_left());
	if(temp_z_right->get_left()!=this->nil)
	{
		(temp_z_right->get_left())->modify_parent(z);
	}
	temp_z_right->modify_parent(z->get_parent());
	if(z->get_parent()==this->nil)
	{
		this->root = temp_z_right;
	}
	else if(z==((z->get_parent())->get_left()))
	{
		(z->get_parent())->modify_left(temp_z_right);
	}
	else
	{
		(z->get_parent())->modify_right(temp_z_right);
	}

	if(temp_z_right!=this->nil)
	{
		temp_z_right->modify_size(size_of_z);
	}
	else
	{
		temp_z_right->modify_size(0);
	}
	if(z!=this->nil)
	{
		z->modify_size(size_of_z - size_of_tem_z_right_right - 1);
	}
	else
	{
		z->modify_size(0);
	}
	temp_z_right->modify_left(z);
	z->modify_parent(temp_z_right);
}
void RB_tree::right_rotation(node* z)
{
	int size_of_z = -2;
	int size_of_tmp_z_left_left = -2;
	node* temp_z_left = z->get_left();

	size_of_z = z->get_size();
	size_of_tmp_z_left_left = (temp_z_left->get_left())->get_size();

	z->modify_left(temp_z_left->get_right());
	if(temp_z_left->get_right()!=this->nil)
	{
		(temp_z_left->get_right())->modify_parent(z);
	}
	temp_z_left->modify_parent(z->get_parent());
	if(z->get_parent()==this->nil)
	{
		this->root = temp_z_left;
	}
	else if(z==(z->get_parent())->get_left())
	{
		(z->get_parent())->modify_left(temp_z_left);
	}
	else
	{
		(z->get_parent())->modify_right(temp_z_left);
	}

	if(temp_z_left!=this->nil)
	{
		temp_z_left->modify_size(size_of_z);
	}
	else
	{
		temp_z_left->modify_size(0);
	}
	if(z!=this->nil)
	{
		z->modify_size(size_of_z - size_of_tmp_z_left_left -1);
	}
	else
	{
		z->modify_size(0);
	}
	temp_z_left->modify_right(z);
	z->modify_parent(temp_z_left);
}
node* RB_tree::left_maximum(node* z)
{
	while(z->get_right()!=this->nil)
	{
		z = z->get_right();
	}
	return z;
}

void RB_tree::node_insert(int data)
{//For newly inserted node in a RBtree
	node* parent_curnode = this->nil;
	node* current_node = this->root;
	node* new_node = new node(data,1);
	while(current_node!=this->nil)
	{
		parent_curnode = current_node;
		if (new_node->get_key_value()<current_node->get_key_value())
		{
			current_node = current_node->get_left();
		}
		else
		{
			current_node = current_node->get_right();
		}
		parent_curnode->modify_size(parent_curnode->get_size()+1);
	}
	new_node->modify_parent(parent_curnode);
	if(parent_curnode==this->nil)
	{
		this->root = new_node;
	}
	else if(new_node->get_key_value()<parent_curnode->get_key_value())
	{
		parent_curnode->modify_left(new_node);
	}
	else
	{
		parent_curnode->modify_right(new_node);
	}
	new_node->initialize_property(this->nil);
	property_fixup(new_node);
}
void RB_tree::node_insert(int color, int data)
{
	node* parent_curnode = this->nil;
	node* current_node = this->root;
	node* new_node = new node(data,color,1);
	while(current_node!=this->nil)
	{
		parent_curnode = current_node;
		if (new_node->get_key_value()<current_node->get_key_value())
		{
			current_node = current_node->get_left();
		}
		else
		{
			current_node = current_node->get_right();
		}
		parent_curnode->modify_size(parent_curnode->get_size()+1);
	}
	new_node->modify_parent(parent_curnode);
	if(parent_curnode==this->nil)
	{
		this->root = new_node;
		this->root->modify_parent(this->nil);
	}
	else if(new_node->get_key_value()<parent_curnode->get_key_value())
	{
		parent_curnode->modify_left(new_node);
	}
	else
	{
		parent_curnode->modify_right(new_node);
	}
	new_node->modify_left(this->nil);
	new_node->modify_right(this->nil);
	//new_node->initialize_property(this->nil);
	//property_fixup(new_node);
}
void RB_tree::node_delete(int data)
{
	node* parent_of_deleted = 0;
	node* real_deleted_node=0;
	node* child_of_RDN=0;
	node* delete_node = this->root;
	while(delete_node!=this->nil && delete_node->get_key_value()!=data)
	{
		parent_of_deleted = delete_node;
		if(delete_node->get_key_value()>data)
		{
			delete_node->modify_size((delete_node->get_size())-1);
			delete_node = delete_node->get_left();
		}
		else if(delete_node->get_key_value()<data)
		{
			delete_node->modify_size((delete_node->get_size())-1);
			delete_node = delete_node->get_right();
		}
	}
	if(delete_node==this->nil)
	{
		while(parent_of_deleted!=this->nil)
		{
			parent_of_deleted->modify_size((parent_of_deleted->get_size())+1);
			parent_of_deleted = (parent_of_deleted->get_parent());
		}
		return;
	}
	if (delete_node->get_left() == this->nil || delete_node->get_right() == this->nil)
	{
		real_deleted_node = delete_node;
	}
	else
	{//Eliminate the delete_node has two children situation
		real_deleted_node = this->left_maximum(delete_node->get_left());
	}
	if(real_deleted_node->get_left()!=this->nil)
	{
		child_of_RDN = real_deleted_node->get_left();
	}
	else
	{
		child_of_RDN = real_deleted_node->get_right();
	}
	child_of_RDN->modify_parent(real_deleted_node->get_parent());

	if(real_deleted_node->get_parent()==this->nil)
	{
		this->root=child_of_RDN;
		child_of_RDN->modify_parent(this->nil);
	}
	else if(real_deleted_node==(real_deleted_node->get_parent())->get_left())
	{
		(real_deleted_node->get_parent())->modify_left(child_of_RDN);
	}
	else
	{
		(real_deleted_node->get_parent())->modify_right(child_of_RDN);
	}

	if(real_deleted_node!=delete_node)
	{
		//delete_node->modify_color(real_deleted_node->get_color());
		delete_node->modify_key_value(real_deleted_node->get_key_value());
	}
	if(real_deleted_node->get_color()==BLACK)
	{
		delete real_deleted_node;
		deletion_fixup(child_of_RDN);
	}
	else
	{
		delete real_deleted_node;
	}
	return;
}
void RB_tree::property_fixup(node* z)
{
	node* cur_deal_node = z;
	node* uncle_node=0;
	node* grandparent=0;
	while((cur_deal_node->get_parent())->get_color()==RED)
	{
		grandparent = (cur_deal_node->get_parent())->get_parent();
		if(cur_deal_node->get_parent()==grandparent->get_left())
		{//parent is left child
			uncle_node = grandparent->get_right();
			if (uncle_node->get_color() == RED)
			{
				(cur_deal_node->get_parent())->modify_color(BLACK);
				uncle_node->modify_color(BLACK);
				grandparent->modify_color(RED);
				cur_deal_node = grandparent;
			}
			else
			{
				if (cur_deal_node == (cur_deal_node->get_parent())->get_right())
				{//cur_deal_node is a right child which need to be left rotated on its parent
					cur_deal_node = cur_deal_node->get_parent();
					this->left_rotation(cur_deal_node);
					grandparent = (cur_deal_node->get_parent())->get_parent();//Since the cur_deal_node has been modified.
				}
				(cur_deal_node->get_parent())->modify_color(BLACK);
				grandparent->modify_color(RED);
				this->right_rotation(grandparent);
			}
		}
		else//parent is right child
		{
			uncle_node = grandparent->get_left();
			if(uncle_node->get_color() == RED)
			{
				(cur_deal_node->get_parent())->modify_color(BLACK);
				uncle_node->modify_color(BLACK);
				grandparent->modify_color(RED);
				cur_deal_node = grandparent;
			}
			else
			{
				if (cur_deal_node == (cur_deal_node->get_parent())->get_left())
				{
					cur_deal_node = cur_deal_node->get_parent();
					this->right_rotation(cur_deal_node);
					grandparent = (cur_deal_node->get_parent())->get_parent();//Since the cur_deal_node has been modified.
				}
				(cur_deal_node->get_parent())->modify_color(BLACK);
				grandparent->modify_color(RED);
				this->left_rotation(grandparent);
			}
		}
	}
	this->root->modify_color(BLACK);
}
void RB_tree::deletion_fixup(node* z)
{
	node* cur_deal_node = z;
	node* sibling_node=0;
	while(cur_deal_node!=this->root && cur_deal_node->get_color()==BLACK)
	{
		if(cur_deal_node==(cur_deal_node->get_parent())->get_left())
		{//cur_deal_node is left node
			sibling_node = (cur_deal_node->get_parent())->get_right();
			if(sibling_node->get_color()==RED)
			{
				sibling_node->modify_color(BLACK);
				(cur_deal_node->get_parent())->modify_color(RED);
				this->left_rotation((cur_deal_node->get_parent()));
				sibling_node=(cur_deal_node->get_parent())->get_right();
			}
			else
			{
				if((sibling_node->get_left())->get_color()==BLACK && (sibling_node->get_right()->get_color()==BLACK))
				{
					sibling_node->modify_color(RED);
					cur_deal_node = cur_deal_node->get_parent();
				}
				else if((sibling_node->get_right())->get_color()==BLACK)
				{
					sibling_node->modify_color(RED);
					(sibling_node->get_left())->modify_color(BLACK);
					this->right_rotation(sibling_node);
					sibling_node = (cur_deal_node->get_parent())->get_right();
				}
			}
			(sibling_node->get_right())->modify_color(BLACK);
			sibling_node->modify_color((cur_deal_node->get_parent())->get_color());
			(cur_deal_node->get_parent())->modify_color(BLACK);
			this->left_rotation((cur_deal_node->get_parent()));
			cur_deal_node = this->root;
		}
		else
		{//cur_deal_node is right node
			sibling_node = (cur_deal_node->get_parent())->get_left();
			if((sibling_node->get_color())==RED)
			{
				sibling_node->modify_color(BLACK);
				(cur_deal_node->get_parent())->modify_color(RED);
				this->right_rotation((cur_deal_node->get_parent()));
				sibling_node = (cur_deal_node->get_parent())->get_left();
			}
			else
			{
				if((sibling_node->get_left())->get_color()==BLACK && (sibling_node->get_right())->get_color()==BLACK)
				{
					sibling_node->modify_color(RED);
					cur_deal_node = cur_deal_node->get_parent();
				}
				else if((sibling_node->get_left())->get_color()==BLACK)
				{
					sibling_node->modify_color(RED);
					(sibling_node->get_right())->modify_color(BLACK);
					this->left_rotation(sibling_node);
					sibling_node = (cur_deal_node->get_parent())->get_left();
				}
			}
			(sibling_node->get_left())->modify_color(BLACK);
			sibling_node->modify_color((cur_deal_node->get_parent())->get_color());
			(cur_deal_node->get_parent())->modify_color(BLACK);
			this->right_rotation((cur_deal_node->get_parent()));
			cur_deal_node = this->root;
		}
	}
	cur_deal_node->modify_color(BLACK);//Restore property 4(two consecutive red are not allowed)
}
bool RB_tree::empty_tree()
{
	return (this->root==this->nil) ? true : false;
}
//tree[3n-2]:color,tree[3n-2]:key_value,tree[3n]:Dynamic Order Statistics
void RB_tree::inorder_travel(int start_index, int* tree,const node* cur_deal_node)
{//First time calling this function, cur_deal_node will be the root;
	if(cur_deal_node == this->nil)
	{
		tree[3*start_index-2] = 0;
		tree[3*start_index-1] = 0;
		tree[3*start_index] = 0;
		return;
	}
	tree[3*start_index-2] = cur_deal_node->get_color();
	tree[3*start_index-1] = cur_deal_node->get_key_value();
	tree[3*start_index] = cur_deal_node->get_size();
	inorder_travel(start_index*2, tree, (cur_deal_node)->get_left());
	inorder_travel(start_index*2+1, tree, (cur_deal_node)->get_right());
	return;
}
//tree[3n-2]:color,tree[3n-1]:key_value,tree[3n]:Dynamic Order Statistics
void Insert(int * tree, int key)
{
	int arr_size = tree[0];
	RB_tree* RBTree = 0;
	RBTree = new RB_tree;
	int node_size = (tree[0]-1)/3;
	if (RBTree->empty_tree() && tree[1]==-1)
	{
		RBTree->node_insert(0, key);
	}
	else
	{
		for(int i = 1;i<=node_size;i++)
		{
			if(tree[3*i-1] == 0)
				continue;
			else if(tree[3*i-1] == -1)
				break;
			RBTree->node_insert(tree[3*i-2], tree[3*i-1]);
		}
		RBTree->node_insert(key);
	}
	/*------------------Write Back------------------------------------*/
	//memset(tree, -1, arr_size);
	for (int i = 1; i < arr_size; i++)
	{
		tree[i] = -1;
	}
	RBTree->inorder_travel(1, tree, RBTree->get_root());
	/*int node_size = (tree[0]-1)/3;
	for(int i=1;i<=node_size;i++)
	{
		RBTree->node_insert(tree[3*i-2],tree[3*i-1]);
	}
	RBTree->node_insert(key);*/
}
//tree[3n-2]:color,tree[3n-2]:key_value,tree[3n]:Dynamic Order Statistics
void Delete(int * tree, int key)
{
	int arr_size = tree[0];
	RB_tree* RBTree = 0;
	RBTree = new RB_tree;
	int node_size = (tree[0]-1)/3;
	if (RBTree->empty_tree() && tree[1]==-1)
	{
		RBTree->node_insert(0, key);
	}
	else
	{
		for(int i = 1;i<=node_size;i++)
		{
			if (tree[3 * i - 1] == 0)
				continue;
			else if (tree[3 * i - 1] == -1)
				continue;
			RBTree->node_insert(tree[3 * i - 2], tree[3 * i - 1]);
		}
	}
	RBTree->node_delete(key);
	for (int i = 1; i < arr_size; i++)
	{
		tree[i] = -1;
	}
	tree[0] = arr_size;
	/*------------------write back---------------------*/
	RBTree->inorder_travel(1, tree, (RBTree->get_root()));
}

int Select(int * tree, int i) {
	// use Dynamic Order Statistics to return the i'th smallest element


	return -1;
}

int Rank(int * tree, int x) {
	// use Dynamic Order Statistics to return the rank of element x in the tree


	return -1;
}
