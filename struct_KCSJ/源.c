#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_VERTEX_NUM 10	//顶点个数
#define NAME_LEN 20			//名称长度
#define NUM_LEN 5			//代号长度
#define INTRO_LEN 50		//介绍长度
#define INF 32768
typedef struct
{
	char name[NAME_LEN];//景点名称
	char num[NUM_LEN];				//景点代号
	char intro[INTRO_LEN];//经典介绍
}VertexData;//顶点数据
typedef int AdjType;
typedef struct ArcNode
{
	AdjType distance;		//权值为路线长度
}ArcNode;
typedef struct
{
	VertexData vertex[MAX_VERTEX_NUM];		//顶点向量
	ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//邻接矩阵
	int vexnum, arcnum;						//图的顶点数和弧数
}AdjMatrix;

typedef struct ArcData
{
	int start; // 边的起点
	int end;   // 边的终点
	int distance; // 边的权值
}ArcData;

/*景点初始化*/
//num:景点代号，name:景点名称，intro:景点介绍
void creatVertex(VertexData* v, char num[], char name[NAME_LEN], char intro[INTRO_LEN])
{
	strcpy(v->num, num);
	strcpy(v->name, name);
	strcpy(v->intro, intro);
}
void initVertex(VertexData v[])
{
	//调用creatVertex()函数初始化景点信息
	creatVertex(&v[0], "001", "大门", "学生教职工进出通道");
	creatVertex(&v[1], "002", "图书馆", "*****************");
	creatVertex(&v[2], "***", "计算机学院楼", "*****************");
	creatVertex(&v[3], "***", "教学楼", "*****************");
	creatVertex(&v[4], "***", "人文楼", "*****************");
	creatVertex(&v[5], "***", "新食堂", "*****************");
	creatVertex(&v[6], "***", "宿舍楼", "*****************");
	creatVertex(&v[7], "***", "澡堂", "*****************");
	creatVertex(&v[8], "***", "田径运动场", "*****************");
	creatVertex(&v[9], "***", "校医院", "*****************");
}



//创建邻接矩阵
void create_example_graph(AdjMatrix* G)
{
	int matrix[][10] = {
		/*0*//*1*//*2*//*3*//*4*//*5*//*6*//*7*//*8*//*9*/
		/*0*/ { 0, 400,  INF, 270, 210,INF, INF, INF, INF, INF },
		/*1*/ { 400, 0,  INF, 300, 250,270, 400, INF, 460, INF },
		/*2*/ { INF, INF,  0, 150, INF,INF, INF, INF, 580, INF },
		/*3*/ { 270, 300,  150, 0, INF,INF, INF, INF, INF, INF },
		/*4*/ { 210, 250,  INF, INF, 0,INF, INF, 850, INF, INF },
		/*5*/ { INF, 270,  INF, INF, INF,0, 200, INF, INF, INF },
		/*6*/ { INF, 400,  INF, INF, INF,200, 0, 180, 300, 380 },
		/*7*/ { INF, INF,  INF, INF, 850,INF, 180, 0, INF, INF },
		/*8*/ { INF, 460,  580, INF, INF,INF, 300, INF, 0, 380 },
		/*9*/ { INF, INF,  INF, INF, INF,INF, 380, INF, 380, 0 } };
	int i, j;
	
	// 初始化"顶点数"
	G->vexnum = MAX_VERTEX_NUM;
	G->arcnum = 15;
	// 初始化"顶点"
	initVertex(G->vertex);

	//初始化边
	for (i = 0; i < G->vexnum; i++)
	{
		for ( j = 0; j < G->vexnum; j++)
		{
			G->arcs[i][j].distance = matrix[i][j];
		}
	}

}


//邻接矩阵输出
void print_graph(AdjMatrix* G)
{
	int i, j;

	printf("Martix Graph:\n");
	printf("   ");
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf(" (%d) ", i);
		if (i == MAX_VERTEX_NUM - 1)
		{
			printf("\n");
		}
	}

	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			if (j == 0)
			{
				printf("(%d)", i);
			}
			if (G->arcs[i][j].distance == INF) {
				printf("%4c ", '-');
			}
			else { printf("%4d ", G->arcs[i][j].distance); }

		}

		printf("\n");
	}
}
//输出景点信息
void print_vertexData(AdjMatrix* G, int i)
{
	printf("编号:%s\n", G->vertex[i].num);
	printf("名称:%s\n", G->vertex[i].name);
	printf("简介:%s\n\n", G->vertex[i].intro);
	system("pause");
}

///*求顶点位置*/
//int LocateVertex(AdjMatrix* G, VertexData v) 
//{
//	int k;
//	for (k = 0; k < G->vexnum; k++) {
//		if (G->vertex[k].num == v.num)
//			break;
//	}
//	return k;
//}
//
//// 返回顶点v的第一个邻接顶点的索引，失败则返回-1
//int first_vertex(AdjMatrix* G, int v)
//{
//	int i;
//
//	if (v<0 || v>(G->vexnum - 1))
//		return -1;
//
//	for (i = 0; i < G->vexnum; i++)
//		if ( G->arcs[v][i].distance != INF)
//			return i;
//
//	return -1;
//}
////返回顶点v相对于w的下一个邻接顶点的索引，失败则返回-1
//int next_vertix(AdjMatrix* G, int v, int w)
//{
//	int i;
//
//	if (v<0 || v>(G->vexnum - 1) || w<0 || w>(G->vexnum - 1))
//		return -1;
//
//	for (i = w + 1; i < G->vexnum; i++)
//		if (G->arcs[v][i].distance != INF)
//			return i;
//
//	return -1;
//}
////获取图中的边
//ArcData* get_edges(AdjMatrix* G)
//{
//	int i, j;
//	int index = 0;
//	ArcData* edges;
//
//	edges = (ArcData*)malloc(G->arcnum * sizeof(ArcData));
//	for (i = 0; i < G->vexnum; i++)
//	{
//		for (j = i + 1; j < G->vexnum; j++)
//		{
//			if (G->arcs[i][j].distance != INF)
//			{
//				edges[index].start = G->vertex[i].num;
//				edges[index].end = G->vertex[j].num;
//				edges[index].distance = G->arcs[i][j].distance;
//				index++;
//			}
//		}
//	}
//	return edges;
//}
////对边按照权值排序
//void sorted_edges(ArcData* edges, int elen)
//{
//	int i, j;
//
//	for (i = 0; i < elen; i++)
//	{
//		for (j = i + 1; j < elen; j++)
//		{
//			if (edges[i].distance > edges[j].distance)
//			{
//				// 交换"第i条边"和"第j条边"
//				ArcData tmp = edges[i];
//				edges[i] = edges[j];
//				edges[j] = tmp;
//			}
//		}
//	}
//}
//
//// 获取i的终点
//int get_end(int vends[], int i)
//{
//	while (vends[i] != 0)
//		i = vends[i];
//	return i;
//}



/*
 * floyd最短路径。
 *
 * 参数说明：
 *        G -- 图
 *     path -- 路径。path[i][j]=k表示，"顶点i"到"顶点j"的最短路径会经过顶点k。
 *     dist -- 长度数组。即，dist[i][j]=n表示，"顶点i"到"顶点j"的最短路径的长度是n。
 */
void floyd(AdjMatrix* G, int path[][MAX_VERTEX_NUM], int dist[][MAX_VERTEX_NUM])
{
	int i, j, k, v, w;

	// 初始化
	for (i = 0; i < G->vexnum; i++)
	{
		for (j = 0; j < G->vexnum; j++)
		{
			dist[i][j] = G->arcs[i][j].distance;    // "顶点i"到"顶点j"的路径长度为"i到j的权值"。
			path[i][j] = j;                 // "顶点i"到"顶点j"的最短路径是经过顶点j。
		}
	}



	for (k = 0; k < G->vexnum; k++)
	{
		for (v = 0; v < G->vexnum; v++)
		{
			for (w = 0; w < G->vexnum; w++)
			{
				if (dist[v][w] > (dist[v][k] + dist[k][w]))
				{//如果经过下标为k顶点路径比原两点间路径更短，将当前两点间权值设为更小的一个 
					dist[v][w] = dist[v][k] + dist[k][w];
					path[v][w] = path[v][k];
				}

			}
		}
	}

}

void showDist(int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	int i, j;
	printf("通过floyd得到的Dist数组如下:\n");
	printf("  dist[i][j]表示顶点i到顶点j的路径长度为dist[i][j]\n");
	printf("    ");
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf(" (%d) ", i);
		if (i == MAX_VERTEX_NUM - 1)
		{
			printf("\n");
		}
	}
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			if (j == 0)
				printf("(%d)", i);
			printf("%5d", dist[i][j]);
		}
		printf("\n");
	}
}


void showPath(int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{
	int i, j;
	printf("通过floyd得到的Path数组如下:\n");
	printf("  path[i][j]表示顶点i到顶点j的最短路径是经过顶点path[i][j]。\n");
	printf("    ");
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		printf("(%d)", i);
		if (i == MAX_VERTEX_NUM - 1)
		{
			printf("\n");
		}
	}
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			if (j == 0)
				printf("(%d)", i);
			printf("%3d", path[i][j]);
		}

		printf("\n");
	}
}


//最短路线输出
void printMinLoad(AdjMatrix* G, int  dist[10][10], int  path[10][10], int start, int end)
{
	int k, i = start, j = end;
	printf("查询成功！\n");
	printf("%s-->%s 的最短路程为:%d米", G->vertex[i].name, G->vertex[j].name, dist[i][j]);
	k = path[i][j];
	printf("\n路径为:%s", G->vertex[i].name);
	while (k != j)
	{
		printf("->%s", G->vertex[k].name);
		k = path[k][j];
	}
	printf("->%s\n", G->vertex[j].name);
}


void WelcomeMenu()
{
	printf("\n\n\n");
	printf("\t\t\t  ******************************************************\n");
	printf("\t\t\t  *           欢迎使用西安工程大学校园导航系统         *\n");
	printf("\t\t\t  ******************************************************\n");
	printf("\t\t\t  *****************作者：吴金俊，卢博斌*****************\n");
	printf("\t\t\t  ******************************************************\n");
	system("pause");
	system("cls");
}

void list()
{

	printf("\n");
	printf("\t\t\t  * * * * * * * * * * * * * ** * * * * * * * * * * * * *\n");
	printf("\t\t\t  *                       地点列表                     *\n");
	printf("\t\t\t  ******************************************************\n");
	printf("\t\t\t  *      <0>北门                  <1>图书馆            *\n");
	printf("\t\t\t  *      <2>计算机科学学院        <3>教学楼群          *\n");
	printf("\t\t\t  *      <4>人文楼                <5>新食堂            *\n");
	printf("\t\t\t  *      <6>学生宿舍楼群          <7>澡堂              *\n");
	printf("\t\t\t  *      <8>田径运动场            <9>校医院           *\n");
	printf("\t\t\t  ******************************************************\n");
	printf("\n");
}


//系统界面
int sysMenu()
{
	int chose;
	system("cls");
	list();
	printf("\t\t\t  ******************************************************\n");
	printf("\t\t\t  *                         菜单                       *\n");
	printf("\t\t\t  *                1.查询地点信息                      *\n");
	printf("\t\t\t  *                2.查询最短路径                      *\n");
	printf("\t\t\t  *                3.显示邻接矩阵                      *\n");
	printf("\t\t\t  *                4.显示floyd生成的path数组           *\n");
	printf("\t\t\t  *                5.显示floyd生成的dist数组           *\n");
	printf("\t\t\t  *                6.退出                              *\n");
	printf("\t\t\t  ******************************************************\n");
	printf("请输入您所需要使用的功能的序号：");
	scanf("%d", &chose);
	return chose;
}

//"查询最短路径" 的起点与终点的输入及选择合法性判断
void Decision_Input(int a[2])
{
	
	while (1)
	{
		while (1)
		{
			printf("请输入起点序号:");
			scanf("%d", &a[0]);
			if (a[0] >= 0 && a[0] <= 9)
			{
				break;
			}
			else
			{
				system("cls");
				list();
				printf("您输入的起点超出范围,请重新输入\n");

			}
		}

		while (1)
		{
			printf("请输入终点序号:");
			scanf("%d", &a[1]);
			if (a[1] >= 0 && a[1] <= 9)
			{
				break;
			}
			else
			{
				printf("您输入的终点超出范围,请重新输入\n");

			}
		}
		if (a[0] == a[1])
		{
			system("cls");
			list();
			printf("起点与终点不能相同,请重新输入\n");

		}
		else
		{
			break;
		}
	}
	
}



void main()
{
	int chose, flag = 1;
	AdjMatrix G;
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };    // 用于保存floyd路径
	int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };    // 用于保存floyd长度
	create_example_graph(&G);//无向图的创建
	floyd(&G, path, dist);

	WelcomeMenu();
	while (flag)
	{
		chose = sysMenu();
		switch (chose)
		{
		case 1: //查询地点信息
			system("cls");
			list();
			int x;
			printf("请输入要查找的地点序号:");
			scanf("%d", &x);
			print_vertexData(&G, x);
			break;
		case 2://查询任意两地最短路径
			system("cls");
			list();
			int a[2] = {0};
			int start, end;
			Decision_Input(a);
			start = a[0];
			end = a[1];
			printMinLoad(&G, dist, path, start, end);
			system("pause");
			break;
		case 3://输出邻接矩阵
			system("cls");
			list();
			print_graph(&G);
			system("pause");
			break;
		case 4://显示floyd生成的path数组
			system("cls");
			list();
			showPath(path);
			system("pause");
			break;
		case 5://显示floyd生成的dist数组 
			system("cls");
			list();
			showDist(dist);
			system("pause");
			break;
		default:
			flag = 0;
			break;
		}
	}

}


