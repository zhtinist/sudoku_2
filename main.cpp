#include"include/def.h"
#include<bits/stdc++.h>
//全局变量
int boolCount;  //布尔变元数量
int clauseCount;  //子句数量
char fileName[300]; //文件名
char filename3[300];
int temp[9][9];
char CHESS[100]="HQV1G0000000000000000000000000000000000000000000000000000000000000";
int zeroNum;
SATList* CNFList = NULL, * lp;
HeadNode* L =NULL,*yp;
SATNode* tp;
clock_t start, finish;  //设置时间变量
double time1=0.0,time2=0.0;
int op = 1, i, result,q,a1,a2,a3;
int* value;  //保存结果
char SE[88];
int nnn[100]={0};
int d[10]={0,5,11,18,26,35,43,50,56,61};
int isBetter=0;
//引入其他模块
#include"include/function.h"


//函数定义
/*
 * 函数名称: main
 * 接受参数: void
 * 函数功能: 主函数
 * 返回值: int
 */
int main(void)
{
	int cod=0;
	string filename;
	while (op)
	{
		system("cls");	cout.clear(); fflush(stdout);
		printf("\n\n");
		display();
		scanf("%d", &op);
		cod=1;
		switch (op)
		{
		case 1:
			printf("输入要读取的cnf文件:");
			cin >> filename;
			L = CnfParser(filename);
			if(!L) printf("读取失败！");
			strcpy_s(fileName,filename.c_str());
			ReadFile(CNFList,fileName);
			cout<<"读取完成"<<endl;
			// getchar(); getchar();
			system("pause");
			break;
		case 2:
			if (CNFList == NULL) printf("未导入文件\n");
			else
			{
				printf("cnf子句如下：\n");
				for (lp = CNFList; lp != NULL; lp = lp->next)
				{
					for (tp = lp->head; tp != NULL; tp = tp->next)
					{
						printf("%d ", tp->data);
					}
					printf("\n");
				}
				cout<<"所有数据已输出!"<<endl;
			}
			system("pause");
			break;
		case 3:
			if (L == NULL) printf("未导入文件\n");
			else
			{
				
				cod=1;
				isBetter=0;
				strcpy(filename3,fileName);
				CoreFun(L, filename, FunNum, cod, temp);
				cout<<"\n请重新用1读取文件"<<endl;
			}
			system("pause");
			break;
		case 4:
			if (L == NULL) printf("未导入文件\n");
			else
			{
				cod=2;
				isBetter=1;
				CoreFun(L, filename, FunNum, cod, temp);
				cout<<"\n请重新用1读取文件"<<endl;
			}
			system("pause");
			break;	
		case 5:
			{
				char temper[100]={};
				ifstream read_file;
				printf("请输入待解决蜂窝数独文件名\n");
				scanf("%s",temper);
				read_file.open(temper,ios::in);
				read_file.getline(SE,80);
				read_file.close();
				printf("输入CNF文件名,此文件用于保存数独对应的cnf文件：\n");
				scanf("%s", fileName);
				boolCount=9*61;
				cnfmaker(SE,fileName);
				value = (int*)malloc(sizeof(int) * (boolCount + 1));
				for (i = 1; i <= boolCount; i++)
				{
					if (value[i] == 1){
						q=disresort(i);
						a1=q%10;q=q/10;
						a2=q%10;q=q/10;
						a3=q%10;
						nnn[d[a3-1]+a2]=a1;
					}
				}
				printf("cnf文件已生成!准备求解\n");
				int crea_sudoku[100]={0};
				for(i=1;i<=61;i++)
				{
				crea_sudoku[i]=SE[i+4]-'0';
				}
				CreateSudoku(crea_sudoku);
				system("pause");
				ReadFile(CNFList,fileName);
				if (CNFList == NULL) printf("未导入文件\n");
				else {
					value = (int*)malloc(sizeof(int) * (boolCount + 1));
					for (i = 1; i <= boolCount; i++) value[i] = 1;
					start = clock();
					result = DPLL(CNFList, value);
					finish = clock();
					printf("求解结果：%d\n", result);
					if (result == 1)
					{
						for (i = 1; i <= boolCount; i++)
						{
							if (value[i] == 1){
								q=disresort(i);
								a1=q%10;q=q/10;
								a2=q%10;q=q/10;
								a3=q%10;
								nnn[d[a3-1]+a2]=a1;
							}
						}
					}
					CreateSudoku(nnn);
					if (WriteFile(result, time1, value) == 1)
						printf("结果已保存至同名文件.res\n");
					else printf("结果保存失败\n");
				}
				getchar();getchar();
				break;
			}
		case 6:{
			cout<<"正在生成蜂窝数独!请输入难度:\n1--easy\n2--normal\n3--hard"<<endl;
			int rank=1;
			cin>>rank;
			char game[70]={0};
			create_new_game(game,rank);
			ofstream fp;
			fp.open("new_game.play",ios::out);
			string new_game=game;
			fp<<new_game<<endl;
			fp.close();
			cout<<endl<<"游戏初始化棋盘已生成,保存在new_game.play中,重新生成将会覆盖之前的游戏"<<endl;
			cout.clear();
			fflush(stdout);
			// system("cls");
			system("pause");
			}
			break;

		case 0:
			break;
		default:
			cout<<"please use avalable numbers!";
			system("pause");
			break;
		}
	}
	return 0;
}












void CoreFun(HeadNode* L, string& filename, int FunNum, int cod, int array[ROW][COL]){

    //文件输出准备部分
    string _PATH = filename.replace(filename.end()-4, filename.end(), ".res");
    bool suc;
    int *book = new int[FunNum];
    memset(book, 0, sizeof(int)*FunNum);
    int begin = 0, end = 0;

    //DPLL()核心处理部分
    begin = clock();
    bool isTrue;
    if(!isBetter) {isTrue = DPLL(L, book);}
    else {isTrue = NewDPLL(L, book);}
    if(isTrue) {suc = TRUE;}
    else {suc = FALSE;}
    if(cod == 1){
        if(isTrue) {cout << "为真" << endl;}
        else {cout << "为假" << endl;}
        end = clock();
		time1=end-begin;
        cout << "DPLL()部分运行的时间为" << end-begin << "ms" << endl;
    }
		if(cod == 2){
        if(isTrue) {cout << "为真" << endl;}
        else {cout << "为假" << endl;}
        end = clock();
		time2=end-begin;
        cout << "DPLL()部分运行的时间为" << end-begin << "ms" << endl;
		if(isTrue&&time1&&time2&&!(strcmp(filename3,fileName))){
			if(time1>time2){
						printf("优化率为[(t-to)/t]*100%%=%f%%",((time1-time2)/time1)*100);
					}
					else printf("优化率为[(t-to)/t]*100%%=%f%%",((time2-time1)/time2)*100);
		}
    }
    //输出.res文件
    OutFileFun1(_PATH, suc, book, end-begin, FunNum, cod);
}