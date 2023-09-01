#include"def.h"
extern int FunNum;
/*
 * ��������: destroyClause
 * ���ܲ���: SATList*&
 * ��������: ��������
 * ����ֵ: int
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
 * ��������: isUnitClause
 * ���ܲ���: SATNode*
 * ��������: �ж��Ƿ�Ϊ���Ӿ䣬�Ƿ���1�����Ƿ���0
 * ����ֵ: int
 */
int isUnitClause(SATNode* cnf)
{
	if (cnf != NULL && cnf->next == NULL)
		return 1;
	else
		return 0;
}

/*
 * ��������: evaluateClause
 * ���ܲ���: SATList*
 * ��������: �����Ӿ�����״̬���淵��1���ٷ���0
 * ����ֵ: int
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
 * ��������: removeClause
 * ���ܲ���: SATList*,SATList*
 * ��������: �����е�ʮ��������ɾ��ָ�����Ӿ䣬ɾ���ɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int removeClause(SATList*& cnf, SATList*& root)
{
	SATList* lp = root;
	if (lp == cnf) root = root->next;  //ɾ��Ϊͷ
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
 * ��������: removeNote
 * ���ܲ���: SATNode*,SATNode*
 * ��������: ��ָ�����Ӿ���ɾ��ָ�������֣�ɾ���ɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int removeNode(SATNode*& cnf, SATNode*& head)
{
	SATNode* lp = head;
	if (lp == cnf) head = head->next;  //ɾ��Ϊͷ
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
 * ��������: addClause
 * ���ܲ���: SATList*,SATList*
 * ��������: �����е�ʮ�����������ָ�����Ӿ䣬��ӳɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int addClause(SATList* cnf, SATList*& root)
{
	//ֱ�Ӳ����ڱ�ͷ
	if (cnf != NULL)
	{
		cnf->next = root;
		root = cnf;
		return 1;
	}
	return 0;
}

/*
 * ��������: emptyClause
 * ���ܲ���: SATList*
 * ��������: �ж��Ƿ��п��Ӿ䣬�Ƿ���1�����Ƿ���0
 * ����ֵ: int
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
 * ��������: CopyClause
 * ���ܲ���: SATList*,SATList*
 * ��������: ������b��ֵ���Ƶ�����a��
 * ����ֵ: void
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
* ��������: DPLL
* ���ܲ���: SATList *
* ��������: ���SAT���⣬������������ʱ��һ��ʽ��,���н��򷵻�1���޽ⷵ��0
* ����ֵ: int
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
    SATList* unit_clause = IsUnitClause(s_tmp);    // ��õ��Ӿ�

    // ���Ӿ����
    while(unit_clause)
    {
		// ios_base::sync_with_stdio(false);
		// cout<<"����������,���Ժ�......\r";
		// printf("����������,���Ժ�......\r");
        RecordTruth(unit_clause, truth_table);        // ��¼���Ӿ��еı�Ԫ����ֵ
        int var = unit_clause->head->data;
        RemoveVar(s, var);

        if(s->next == NULL) return FOUND;             // SΪ��
        else if(IsEmptyClause(s))   return NOTFOUND;  // S�д��ڿ��Ӿ�

        s_tmp = s;
        unit_clause = IsUnitClause(s_tmp);            // �����ڵ��Ӿ������ѭ��
    }
	// ios_base::sync_with_stdio(false);
	// cout<<"������,���Ժ�.......\r";
	// printf("������,���Ժ�........\r");
    // ���Ѳ���
    int var = PickVar(s);                                                  // ѡ��Ԫ
    if(DpllSolver(AddClause(CopyS(s), var), truth_table))  return FOUND;   // ��Ԫ����ֵѡ����,�˴�����S�Ŀ���
    return DpllSolver(AddClause(s, -var), truth_table);                    // ��Ԫ����ֵѡ����
}

SATList* CopyS(SATList* s)
{
    SATList *s_new, *c_tmp, *s_origin = s->next;

    // ����root
    s_new = (SATList *)malloc(sizeof(SATList));
    s_new->head = NULL;
    c_tmp = s_new;

    // ѭ�������Ӿ�
    while(s_origin)
    {
        c_tmp->next = CopyClause(s_origin);  // ���������Ӿ�
        c_tmp = c_tmp->next;                 // ��һ��
        s_origin = s_origin->next;
    }
    return s_new;
}

SATList* CopyClause(SATList* s)
{
    SATList* clause_tmp;
    SATNode *literal_tmp, *s_tmp = s->head;

    // �����Ӿ���
    clause_tmp = (SATList *)malloc(sizeof(SATList));
    clause_tmp->next = NULL;
    clause_tmp->head = NULL;

    // ������һ�����ֽ��
    if(s_tmp)
    {
        literal_tmp = (SATNode *)malloc(sizeof(SATNode));
        literal_tmp->data = s_tmp->data;
        literal_tmp->next = NULL;
        s_tmp = s_tmp->next;
        clause_tmp->head = literal_tmp;
    }

    // ѭ������֮������ֽ��
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
    while(c_tmp)                                     // ѭ����ȡÿһ���Ӿ�
    {
        c_tmp = DeleteLiteral(c_tmp, var);           // ɾ���Ӿ������еĸ���Ԫ���������������Ԫ�򷵻�NULL
        if(c_tmp == NULL)                            // ����������Ԫ
        {
            c_tmp = DeleteClause(last_c_tmp->next);  // ������Ԫ��ͬ��ɾ���Ӿ�
            last_c_tmp->next = c_tmp;
            continue;
        }
        if(c_tmp == NULL)   break;
        last_c_tmp = c_tmp;                          // ��һ���Ӿ�
        c_tmp = c_tmp->next;
    }
    return OK;
}

SATList* DeleteClause(SATList* s)
{
    SATList* c_tmp = s;
    SATNode* l;
    while(s->head)                     // ��ɾ���Ӿ�����������
    {
        l = s->head;
        s->head = s->head->next;
        free(l);
    }
    s = s->next;
    free(c_tmp);                        // ��ɾ�����Ӿ�
    return s;
}

SATList* DeleteLiteral(SATList* s, int var)
{
    SATNode *l = s->head, *l_tmp;

    // �����һ������
    if(l->data == -var)                  // ����Ԫ
    {
        l_tmp = s->head->next;
        free(l);
        s->head = l_tmp;
        return s;
    }
    else if(l->data == var) return NULL; // ����Ԫ

    // ѭ�����������������
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
    int idx = abs(s->head->data) - 1;   // ���=����ֵ-1
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
        else    printf("��\n");
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
	int* count, i, MaxWord, max, re; //count��¼ÿ�����ֳ��ִ���,MaxWord��¼����������������
	count = (int*)malloc(sizeof(int) * (boolCount * 2 + 1));
FIND:	while (tp != NULL && isUnitClause(tp->head) == 0) tp = tp->next;  //�ҵ����еĵ��Ӿ�
	if (tp != NULL)
	{
		// ios_base::sync_with_stdio(false);
		// cout<<"���ݴ�����,���Ժ�.....\r";
		// printf("����������,���Ժ�......\r");
		//���Ӿ�����
		if (tp->head->data > 0) value[tp->head->data] = 1;
		else value[-tp->head->data] = 0;
		re = tp->head->data;
		for (lp = cnf; lp != NULL; lp = sp)
		{
			sp = lp->next;

			//���Һ��к������ֵľ���
			for (dp = lp->head; dp != NULL; dp = dp->next)
			{
				if (dp->data == re)
				{
					removeClause(lp, cnf);  //ɾ���Ӿ䣬��ʽ��
					break;
				}
				if (dp->data == -re)
				{
					removeNode(dp, lp->head);  //ɾ�����֣����Ӿ�
					break;
				}
			}
		}
		//���򻯹���򻯺�
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
		// cout<<"������,���Ժ�........\r";
		// printf("������,���Ժ�........\r");
		goto FIND;  //������
	}
	for (i = 0; i <= boolCount * 2; i++) count[i] = 0;  //��ʼ��

	//�����Ӿ��и����ֳ��ִ���
	for (lp = cnf; lp != NULL; lp = lp->next)
	{
		for (dp = lp->head; dp != NULL; dp = dp->next)
		{
			if (dp->data > 0) count[dp->data]++;
			else count[boolCount - dp->data]++;
		}
	}
	max = 0;

	//�ҵ����ִ�������������
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
		//��û�г���������,�ҵ����ִ������ĸ�����
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
	if (DPLL(tp, value) == 1) return 1;  //�ڵ�һ��֧������
	destroyClause(tp);
	lp = (SATList*)malloc(sizeof(SATList));
	lp->head = (SATNode*)malloc(sizeof(SATNode));
	lp->head->data = -MaxWord;
	lp->head->next = NULL;
	lp->next = NULL;
	addClause(lp, cnf);
	re = DPLL(cnf, value); //���ݵ�ִ�з�֧���Եĳ�̬������һ��֧
	destroyClause(cnf);
	return re;
}


































































































































bool DPLL(HeadNode* L, int* book){
    int SC;//�洢���Ӿ�(SingleClause����д)
    //cout << ++TestNum << endl;
    //printList(L);
    while(SC = isHaveSingleClause(L)){
        //cout << "2-" << TestNum << " ����ѭ��Ҫɾ����Ϊ:" << SC << endl;
        if(SC > 0) book[SC] = 1;
        else if(SC < 0) book[0-SC] = -1;//���磺book[-(-2)] = -1��ʾ2����ı�Ԫȡ��ֵ����-2
        SimplifyCnf(L, SC);//���ݵ��Ӿ䴫�����Լ򻯵��Ӿ�
       //printList(L);
        if(isemptyCnf(L)) return TRUE;
        else if(isHaveEmptyClause(L)) return FALSE;
    }
    //int v = SelectWord(L);
    int v = SelectWord2(L);//��������Ӿ�����ѡȡ�������ѡȡ��Ԫ
    //cout << "���ѡȡ�ı�ԪΪ��" << v << endl;
    HeadNode* temL = CopyList(L);
    if(DPLL(merge(L, v), book)) return TRUE;
    bool result = DPLL(merge(temL, 0-v), book);
    //ɾ��temL�����ݿռ�
    FreeList(temL);
    return result;
}

bool NewDPLL(HeadNode* L, int* book){//�ǵݹ�汾DPLL�㷨
    stack<HeadNode*> S;
    HeadNode* ListL[10000] = {nullptr}; int i = 0;//ListL������¼ÿ�θı������������
    HeadNode* temL = nullptr;
    int v[10000]; int val;
    S.push(L);
    while(!S.empty()){
        while((L = S.top()) && (val = SingleSpread(L, book)) == NOMAL){
            //cout << "ѭ����ʼ" << endl; printList(L);
            temL = CopyList(L);
            ListL[i] = temL;
            v[i] = SelectWord2(L);
            //cout << "ѡȡ�ı�ԪΪ��" << v[i] << endl;
            L = merge(L, v[i]);
            S.push(L);i++;
        }
        //printList(L); cout << "ѭ������" << endl;
        if(val == TRUE) return TRUE;
        S.pop();i--;
        //cout << "�˴��ı�ԪΪ��" << v[i] << endl;
        FreeList(L);
        //cout << "ջ�Ĵ�СΪ" << S.size() << endl;
        if(!S.empty()){
            L = ListL[i]; S.pop();
            S.push(merge(L, -v[i]));
        }
    }
    return FALSE;
}

int SingleSpread(HeadNode* L, int* book){
    int SC;//�洢���Ӿ�(SingleClause����д)
    //cout << ++TestNum << endl;
    //printList(L);
    while(SC = isHaveSingleClause(L)){
        //cout << "2-" << TestNum << " ����ѭ��Ҫɾ����Ϊ:" << SC << endl;
        if(SC > 0) book[SC] = 1;
        else if(SC < 0) book[0-SC] = -1;//���磺book[-(-2)] = -1��ʾ2����ı�Ԫȡ��ֵ����-2
        SimplifyCnf(L, SC);//���ݵ��Ӿ䴫�����Լ򻯵��Ӿ�
       //printList(L);
        if(isemptyCnf(L)) return TRUE;
        else if(isHaveEmptyClause(L)) return FALSE;
    }
    return NOMAL;
}

//L�д洢�ĺ�����ʽ�Ƿ��е��Ӿ䣨ֻ����һ�����ֵ��Ӿ�������Ӿ䣩
//������е��Ӿ䣬�򷵻ص��Ӿ��ֵ
//��������е��Ӿ䣬�򷵻�0
int isHaveSingleClause(HeadNode* L){
    HeadNode* _pH = L->down;
    while(_pH){
        if(_pH->num == 1) return _pH->right->value;
        _pH = _pH->down;
    }
    return 0;
}

//���ݵ��Ӿ�SC���л���ʽL��������SC���Ӿ�ֱ��ȥ��������-SC���Ӿ���ȥ��-SC�������
void SimplifyCnf(HeadNode* L, int SC){
    HeadNode* _pH = L->down;
    HeadNode* _fpH = L;//��¼֮ǰ�������Ľ��
    int flag;
    while(_pH){
        DataNode* _p = _pH->right;
        DataNode* _fp = _p;
        flag = 0;
        while(_p){
            flag = 0;
            if(_p->value == SC){//ȥ������Ӿ䣨ɾ��һ�У�
                _fpH->down = _pH->down;
                _p = _pH->right;
                while(_p){
                    _fp = _p;
                    _p = _p->next;
                    delete _fp;
                }
                L->num--;
                flag = 1;
                break;//������һ��
            }
            else if(_p->value == 0-SC){//ȥ��������֣�ɾ��һ���㣬��Ҫ���ǵ�һ���ڵ�����������
                if(_pH->right == _p){
                    flag = 2;//��һ�����ͳ���Ŀ�����ݣ���Ҫɾ��
                    _pH->right = _p->next;
                    _pH->num--;
                    //cout << "��һ����㴦������ɾ����num��ֵΪ��" << _pH->num << endl;
                }
                else{
                    flag = 3;
                    _fp->next = _p->next;
                    _pH->num--;
                }
            }
            if(!flag){//û����Ҫɾ���Ľڵ�
                if(_fp != _p) _fp = _p;
                _p = _p->next;
            }
            else if(flag == 2){//ɾ���Ľ��Ϊ��һ���ڵ���������
                _p = _pH->right;
                _fp = _p;
            }
            else if(flag == 3){//ɾ���Ľڵ㲻�ǵ�һ�������м�
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

//L�д洢�ķ�ʽ�Ƿ�Ϊ�շ�ʽ
bool isemptyCnf(HeadNode* L){
    if(L->num) return FALSE;
    else return TRUE;
}

//�жϷ�ʽ���Ƿ��п��Ӿ�
bool isHaveEmptyClause(HeadNode* L){
    HeadNode* _pH = L->down;
    while(_pH){
        if(_pH->num == 0) return TRUE;
        _pH = _pH->down;
    }
    return FALSE;
}

//��v��Ϊһ�����Ӿ�ϲ�����ʽL�У����ϲ���ķ�ʽ��Ϊ����ֵ
HeadNode* merge(HeadNode* L, int v){
    HeadNode* pH = new HeadNode; pH->num++;
    pH->down = L->down;
    L->down = pH;
    DataNode* p = new DataNode; p->value = v;
    pH->right = p; p->next = nullptr;
    L->num++;
    //cout << "merge��֮����ӵ�vΪ��" << L->down->right->value << endl;
    return L;
}

//ֱ�ӷ��ص�һ�����ּ���
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
    cout << "��ʽΪ�ռ����޷�ѡ�����ַ���" << endl;
    return 0;
}

int SelectWord2(HeadNode* L){//����Ӿ�����
    HeadNode* _pH = L->down;
    int _min, ans = 0;
    if(!_pH){cout << "��ʽΪ�ռ����޷�ѡ�����ַ���" << endl; return 0;}
    _min = _pH->num; ans = _pH->right->value;
    while(_pH){
        if(_pH->num != 0 && _pH->num < _min) ans = _pH->right->value;
        _pH = _pH->down;
    }
    return ans;
}

//�����ڲ���ʹ��
void printList(HeadNode* L){
    HeadNode* _pH = L->down;
    int i = 1;
    while(_pH){
        cout << "��" << i++ << "�У�" << _pH->num;
        DataNode* _p = _pH->right;
        while(_p){
            cout << "->" << _p->value;
            _p = _p->next; 
        }
        cout << endl;
        _pH = _pH->down;
    }
}

//��L��ȫ�����ݶ�������temL�У������ṹ��cnfparser����������ͬ
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
            _p->value = tep;//����ͷ�巨��������
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
    //�ͷŵ�L����������ڴ�ռ�
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
//��֤����DPLL�㷨���ɵ��ļ��Ƿ���ȷ
bool isCorrect(string& filename){
    HeadNode* L = CnfParser(filename);
    HeadNode* ordL = CopyList(L);

    int _FunNum = FunNum>1000? FunNum: 1000;
    int *book = new int[_FunNum];
    memset(book, 0, sizeof(int)*_FunNum);

    int isTrue = NewDPLL(L, book);
    if(!isTrue){cout << ".cnf�ļ���������"; exit(0);}
    else{
        if(verification(ordL, book)) return TRUE;
        else return FALSE;
    }
}
/*
�����ļ�����������L��ͬʱ����һ�ݲ���ı��ordL;������ı��L��
ִ��DPLL�㷨������.res�ļ�
���DPLL�㷨����Ϊ�٣�ֱ���˳����У�Ϊ�������һ��
ֱ�ӱ���ordL�ṹ������book��Ӧ�����ֵ�ֵ
�����һ���Ӿ�����е����ֶ��������㣬��ô�ý����������
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