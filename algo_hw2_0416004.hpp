#include <cstddef>
// change this to your id
static const char* student_id = "0416004" ;


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

//
// do your homework here
//

struct Tree{
    int color,value,size;
    Tree *Left,*Right,*parent;
    Tree()
    {
    	Left = NULL;
    	Right = NULL;
    	parent = NULL;
    }
};

void BuildLeft(Tree *,int *,int ,int);
void BuildRight(Tree *,int *,int ,int);
void BuildOriTree(Tree *,int *);
Tree* LeftRotate(Tree *, Tree*);
Tree* RightRotate(Tree *, Tree*);
Tree* RB_InsertFixup(Tree*,Tree *);
Tree* RB_DelFixup(Tree *,Tree *);
Tree* TreeSearch(Tree *,int);
void TreeToArray(Tree *,int *,int);
//void printtree(Tree*);
//Tree *Root=new Tree;
void BuildOriTree(Tree *Root,int *tree)
{	
	int data_size=tree[0];
		
	Root->color=tree[1];
    Root->value=tree[2];
    Root->size=tree[3];
	Root->parent=NULL;
    
    BuildLeft(Root,tree,1,data_size);
	BuildRight(Root,tree,1,data_size);
	
	return ;	
}
void BuildLeft(Tree *node,int *tree,int CurNode,int size)
{	
	//Parent=CurNode;
    CurNode=CurNode*2; //Left child
	if(3*CurNode+1>size)return;
	if(tree[3*CurNode]==0&&tree[3*CurNode-1]==0&&tree[3*CurNode-2]==0)
    {
		node->Left=NULL;
    	return ;
	}
    if(tree[3*CurNode]==-1&&tree[3*CurNode-1]==-1&&tree[3*CurNode-2]==-1)
    	return;
    Tree *LeftNode=new Tree;
	LeftNode->color=tree[3*CurNode-2];
    LeftNode->value=tree[3*CurNode-1];
    LeftNode->size=tree[3*CurNode];
    LeftNode->parent=node;
	node->Left=LeftNode;

    BuildLeft(LeftNode,tree,CurNode,size);
    BuildRight(LeftNode,tree,CurNode,size);
    return ;
}
void BuildRight(Tree *node,int *tree,int CurNode,int size)
{
    CurNode=CurNode*2+1;                       
	if(3*CurNode+1>size)return;
	if(tree[3*CurNode]==0&&tree[3*CurNode-1]==0&&tree[3*CurNode-2]==0)
    {
		node->Right=NULL;
    	return;
	}
    if(tree[3*CurNode]==-1&&tree[3*CurNode-1]==-1&&tree[3*CurNode-2]==-1)
    	return;
	
    Tree *RightNode=new Tree;
	RightNode->color=tree[3*CurNode-2];
    RightNode->value=tree[3*CurNode-1];
    RightNode->size=tree[3*CurNode];
    RightNode->parent=node;
	node->Right=RightNode;

	BuildLeft(RightNode,tree,CurNode,size);
    BuildRight(RightNode,tree,CurNode,size);

	return;
}
Tree* LeftRotate(Tree *Root, Tree* x)
{
	Tree *y=new Tree;
	y=x->Right;
	x->Right=y->Left;
    if (y->Left!=NULL)
        y->Left->parent=x;
    y->parent=x->parent;
	if (x->parent==NULL)
   		Root=y;
   	else
    {
        if (x->parent->Left==x)
            x->parent->Left=y;
        else
            x->parent->Right=y;
    }
    y->Left=x;
    x->parent=y; 

	return Root;  
}
	
Tree* RightRotate(Tree *Root,Tree *y)
{
	Tree *x=new Tree;
	x=y->Left;
    y->Left=x->Right;
    if(x->Right!=NULL)
    	x->Right->parent=y;     
    x->parent=y->parent; 
    if (y->parent==NULL) 
		Root=x;
    else
    {
		if(y==y->parent->Right)
			y->parent->Right=x;
		else
			y->parent->Left=x;
    }
    x->Right=y;
    y->parent=x;

	return Root;
}
Tree* RB_InsertFixup(Tree* RBtreeRoot,Tree *InsertNode)
{
//	cout<<RBtreeRoot->value<<" "<<RBtreeRoot->Right->value<<" "<<RBtreeRoot->Left->value;
	Tree *Parent;
	Tree *GParent;
	while(((Parent=InsertNode->parent)!=NULL)&&(InsertNode->parent->color==1))
	{
		//InsertNode->parent;
		GParent=InsertNode->parent->parent;
		if(Parent==GParent->Left)
		{
			Tree *Uncle=GParent->Right;
        	if (Uncle!=NULL&&Uncle->color==1)//case 1;
            {
				Uncle->color=0;
            	Parent->color=0;
                GParent->color=1;
                InsertNode=GParent;
                
                continue;
                }
            if(Parent->Right==InsertNode)
            {
            	Tree *tmp;
            	RBtreeRoot=LeftRotate(RBtreeRoot,Parent);
            	
            	//printtree(RBtreeRoot);
            	//cout<<"1"<<endl;
        		tmp=Parent;
            	Parent=InsertNode;
            	InsertNode=tmp;
            //	printtree(RBtreeRoot);
            //cout<<"2"<<endl;
            }
        
            	Parent->color=0;
            	GParent->color=1;
				RBtreeRoot=RightRotate(RBtreeRoot,GParent);
				//cout<<RBtreeRoot->value<<"curvalue"<<endl;
			//	printtree(RBtreeRoot);
            	//cout<<"3"<<endl;         
		}
		else
		{
            Tree *Uncle= GParent->Left;
               if(Uncle!=NULL&&Uncle->color==1)
                {
                    Uncle->color=0;
                    Parent->color=0;
                    GParent->color=1;
                    InsertNode=GParent;
                    
                    continue;
                }
           	if(Parent->Left==InsertNode)
            {
                Tree *tmp;
                RBtreeRoot=RightRotate(RBtreeRoot,Parent);
                tmp=Parent;
                Parent=InsertNode;
                InsertNode=tmp;
            }
				Parent->color=0;
            	GParent->color=1;
            	RBtreeRoot=LeftRotate(RBtreeRoot, GParent);
			
            
		}
	}
	RBtreeRoot->color=0;

	return RBtreeRoot;
}

void Insert(int * tree, int key)
{
	
	Tree *RBtreeRoot=new Tree;

	BuildOriTree(RBtreeRoot,tree); 
	
	Tree *RootRecord=new Tree;
	RootRecord=RBtreeRoot;
	
//	printtree(RBtreeRoot);
	
	Tree *y= new Tree;
	y->color=NULL;
	y->Left=NULL;
	y->Right=NULL;
	y->size=NULL;
	y->value=NULL;
	
	Tree *InsertNode=new Tree;
	InsertNode->color=1;
	InsertNode->value=key;
	InsertNode->Left=NULL;
	InsertNode->Right=NULL;

	while(RootRecord!=NULL)
    {
		y=RootRecord;
		//cout<<y->color<<" "<<y->value<<" ";
        if(InsertNode->value<RootRecord->value)
            RootRecord=RootRecord->Left;
		else
            RootRecord=RootRecord->Right;
    }
    InsertNode->parent=y;
	if(y!=NULL)
    {
		if(InsertNode->value<y->value)
			y->Left=InsertNode;                
        else
			y->Right=InsertNode;  
    }
    else
		RootRecord=InsertNode;
	
	////cout<<RBtreeRoot->value<<" "<<RBtreeRoot->Right->value<<" "<<RBtreeRoot->Left->value;	
	//cout<<endl;
//	printtree(RBtreeRoot);
	//cout<<"before"<<RBtreeRoot->value<<endl;
	RBtreeRoot=RB_InsertFixup(RBtreeRoot,InsertNode);
	
	for(int i=1;i<tree[0];i++)
	{
		tree[i]=-1;
	}
	TreeToArray(RBtreeRoot,tree,1);
	//printtree(RBtreeRoot);
	return ;
		
}

Tree* RB_DelFixup(Tree *RBtreeRoot,Tree *Alter,Tree *parent)
{
	Tree *x=new Tree;

    while((Alter==NULL||Alter->color==0)&&Alter!=RBtreeRoot)/************/
    {
        if (parent->Left==Alter)
        {
            x=parent->Right;
            if (x->color==1)
            {
                x->color=0;
                parent->color=1;
                RBtreeRoot=LeftRotate(RBtreeRoot,parent);
                x=parent->Right;
            }
            if ((x->Left==NULL||x->Left->color==0)&&(x->Right==NULL||x->Right->color==0))
            {
                x->color=1;
                Alter=parent;
                parent=Alter->parent;
            }
            else
            {
                if (x->Right==NULL||x->Right->color==0)
                {  
            		x->Left->color=0;
                    x->color=1;
                    RBtreeRoot=RightRotate(RBtreeRoot,x);
                    x=parent->Right;
                }	
				x->color=parent->color;
				parent->color=0;
                x->Right->color=0;
                RBtreeRoot=LeftRotate(RBtreeRoot,parent);
                Alter=RBtreeRoot;
                
				break ;
            }
        }
        else
        {
            x=parent->Left;
            if (x->color==1)
            { 
            	x->color=0;
                parent->color=1;
                RBtreeRoot=RightRotate(RBtreeRoot,parent);
                x=parent->Left;
            }
            if((x->Left==NULL||x->Left->color==0)&&(x->Right==NULL||x->Right->color==0))
            {
                x->color=1;
                Alter=parent;
                parent=Alter->parent;
            }
            else
            {
                if(x->Left==NULL||x->Left->color==0)
                {  
                    x->Right->color=0;
                    x->color=1;
                    RBtreeRoot=LeftRotate(RBtreeRoot,x);
                    x=parent->Left;
                }
                x->color=parent->color;
                parent->color=0;
                x->Left->color=0;
                RBtreeRoot=RightRotate(RBtreeRoot,parent);
                Alter=RBtreeRoot;
                break ;
            }
        }
    }
    if(Alter!=NULL)
        Alter->color=0;
        
    return RBtreeRoot;
}
Tree* TreeSearch(Tree* Root,int key)
{
	Tree* CurNode=new Tree;
	CurNode=Root;
	while(CurNode->value!=key)
	{
		if(key<CurNode->value)
			CurNode=CurNode->Left;
		else 
			CurNode=CurNode->Right;
		if(CurNode==NULL)
			return NULL;
	}	
		while(CurNode->Left!=NULL&&CurNode->Left->value==key)
			CurNode=CurNode->Left;
		
		return CurNode;
}
void Delete(int * tree, int key)
{
	Tree *RBtreeRoot=new Tree;

	BuildOriTree(RBtreeRoot,tree); 
	
	Tree *RootRecord=new Tree;
	RootRecord=RBtreeRoot;
	
	//cout<<"hrer";
	//	printtree(RBtreeRoot);
	
	Tree *DeleNode=new Tree;
	DeleNode=TreeSearch(RBtreeRoot,key);
	
	Tree *Child;
	Tree *Parent;
    int Color;
	
    if((DeleNode->Left!=NULL)&&(DeleNode->Right!=NULL)) 
    {
        Tree *NewNode=DeleNode;
        NewNode=NewNode->Left;
        
        while(NewNode->Right!=NULL)
            NewNode=NewNode->Right;
   
        if(DeleNode->parent!=NULL)
        {
            if (DeleNode->parent->Left==DeleNode)
                DeleNode->parent->Left=NewNode;
            else
               DeleNode->parent->Right=NewNode;
		} 
        else 
			RBtreeRoot=NewNode;		

        Child=NewNode->Left;
        Parent=NewNode->parent;
        
        Color=NewNode->color;
   
        if(Parent==DeleNode)
            Parent=NewNode;
        else
        {
            if (Child!=NULL)
               Child->parent=Parent;
            Parent->Right=Child;
            NewNode->Left=DeleNode->Left;
            DeleNode->Left->parent=NewNode;
        }
        NewNode->color=DeleNode->color;
        NewNode->parent=DeleNode->parent;
        NewNode->Right=DeleNode->Right;
        DeleNode->Right->parent=NewNode;
   
        if(Color==0)
            RBtreeRoot=RB_DelFixup(RBtreeRoot,Child,Parent);
        //free(DeleNode);
        for(int i=1;i<tree[0];i++)
			tree[i]=-1;
	
    	TreeToArray(RBtreeRoot,tree,1);
    	
    	return;
    }
   
    if (DeleNode->Right!=NULL)
        Child=DeleNode->Right;
    else 
        Child=DeleNode->Left;
   
    Parent=DeleNode->parent;
    Color=DeleNode->color;
   
    if(Child!=NULL)
        Child->parent=Parent;
    
    if (Parent!=NULL)
    {
        if (Parent->Right==DeleNode)
            Parent->Right = Child;
        else
            Parent->Left = Child;
    }
    else
        RBtreeRoot=Child;
   
	if (Color==0)
        RBtreeRoot=RB_DelFixup(RBtreeRoot,Child,Parent);
    //free(DeleNode);
    
    //printtree(RBtreeRoot);
    for(int i=1;i<tree[0];i++)
		tree[i]=-1;
    
    TreeToArray(RBtreeRoot,tree,1);
    
    
    
}
void TreeToArray(Tree *RBtreeRoot,int *tree,int CurNode)
{
   
	if(RBtreeRoot->Left!=NULL)
        TreeToArray(RBtreeRoot->Left,tree,CurNode*2);
    if(RBtreeRoot->Right!=NULL)
        TreeToArray(RBtreeRoot->Right,tree,CurNode*2+1);

    if(RBtreeRoot->Left==NULL)
	{
        int left=CurNode*2;
        tree[3*left-2]=0;
        tree[3*left-1]=0;
        tree[3*left]=0;
    }
    if(RBtreeRoot->Right==NULL){
        int right=CurNode*2+1;
        tree[3*right-2]=0;
        tree[3*right-1]=0;
        tree[3*right]=0;
    }
    tree[3*CurNode-2]=RBtreeRoot->color;
    tree[3*CurNode-1]=RBtreeRoot->value;
    tree[3*CurNode]=RBtreeRoot->size;
    return ;
}
/*void printtree(Tree*RBtreeRoot)
{
    if(RBtreeRoot->Left!=NULL)
        printtree(RBtreeRoot->Left);
    if(RBtreeRoot->Right!=NULL)
        printtree(RBtreeRoot->Right);
        //cout<<"color :"<<RBtreeRoot->color<<" key: "<<RBtreeRoot->value<<" size: "<<RBtreeRoot->size<<endl;
    return ;
}*/




int Select(int * tree, int i) {
	// use Dynamic Order Statistics to return the i'th smallest element

	
	return -1;
}

int Rank(int * tree, int x) {
	// use Dynamic Order Statistics to return the rank of element x in the tree

	
	return -1;
}
