#include"def.h"
/*
 * ��������: ReadFile
 * ���ܲ���: SATList*&
 * ��������: ���ļ�ָ��fp���û�ָ�����ļ�������ȡ�ļ����ݱ��浽���������У���ȡ�ɹ�����1��ʧ�ܷ���0
 * ����ֵ: int
 */
int FunNum;
int ReadFile(SATList*& cnf,char* fileName)
{
	FILE* fp;
	char ch;
	int number, i;
	SATList* lp;
	SATNode* tp;
	if (!(fp=fopen(fileName, "r"))) {
		printf("�ļ���ʧ��!\n");
		return 0;
	}
	while ((ch = getc(fp)) == 'c') {
		while ((ch = getc(fp)) != '\n')
			continue;           //��ȥһ����
	}   //���е��ˣ��Ѿ���ȡ���ַ�p
	getc(fp); getc(fp); getc(fp); getc(fp); //��ȥcnf������ĸ
	fscanf(fp, "%d", &boolCount);    //p��ĵ�1����ֵ�ǲ�����Ԫ����
	fscanf(fp, "%d", &clauseCount);  //p��ĵ�2����ֵ���Ӿ�����
	cnf = (SATList*)malloc(sizeof(SATList));
	cnf->next = NULL;
	cnf->head = (SATNode*)malloc(sizeof(SATNode));
	cnf->head->next = NULL;
	lp = cnf;
	tp = cnf->head;

	//��������ΪclauseCount���Ӿ�, iΪ������
	for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head)
	{
		fscanf(fp, "%d", &number);
		for (; number != 0; tp = tp->next)
		{
			tp->data = number;  //������ֵ
			tp->next = (SATNode*)malloc(sizeof(SATNode));  //�����½��
			fscanf(fp, "%d", &number);
			if (number == 0) tp->next = NULL;
		}
		lp->next = (SATList*)malloc(sizeof(SATList));  //�����±�
		lp->next->head = (SATNode*)malloc(sizeof(SATNode));
		if (i == clauseCount - 1)
		{
			lp->next = NULL;
			break;
		}
	}

	fclose(fp);
	return 1;
}





















HeadNode* CnfParser(string& filename){//�����ļ�������ͷ���ָ��L
    string PATH = filename;
    ifstream fp(PATH);//ע�⣺����\���ű���Ϊת���ַ���������Ҫ�����˷���
    if(!fp){cout << "File can not open"; system("pause");return nullptr;}
    char ch;
    char exp[105];//exp:��cnf�ļ��Ľ���explain
    fp >> ch;
    while(ch != 'p'){
        fp.getline(exp, 100);
        //ע�⣺�˴���expֻ������c-string�����飩��������string
        //��ϸ����:n:Pointer to an array of characters where extracted characters are stored as a c-string.
        fp >> ch;
    }
    string cnf; int ClauseNum;//�ֱ�洢CNF����Ԫ�������Ӿ������
    fp >> cnf >> FunNum >> ClauseNum;
    //����������cout << ClauseNum << " " << FunNum << endl;
    //����ѭ�������е��Ӿ���뵽��ƺõ����ݽṹ��
    HeadNode* L = new HeadNode;//LΪHeadNode����ͷ���
    L->num = ClauseNum;//�־������Ҳ�����ж����У�
    HeadNode* pH = new HeadNode; L->down = pH; pH->down = nullptr;//L��num��ʾ�ж�����
    for(int i = 1; i <= ClauseNum; i++){
        int tep;
        fp >> tep;
        DataNode* p = new DataNode;
        p->value = tep; pH->right = p; pH->num++; p->next = nullptr;
        fp >> tep;
        while(tep){
            p = new DataNode;
            p->value = tep;//����ͷ�巨��������
            p->next = pH->right;
            pH->right = p;
            pH->num++;
            fp >> tep;
        }
        if(i != ClauseNum){
            pH = new HeadNode;
            pH->down = L->down;
            L->down = pH;
        }
        //fp.get();//get�����з�
    }
    fp.close();//�ر��ļ���
    
    //���������cnf�ļ����������ʾ�����ڽ��д�������
    /*HeadNode* _pH = L->down;

    while(_pH){
        DataNode* _p = _pH->right;
        while(_p->next){
            cout << _p->value << " ";
            _p = _p->next;
        }
        cout << _p->value << endl;
        _pH = _pH->down;
    }
    */

    return L;
}