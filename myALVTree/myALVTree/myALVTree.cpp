// myALVTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>

using namespace std;


/*
 * 平衡二叉树
 * 
 * 知识参考：http://www.cnblogs.com/huangxincheng/archive/2012/07/22/2603956.html
 * 
 * 二叉排序树的父节点的左子树和右子树的高度之差不能大于1，也就是说不能高过1层，否则该树就失衡了，
 * 此时就要旋转节点，在编码时，我们可以记录当前节点的高度，
 * 比如空节点是-1，叶子节点是0，非叶子节点的height往根节点递增
 */


/*
 * 平衡二叉树结点
 */

struct BBSTNode
{
	int data;
	int height;  //与二叉排序树不同的是，平衡二叉树结点中多了一个维护结点高度的变量height
	BBSTNode *lchild, *rchild;
};


/*
 * 递归查找函数，与二叉排序树相同
 */
BBSTNode *find(int data,BBSTNode *t)
{
	if(t==NULL)
	{
		return NULL;
	}
	if(data<t->data)
	{
		return find(data, t->lchild);
	}else if(data>t->data)
	{
		return find(data, t->rchild);
	}else
	{
		return t;
	}
}



BBSTNode *findMin(BBSTNode *t)
{
	if (t == NULL)
	{
		return NULL;
	}else if(t->lchild==NULL)
	{
		return t;
	}else
	{
		return findMin(t->lchild);
	}
}


BBSTNode *findMax(BBSTNode *t)
{
	if(t==NULL)
	{
		return NULL;
	}else if(t->rchild==NULL)
	{
		return t;
	}else
	{
		return findMax(t->rchild);
	}
}

/*
 * 获得当前结点的高度
 */
int getHeight(BBSTNode *t)
{
	return t == NULL ? -1 : t->height;
}


/*
 * 获取两个数中较大的数
 */
int MAX(int a,int b)
{
	return a > b ? a : b;
}

/*
 *平衡二叉树的旋转一共有4种情况
 *1.只旋转一次就可平衡：
 *1. 1 左左情况（顺时针旋转）
 *1.2 右右情况（逆时针旋转）
 *2. 经两次旋转后平衡：
 *2.1  左右情况（先逆时针再顺时针）
 *2.2  右左旋转（先顺时针再逆时针）
 *
 */


/*
 * 左左旋转情况
 * 即在当前结点的左孩子的左子树进行插入，导致当前节点左子树高度-右子树高度=2
 * 当前结点失衡
 * 
 * lose_balance_node为失衡结点
 */
BBSTNode *singleRotateWithLeft(BBSTNode *lose_balance_node)
{
	BBSTNode *top;  //顶结点，即进行一次旋转后成为双亲节点的节点

	//在使顶结点的右子树作为失衡节点的左子树之后，将失衡节点及其子树以顶结点为轴，顺时针旋转
	top = lose_balance_node->lchild;  //该节点为失衡节点的左孩子
	lose_balance_node->lchild = top->rchild;//将顶节点的右孩子作为失衡节点的左孩子
	top->rchild = lose_balance_node;//失衡节点及其右子树作为顶结点的左子树

	//按照平衡二叉树高度的定义，重新结算失衡节点和顶结点的高度
	lose_balance_node->height = MAX(getHeight(lose_balance_node->lchild), getHeight(lose_balance_node->rchild))+1;
	top->height = MAX(getHeight(top->lchild), getHeight(top->rchild)) + 1;

	//返回旋转后的子树
	return top;

}



/*
 * 右右旋转情况
 * 即在当前节点的右孩子的右子树进行插入，导致当前节点的右子树高度-左子树高度=2
 * 节点失衡
 */
BBSTNode *singleRotateWithRight(BBSTNode *lose_balance_node)
{
	BBSTNode *top;//顶结点，即进行一次旋转后成为双亲节点的节点

	//在使顶结点的左子树作为失衡节点的右子树之后，将失衡节点及其子树以顶结点为轴，逆时针旋转
	top = lose_balance_node->rchild;//右右旋转中，顶结点是失衡节点的右孩子
	lose_balance_node->rchild = top->lchild; //将顶结点的左子树作为失衡节点的右子树
	top->lchild = lose_balance_node;//将失衡节点及其子树作为顶结点的左子树


	//重新计算失衡节点和顶结点的高度
	lose_balance_node->height = MAX(getHeight(lose_balance_node->lchild), getHeight(lose_balance_node->rchild)) + 1;
	top->height = MAX(getHeight(top->lchild), getHeight(top->rchild)) + 1;

	//返回调整好的子树
	return top;
}




/*
 * 左右旋转
 * 即向当前节点的左孩子的右子树进行插入，导致当前节点左子树高度-右子树高度=2
 * 此时，先将失衡节点的左子树进行一次右旋，再整体进行一次左旋
 */
BBSTNode *doubleRotateWithLeft(BBSTNode *lose_balance_node)
{
	lose_balance_node->lchild = singleRotateWithRight(lose_balance_node->lchild);

	return singleRotateWithLeft(lose_balance_node);
}


/*
 * 右左情况
 * 即向当前节点的右孩子的左子树进行插入，导致当前节点右子树高度-左子树高度=2
 * 当前节点失衡
 * 先将失衡节点的右孩子进行一次左左情况的旋转（顺时针旋转），再整体进行右右情况旋转（逆时针旋转）
 */
BBSTNode *doubleRotateWithRight(BBSTNode *node)
{
	node->rchild = singleRotateWithLeft(node->rchild);

	return singleRotateWithRight(node);
}




/*
 * 平衡二叉树扎入节点
 * 为了将关键字是X的新节点插入到一颗AVL树中，
 * 递归的将X插入到T的相应的子树中。
 * 如果子树高度不变，则插入完成，
 * 如果在T中出现高度不平衡，那么根据X和子树中的关键字做适当的单旋转或双旋转，
 * 更新这些高度，从而完成插入。
 */
BBSTNode *insert(int data,BBSTNode *t)
{
	if(t==NULL)
	{
		t = new BBSTNode;
		t->data = data;
		t->lchild = NULL;
		t->rchild = NULL;
		t->height = 0;
	}else if(data<t->data)//如果插入之比当前节点的值小，
	{
		t->lchild = insert(data, t->lchild); //则在当前节点的左子树进行插入
		if(getHeight(t->lchild)-getHeight(t->rchild)==2)//若插入后导致当前节点失衡
		{
			if(data<t->lchild->data)//如果插入位置为当前节点的左孩子的左子树
			{
				//满足左左情况
				t = singleRotateWithLeft(t);
			}else
			{
				//否则，满足左右情况
				t = doubleRotateWithLeft(t);
			}
		}
	}else if(data>t->data)//如果插入值大于当前节点的值
	{
		t->rchild = insert(data, t->rchild);//在当前节点的右子树中进行插入
		if(getHeight(t->rchild)-getHeight(t->lchild)==2)//如果插入后，导致当前节点失衡
		{
			if(data>t->rchild->data)//若插入位置为当前节点右孩子的右子树
			{
				//满足右右情况
				t = singleRotateWithRight(t);
			}else
			{
				//否则满足右左情况
				t = doubleRotateWithRight(t);
			}

			
		}

	}
	//重新结算调整后的节点的高度
	t->height = MAX(getHeight(t->lchild), getHeight(t->rchild)) + 1;


	return t;
}



/*
 * 平衡二叉树删除节点，原理即二叉排序树删除节点原理
 * 如果删除某节点后出现不平衡的情况，则需要进行相应的旋转
 * 调整结构
 */
BBSTNode *deleteNode(int data,BBSTNode *t)
{
	BBSTNode *temp = NULL;  //临时节点
	if(t==NULL)//如果未找到要删除的信息，反馈
	{
		cout << "NOT FOUND" << endl;
	}else if(data<t->data)//如果要删除的值小于当前节点t的值域
	{
		t->lchild = deleteNode(data, t->lchild);//递归调用，在t的左子树进行查找，并返回删除后的子树
		if(getHeight(t->rchild) - getHeight(t->lchild) == 2)  //若删除后，导致t的右子树高度-左子树的高度=2
		{
			//对t的右子树进行调整
			BBSTNode *tmp = t->rchild;//获取t的右子树
		   //判断右子树失衡的类型是右右情况还是右左情况
			if (getHeight(tmp->lchild) > getHeight(tmp->rchild))//如果t的右孩子的左子树高度>右子树高度，属于右左情况
			{
				t = doubleRotateWithRight(t);
			}
		}else
		{
			//否则，属于右右情况
			t = singleRotateWithRight(t);
		}
	}else if(data>t->data)//如果需要删除的值>当前节点t的值域
	{
		t->rchild = deleteNode(data, t->rchild);//递归调用，在t的右子树进行查找，并返回删除后的子树
		if(getHeight(t->lchild) - getHeight(t->rchild) == 2)//若删除后，导致t的左子树高度-右子树高度=2
		{
			BBSTNode *tmp = t->lchild;//获取t的左孩子
			//根据左孩子的左子树和右子树的高度情况，判断失衡点t的失衡类型
			if(getHeight(temp->rchild)>getHeight(tmp->lchild))//如果右子树的高度>左子树的高度
			{
				//左右情况
				t = doubleRotateWithLeft(t);
			}else
			{
				//否则，左左情况
				t = singleRotateWithLeft(t);
			}
		}
	}else if(t->lchild&&t->rchild)//若要删除的值与t的值域相同，且t同时拥有左右孩子
	{
		//如果t的右子树高度高于左子树
		if(getHeight(t->rchild)>getHeight(t->lchild))
		{
			temp = findMin(t->rchild);//在t的右子树中找到最小值，来代替将要被删除的节点t的位置
			t->data = temp->data;//将最小值节点的值域赋给t
			t->rchild = deleteNode(t->data, t->rchild);//删除这个最小值节点
		}else
		{
			//如果t的左子树高度高于右子树
			temp = findMax(t->lchild);//找到t的左子树中的最大值
			t->data = temp->data;//将这个最大值赋给t
			t->lchild = deleteNode(t->data, t->lchild);//删除这个最大值节点
		}
	}else
	{
		//如果将要被删除的节点为叶子节点或只有一个左孩子或右孩子
		temp = t;
		t = (t->lchild == NULL? t->lchild : t->rchild);//使t的左孩子或右孩子直接取代t的位置
		free(temp);//删除t节点
	}

	return t;
}



/*
 * 中序遍历平衡二叉树 
 */
void inorderTraverse(BBSTNode *t)
{
	if(t!=NULL)
	{
		inorderTraverse(t->lchild);
		cout << t->data;
		inorderTraverse(t->rchild);
	}
}



int main()
{
	int n, m;
	BBSTNode *t=NULL ;
	cout << "出入节点个数：" << endl;
	cin >> n;
	cout << "输入数据：" << endl;
	for(int i=0;i<n;i++)
	{
		cin >> m;
		t=insert(m, t);
	}
	inorderTraverse(t);
	cout << endl;

	cout << "输入要删除的数据：" << endl;
	cin >> m;
	t = deleteNode(m, t);
	inorderTraverse(t);
	cout << endl;

    return 0;
}

