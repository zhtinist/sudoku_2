#include"include/def.h"
#include<bits/stdc++.h>
//ȫ�ֱ���
int boolCount;  //������Ԫ����
int clauseCount;  //�Ӿ�����
char fileName[300]; //�ļ���
int temp[9][9];
char CHESS[100]="HQV1G0000000000000000000000000000000000000000000000000000000000000";
int zeroNum;
SATList* CNFList = NULL, * lp;
HeadNode* L =NULL,*yp;
SATNode* tp;
clock_t start, finish;  //����ʱ�����
double time1=0.0,time2=0.0;
int op = 1, i, result,q,a1,a2,a3;
int* value;  //������
char SE[88];
int nnn[100]={0};
int d[10]={0,5,11,18,26,35,43,50,56,61};
int isBetter=0;
//��������ģ��
#include"include/function.h"


//��������
/*
 * ��������: main
 * ���ܲ���: void
 * ��������: ������
 * ����ֵ: int
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
			printf("����Ҫ��ȡ��cnf�ļ�:");
			cin >> filename;
			L = CnfParser(filename);
			if(!L) printf("��ȡʧ�ܣ�");
			strcpy_s(fileName,filename.c_str());
			ReadFile(CNFList,fileName);
			cout<<"��ȡ���"<<endl;
			// getchar(); getchar();
			system("pause");
			break;
		case 2:
			if (CNFList == NULL) printf("δ�����ļ�\n");
			else
			{
				printf("cnf�Ӿ����£�\n");
				for (lp = CNFList; lp != NULL; lp = lp->next)
				{
					for (tp = lp->head; tp != NULL; tp = tp->next)
					{
						printf("%d ", tp->data);
					}
					printf("\n");
				}
				cout<<"�������������!"<<endl;
			}
			system("pause");
			break;
		case 3:
			if (L == NULL) printf("δ�����ļ�\n");
			else
			{
				
				cod=1;
				isBetter=0;
				CoreFun(L, filename, FunNum, cod, temp);
				cout<<"��������1��ȡ�ļ�"<<endl;
			}
			system("pause");
			break;
		case 4:
			if (L == NULL) printf("δ�����ļ�\n");
			else
			{
				cod=2;
				isBetter=1;
				CoreFun(L, filename, FunNum, cod, temp);
				cout<<"��������1��ȡ�ļ�"<<endl;
			}
			system("pause");
			break;	
		case 5:
			{
				char temper[100]={};
				ifstream read_file;
				printf("�������������������ļ���\n");
				scanf("%s",temper);
				read_file.open(temper,ios::in);
				read_file.getline(SE,80);
				read_file.close();
				printf("����CNF�ļ���,���ļ����ڱ���������Ӧ��cnf�ļ���\n");
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
				printf("cnf�ļ�������!׼�����\n");
				int crea_sudoku[100]={0};
				for(i=1;i<=61;i++)
				{
				crea_sudoku[i]=SE[i+4]-'0';
				}
				CreateSudoku(crea_sudoku);
				system("pause");
				ReadFile(CNFList,fileName);
				if (CNFList == NULL) printf("δ�����ļ�\n");
				else {
					value = (int*)malloc(sizeof(int) * (boolCount + 1));
					for (i = 1; i <= boolCount; i++) value[i] = 1;
					start = clock();
					result = DPLL(CNFList, value);
					finish = clock();
					printf("�������%d\n", result);
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
						printf("����ѱ�����ͬ���ļ�.res\n");
					else printf("�������ʧ��\n");
				}
				getchar();getchar();
				break;
			}
		case 6:{
			cout<<"�������ɷ�������!�������Ѷ�:\n1--easy\n2--normal\n3--hard"<<endl;
			int rank=1;
			cin>>rank;
			char game[70]={0};
			create_new_game(game,rank);
			ofstream fp;
			fp.open("new_game.play",ios::out);
			string new_game=game;
			fp<<new_game<<endl;
			fp.close();
			cout<<endl<<"��Ϸ��ʼ������������,������new_game.play��,�������ɽ��Ḳ��֮ǰ����Ϸ"<<endl;
			cout.clear();
			fflush(stdout);
			// system("cls");
			system("pause");
			}
			break;

		case 0:
			break;
		}
	}
	return 0;
}












void CoreFun(HeadNode* L, string& filename, int FunNum, int cod, int array[ROW][COL]){

    //�ļ����׼������
    string _PATH = filename.replace(filename.end()-4, filename.end(), ".res");
    bool suc;
    int *book = new int[FunNum];
    memset(book, 0, sizeof(int)*FunNum);
    int begin = 0, end = 0;

    //DPLL()���Ĵ�����
    begin = clock();
    bool isTrue;
    if(!isBetter) {isTrue = DPLL(L, book);}
    else {isTrue = NewDPLL(L, book);}
    if(isTrue) {suc = TRUE;}
    else {suc = FALSE;}
    if(cod == 1){
        if(isTrue) {cout << "Ϊ��" << endl;}
        else {cout << "Ϊ��" << endl;}
        end = clock();
		time1=end-begin;
        cout << "DPLL()�������е�ʱ��Ϊ" << end-begin << "ms" << endl;
    }
		if(cod == 2){
        if(isTrue) {cout << "Ϊ��" << endl;}
        else {cout << "Ϊ��" << endl;}
        end = clock();
		time2=end-begin;
        cout << "DPLL()�������е�ʱ��Ϊ" << end-begin << "ms" << endl;
		if(isTrue&&time1&&time2){
			if(time1>time2){
						printf("�Ż���Ϊ[(t-to)/t]*100%%=%f%%",((time1-time2)/time1)*100);
					}
					else printf("�Ż���Ϊ[(t-to)/t]*100%%=%f%%",((time2-time1)/time2)*100);
		}
    }
    //���.res�ļ�
    OutFileFun1(_PATH, suc, book, end-begin, FunNum, cod);
}