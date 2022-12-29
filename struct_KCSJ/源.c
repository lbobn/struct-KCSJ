#define _CRT_SECURE_NO_WARNINGS 1


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_VERTEX_NUM 10	//顶点个数
#define NAME_LEN 20			//名称长度
#define NUM_LEN 5			//代号长度
#define INTRO_LEN 50		//介绍长度
#define INF 32768

typedef struct zhanghu
{
	char admin[20];
	char password[20];
};//账户结构定义


/*定义无向图的邻接矩阵存储法*/
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

/*景点初始化*/
//num:景点代号，name:景点名称，intro:景点介绍
void creatVertex(VertexData* v, char num[], char name[NAME_LEN], char intro[INTRO_LEN]);
void initVertex(VertexData v[]);//调用creatVertex()函数初始化景点信息
void create_example_graph(AdjMatrix* G);//创建邻接矩阵
void print_graph(AdjMatrix* G);//邻接矩阵输出
void print_vertexData(AdjMatrix* G, int i);//输出景点信息
void floyd(AdjMatrix* G, int path[][MAX_VERTEX_NUM], int dist[][MAX_VERTEX_NUM]);//floyd最短路径
void showDist(int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM]);
void showPath(int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM]);
void printMinLoad(AdjMatrix* G, int  dist[10][10], int  path[10][10], int start, int end);//最短路线输出
void Decision_Input(int a[]);//"查询最短路径" 的起点与终点的输入及选择合法性判断
void zhuce();//注册
int denglu();//登录
int menu_1();//账户操作菜单
void WelcomeMenu();//欢迎菜单
void list();//地点清单
int sysMenu();//系统菜单



int main()
{
	int choose1, choose2, flag1 = 1, flag2 = 1;

	int t;
	char pic_name[80] = "school.jpg";
	char cmd[100];

	int i;
	int a[2] = { 0 };
	int x;
	int start, end;
	AdjMatrix G;
	int path[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };    // 用于保存floyd路径
	int dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = { 0 };    // 用于保存floyd长度
	create_example_graph(&G);//无向图的创建
	floyd(&G, path, dist);

	WelcomeMenu();

	while (flag1 == 1)
	{
		choose1 = menu_1();
		switch (choose1)
		{
		case 1:
			t = denglu();
			if (t == -1)
				return;
			else if (t == 1)
			{
				flag1 = 0;
				system("pause");
			}
			break;

		case 2:zhuce(); break;
		case 0:
			printf("退出\n");
			system("pause");
			exit(0);
		default:system("cls"); printf("没有这个选项！\n");
		}
	}


	while (flag2 == 1)
	{
		choose2 = sysMenu();
		switch (choose2)
		{
		case 1: //查询地点信息
			system("cls");
			list();
			printf("请输入要查找的地点序号:");
			scanf("%d", &x);
			print_vertexData(&G, x);
			break;
		case 2://查询任意两地最短路径
			system("cls");
			list();
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
		case 4://显示floyd生成的path,dist数组
			system("cls");
			list();
			showPath(path);
			showDist(dist);
			system("pause");
			break;
		case 5://显示学校简易图
			sprintf(cmd, pic_name);
			system(cmd);
			printf("地图已显示\n");
			system("pause");
			break;
		case 0://退出 
			system("cls");
			list();
			printf("退出\n");
			flag2 = 0;
			system("pause");
			break;
		default:
			printf("没有这个选项\n");
			system("pause");
			break;
		}
	}
	return 0;
}



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
	creatVertex(&v[0], "000", "大门", "学生教职工进出通道");
	creatVertex(&v[1], "001", "图书馆", "保存书籍之地，拥有保存人类文化遗产、开发信息资源、参与社会教育的职能。");
	creatVertex(&v[2], "002", "计算机学院楼", "拥有计算机系办公室，会议室等场所的计算机综合性大楼。");
	creatVertex(&v[3], "003", "教学楼", "教书育人之地。");
	creatVertex(&v[4], "004", "人文楼", "即文学、哲学、国学、历史 艺术、美学、教育、社会等学科，包括教学、科研、办公、会议、图书阅览等综合功能大楼。");
	creatVertex(&v[5], "005", "新食堂", "食堂里不单单有西安美食，还为各省学生提供国内各地特色餐饮。");
	creatVertex(&v[6], "006", "宿舍楼", "学生休息之所，上床下桌，内置空调，环境舒适。");
	creatVertex(&v[7], "007", "澡堂", "学生沐浴之所，约有五十个单间，单次沐浴平均约两块。");
	creatVertex(&v[8], "008", "田径运动场", "学生运动之所，生命在于运动，学业繁忙之际对于身体的锻炼也不该懈怠。");
	creatVertex(&v[9], "009", "校医院", "内置的数名医务人员构成保护学生身体健康的防线。");
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
		for (j = 0; j < G->vexnum; j++)
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

//"查询最短路径" 的起点与终点的输入及选择合法性判断
void Decision_Input(int a[])
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

/*登录注册*/
void zhuce()
{
	FILE* fp;
	char yhm[20], mima_0[20], mima_1[20];
	struct zhanghu s;
	struct zhanghu* p = &s;
	int t = 0, i, m = 0;
	do {
		printf("请输入用户名：\n");
		scanf("%s", yhm);
		printf("请输入密码：\n");
		scanf("%s", mima_0);
		printf("请再一次输入密码：\n");
		scanf("%s", mima_1);
		if (strcmp(mima_0, mima_1) == 0)
		{
			system("cls");
			printf("注册成功！\n");
			t = 1;
			break;
		}
		else
		{
			m++;
			if (m > 2) { system("cls"); printf("您已3次输入不一致，已退出此操作！\n"); }
			else printf("密码不一致，请重新输入：\n");
		}
	} while (t == 0 && m < 3);
	/***********保存到账户文件**************************************/
	if (m < 3)
	{
		for (i = 0; mima_0[i] != '\0'; i++)
			mima_0[i] += 10;                                     //密码加密
		strcpy(p->admin, yhm);		strcpy(p->password, mima_0);
		if ((fp = fopen("zhanghu.txt", "ab")) == NULL)
		{
			printf("cuowu0"); exit(0);
		}
		if ((fwrite(&s, sizeof(struct zhanghu), 1, fp)) != 1)
		{
			printf("写入数据错误！"); exit(0);
		}
		fclose(fp);
	}
}

int denglu()
{
	struct zhanghu read;
	struct zhanghu* p = &read;
	char yhm[20], mima[20];
	FILE* fp;
	int n = 0, i, j, t = 0;
	if ((fp = fopen("zhanghu.txt", "rb")) == NULL)
	{
		system("cls");
		printf("不存在账户数据，请注册\n"); return 0;
	}
	for (i = 4; i >= 0; i--)
	{
		printf("请输入用户名：\n");
		scanf("%s", yhm);
		printf("请输入密码：\n");
		scanf("%s", mima);
		rewind(fp);
		while (t == 0 && fp != NULL && n == 0)
		{
			if ((fread(&read, sizeof(struct zhanghu), 1, fp)) != NULL)
			{
				if (strcmp(p->admin, yhm) == 0)
				{
					t = 1; n = 1;
					for (j = 0; p->password[j] != '\0'; j++)
						p->password[j] -= 10;					//密码解密
					if (strcmp(p->password, mima) == 0)
					{
						system("cls");
						printf("登录成功！按任意键开始使用系统\n");
						return 1;
					}
					else
					{
						n = 0; t = 0;
						if (i == 4)
						{
							system("cls");
							printf("用户名或密码输入错误，请重新输入！\n");
						}
						else
						{
							system("cls");
							printf("登录失败！您还有%d次机会！\n", i);
							if (i == 0)
							{
								printf("您输入次数过多，已强制退出！");

								return -1;
							}
						}
						break;
					}
				}
			}
			else
			{
				system("cls");
				printf("此账户不存在！\n");
				return 0;
			}
		}
	}
	fclose(fp);
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

int menu_1()
{
	int n;
	printf("\t\t\t\t********************************\n");
	printf("\t\t\t\t*           1.登录             *\n");
	printf("\t\t\t\t*           2.注册             *\n");
	printf("\t\t\t\t*           0.退出             *\n");
	printf("\t\t\t\t********************************\n");
	printf("请输入您的选择：");
	scanf("%d", &n);
	return n;
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
	printf("\t\t\t  *      <8>田径运动场            <9>校医院            *\n");
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
	printf("\t\t\t  *                4.显示path数组和dist数组            *\n");
	printf("\t\t\t  *                5.显示学校简易地图                  *\n");
	printf("\t\t\t  *                0.退出                              *\n");
	printf("\t\t\t  ******************************************************\n");
	printf("请输入您所需要使用的功能的序号：");
	scanf("%d", &chose);
	return chose;
}