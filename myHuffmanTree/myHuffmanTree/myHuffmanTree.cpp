// myHuffmanTree.cpp: 定义控制台应用程序的入口点。
//

// 由于赫夫曼树中没有度为1的节点
//则一棵具有n个叶子节点的的赫夫曼树共有2n-1个节点（最后一条特性），
//因此可以将这些节点存储在大小为2n-1的一维数组中。
//用数组的0至第n-1个元素表示需要进行赫夫曼编码的代权值的节点
//用数组的第n至第2n-2个元素存储构造过程中产生的中间节点

#include "stdafx.h"
#include"string.h"
#include<iostream>
#pragma warning(disable:4996)
using namespace std;


/*
 * 哈夫曼树节点
 */
struct HuffNode
{
	int weight; //每个节点的权值
	int parent;//父亲节点下标
	int lchild;//左孩子下标
	int rchild;//右孩子下标
};


/*
 * 从ht数组的前k个元素中选出weight最小且parent为-1的元素，并将该元素的下标返回
 */
int getmin(HuffNode *ht,int k)
{
	int i = 0;
	int min; //记录weight最小且parent为-1的节点的下标
	int min_weight;//记录weight最小且parent为-1的节点的权值

	//先将第一个parent为-1的节点的weight值赋给min_weight，用于比较找出weight最小的节点
	//注意，这里不能直接将ht[0]的weight赋给min_weight
	//因为如过ht[0]的值比较小，可能在第一次构造哈夫曼树时就会被选走
	//而在后续的建树过程中，当该函数再次被调用时，仍使用ht[0].weight作比较
	//这样将再次将ht[0]选走，造成逻辑上的错误
	while(ht[i].parent!=-1)
	{
		i++;  //找到第一个parent=-1的节点
	}

	min = i;
	min_weight = ht[i].weight;

	//选出weight最小且parent=-1的节点，并将其下标赋给min
	for(;i<k;i++)
	{
		if(min_weight>ht[i].weight&&ht[i].parent==-1)
		{
			min_weight = ht[i].weight;
			min = i;
		}
	}
	//选出后，将权值最小的parent设置为1，使得下次比较时可将其排除在外。
	ht[min].parent = 1; 
	return min;
}



/*
 * 选出权值最小的两个节点，并赋值给min1和min2
 */
void select(HuffNode *ht, int k, int &min1, int &min2)
{
	min1 = getmin(ht, k);
	min2 = getmin(ht, k);
	
}


/*
 * 创建赫夫曼树
 * int *weights为用来存储权值的数组
 */
void createHuffmanTree(HuffNode * &huffTree, int n, int *weights)
{
	int total = 2 * n - 1;//计算总节点个数
	huffTree = new HuffNode[total];//为赫夫曼树开辟空间

	int i;//计数器

	//初始化赫夫曼树，用第0至第n-1存放叶子节点
	for ( i = 0; i<total; i++)
	{
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
		huffTree[i].weight = *weights;
		weights++;
	}

	int min1, min2;

	//用第n至第2n-2个元素存放建树过程中产生的中间节点
	for (i = n; i<total; i++)
	{
		select(huffTree, i, min1, min2);//选出weight最小的两个节点

		//创建由这两个节点产生的中间节点
		huffTree[i].weight = huffTree[min1].weight + huffTree[min2].weight;//设置这个中间节点的权值
		huffTree[i].lchild = min1;//设置中间节点的左孩子
		huffTree[i].rchild = min2;//设置中间节点的右孩子
		huffTree[min1].parent = i;//将左孩子的parent指向创建的中间节点
		huffTree[min2].parent = i;//将右孩子的parent指向创建的中间节点
	}
}


/*
 * 从叶子节点开始，得到每个权值所对应的赫夫曼编码
 * HuffNode *huffTree为构建好的赫夫曼树
 * char **&hc为用于存储赫夫曼编码的数组
 * int n为待求赫夫曼编码的权值的个数
 */
void getHuffmanCode(HuffNode *huffTree,char **&hc,int n)
{
	hc=new char*[n];//为用于存储赫夫曼编码的二维数组分配空间

    //临时存储，用于存储得到的赫夫曼编码
	//对于有n个叶子节点的赫夫曼树，各个叶子节点的编码长度不超过n-1
	//再加上一个'\0'，因此分配数组最长为n
	char *code = new char[n];
	code[n - 1] = '\0';

	//求每个叶子节点的赫夫曼编码
	int i;
	for(i=0;i<n;i++)
	{
		int current = i;  //记录当前访问的节点
		int parent = huffTree[i].parent; //记录当前节点的双亲节点
		int start = n - 1;  //每次编码的起始位置，从叶子节点逆向生成赫夫曼编码，因此起始位置为结束符位置

		//从叶子节点遍历赫夫曼树到根节点
		while(parent!=-1)
		{
			if(huffTree[parent].lchild==current) //如果当前访问节点为左孩子
			{
				code[--start] = '0';//则赫夫曼编码为0
			}else
			{
				code[--start] = '1';//否则为右孩子，编码为1
			}
			current = parent;//将当前节点设置为双亲节点
			parent = huffTree[parent].parent;//修改双亲节点为更上层的双亲节点
		}
		hc[i] = new char[n - start];  //为第i个字符的编码串分配空间
		strcpy(hc[i], code + start); //将编码串从code复制到hc
	}
	free(code);  //释放空间
}

int main()
{
	HuffNode *huffTree;
	int n;
	cout << "请输入需要编码的字符个数(>1)：" << endl;
	cin >> n;
	int *weights = new int[n];
	cout << "请依次输入这" << n << "个字符的权值：" << endl;
	for(int i=0;i<n;i++)
	{
		cin >> weights[i];
	}
	cout << "开始创建哈夫曼树" << endl;
	createHuffmanTree(huffTree, n, weights);
	cout << "创建完毕" << endl;
	cout << "开始依次计算相应的哈夫曼编码：" << endl;
	char **huffcodes;
	getHuffmanCode(huffTree, huffcodes, n);
	cout << "依次输出相应哈夫曼编码：" << endl;
	for(int i=0;i<n;i++)
	{
		int j = 0;
		while (huffcodes[i][j] != '\0')
		{
			cout << huffcodes[i][j]<<" ";
			j++;
		}
		cout << endl;
	}
    return 0;
}

