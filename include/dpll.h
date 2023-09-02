#include"def.h"
extern int FunNum;

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



// extern int FunNum;
// bool verification(HeadNode* ordL, int* book);
// //��֤����DPLL�㷨���ɵ��ļ��Ƿ���ȷ
// bool isCorrect(string& filename){
//     HeadNode* L = CnfParser(filename);
//     HeadNode* ordL = CopyList(L);

//     int _FunNum = FunNum>1000? FunNum: 1000;
//     int *book = new int[_FunNum];
//     memset(book, 0, sizeof(int)*_FunNum);

//     int isTrue = NewDPLL(L, book);
//     if(!isTrue){cout << ".cnf�ļ���������"; exit(0);}
//     else{
//         if(verification(ordL, book)) return TRUE;
//         else return FALSE;
//     }
// }
// /*
// �����ļ�����������L��ͬʱ����һ�ݲ���ı��ordL;������ı��L��
// ִ��DPLL�㷨������.res�ļ�
// ���DPLL�㷨����Ϊ�٣�ֱ���˳����У�Ϊ�������һ��
// ֱ�ӱ���ordL�ṹ������book��Ӧ�����ֵ�ֵ
// �����һ���Ӿ�����е����ֶ��������㣬��ô�ý����������
// */
// bool verification(HeadNode* ordL, int* book){
//     HeadNode* _pH = ordL->down;
//     while(_pH){
//         DataNode* _p = _pH->right;
//         while(_p){
//             if(book[abs(_p->value)]*_p->value > 0) break;
//             _p = _p->next;
//         }
//         if(!_p) return FALSE;
//         _pH = _pH->down;
//     }
//     return TRUE;
// }