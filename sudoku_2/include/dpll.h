#include"def.h"
extern int FunNum;
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


































































































































bool DPLL(HeadNode* L, int* book){
    int SC;//存储单子句(SingleClause的缩写)
    //cout << ++TestNum << endl;
    //printList(L);
    while(SC = isHaveSingleClause(L)){
        //cout << "2-" << TestNum << " 本次循环要删除的为:" << SC << endl;
        if(SC > 0) book[SC] = 1;
        else if(SC < 0) book[0-SC] = -1;//例如：book[-(-2)] = -1表示2代表的变元取负值，即-2
        SimplifyCnf(L, SC);//根据单子句传播策略简化单子句
       //printList(L);
        if(isemptyCnf(L)) return TRUE;
        else if(isHaveEmptyClause(L)) return FALSE;
    }
    //int v = SelectWord(L);
    int v = SelectWord2(L);//采用最短子句优先选取规则进行选取变元
    //cout << "这次选取的变元为：" << v << endl;
    HeadNode* temL = CopyList(L);
    if(DPLL(merge(L, v), book)) return TRUE;
    bool result = DPLL(merge(temL, 0-v), book);
    //删除temL的内容空间
    FreeList(temL);
    return result;
}

bool NewDPLL(HeadNode* L, int* book){//非递归版本DPLL算法
    stack<HeadNode*> S;
    HeadNode* ListL[10000] = {nullptr}; int i = 0;//ListL用来记录每次改变的链表结点内容
    HeadNode* temL = nullptr;
    int v[10000]; int val;
    S.push(L);
    while(!S.empty()){
        while((L = S.top()) && (val = SingleSpread(L, book)) == NOMAL){
            //cout << "循环开始" << endl; printList(L);
            temL = CopyList(L);
            ListL[i] = temL;
            v[i] = SelectWord2(L);
            //cout << "选取的变元为：" << v[i] << endl;
            L = merge(L, v[i]);
            S.push(L);i++;
        }
        //printList(L); cout << "循环结束" << endl;
        if(val == TRUE) return TRUE;
        S.pop();i--;
        //cout << "此处的变元为：" << v[i] << endl;
        FreeList(L);
        //cout << "栈的大小为" << S.size() << endl;
        if(!S.empty()){
            L = ListL[i]; S.pop();
            S.push(merge(L, -v[i]));
        }
    }
    return FALSE;
}

int SingleSpread(HeadNode* L, int* book){
    int SC;//存储单子句(SingleClause的缩写)
    //cout << ++TestNum << endl;
    //printList(L);
    while(SC = isHaveSingleClause(L)){
        //cout << "2-" << TestNum << " 本次循环要删除的为:" << SC << endl;
        if(SC > 0) book[SC] = 1;
        else if(SC < 0) book[0-SC] = -1;//例如：book[-(-2)] = -1表示2代表的变元取负值，即-2
        SimplifyCnf(L, SC);//根据单子句传播策略简化单子句
       //printList(L);
        if(isemptyCnf(L)) return TRUE;
        else if(isHaveEmptyClause(L)) return FALSE;
    }
    return NOMAL;
}

//L中存储的合区范式是否含有单子句（只含有一个文字的子句叫做单子句）
//如果含有单子句，则返回单子句的值
//如果不含有单子句，则返回0
int isHaveSingleClause(HeadNode* L){
    HeadNode* _pH = L->down;
    while(_pH){
        if(_pH->num == 1) return _pH->right->value;
        _pH = _pH->down;
    }
    return 0;
}

//根据单子句SC进行化简范式L——含有SC的子句直接去掉，含有-SC的子句中去掉-SC这个文字
void SimplifyCnf(HeadNode* L, int SC){
    HeadNode* _pH = L->down;
    HeadNode* _fpH = L;//记录之前遍历过的结点
    int flag;
    while(_pH){
        DataNode* _p = _pH->right;
        DataNode* _fp = _p;
        flag = 0;
        while(_p){
            flag = 0;
            if(_p->value == SC){//去掉这个子句（删除一行）
                _fpH->down = _pH->down;
                _p = _pH->right;
                while(_p){
                    _fp = _p;
                    _p = _p->next;
                    delete _fp;
                }
                L->num--;
                flag = 1;
                break;//跳过这一行
            }
            else if(_p->value == 0-SC){//去掉这个文字（删除一个点，需要考虑第一个节点的特殊情况）
                if(_pH->right == _p){
                    flag = 2;//第一个结点就出现目标数据，需要删除
                    _pH->right = _p->next;
                    _pH->num--;
                    //cout << "第一个结点处地文字删除后num的值为：" << _pH->num << endl;
                }
                else{
                    flag = 3;
                    _fp->next = _p->next;
                    _pH->num--;
                }
            }
            if(!flag){//没有需要删除的节点
                if(_fp != _p) _fp = _p;
                _p = _p->next;
            }
            else if(flag == 2){//删除的结点为第一个节点的情况处理
                _p = _pH->right;
                _fp = _p;
            }
            else if(flag == 3){//删除的节点不是第一个，在中间
                delete _p;
                _p = _fp->next;
            } 
        }
        if(!flag){
            _fpH = _pH;
            _pH = _pH->down;
        }
        else if(flag == 1){
            delete _pH;
            _pH = _fpH->down;
        } 
    }
}

//L中存储的范式是否为空范式
bool isemptyCnf(HeadNode* L){
    if(L->num) return FALSE;
    else return TRUE;
}

//判断范式中是否有空子句
bool isHaveEmptyClause(HeadNode* L){
    HeadNode* _pH = L->down;
    while(_pH){
        if(_pH->num == 0) return TRUE;
        _pH = _pH->down;
    }
    return FALSE;
}

//将v作为一个单子句合并到范式L中，将合并后的范式作为返回值
HeadNode* merge(HeadNode* L, int v){
    HeadNode* pH = new HeadNode; pH->num++;
    pH->down = L->down;
    L->down = pH;
    DataNode* p = new DataNode; p->value = v;
    pH->right = p; p->next = nullptr;
    L->num++;
    //cout << "merge完之后添加的v为：" << L->down->right->value << endl;
    return L;
}

//直接返回第一个文字即可
int SelectWord(HeadNode* L){
    HeadNode* _pH = L->down;
    int ans;
    while(_pH){
        DataNode* _p = _pH->right;
        while(_p){
            ans = _p->value;
            return ans;
        }
        _pH = _pH->down;
    }
    cout << "范式为空集，无法选择文字返回" << endl;
    return 0;
}

int SelectWord2(HeadNode* L){//最短子句优先
    HeadNode* _pH = L->down;
    int _min, ans = 0;
    if(!_pH){cout << "范式为空集，无法选择文字返回" << endl; return 0;}
    _min = _pH->num; ans = _pH->right->value;
    while(_pH){
        if(_pH->num != 0 && _pH->num < _min) ans = _pH->right->value;
        _pH = _pH->down;
    }
    return ans;
}

//仅用于测试使用
void printList(HeadNode* L){
    HeadNode* _pH = L->down;
    int i = 1;
    while(_pH){
        cout << "第" << i++ << "行：" << _pH->num;
        DataNode* _p = _pH->right;
        while(_p){
            cout << "->" << _p->value;
            _p = _p->next; 
        }
        cout << endl;
        _pH = _pH->down;
    }
}

//将L中全部内容都拷贝到temL中，函数结构与cnfparser函数基本相同
HeadNode* CopyList(HeadNode* L){
    HeadNode* temL = new HeadNode;
    temL->num = L->num;
    HeadNode* pH = L->down;
    HeadNode* _pH = new HeadNode; temL->down = _pH; _pH->down = nullptr;
    for(int i = 1; i <= L->num; i++){
        _pH->num = pH->num;
        int tep = pH->right->value;
        DataNode* p = pH->right;
        DataNode* _p = new DataNode;
        _p->value = tep; _pH->right = _p; _p->next = nullptr;
        while(p->next){
            p = p->next; tep = p->value;
            _p = new DataNode;
            _p->value = tep;//采用头插法建立链表
            _p->next = _pH->right;
            _pH->right = _p;
        }
        if(i != L->num){
            _pH = new HeadNode;
            _pH->down = temL->down;
            temL->down = _pH;
        }
        pH = pH->down;
    }
    return temL;
}


void FreeList(HeadNode* L){
    //释放掉L里面的所有内存空间
    HeadNode* _pH = L->down;
    while(_pH){
        DataNode* _p = _pH->right;
        while(_p){
            DataNode* _fp = _p;
            _p = _p->next; 
            delete _fp;
        }
        HeadNode* _fpH = _pH;
        _pH = _pH->down;
        delete _fpH;
    }
    delete L;
}


















































extern int FunNum;
bool verification(HeadNode* ordL, int* book);
//验证根据DPLL算法生成的文件是否正确
bool isCorrect(string& filename){
    HeadNode* L = CnfParser(filename);
    HeadNode* ordL = CopyList(L);

    int _FunNum = FunNum>1000? FunNum: 1000;
    int *book = new int[_FunNum];
    memset(book, 0, sizeof(int)*_FunNum);

    int isTrue = NewDPLL(L, book);
    if(!isTrue){cout << ".cnf文件不可满足"; exit(0);}
    else{
        if(verification(ordL, book)) return TRUE;
        else return FALSE;
    }
}
/*
解析文件，生成链表L，同时拷贝一份不会改变的ordL;（不会改变的L）
执行DPLL算法，生成.res文件
如果DPLL算法返回为假，直接退出就行，为真进行下一步
直接遍历ordL结构，访问book对应的文字的值
如果有一个子句的所有的文字都不会满足，那么该解就是有问题
*/
bool verification(HeadNode* ordL, int* book){
    HeadNode* _pH = ordL->down;
    while(_pH){
        DataNode* _p = _pH->right;
        while(_p){
            if(book[abs(_p->value)]*_p->value > 0) break;
            _p = _p->next;
        }
        if(!_p) return FALSE;
        _pH = _pH->down;
    }
    return TRUE;
}