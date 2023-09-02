#include"def.h"

/*
* ��������: WriteFile
* ���ܲ���: int,int,int[]
* ��������: �����н��������ͬ���ļ����ļ���չ��Ϊ.res,����ɹ�����1��ʧ�ܷ���0
* ����ֵ: int
*/
int WriteFile(int result, double time, int value[])
{
	FILE* fp;
	int i;
	for (i = 0; fileName[i] != '\0'; i++)
	{
		//�޸���չ��
		if (fileName[i] == '.' && fileName[i + 4] == '\0')
		{
			fileName[i + 1] = 'r';
			fileName[i + 2] = 'e';
			fileName[i + 3] = 's';
			break;
		}
	}
	if (!(fp=fopen(fileName, "w"))) {
		printf("�ļ���ʧ��!\n");
		return 0;
	}
	fprintf(fp, "s %d\nv ", result);  //�����
	if (result == 1)
	{
		//�����ֵ
		for (i = 1; i <= boolCount; i++)
		{
			if (value[i] == 1) fprintf(fp, "%d ", i);
			else fprintf(fp, "%d ", -i);
		}
	}
	fprintf(fp, "\nt %lf", time * 1000);  //����ʱ��/����
	fclose(fp);
	return 1;
}

int WriteFileAgain(int result, double time, int value[])
{
	FILE* fp;
	int i;
	for (i = 0; fileName[i] != '\0'; i++)
	{
		//�޸���չ��
		if (fileName[i] == '.' && fileName[i + 4] == '\0')
		{
			fileName[i + 1] = 'r';
			fileName[i + 2] = 'e';
			fileName[i + 3] = 's';
			break;
		}
	}
	if (!(fp=fopen(fileName, "a"))) {
		printf("�ļ���ʧ��!\n");
		return 0;
	}
	fprintf(fp, "\ns %d\nv ", result);  //�����
	if (result == 1)
	{
		//�����ֵ
		for (i = 1; i <= boolCount; i++)
		{
			if (value[i] == 1) fprintf(fp, "%d ", i);
			else fprintf(fp, "%d ", -i);
		}
	}
	if(result!=0)
	fprintf(fp, "\nt %lf", time * 1000);  //����ʱ��/����
	fclose(fp);
	return 1;
}



void OutFileFun1(string _PATH, bool suc, int* book, int _Ctime, int FunNum, int cod){
    ofstream op(_PATH);
    if(!op){
        cout << "OutFile can not open!" << endl;
        exit(0);
    }
    op << "s " << suc << endl;//���
    if(suc){
        op << "v";
        for(int i = 1, k = 1; i <= FunNum; i++){
            op << " " << book[i]*i;
            k++;
            if(k == 10) {op<<endl; k = 1;}
        }
		op << endl;
    }
    if(cod == 1|| cod ==2) op << "t " << _Ctime << "ms";
    op.close();

}