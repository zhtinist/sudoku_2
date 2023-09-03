#include"def.h"
//目前存入的终盘模版数,方便加入新的终盘
#define DATA 20
//初始的终盘用于生成游戏
char ending_game_data[DATA][70]={   
                                    "HQV1G4563263847554721632638975437915428625789634463217554876363452",
                                    "HQV1G4536232457667984532367984556813792445281673745283631456263745",
                                    "HQV1G7856963748554123768635124795276413874128365634125787354656789",
                                    "HQV1G5364246723575984636237985434598271678361452451726367483553624",
                                    "HQV1G3647567853474521634536928759218374687321465684725346859775684",
                                    "HQV1G5436263724575986343247985646598271378431652651723437684554326",
                                    "HQV1G3574676458364132754352186758217639476839245375248669485745768",
                                    "HQV1G5634248765335124762769853464273918535892476436875251426376534",
                                    "HQV1G3675461543275621435428937643192768524379856376854268547356234",
                                    "HQV1G3675454231661572434361852772489163551237486367285445876363542",
                                    "HQV1G4632558476337152466529783424683951737492865531672468745345236",
                                    "HQV1G5426342531626317546317842531659284754821763724863545738663574",
                                    "HQV1G7436563584747126535829347636758129454312678672348549685778546",
                                    "HQV1G2435653641262785433589276446978123574396582524317667845335764",
                                    "HQV1G5236464573247986533542987626831794537986452657983442357654623",
                                    "HQV1G6845754679887935644582137676398214537461528582437663725445637",
                                    "HQV1G5426376354263721544251873637842961556398742487695375483663524",
                                    "HQV1G5637461542374631524389726535928174627594863486732563857456432",
                                    "HQV1G5632438465747251366387241524519876357861324637241548653735246",
                                    "HQV1G2436557624363451274581273636278951427396845587493643865765423"};
//旋转棋盘以提高数独棋盘多样性
void clockwise(char* input,char* output);//顺指针旋转棋盘
void counter_clockwise(char* input,char* output);//逆时针旋转棋盘
int iscorrect(char* game);//验证挖洞后解是否唯一
//生成新游戏,本文件主要功能
void create_new_game(char *game,int rank)
{
    switch (rank)
    {
    case 1: rank=20;break;
    case 2: rank=30;break;
    case 3: rank=40;break;
    
    default:
        rank=35;
        break;
    }
    //根据时间生成随机数
    int timestamp;
    int random_num,randomnum;
    // 获取当前系统时间的时间戳
    timestamp = (int)time(NULL);
    // 设置随机数种子
    srand((unsigned int)time(NULL));
    // 生成随机数
    random_num = rand();
    randomnum=rand();
    random_num%=DATA;
    randomnum%=6;
    strcpy(game,*(ending_game_data+random_num));
    //随机旋转0~5次60度角
    for(int i=0;i<randomnum;i++)
    {
        char temp[70]={0};
        clockwise(game,temp);
        strcpy(game,temp);
    }
    int pos=0;
    for(int i=0;i<rank;i++)
    {
        char temp_game[70]={0};
        strcpy(temp_game,game);
        
        //随机取挖洞位置
        do
        {
            pos=rand();
            pos%=61;
        }while(temp_game[pos+5]=='0');
        // cout<<pos<<endl;
        int sum_answer=0;
        for(int j=1;j<=9;j++){//'1'到'9'逐个尝试是否只有其中之一有解
            temp_game[5+pos]='0'+j;
            sum_answer+=iscorrect(temp_game);
            // cout<<sum_answer<<endl;
        }
        // cout<<sum_answer<<endl;
        if(sum_answer==1)
        {
            game[5+pos]='0';
            cout<<"\r已经生成"<<i+1<<"个洞!";
        }else i--;
    }
    randomnum=rand();
    randomnum%=6;
    //随机旋转0~5次60度角
    for(int i=0;i<randomnum;i++)
    {
        char temp[70]={0};
        clockwise(game,temp);
        strcpy(game,temp);
    }

}



//转换结果存在第二个参数中
void clockwise(char* input,char* output){
    int clockwise[65]={27,19,12,6,1,36,28,20,13,7,2,44,37,29,21,14,8,3,51,45,38,30,22,15,9,4,57,52,46,39,31,23,16,10,5,58,53,47,40,32,24,17,11,59,54,48,41,33,25,18,60,55,49,42,34,26,61,56,50,43,35,0,0};
    for(int i=0;i<5;i++) output[i]=input[i];
    for(int i=5,k=0;clockwise[k];i++,k++)
    {
        output[i]=input[clockwise[k]+4];
    }
}

void counter_clockwise(char* input,char* output){
    int counter_clockwise[65]={5,11,18,26,35,4,10,17,25,34,43,3,9,16,24,33,42,50,2,8,15,23,32,41,49,56,1,7,14,22,31,40,48,55,61,6,13,21,30,39,47,54,60,12,20,29,38,46,53,59,19,28,37,45,52,58,27,36,44,51,57};
    int i=0;
    int k=0;
    for(i=0;i<5;i++) output[i]=input[i];
    for(int i=5,k=0;counter_clockwise[k];i++,k++)
    {
        output[i]=input[counter_clockwise[k]+4];
    }

}


int iscorrect(char* game){
    cout<<'.';
    // //关闭输出流
    // fclose(stdout);
    cnfmaker(game,"temp.cnf");
    int value[61*9+1]={0};
    SATList* templist=NULL;
    ReadFile(templist,"temp.cnf");
    //删除临时文件
    remove("temp.cnf");
    int re=DPLL(templist,value);


    // //重新开启输出流
    // freopen("CON","w",stdout);
    return re;

}

/*
 * 函数名称: destroyClause
 * 接受参数: SATList*&
 * 函数功能: 销毁链表
 * 返回值: int
 */
void destroyClause(SATList*& cnf)
{
	SATList* lp1, * lp2;
	SATNode* tp1, * tp2;
	for (lp1 = cnf; lp1 != NULL; lp1 = lp2)
	{
		lp2 = lp1->next;
		for (tp1 = lp1->head; tp1 != NULL; tp1 = tp2)
		{
			tp2 = tp1->next;
			free(tp1);
		}
		free(lp1);
	}
	cnf = NULL;
}

/*
 * 函数名称: isUnitClause
 * 接受参数: SATNode*
 * 函数功能: 判断是否为单子句，是返回1，不是返回0
 * 返回值: int
 */
int isUnitClause(SATNode* cnf)
{
	if (cnf != NULL && cnf->next == NULL)
		return 1;
	else
		return 0;
}

/*
 * 函数名称: evaluateClause
 * 接受参数: SATList*
 * 函数功能: 评估子句的真假状态，真返回1，假返回0
 * 返回值: int
 */
int evaluateClause(SATNode* cnf,int v[])
{
	SATNode* tp = cnf;
	while (tp != NULL)
	{
		if (tp->data > 0 && v[tp->data] == 1 ||
			tp->data < 0 && v[-tp->data] == 0)
			return 1;
	}
	return 0;
}

/*
 * 函数名称: removeClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中删除指定的子句，删除成功返回1，失败返回0
 * 返回值: int
 */
int removeClause(SATList*& cnf, SATList*& root)
{
	SATList* lp = root;
	if (lp == cnf) root = root->next;  //删除为头
	else
	{
		while (lp != NULL && lp->next != cnf) lp = lp->next;
		lp->next = lp->next->next;
	}
	free(cnf);
	cnf = NULL;
	return 1;
}

/*
 * 函数名称: removeNote
 * 接受参数: SATNode*,SATNode*
 * 函数功能: 在指定的子句中删除指定的文字，删除成功返回1，失败返回0
 * 返回值: int
 */
int removeNode(SATNode*& cnf, SATNode*& head)
{
	SATNode* lp = head;
	if (lp == cnf) head = head->next;  //删除为头
	else
	{
		while (lp != NULL && lp->next != cnf) lp = lp->next;
		lp->next = lp->next->next;
	}
	free(cnf);
	cnf = NULL;
	return 1;
}

/*
 * 函数名称: addClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中添加指定的子句，添加成功返回1，失败返回0
 * 返回值: int
 */
int addClause(SATList* cnf, SATList*& root)
{
	//直接插入在表头
	if (cnf != NULL)
	{
		cnf->next = root;
		root = cnf;
		return 1;
	}
	return 0;
}

/*
 * 函数名称: emptyClause
 * 接受参数: SATList*
 * 函数功能: 判断是否含有空子句，是返回1，不是返回0
 * 返回值: int
 */
int emptyClause(SATList* cnf)
{
	SATList* lp = cnf;
	while (lp != NULL)
	{
		if (lp->head == NULL) return 1;
		lp = lp->next;
	}
	return 0;
}

/*
 * 函数名称: CopyClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 将链表b的值复制到链表a中
 * 返回值: void
 */
void CopyClause(SATList*& a, SATList* b)
{
	SATList* lpa,*lpb;
	SATNode* tpa,*tpb;
	a = (SATList*)malloc(sizeof(SATList));
	a->head = (SATNode*)malloc(sizeof(SATNode));
	a->next = NULL;
	a->head->next = NULL;
	for (lpb = b, lpa = a; lpb != NULL; lpb = lpb->next, lpa = lpa->next)
	{
		for (tpb = lpb->head, tpa = lpa->head; tpb != NULL; tpb = tpb->next, tpa = tpa->next)
		{
			tpa->data = tpb->data;
			tpa->next = (SATNode*)malloc(sizeof(SATNode));
			tpa->next->next = NULL;
			if (tpb->next == NULL)
			{
				free(tpa->next);
				tpa->next = NULL;
			}
		}
		lpa->next = (SATList*)malloc(sizeof(SATList));
		lpa->next->head = (SATNode*)malloc(sizeof(SATNode));
		lpa->next->next = NULL;
		lpa->next->head->next = NULL;
		if (lpb->next == NULL)
		{
			free(lpa->next->head);
			free(lpa->next);
			lpa->next = NULL;
		}
	}
}

/*
* 函数名称: DPLL
* 接受参数: SATList *
* 函数功能: 求解SAT问题，给出满足条件时的一个式子,若有解则返回1，无解返回0
* 返回值: int
*/
//int ReadFile(SATList*& cnf);
//void destroyClause(SATList*& cnf);
//int isUnitClause(SATNode* cnf);
//int evaluateClause(SATNode* cnf, int v[]);
//int removeClause(SATList*& cnf, SATList*& root);
//int removeNode(SATNode*& cnf, SATNode*& head);
//int addClause(SATList* cnf, SATList*& root);
//int emptyClause(SATList* cnf);
//int DPLL(SATList*& cnf, int value[]);
//void CopyClause(SATList*& a, SATList* b);
//int WriteFile(int result, double time, int value[]);
//void CreateBinary(int size);
//int SolvePuzzle(int chess[], int size);
status DpllSolver(SATList* s, int* truth_table)
{
    SATList* s_tmp = s;
    SATList* unit_clause = IsUnitClause(s_tmp);    // 获得单子句

    // 单子句规则
    while(unit_clause)
    {
		// ios_base::sync_with_stdio(false);
		// cout<<"数据整理中,请稍候......\r";
		// printf("数据整理中,请稍候......\r");
        RecordTruth(unit_clause, truth_table);        // 记录单子句中的变元的真值
        int var = unit_clause->head->data;
        RemoveVar(s, var);

        if(s->next == NULL) return FOUND;             // S为空
        else if(IsEmptyClause(s))   return NOTFOUND;  // S中存在空子句

        s_tmp = s;
        unit_clause = IsUnitClause(s_tmp);            // 还存在单子句则继续循环
    }
	// ios_base::sync_with_stdio(false);
	// cout<<"运算中,请稍候.......\r";
	// printf("运算中,请稍候........\r");
    // 分裂策略
    int var = PickVar(s);                                                  // 选变元
    if(DpllSolver(AddClause(CopyS(s), var), truth_table))  return FOUND;   // 变元的真值选对了,此处传入S的拷贝
    return DpllSolver(AddClause(s, -var), truth_table);                    // 变元的真值选错了
}

SATList* CopyS(SATList* s)
{
    SATList *s_new, *c_tmp, *s_origin = s->next;

    // 创建root
    s_new = (SATList *)malloc(sizeof(SATList));
    s_new->head = NULL;
    c_tmp = s_new;

    // 循环创建子句
    while(s_origin)
    {
        c_tmp->next = CopyClause(s_origin);  // 复制整个子句
        c_tmp = c_tmp->next;                 // 下一个
        s_origin = s_origin->next;
    }
    return s_new;
}

SATList* CopyClause(SATList* s)
{
    SATList* clause_tmp;
    SATNode *literal_tmp, *s_tmp = s->head;

    // 创建子句结点
    clause_tmp = (SATList *)malloc(sizeof(SATList));
    clause_tmp->next = NULL;
    clause_tmp->head = NULL;

    // 创建第一个文字结点
    if(s_tmp)
    {
        literal_tmp = (SATNode *)malloc(sizeof(SATNode));
        literal_tmp->data = s_tmp->data;
        literal_tmp->next = NULL;
        s_tmp = s_tmp->next;
        clause_tmp->head = literal_tmp;
    }

    // 循环创建之后的文字结点
    while(s_tmp)
    {
        literal_tmp->next = (SATNode *)malloc(sizeof(SATNode));
        literal_tmp->next->data = s_tmp->data;
        literal_tmp->next->next = NULL;
        literal_tmp = literal_tmp->next;
        s_tmp = s_tmp->next;
    }
    return clause_tmp;
}

SATList* AddClause(SATList* s, int var)
{
    SATList* c_tmp;
    c_tmp = (SATList *)malloc(sizeof(SATList));
    c_tmp->head = (SATNode *)malloc(sizeof(SATNode));
    c_tmp->head->data = var;
    c_tmp->head->next = NULL;
    c_tmp->next = s->next;
    s->next = c_tmp;
    return s;
}

int PickVar(SATList* s)
{
    int var = s->next->head->data;
    return var;
}

status RemoveVar(SATList* s, int var)
{
    SATList *c_tmp = s->next, *last_c_tmp = s;
    while(c_tmp)                                     // 循环读取每一个子句
    {
        c_tmp = DeleteLiteral(c_tmp, var);           // 删除子句里所有的负变元，如果遇到了正变元则返回NULL
        if(c_tmp == NULL)                            // 遇到了正变元
        {
            c_tmp = DeleteClause(last_c_tmp->next);  // 与正变元相同则删除子句
            last_c_tmp->next = c_tmp;
            continue;
        }
        if(c_tmp == NULL)   break;
        last_c_tmp = c_tmp;                          // 下一个子句
        c_tmp = c_tmp->next;
    }
    return OK;
}

SATList* DeleteClause(SATList* s)
{
    SATList* c_tmp = s;
    SATNode* l;
    while(s->head)                     // 先删除子句中所有文字
    {
        l = s->head;
        s->head = s->head->next;
        free(l);
    }
    s = s->next;
    free(c_tmp);                        // 再删除空子句
    return s;
}

SATList* DeleteLiteral(SATList* s, int var)
{
    SATNode *l = s->head, *l_tmp;

    // 处理第一个文字
    if(l->data == -var)                  // 负变元
    {
        l_tmp = s->head->next;
        free(l);
        s->head = l_tmp;
        return s;
    }
    else if(l->data == var) return NULL; // 正变元

    // 循环处理接下来的文字
    while(l)
    {
        if(l->next && l->next->data == -var)
        {
            l_tmp = l->next;
            l->next = l->next->next;
            free(l_tmp);
        }
        else if(l->next && l->next->data == var)  return NULL;
        l = l->next;
    }
    return s;
}

status IsEmptyClause(SATList* s)
{
    SATList* c_tmp = s->next;
    while(c_tmp)
    {
        if(!c_tmp->head) return YES;
        c_tmp = c_tmp->next;
    }
    return NO;
}

status RecordTruth(SATList* s, int* truth_table)
{
    int idx = abs(s->head->data) - 1;   // 序号=绝对值-1
    if(s->head->data > 0)  truth_table[idx] = 1;
    else    truth_table[idx] = 0;
    return OK;
}

SATList* IsUnitClause(SATList* s)
{
    SATList* c_tmp = s;
    while(c_tmp)
    {
        if(c_tmp->head && !c_tmp->head->next)    return c_tmp;
        c_tmp = c_tmp->next;
    }
    return NULL;
}

status Print(SATList* s)
{
    SATList* c_tmp = s->next;
    SATNode* l_tmp;
    printf("\n-----Start-----\n");
    while(c_tmp)
    {
        l_tmp = c_tmp->head;
        while(l_tmp)
        {
            printf("%d ", l_tmp->data);
            l_tmp = l_tmp->next;
        }
        if(c_tmp->head)    printf("\n");
        else    printf("空\n");
        c_tmp = c_tmp->next;
    }
    printf("------End------\n");
    return OK;
}
//
int DPLL(SATList*& cnf, int value[])
{
	SATList* tp = cnf, * lp = cnf, * sp;
	SATNode* dp;
	int* count, i, MaxWord, max, re; //count记录每个文字出现次数,MaxWord记录出现最多次数的文字
	count = (int*)malloc(sizeof(int) * (boolCount * 2 + 1));
FIND:	while (tp != NULL && isUnitClause(tp->head) == 0) tp = tp->next;  //找到表中的单子句
	if (tp != NULL)
	{
		// ios_base::sync_with_stdio(false);
		// cout<<"数据处理中,请稍候.....\r";
		// printf("数据整理中,请稍候......\r");
		//单子句规则简化
		if (tp->head->data > 0) value[tp->head->data] = 1;
		else value[-tp->head->data] = 0;
		re = tp->head->data;
		for (lp = cnf; lp != NULL; lp = sp)
		{
			sp = lp->next;

			//查找含有核心文字的句子
			for (dp = lp->head; dp != NULL; dp = dp->next)
			{
				if (dp->data == re)
				{
					removeClause(lp, cnf);  //删除子句，简化式子
					break;
				}
				if (dp->data == -re)
				{
					removeNode(dp, lp->head);  //删除文字，简化子句
					break;
				}
			}
		}
		//极简化规则简化后
		if (cnf == NULL)
		{
			free(count);
			return 1;
		}
		else if (emptyClause(cnf))
		{
			free(count);
			destroyClause(cnf);
			return 0;
		}
		tp = cnf;
		// ios_base::sync_with_stdio(false);
		// cout<<"运算中,请稍候........\r";
		// printf("运算中,请稍候........\r");
		goto FIND;  //继续简化
	}
	for (i = 0; i <= boolCount * 2; i++) count[i] = 0;  //初始化

	//计算子句中各文字出现次数
	for (lp = cnf; lp != NULL; lp = lp->next)
	{
		for (dp = lp->head; dp != NULL; dp = dp->next)
		{
			if (dp->data > 0) count[dp->data]++;
			else count[boolCount - dp->data]++;
		}
	}
	max = 0;

	//找到出现次数最多的正文字
	for (i = 2; i <= boolCount; i++)
	{
		if (max < count[i])
		{
			max = count[i];
			MaxWord = i;
		}
	}

	if (max == 0)
	{
		//若没有出现正文字,找到出现次数最多的负文字
		for (i = boolCount + 1; i <= boolCount * 2; i++)
		{
			if (max < count[i])
			{
				max = count[i];
				MaxWord = -i;
			}
		}
	}
	free(count);
	lp = (SATList*)malloc(sizeof(SATList));
	lp->head = (SATNode*)malloc(sizeof(SATNode));
	lp->head->data = MaxWord;
	lp->head->next = NULL;
	lp->next = NULL;
	CopyClause(tp, cnf);
	addClause(lp, tp);
	if (DPLL(tp, value) == 1) return 1;  //在第一分支中搜索
	destroyClause(tp);
	lp = (SATList*)malloc(sizeof(SATList));
	lp->head = (SATNode*)malloc(sizeof(SATNode));
	lp->head->data = -MaxWord;
	lp->head->next = NULL;
	lp->next = NULL;
	addClause(lp, cnf);
	re = DPLL(cnf, value); //回溯到执行分支策略的初态进入另一分支
	destroyClause(cnf);
	return re;
}
