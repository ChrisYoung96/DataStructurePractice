// Kruscal.cpp: 定义控制台应用程序的入口点。
//
/*
 *kruskal算法基本思想：
 * 在初始状态时隐去图中的所有边，这样图中每个顶点都自成一个连通块。
 * 之后执行下面的步骤：
（1）对所有的边按边权从小到大进行排序；
（2）按边权从小到大测试所有边，如果当前测试边所连接的两个顶点不在同一个连通块中，
则把这条测试边加入当前最小生成树中；否则，将边舍弃；
（3）执行步骤（2），知道最小生成树中的边数等于总顶点数减1或者测试完所有的边时结束。
当结束时，如果最小生成树的边数小于总顶点数减1，则说明该图不连通。

*如何判断边的两个顶点在不在同一个连通块内？
*最方便的办法是使用并查集
*kruskal算法在初始状态，将每个顶点都视为一个连通块，
*我们可以把每个连通块看成一个集合，该集合包含了连通分量中的所有点。
*这些点两两连通，连通方式无关紧要。
*在图中，每个点属于一个连通分量，对应到集合表示中，每个元素属于一个集合。
*并查集的精妙之处在于用树来表示集合。
*规定每棵树的根节点是这棵树所对应集合的代表元
*如果把x的父结点保存在数组father[x]中，则如果x没有父结点，father[x]=x，既x本身就是根；
*若x有根节点为y,则father[x]=y
*因此，查找x所在树的根节点的函数思想为：
*如果father[x]=x，则返回x
*如果father[x]!=x，则返回x的父亲节点father[x]所在树的根节点
*递归程序可为：int find(int x){x==father[x]?x:find(father[x])}
 */

#include "stdafx.h"
#include<iostream>
#include<algorithm>
using namespace std;


/*
 * 代表边的结构体
 */
struct edge
{
	int start; //边的起点
	int end; //边的终点
	int weight;//边的权值
	edge(int x,int y,int z):start(x),end(y),weight(z){}
};


/*
 * 比较函数，使边按从小到大排列
 */
bool cmp(edge a,edge b)
{
	return a.weight < b.weight;
}

/*并查集查询函数，返回x所在集合的根结点
 * 如果并查集生成的树是一条长链，则若x为链尾,则查找x的根节点，则每次执行findFather（）都会遍历整条链
 * 效率低下。由于并查集中，每棵树表示的只是一个集合，因此树的形态无关紧要
 * 并不需要在查找操作之后保持树的形态
 * 所以，解决方案为，如果x的根节点不是自己，则让x的根节点father[x]等于x的根节点的根节点
 * 既路径压缩
 */
int findFather(int *father,int x)
{
	
	return x==father[x]?x:father[x]=findFather(father,father[x]);
}

/*
 * kruskal算法
 */
int kruskal(int n,int m,edge   e[])
{
	int *father = new int[n];  //并查集数组，记录每个顶点的根节点
	int ans = 0;//所求边权的和
	int num_edge = 0; //记录最下生成树边的数量

	for(int i=0;i<n;i++)//初始化并查集
	{
		father[i] = i;
	}
	sort(e, e + m,cmp); //所有边按边权从小到大排序

	for(int i=0;i<m;i++)//枚举所有边
	{
		int fa_start = findFather(father, e[i].start);  //查询当前边的起点start所在的集合的根节点
		int fa_end = findFather(father, e[i].end);  //查询当前边的终点end  所在的集合的根节点
		if(fa_start!=fa_end)  //如果边的两个端点不在一个集合中
		{
			father[fa_start] = fa_end; //合并集合（相当于把测试边加入到最小生成树）
			ans += e[i].weight;
			num_edge++;  //当前生成树边数加1
			if(num_edge==n-1) //当边数等于定点数-1，算法结束
			{
				break;
			}
		}
	}

	if(num_edge!=-1)
	{
		return -1;
	}
	return ans; //返回最小生成树边权之和
}

int main()
{
	edge E[10] = { edge(0,1,6),edge(0,2,1),edge(0,3,5),edge(1,2,5),edge(2,3,5),
		edge(1,4,3),edge(2,4,6),edge(2,5,4),edge(3,5,2),edge(4,5,6) };
	int n = 6;
	int m = 10;
	int res = kruskal(n, m,E);
	cout << res << endl;
    return 0;
}

