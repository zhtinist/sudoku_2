#include"def.h"
/*
 * 函数名称: ReadFile
 * 接受参数: SATList*&
 * 函数功能: 用文件指针fp打开用户指定的文件，并读取文件内容保存到给定参数中，读取成功返回1，失败返回0
 * 返回值: int
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
		printf("文件打开失败!\n");
		return 0;
	}
	while ((ch = getc(fp)) == 'c') {
		while ((ch = getc(fp)) != '\n')
			continue;           //弃去一整行
	}   //运行到此，已经读取了字符p
	getc(fp); getc(fp); getc(fp); getc(fp); //弃去cnf三个字母
	fscanf(fp, "%d", &boolCount);    //p后的第1个数值是布尔变元数量
	fscanf(fp, "%d", &clauseCount);  //p后的第2个数值是子句数量
	cnf = (SATList*)malloc(sizeof(SATList));
	cnf->next = NULL;
	cnf->head = (SATNode*)malloc(sizeof(SATNode));
	cnf->head->next = NULL;
	lp = cnf;
	tp = cnf->head;

	//创建数量为clauseCount的子句, i为计数器
	for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head)
	{
		fscanf(fp, "%d", &number);
		for (; number != 0; tp = tp->next)
		{
			tp->data = number;  //数据域赋值
			tp->next = (SATNode*)malloc(sizeof(SATNode));  //开辟新结点
			fscanf(fp, "%d", &number);
			if (number == 0) tp->next = NULL;
		}
		lp->next = (SATList*)malloc(sizeof(SATList));  //开辟新表
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





















HeadNode* CnfParser(string& filename){//解析文件，返回头结点指针L
    string PATH = filename;
    ifstream fp(PATH);//注意：由于\符号本身为转义字符，所以需要两个此符号
    if(!fp){cout << "File can not open"; system("pause");return nullptr;}
    char ch;
    char exp[105];//exp:对cnf文件的解释explain
    fp >> ch;
    while(ch != 'p'){
        fp.getline(exp, 100);
        //注意：此处的exp只能是用c-string（数组），不能用string
        //详细解释:n:Pointer to an array of characters where extracted characters are stored as a c-string.
        fp >> ch;
    }
    string cnf; int ClauseNum;//分别存储CNF、变元个数、子句个数。
    fp >> cnf >> FunNum >> ClauseNum;
    //测试用例：cout << ClauseNum << " " << FunNum << endl;
    //下面循环将所有的子句读入到设计好的数据结构中
    HeadNode* L = new HeadNode;//L为HeadNode结点的头结点
    L->num = ClauseNum;//字句个数（也就是有多少行）
    HeadNode* pH = new HeadNode; L->down = pH; pH->down = nullptr;//L中num表示有多少行
    for(int i = 1; i <= ClauseNum; i++){
        int tep;
        fp >> tep;
        DataNode* p = new DataNode;
        p->value = tep; pH->right = p; pH->num++; p->next = nullptr;
        fp >> tep;
        while(tep){
            p = new DataNode;
            p->value = tep;//采用头插法建立链表
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
        //fp.get();//get掉换行符
    }
    fp.close();//关闭文件流
    
    //将解析后的cnf文件进行输出表示，用于进行代码块测试
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