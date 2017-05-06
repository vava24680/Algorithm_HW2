#include <iostream>
#include <cstdlib>
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
		node(int key_value);//For Insertion new node;
		node(int key_value, int color);
		node(int key_value, int color, bool nil_node);
		void initialize_property(node* nil);
		node* get_left(void) const;
		node* get_right(void) const;
		node* get_parent(void) const;
		int get_key_value(void) const;
		int get_color(void) const;
		void modify_left(node* n_left);
		void modify_right(node* n_right);
		void modify_parent(node* n_parent);
		void modify_color(int color);
		void modify_key_value(int key_value);
		~node();
	private:
		node *left, *right, *parent;
		int key_value;
		bool nil_node;
		int color;//zero(0) means black, one(1) means red.
};
node::node()
{
	this->key_value = -111;
	this->color = 2;//Means not exist.
	this->nil_node = 0;
}
node::node(int key_value)
{
	this->key_value = key_value;
	this->color = 1;//New inserted node's color is red;
	this->nil_node = 0;
}
node::node(int key_value, int color)
{
	this->key_value = key_value;
	this->color = color;
	this->nil_node = 0;
}
node::node(int key_value, int color, bool nil_node)
{
	this->key_value = key_value;
	this->color = color;
	this->nil_node = nil_node;
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
int node::get_key_value(void) const
{
	return this->key_value;
}
int node::get_color(void) const
{
	return this->color;
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
node::~node()
{}
/*---------------------------------------------------------*/
class RB_tree
{
public:
	RB_tree();
	void left_rotation(node* z);
	void right_rotation(node* z);
	node* left_maximum(node* z);
	void node_insert(int data);
	void node_insert(int data, int color);
	void node_delete(int data);
	void property_fixup(node* z);
	void deletion_fixup(node* z);
	bool empty_tree();
private:
	node *nil;
	node *root;
};

RB_tree::RB_tree()
{
	nil = new node(-111,0,1);
	//root = nil;
	root = nil;
}

void RB_tree::left_rotation(node* z)
{
	node* temp_z_right = z->get_right();
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
	temp_z_right->modify_left(z);
	z->modify_parent(temp_z_right);
}
void RB_tree::right_rotation(node* z)
{
	node* temp_z_left = z->get_left();
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
{
	node* parent_curnode = this->nil;
	node* current_node = this->root;
	node* new_node = new node(data);
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
	node* new_node = new node(data,color);
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
	//new_node->initialize_property(this->nil);
	//property_fixup(new_node);
}
void RB_tree::node_delete(int data)
{
	node* real_deleted_node=0;
	node* child_of_RDN=0;
	node* delete_node = this->root;
	while(delete_node!=this->nil && delete_node->get_key_value()!=data)
	{
		if(delete_node->get_key_value()<data)
		{
			delete_node = delete_node->get_left();
		}
		else if(delete_node->get_key_value()>data)
		{
			delete_node = delete_node->get_right();
		}
	}
	if(delete_node==this->nil)
	{
		return;
	}
	if (delete_node->get_left() == NULL || delete_node->get_right() == NULL)
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
		delete_node->modify_color(real_deleted_node->get_color());
		//delete_node->modify_key_value(real_deleted_node->get_key_value());
	}
	delete real_deleted_node;
	if(real_deleted_node->get_color()==BLACK)
	{
		deletion_fixup(child_of_RDN);
	}
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
			else if(cur_deal_node = (cur_deal_node->get_parent())->get_right())
			{//cur_deal_node is a right child which need to be left rotated on its parent
				cur_deal_node = cur_deal_node->get_parent();
				this->left_rotation(cur_deal_node);
				grandparent = (cur_deal_node->get_parent())->get_parent();//Since the cur_deal_node has been modified.
			}
			(cur_deal_node->get_parent())->modify_color(BLACK);
			grandparent->modify_color(RED);
			this->right_rotation(cur_deal_node);
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
			else if(cur_deal_node = (cur_deal_node->get_parent())->get_left())
			{
				cur_deal_node = cur_deal_node->get_parent();
				this->right_rotation(cur_deal_node);
				grandparent = (cur_deal_node->get_parent())->get_parent();//Since the cur_deal_node has been modified.
			}
			(cur_deal_node->get_parent())->modify_color(BLACK);
			grandparent->modify_color(RED);
			this->left_rotation(cur_deal_node);
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
			}
			else
			{
				if((sibling_node->get_left())->get_color()==BLACK && (sibling_node->get_right())->get_color()==BLACK)
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
			}
			else
			{
				if((sibling_node->get_left())->get_color()==BLACK && (sibling_node->get_right())->get_color()==BLACK)
				{

				}
				else if((sibling_node->get_right())->get_color()==BLACK)
				{

				}
				/*
				else
				{

				}
				*/
			}
			cur_deal_node = this->root;
		}
	}
	z->modify_color(BLACK);//Restore property 4(two consecutive red are not allowed)
}
bool RB_tree::empty_tree()
{
	return (this->root==this->nil) ? true : false;
}
//tree[3n-2]:color,tree[3n-2]:key_value,tree[3n]:Dynamic Order Statistics
void Insert(int * tree, int key)
{
	RB_tree* RBTree = 0;
	RBTree = new RB_tree;
	int node_size = (tree[0]-1)/3;
	if (RBTree->empty_tree())
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
	}
	RBTree->node_insert(key);
	/*------------------Write Back------------------------------------*/

	/*int node_size = (tree[0]-1)/3;
	for(int i=1;i<=node_size;i++)
	{
		RBTree->node_insert(tree[3*i-2],tree[3*i-1]);
	}
	RBTree->node_insert(key);*/
}

void Delete(int * tree, int key)
{
	RB_tree* RBTree = 0;
	RBTree = new RB_tree;
	int node_size = (tree[0]-1)/3;
	if (RBTree->empty_tree())
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
	}
	RBTree->node_delete(key);
	/*------------------write back---------------------*/
}

int Select(int * tree, int i) {
	// use Dynamic Order Statistics to return the i'th smallest element


	return -1;
}

int Rank(int * tree, int x) {
	// use Dynamic Order Statistics to return the rank of element x in the tree


	return -1;
}
