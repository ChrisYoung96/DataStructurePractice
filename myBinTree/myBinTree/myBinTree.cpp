// myBinTree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

/*
 * 二叉树节点
 */
struct BiNode
{
	int data ;      //数据
	BiNode *lchild, *rchild;     //左孩子和右孩子
};




/*
 * 先序递归创建二叉树
 *
 */
void createTree(BiNode * &t)
{
	int n;
	cin >> n;
	if(n==0)
	{
		t = NULL;
	}else
	{
		t = new BiNode; //产生新的子树
		t->data = n; //写入数据
		createTree(t->lchild);//创建左子树
		createTree(t->rchild);//创建右子树
	}
}



/*
 * 先序（根，左，右）递归遍历二叉树
 */
void preOrderTraverse(BiNode * &t)
{
	if(t)
	{
	
		cout << t->data<<" ";
		preOrderTraverse(t->lchild);
		preOrderTraverse(t->rchild);
	}else{
		cout << 0;
	}
	
}


/*
 * 前序非递归遍历二叉树
 */
void PreOrderTraverse(BiNode *r)
{
	stack<BiNode *>s;
	BiNode *temp = r;
	while (!s.empty() || temp)
	{
		if (temp)  //根据前序遍历“根、左、右”的遍历顺序，先遍历根节点及左孩子，最后遍历右孩子，先输出根节点和左孩子的数据，并将根节点入栈保存，一遍找到右节点
		{
			cout << temp->data << " ";//输出该节点的数据
			s.push(temp); //只要该节点不为空，则入栈保存
			temp = temp->lchild;  //寻找下一个左孩子
		}
		else   //当当前节点为空时，说明已到最下层，此时开始出栈
		{
			temp = s.top();  //获得栈顶节点
			s.pop();//出栈
			temp = temp->rchild;//找右孩子
		}
	}
	cout << endl;
}






/*
 *中序（左，根，右）递归遍历二叉树
 */
void inorderTraverse(BiNode * &t)
{
	if(t)
	{
		inorderTraverse(t->lchild);
		cout << t->data << " ";
		inorderTraverse(t->rchild);
	}else
	{
		cout << 0;
	}
}



/*
 * 中序非递归遍历二叉树
 * 
 */

void inOrderTraverse(BiNode * root)
{
	stack<BiNode *>s;
	BiNode *temp = root;
	while(!s.empty()||temp)
	{
		if(temp)  //根据中序遍历“左、根、右”的遍历顺序，不断遍历到左子树最下面的左孩子并将遍历过得节点保存到栈中
		{
			s.push(temp); //只要该节点不为空，则入栈保存
			temp = temp->lchild;  //寻找下一个左孩子
		}else   //当当前节点为空时，说明已到最下层，此时开始出栈
		{
			temp = s.top();  //获得栈顶节点
			s.pop();//出栈
			cout << temp->data << " ";//输出该节点的数据
			temp = temp->rchild;//找右孩子
		}
	}
	cout << endl;
	
}



/*
 * 后序（左，右，根）递归后序遍历
 */
void posOrderTraverse(BiNode * &t)
{
	if(t)
	{
		posOrderTraverse(t->lchild);
		posOrderTraverse(t->rchild);
		cout << t->data << " ";
	}else
	{
		cout <<0;
	}
}




/*
 * 层序（自上而下，从左到右）遍历二叉树
 */
void levelTraverse(BiNode * &t)
{
	queue<BiNode *> myqueue;
	if(t)
	{
		myqueue.push(t);
		while(!myqueue.empty())
		{
			BiNode *temp = myqueue.front();
			cout << temp->data<<" ";
			myqueue.pop();
			if(temp->lchild)
			{
				myqueue.push(temp->lchild);
			}
			if(temp->rchild)
			{
				myqueue.push(temp->rchild);
			}
			cout << endl;
		}
	}
}

/*
 * 求二叉树结点个数
 */
 int getNodeNum(BiNode *t)
{
	if(t==NULL)
	{
		return 0;
	}
	return getNodeNum(t->lchild) + getNodeNum(t->rchild) + 1;
}

/*
 *求二叉树深度
 */
int getDepth(BiNode *r)
{
	if(r==NULL)
	{
		return 0;
	}
	int depthleft = getDepth(r->lchild);
	int depthright = getDepth(r->rchild);
	return depthleft > depthright ? (depthleft + 1) : (depthright + 1);
}

int main()
{
	cout << "创建一棵树，0代表空树" << endl;
	BiNode *root;  //二叉树根节点
	createTree(root);
	cout << "先序遍历：" << endl;
	preOrderTraverse(root);
	cout << "先序非递归遍历：" << endl;
	PreOrderTraverse(root);
	cout << "中序遍历：" << endl;
	inorderTraverse(root);
	cout << "中序非递归遍历：" << endl;
	inOrderTraverse(root);
	cout << "后序遍历：" << endl;
	posOrderTraverse(root);
	cout << "层序遍历" << endl;
	levelTraverse(root);
	cout << "二叉树节点个数为：" << endl;
	cout << getNodeNum(root)<<endl;
	cout << "二叉树深度为：" << endl;
	cout << getDepth(root)<<endl;
    return 0;
}

