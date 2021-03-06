// myGraph.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include<iostream>
#include<queue>
#include <stack>
using namespace std;

#define INFINITY 1000
#define MAX_VERTEX_NUM 20
bool visit[MAX_VERTEX_NUM];//辅助数字，用于遍历时标记顶点是否被访问过
bool solved[MAX_VERTEX_NUM];//用来记录迪杰斯特拉算法中，从源点到各定点是否以求最小路径



struct MGraph
{
	int  vex[MAX_VERTEX_NUM];  //存放顶点的数组，可以为整型、字符型、结构体型或其他类型 
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//记录边及边权的二位数组。若无权值，则用1表示连通，0表示不通。若有权值，则为权值。
	int vexnum, arcnum;//顶点数量，边的数量
};



/*
 *构造无向图
 */
void createUDGraph(MGraph &g)
{
	cout << "输入无向图顶点个数和边的个数：" << endl;
	cin >> g.vexnum >> g.arcnum;
	cout << "输入顶点：" << endl;
	for (int i = 0; i < g.vexnum; i++)
	{
		cin >> g.vex[i];
	}
	for(int i=0;i<g.vexnum;i++)
	{
		for(int j=0;j<g.vexnum;j++)
		{
			g.arcs[i][j] = INFINITY;
		}
	}
	cout << "输入顶点vi,vj之间边(vi,vj)的权值w:" << endl;
	int vi,vj,w;
	for(int k=0;k<g.arcnum;k++)
	{
		cin >> vi >> vj >> w;
		g.arcs[vi][vj] = w;
		g.arcs[vj][vi] = w;//因为是无向图，所以arcs[i][j]与arcs[j][i]相同
	}
}


/*
 *递归方式进行深度优先，类似树的先序遍历，其思想为
 *假设初始状态是图中所有顶点均未被访问，
 *则从某个顶点v出发，首先访问该顶点，
 *然后依次从它的各个未被访问的邻接点出发深度优先搜索遍历图，
 *直至图中所有和v有路径相通的顶点都被访问到。 若此时尚有其他顶点未被访问到，
 *则另选一个未被访问的顶点作起始点，重复上述过程，直至图中所有顶点都被访问到为止。
 */
void DFS(MGraph g,int i)
{
	int j;
	visit[i] = true;
	cout << g.vex[i] << " ";
	for(j=0;j<g.vexnum;j++)
	{
		if(i!=j)
		{
			if (g.arcs[i][j] != INFINITY && !visit[j])
			{
				DFS(g, j);
			}
		}
		
	}
}

void DFSTraverse(MGraph g)
{
	int i;
	//初始化visit[]使所有顶点都没有被访问
	for(i=0;i<g.vexnum;i++)
	{
		visit[i] = false;
	}
	for(i=0;i<g.vexnum;i++)
	{
		if(!visit[i])
		{
			DFS(g, i);
		}
	}
}

/*
 * 广度优先遍历
 * 广度优先遍历类似树的层序遍历，可借助队列,将某顶点的临界点做入队操作，
 * 访问过的节点出队，并对刚被访问过的节点的临节点再做入队操作。
 * 其思想为：
 * 从图中某顶点v出发，在访问了v之后依次访问v的各个未曾访问过的邻接点，
 * 然后分别从这些邻接点出发依次访问它们的邻接点，
 * 并使得“先被访问的顶点的邻接点先于后被访问的顶点的邻接点被访问，
 * 直至图中所有已被访问的顶点的邻接点都被访问到。
 * 如果此时图中尚有顶点未被访问，则需要另选一个未曾被访问过的顶点作为新的起始点，
 * 重复上述过程，直至图中所有顶点都被访问到为止。
 */
void BFSTraverse(MGraph g)
{
	int i;
	queue<int> q;
	//初始化visit[]，假设所有顶点都没有访问过
	for (i = 0; i<g.vexnum; i++)
	{
		visit[i] = false;
	}
	for(i=0;i<g.vexnum;i++)//从编号为0的顶点开始遍历
	{
		q.push(i);
		while(!q.empty())
		{
			int temp = q.front();//获取队头元素
			if(!visit[temp])//如果队头节点没有被访问
			{
				visit[temp] = true;//修改状态为访问
				cout << g.vex[temp]<<" ";//输出信息
			}
			q.pop();//队头元素出队列
			for(int j=0;j<g.vexnum;j++)//访问队头元素的临接点，并做入队操作7
			{
				if(g.arcs[temp][j]!=INFINITY&&!visit[j])
				{
					q.push(j);
				}
			}
		}
	}
}


void showGraph(MGraph g)
{
	for(int i=0;i<g.vexnum;i++)
	{
		for(int j=0;j<g.vexnum;j++)
		{
			cout << g.arcs[i][j] << " ";
		}
		cout << endl;
	}
}

/*
 * prim算法求最小生成树
 * 对图G（V,E）设置集合S，存放已经被访问的顶点，
 * 然后每次从集合V-S中选择与集合S的最短距离最小的一个顶点（记为u），
 * 访问并加入集合S。
 * 之后，令顶点u为中介点，
 * 优化所有从u能到达的顶点v与集合S之间的最短距离。
 * 这样的操作执行n次（n为顶点个数），
 * 直到集合S已包含所有顶点。
 */
int prim(MGraph g,int s)
{
	int d[MAX_VERTEX_NUM]; //存储图中各个节点距离集合S的最短路径

	//初始化记录节点 被访问状态的数组visit[],d[]
	for (int i = 0; i<g.vexnum; i++)
	{
		visit[i] = false;
		d[i] = INFINITY;
	}

	d[s] = 0; //起始点与集合S（S为空）的距离为0
	int sum = 0;   //边权和

	//遍历各点
	for(int i=0;i<g.vexnum;i++)
	{
		int u = -1;//记录集合V-S中，到集合S的距离最短的点的下标
		int min = INFINITY;  //记录u到集合S的最短距离

		//从未被访问过的节点（V-S集合）中选出距离S路径最短的点u
		for(int j=0;j<g.vexnum;j++)
		{
			if(visit[j]==false&&d[j]<min)
			{
				min = d[j];
				u = j;
			}
		}

		//剩下的点与集合S不通
		if(u==-1)
		{
			return -1;
		}
		cout << g.vex[u] << " ";
		visit[u] = true;  //将该点设为被访问（加入集合S）
		sum += d[u]; 

		//v未访问 && u能够到达v && 以u为中介点可以使v离集合S更近 
		for(int v=0;v<g.vexnum;v++)
		{
			//v未访问 && u能够到达v && 以u为中介点可以使v离集合S更近 
			if(visit[v]==false&&g.arcs[u][v]!=INFINITY&&g.arcs[u][v]<d[v])
			{
				d[v] = g.arcs[u][v];
			}
		}
	}
	cout << endl;
	return sum;
}

/*
 * 迪杰斯特拉算法，求单点到其余每个点的最短路径(单源最短路径）
 * 算法步骤：
 * a.初始时，S只包含源点，即S＝{v}，v的距离为0。U包含除v外的其他顶点，即:U={其余顶点}，
 * 若v与U中顶点u有边，则<u,v>正常有权值，若u不是v的出边邻接点，则<u,v>权值为∞。
 * b.从U中选取一个距离v最小的顶点k，把k，加入S中（该选定的距离就是v到k的最短路径长度）。
 * c.以k为新考虑的中间点，修改U中各顶点的距离；若从源点v到顶点u的距离（经过顶点k）比原来距离（不经过顶点k）短，则修改顶点u的距离值，修改后的距离值的顶点k的距离加上边上的权。
 * d.重复步骤b和c直到所有顶点都包含在S中。
 * 
 * 这里用solved[]数组来记录源点到各顶点的最短路径是否以求得，以求得的顶点设为true，既加入集合S；未求得的顶点设为false，既集合U;
 */
void Dijkstra(MGraph g,int start)
{
	int dis[MAX_VERTEX_NUM];//储存源点到其他点的最小距离
	int prevetx[MAX_VERTEX_NUM];//用来记录从源点到各顶点的路径上，各顶点的前驱节点

	//初始化集合S，U。
	for(int i=0;i<g.vexnum;i++)
	{
		solved[i] = false;
		dis[i] = g.arcs[start][i]; //若v与U中顶点u有边，则<u, v>正常有权值，若u不是v的出边邻接点，则<u, v>权值为∞(在创建图的过程中，互不联通的顶点距离为无穷)
		prevetx[i] =0;
	}
	dis[start] = 0;
	solved[start] = true;
	prevetx[start] = start;

	//
	for(int i=0;i<g.vexnum;i++)
	{
		int min = INFINITY;
		int u = 0;
		//查询当前源点到集合U中各顶点的距离中最小的一个
		for(int j=0;j<g.vexnum;j++)
		{
			if(solved[j]==false&&dis[j]<min)//如果从源点到顶点j的最短路径未找到，且从源点到j的距离比当前最小值小
			{
				min = dis[j];//记录这个最小值
				u = j;//记录这个点
			}
		}
		solved[u] = true;//将这个顶点加入到集合S中

		//判断以当前这个顶点u为中间顶点，源点经u到集合U中各顶点的距离如果小于当前源点到集合U中各顶点的距离
		//则更新这个距离
		for(int v=0;v<g.vexnum;v++)
		{
			if(solved[v]==false&&g.arcs[u][v]!=INFINITY)
			{
				if(dis[u]+g.arcs[u][v]<dis[v])
				{
					dis[v] = dis[u] + g.arcs[u][v];
					prevetx[v] = u;
				}
			}
		}
	}

	stack<int>path;
	for(int i=0;i<g.vexnum;i++)
	{
		int vstart = prevetx[i];
		if(vstart!=start)
		{
			while(vstart!=start)
			{
				path.push(vstart);
				vstart = prevetx[vstart];
			}
			
		}
		cout << "v" << start;
		while(!path.empty())
		{
			cout << "→v" << path.top();
			path.pop();
		}
		cout<< "→v"<< i << " " <<"The shortest distance is "<< dis[i] << endl;
		
	}

}


/*
 * Floyd算法求解图中任意两点间的最短距离
 * 
 */

void Floyd(MGraph g)
{
	int i, j, k;

	int d[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//记录两点间的最短路径

	int p[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//记录求得两点间最短路径用到的中间结点

	for(i=0;i<g.vexnum;i++)//初始化d.p
	{
		for(j=0;j<g.vexnum;j++)
		{
			d[i][j] = g.arcs[i][j];//d初始就是记录边的数组
			p[i][j] = j;//p初始为不经任何中间结点，直接从i到j
		}
	}

	//Floyd核心代码
	for(i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
		{
			for(k=0;k<g.vexnum;k++)
			{
				if(d[j][k]>d[j][i]+d[i][k])//以i为中间结点，如果从点j经中间结点i到点k的距离<j到k的当前距离
				{
					d[j][k] = d[j][i] + d[i][k]; //修改j到k的距离
					p[j][k] = i;//记录j到k的中间结点i
				}
			}
		}
	}


	//输出结果
	for(i=0;i<g.vexnum;i++)
	{
		for(j=i+1;j<g.vexnum;j++)
		{
			cout << "v" << i << "--" << "v" << j << " weight: " << d[i][j]
				<< " Path: " << i << ' ';
			k = p[i][j];
			while(k!=j)
			{
				cout << "→" << k << " ";
				k = p[k][j];
			}
			cout << "→" << j << endl;
		}
		cout << endl;
	}


}


int main()
{
	MGraph graph;
	createUDGraph(graph);
	showGraph(graph);
	cout << "深度优先遍历结果为：" << endl;
	DFSTraverse(graph);
	cout << endl;
	cout << "广度优先遍历结果为：" << endl;
	BFSTraverse(graph);
	cout << endl;
	cout << "prim求得最小生成树的带权和为：" << endl;
	cout << prim(graph, 0);
	cout << endl;
	cout << "Dijkstra求得的最短路径为：" << endl;
	Dijkstra(graph, 0);
	cout << "Floyd求得两点之间的最短路径为：" << endl;
	Floyd(graph);
    return 0;
}

