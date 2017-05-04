
// change this to your id
static const char* student_id = "0416005" ;


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
node::~node()
{}
/*---------------------------------------------------------*/
class RB_tree
{
public:
	RB_tree();
	void left_rotation(node* z);
	void right_rotation(node* z);
	void tree_insert(int data);
	void tree_insert(int data, int color);
	void property_fixup(node* z);
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
	//z->get_right() = temp_z_right->get_left();
	z->modify_right(temp_z_right->get_left());
	if(temp_z_right->get_left()!=this->nil)
	{
		//temp_z_right->get_left()->get_parent() = z;
		(temp_z_right->get_left())->modify_parent(z);
	}
	//temp_z_right->get_parent() = z->get_parent();
	temp_z_right->modify_parent(z->get_parent());
	if(z->get_parent()==this->nil)
	{
		this->root = temp_z_right;
	}
	else if(z==(z->get_parent())->get_left())
	{
		//(z->get_parent())->get_left() = temp_z_right;
		(z->get_parent())->modify_left(temp_z_right);
	}
	else
	{
		//z->get_parent()->get_right() = temp_z_right;
		(z->get_parent())->modify_right(temp_z_right);
	}
	//temp_z_right->get_left() = z;
	temp_z_right->modify_left(z);
	//z->get_parent() = temp_z_right;
	z->modify_parent(temp_z_right);
}
void RB_tree::right_rotation(node* z)
{
	node* temp_z_left = z->get_left();
	//z->left = temp_z_left->right;
	z->modify_left(temp_z_left->get_right());
	if(temp_z_left->get_right()!=this->nil)
	{
		//temp_z_left->right->parent = z;
		(temp_z_left->get_right())->modify_parent(z);
	}
	//temp_z_left->parent = z->parent;
	temp_z_left->modify_parent(z->get_parent());
	if(z->parent==this->nil)
	{
		this->root = temp_z_left;
	}
	else if(z=z->parent->left)
	{
		z->parent->left = temp_z_left;
	}
	else
	{
		z->parent->right = temp_z_left;
	}
	temp_z_left->right = z;
	z->parent = temp_z_left;
}

void RB_tree::tree_insert(int data)
{
	node* parent_curnode = this->nil;
	node* current_node = this->root;
	node* new_node = new node(data);
	while(current_node!=this->nil)
	{
		parent_curnode = current_node;
		if (new_node->key_value<current_node->key_value)
		{
			current_node = current_node->left;
		}
		else
		{
			current_node = current_node->right;
		}
	}
	new_node->parent = parent_curnode;
	if(parent_curnode==this->nil)
	{
		this->root = new_node;
	}
	else if(new_node->key_value<parent_curnode->key_value)
	{
		parent_curnode->left = new_node;
	}
	else
	{
		parent_curnode->right = new_node;
	}
	new_node->initialize_property(this->nil);
	property_fixup(new_node);
}
void RB_tree::tree_insert(int data, int color)
{
	node* parent_curnode = this->nil;
	node* current_node = this->root;
	node* new_node = new_node(data,color);
	while(current_node!=this->nil)
	{
		parent_curnode = current_node;
		if(z->key_value<current_node->key_value)
		{
			current_node = current_node->left;
		}
		else
		{
			current_node = current_node->right;
		}
	}
	new_node->parent = parent_curnode;
	if(parent_curnode==this->nil)
	{
		this->root = new_node;
	}
	else if(new_node->key_value<parent_curnode->key_value)
	{
		parent_curnode->left = new_node;
	}
	else
	{
		parent_curnode->right = new_node;
	}
	new_node->initialize_property(this->nil);
	property_fixup(new_node);
}
//tree[3n-2]:color,tree[3n-2]:key_value,tree[3n]:Dynamic Order Statistics
void Insert(int * tree, int key)
{
	int node_size = (tree[0]-1)/3;
	RB_tree* RBTree = NULL:
	RBTree = new RB_tree;
	for(int i=1;i<=node_size;i++)
	{
		RBTree->tree_insert(tree[3*i-1],tree[3*i-2]);
	}
}

void Delete(int * tree, int key) {

}

int Select(int * tree, int i) {
	// use Dynamic Order Statistics to return the i'th smallest element


	return -1;
}

int Rank(int * tree, int x) {
	// use Dynamic Order Statistics to return the rank of element x in the tree


	return -1;
}