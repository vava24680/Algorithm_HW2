
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
		~node();
	private:
		node *left, *right, *parent;
		int key_value;
		int color;//zero(0) means black, one(1) means red.
};
node::node()
{
	this->key_value = -111;
	this->color = 2;//Means not exist.
}
node::node(int key_value)
{
	this->key_value = key_value;
	this->color = 1;//New inserted node's color is red;
}
node::node(int key_value, int color)
{
	this->key_value = key_value;
	this->color = color;
}
node::~node()
{}
/*---------------------------------------------------------*/
class RB_tree
{
public:
	RB_tree();
private:
	node *nil;
};

RB_tree::RB_tree()
{
	nil = new node(-111,0);
}

void Insert(int * tree, int key)
{

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