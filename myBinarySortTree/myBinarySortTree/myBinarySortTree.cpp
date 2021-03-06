// myBinarySortTree.cpp: 定义控制台应用程序的入口点。
//


//二叉排序树又称“二叉查找树”、“二叉搜索树”。

//二叉排序树：或者是一棵空树，或者是具有下列性质的二叉树：

//1. 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；

//2. 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；

//3. 它的左、右子树也分别为二叉排序树。




#include "stdafx.h"
#include<iostream>
using namespace std;

/*
 * 二叉树结点结构体
 */
struct BiNode
{
	int data;
	BiNode *rchild, *lchild;
};



/*
 * 查询二叉排序树
 * 递归查找二叉排序树t中是否存在key
 * 指针parent指向t的双亲结点，其初始调用值为null
 * 指针last指向查找路径上的最后一个结点
 * 
 * 在二元排序树b中查找x的过程为：
 * 1.若b是空树，则搜索失败，否则：
 * 2.若x等于b的根节点的数据域之值，则查找成功；否则：
 * 3.若x小于b的根节点的数据域之值，则搜索左子树；否则：
 * 4.查找右子树。
 * 
 * 若找到，返回true
 * 若不存在，返回false
 * 
 * 
 * 
 */
bool searchBST(BiNode *t,int key,BiNode *parent,BiNode *&last)
{
	if(!t) //若二叉树不存在则返回false
	{
		last = parent;
		return false;
	}else if(key==t->data)//若找到
	{
		last = t;  //保存当前查找路径的最后一个结点t
		return true;//查找成功
	}else if(key<t->data) //若key小于当前结点的值，则从当前节点的左子树进行查找
	{
		return searchBST(t->lchild, key, t, last);
	}else
	{
		return searchBST(t->rchild, key, t, last);//若key大于当前结点的值，则从当前节点的右子树进行查找
	}
}




/*
 * 二叉树的插入算法（随着查找的进行动态建树）
 * 
 * 当二叉排序树不存在当前要查询的key时
 * 在合适的位置插入key并返回true，
 * 否则返回false
 */
bool inseartBST(BiNode *&t,int key)
{
	BiNode *p, *s;//辅助指针p用来记录查找路径的最后一个结点，辅助指针s则用来插入新的结点
	if(!searchBST(t,key,NULL,p))//先查询排序二叉树，如果当前要查询的key不存在，则
	{
		//用指针p记录查询路径的最后一个结点
		//初始化用来创建新节点的指针s
		s = new BiNode();
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)//如果p为空，说明排序二叉树还没有建立，则
		{
			t = s;//创建根节点
		}else if(key<p->data)//如果当前查询的key小于查询路径最后一个结点的值，则
		{
			p->lchild = s;//使新节点成为p的左孩子
		}else//否则为右孩子
		{
			p->rchild = s;
		}
		return true;//插入成功
	}else
	{
		return false; //当前二叉树已经有key这个值，不需要插入
	}
}



/*
 * 排序二叉树删除结点算法
 * 从二叉排序树中删除结点p，并重接它的左或右子树
 * 
 * 在二叉排序树中删去一个结点，分三种情况讨论：
 *  1.若*p结点为叶子结点，即PL(左子树)和PR(右子树)均为空树。
 *  由于删去叶子结点不破坏整棵树的结构，
 *  则只需修改其双亲结点的指针即可。
 *  
 *  2.若*p结点只有左子树PL或右子树PR，
 *  此时只要令PL或PR直接成为其双亲结点*f的左子树（当*p是左子树）或右子树（当*p是右子树）即可，
 *  作此修改也不破坏二叉排序树的特性。
 *  
 *  3.若*p结点的左子树和右子树均不空。
 *  在删去*p之后，为保持其它元素之间的相对位置不变，
 *  可按中序遍历保持有序进行调整。
 *  比较好的做法是，找到*p的直接前驱（或直接后继）*s，
 *  用*s来替换结点*p，然后再删除结点*s。
 * 
 * 
 */
bool Delete(BiNode *&p)
{
	BiNode *q, *s;//辅助指针q用来删除结点，s用来重构二叉排序树

	if(p->rchild==NULL)//如果没有右子树，则将其左子树上移，取代p的位置，成为p的双亲结点的左子树
	{
		q = p;//q来接收p的存储空间，并释放
		p = p->lchild;
		free(q);
	}else if(p->lchild==NULL)//如果没有左子树，则将其右子树上移，取代取代p的位置，成为p的双亲结点的右子树
	{
		q = p;
		p = p->rchild;
		free(q);
	}else //如果左右子树都不为空
	{
		q = p;
		s = p->lchild;//找到p左子树中最大的元素（多位于p的左子树的右子树的右叶子结点或只有左叶子结点的根）
		while(s->rchild)
		{
			q = s;//用q记录s的双亲结点
			s = s->rchild;
		}
		p->data = s->data;//将这个最大元素的值赋给p的值域
		if(q!=p)//如果s的双亲结点不是p
		{
			q->rchild = s->lchild;//将s的左孩子作为s的双亲的右孩子
		}else//否则，说明p的左子树只有一个结点即s，此时，s的左右孩子都为null
		{
			q->lchild = s->lchild;//将s的左孩子作为s的双亲的左孩子
		}
		free(s);//释放s
		return true;
	}
	return false;
}


/*
 * 二叉排序树，删除元素key
 * 删除成功返回true，失败返回false
 */
bool deleteBST(BiNode *&t,int key)
{
	if(!t) //不存在值域等于key的节点
	{
		return false;
	}else
	{     //查找值域等于key的节点并删除
		if(key==t->data)
		{
			return Delete(t);
		}else if(key<t->data)
		{
			return deleteBST(t->lchild, key);
		}else
		{
			return deleteBST(t->rchild, key);
		}
	}
}


int main()
{
	BiNode *root = new BiNode();
	BiNode *last = new BiNode();
	int  n, m, i, j;
	cout << "输入二叉排序树节点个数n:" << endl;
	cin >> n;
	cout << "输入各节点的数据：" << endl;
	for(i=0;i<n;i++)
	{
		cin >> m;
		inseartBST(root, m);
	}
	cout << "输入要查询的数据：" << endl;
	cin >> j;
	if(searchBST(root, j, NULL, last))
	{
		cout << "查找成功" << endl;
	}
	cout << "输入删除值：" << endl;
	cin >> j;
	if(deleteBST(root, j))
	{
		cout << "删除成功" << endl;
	}


    return 0;
}

