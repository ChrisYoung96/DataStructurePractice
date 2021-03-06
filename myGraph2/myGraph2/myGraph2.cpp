// myGraph2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

#define MAX_VERTEX_NUM 20
bool visited[MAX_VERTEX_NUM];  //记录节点是否被访问的数组
int ve[MAX_VERTEX_NUM];//关键路径算法中，记录每个事件最早开始时间数组
int vl[MAX_VERTEX_NUM];//关键路径算法中，记录每个时间最晚开始时间数组

/*
 * 表示边的结构体
 */
struct ArcNode
{
	int adjvex; //与当前节点相邻的下一个临节点
	ArcNode *nextarc;//指向下一个边的指针
	int info;//边的信息
};


/*
 * 表示图中节点的结构体
 */
struct VNode
{
	int vexdata;//节点信息
	ArcNode *firstarc;//指向与节点相连的第一条边
};


/*
 * 表示图的结构体
 */
struct  ALGraph
{
	VNode adjlist[MAX_VERTEX_NUM]; //节点数组
	int vexnum;  //节点数量
	int arcnum;    //边的数量
	int *indegree;
};




/*
 * 创建无向图
 */
void createGraph(ALGraph &g)
{
	int i, j,k,w;
	ArcNode *a;
	cout << "输入顶点数和边数：" << endl;
	cin >> g.vexnum >> g.arcnum;
	g.indegree = new int[g.vexnum];
	cout << "输入顶点信息：" << endl;
	for(i=0;i<g.vexnum;i++)
	{
		cin >> g.adjlist[i].vexdata;//输入顶点信息
		g.adjlist[i].firstarc = NULL;//初始化指针
		g.indegree[i] = 0;
	}
	cout << "输入边(vi,vj)的顶点序号,及边(vi,vj)的权值：" << endl;

	//以邻接表法构建图的关键
	for(k=0;k<g.arcnum;k++)
	{	
		cin >> i >> j>>w;
		a = new ArcNode;
		a->adjvex = j;
		a->nextarc = NULL;
		a->info = w;
		//此处相当于将新的节点插入到链表的第一个位置
		a->nextarc = g.adjlist[i].firstarc;    
		g.adjlist[i].firstarc = a;	
		g.indegree[j]++; //计算节点j的入度
		//无向图构建
		/*a = new ArcNode;
		a->adjvex = i - 1;
		a->nextarc = NULL;
		a->info = w;
		a->nextarc = g.adjlist[j - 1].firstarc;
		g.adjlist[j - 1].firstarc = a;*/
	}
}



/*
 * 深度优先，递归遍历邻接表
 * 以第i个节点为起点，深度优先遍历
 */
void DFS(ALGraph g,int i)
{
	ArcNode *temp;
	visited[i] = true;
	cout << g.adjlist[i].vexdata << " ";
	temp = g.adjlist[i].firstarc;
	while(temp)
	{
		if(!visited[temp->adjvex])
		{
			DFS(g, temp->adjvex);
		}
		temp = temp->nextarc;
	}
}

void DFSTraverse(ALGraph g)
{
	for (int i = 0; i<g.vexnum; i++)
	{
		visited[i] = false;
	}
	for(int i=0;i<g.vexnum;i++)
	{
		if(!visited[i])
		{
			DFS(g, i);
			cout << endl;
		}
	}
	
}


/*
 * 广度优先遍历图，从节点k开始
 */
void BFSTraverse(ALGraph g,int k)
{
	queue <int>q;
	ArcNode *temp;
	int m;
	//假设都没有被访问
	//for(int i=0;i<g.vexnum;i++)
	//{
	//	visited[i] = false;
	//}
	q.push(k);  //将初始节点入队
	visited[k] = true;//设置初始节点被访问
	cout << k+1 << " ";//输出初始节点的信息
	while(!q.empty())
	{
		m = q.front();//取队头节点编号
		q.pop();//将队头节点出栈
		temp = g.adjlist[m].firstarc;//开始寻找与该节点相邻的节点
		while(temp)
		{
			if(!visited[temp->adjvex])//如果与该节点相邻的节点没有被访问
			{
				visited[temp->adjvex] = true;//设置为被访问
				cout << temp->adjvex+1 << " ";//输出节点信息
				q.push(temp->adjvex);//将该临接点入队
			}
			temp = temp->nextarc;//如果该节点已被访问，则查看下一个与当前节点相邻的临接点
		}
	}

}

/*
 * 拓扑排序
 * 
 * 在图论中，拓扑排序（Topological Sorting）是一个有向无环图（DAG, Directed Acyclic Graph）的所有顶点的线性序列。
 * 且该序列必须满足下面两个条件：
 * 1. 每个顶点出现且只出现一次。
 * 2.若存在一条从顶点 A 到顶点 B 的路径，那么在序列中顶点 A 出现在顶点 B 的前面。
 * 有向无环图（DAG）才有拓扑排序，非DAG图没有拓扑排序一说。
 * 
 * 如何写出它的拓扑排序呢？这里说一种比较常用的方法：
 * 1.从 DAG 图中选择一个 没有前驱（即入度为0）的顶点并输出。
 * 2.从图中删除该顶点和所有以它为起点的有向边。
 * 3.重复 1 和 2 直到当前的 DAG 图为空或当前图中不存在无前驱的顶点为止。后一种情况说明有向图中必然存在环。
 * 
 * 
 * parameter：
 * @ALGraph g 有向图
 * @stack <int> &t 关键路径算法中需要用到的逆拓扑栈
 * 
 */
bool Topologicalsort(ALGraph g,stack <int> &t)
{
	stack<int> q;//存储入度为0的栈
	for(int i=0;i<g.vexnum;i++)
	{
		ve[i] = 0;//初始化关键路径算法中需要用到的记录时间最早开始时间的数组
		if(g.indegree[i]==0)//将所有入都为0的顶点入栈
		{
			q.push(i);
		}
	}

	int count = 0;//记录当前已经输出的顶点数

	while(!q.empty())
	{
		int v = q.top();//从入度为0的顶点中选择一个
		q.pop();
		t.push(v);
		cout << v << " ";  //输出该顶点
		count++;
		
		//将所有v指向的顶点的入度减一，若减一后入度为0，则入栈
		ArcNode *temp = g.adjlist[v].firstarc;
		while(temp)
		{
			if(!(--g.indegree[temp->adjvex]))
			{
				q.push(temp->adjvex);
			}
			//关键路径算法中计算各点（事件）的最早开始时间
			if(ve[v]+temp->info>ve[temp->adjvex]){
				ve[temp->adjvex] = ve[v] + temp->info;
			}
			temp = temp->nextarc;
		}
	}

	cout << endl;
	//若输出顶点数目小于顶点数目，说明图中有环
	if(count<g.vexnum)
	{
		cout << "有环" << endl;
		return false;
	}
	return true;
}



/*
 * 关键路径算法
 * AOE网：Activity on edge network
 * 若在带权的有向图中，以顶点表示事件，以有向边表示活动，
 * 边上的权值表示活动的开销（如该活动持续的时间），
 * 则此带权的有向图称为AOE网。
 * 
 * 
 * 基本思想：
 * 要准备两个数组，a：AOE网顶点最早开始时间数组ve，b：AOE网顶点最迟开始时间数组vl。（针对顶点即事件而言）
*1.从源点V0出发，令ve[0]（源点）=0，按拓扑有序求其余各顶点的最早发生时间ve[i]（1 ≤ i ≤ n-1）。同时按
*拓扑排序的方法检测是否有环存在。
*2.从汇点Vn出发，令vl[0...n-1] = ve[n-1]，按拓扑排序求各个其余各顶点的最迟发生时间vl[i]（n-2 ≥ i ≥ 2）;
*3.根据各顶点的ve和vl数组的值，求出弧（活动）的最早开工时间和最迟开工时间，
*求每条弧的最早开工时间和最迟开工时间是否相等，若相等，则是关键活动。
*
*计算各顶点及个边（活动）最早开工和最迟开工时间方法
*设以顶点j为头的边（活动）<i,j>权值为w,i为边的尾，从顶点v0开始计算每个顶点（事件）的最早开始时间，则:
*   ve[j]=max{ve[i]+w}
*设以顶点j为尾的边（活动）<j,k>权值为w,k为边的头，从vn开始倒序计算每个顶点（事件）的最迟开始时间，则：
*   vl[j]=min{vl[k]-w}
* 设边（活动）以<i,j>表示,权值（活动开销）为w，则活动的最早开始时间和最晚开始时间为：
*   ee=ve[i]
*   el=ve[j]-w
*


 * 
 */
void CriticalPath(ALGraph g)
{
	//从vn出发计算各点（事件）最迟开始事件的实现方式：逆拓扑排序
	stack <int> t;
	ArcNode *temp;
	int k,j,ee,el;
	if(!Topologicalsort(g,t))
	{
		cout << "无法输出关键路径" << endl;
	}
	for(int i=0;i<g.vexnum;i++)
	{
		vl[i] = ve[g.vexnum - 1];
	}

	//计算各点（事件）最迟开始时间
	while (!t.empty())
	{
		j = t.top();
		t.pop();
		temp = g.adjlist[j].firstarc;
		while(temp)
		{
			k = temp->adjvex;
			if(vl[k]-temp->info<vl[j])
			{
				vl[j] = vl[k] - temp->info;
			}
			temp = temp->nextarc;
		}
	}


	//计算个边（活动）的最早和最迟开始时间
	for(int i=0;i<g.vexnum;i++)
	{
		for(temp=g.adjlist[i].firstarc;temp;temp=temp->nextarc)
		{
			j = temp->adjvex;
			ee = ve[i];
			el = vl[j] - temp->info;
			if(ee==el)//如果最迟和最早开始时间相同，则是关键路径
			{
				cout << "<v" << i << ", v" << j << ">" << " " << temp->info << endl;
			}
			
		}
		
	}
	
}

int main()
{
	ALGraph graph;
	createGraph(graph);
	cout << "深度遍历：" << endl;
	DFSTraverse(graph);
	cout << endl;
	cout << "广度遍历：" << endl;
	for (int i = 0; i<graph.vexnum; i++)
	{
		visited[i] = false;
	}
	for(int i=0;i<graph.vexnum;i++)
	{
		if(!visited[i])
		{
			BFSTraverse(graph, i);
			cout << endl;
		}
	}
	cout << endl;

	cout << "该图的拓扑排序为：" << endl;
	//Topologicalsort(graph);
	CriticalPath(graph);
    return 0;
}

