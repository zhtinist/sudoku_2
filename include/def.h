#ifndef def_H
#define def_H
#include<bits/stdc++.h>
#include <unistd.h>
#include<windows.h>
#define _CRT_SECURE_NO_DEPRECATE

#define OK 1
#define ERROR 0
#define FOUND 1
#define NOTFOUND 0
#define NOANSWER 0
#define YES 1
#define NOMAL -1
#define ROW 9
#define COL 9
#define NoAnwser -1
#define NO 0
using namespace std;
typedef int status;
////���������dpll
//ʮ������ṹ��
typedef struct SATNode{
	int data;  //������
	SATNode* next;
}SATNode;
typedef struct SATList {
	SATNode* head;  //��ͷ
	SATList* next;
}SATList;

//��������
int cnfmaker(char chess[],char *fileName);
int ReadFile(SATList*& cnf);
void destroyClause(SATList*& cnf);
int isUnitClause(SATNode* cnf);
// bool las_Vegas(int n);
int evaluateClause(SATNode* cnf, int v[]);
int removeClause(SATList*& cnf, SATList*& root);
int removeNode(SATNode*& cnf, SATNode*& head);
int addClause(SATList* cnf, SATList*& root);
int emptyClause(SATList* cnf);
int DPLL(SATList*& cnf, int value[]);
void CopyClause(SATList*& a, SATList* b);
int WriteFile(int result, double time, int value[]);
int WriteFileAgain(int result, double time, int value[]);
// int SolvePuzzle(int chess[], int size);
int resort(int x);
int disresort(int x);
int num_position(char* input,int *output);
void CreateSudoku(int a[]);
int randnum(int low,int high);
//
status DpllSolver(SATList* f, int* truth_table);
SATList* AddClause(SATList* s, int var);        // ���ӵ��Ӿ�
SATList* IsUnitClause(SATList* s);              // �ж��Ƿ���ڵ��Ӿ�
SATList* CopyS(SATList* s);                     // ���Ʊ�
SATList* CopyClause(SATList* s);                // ����һ���Ӿ�
SATList* DeleteClause(SATList* s);              // ɾ��һ���Ӿ�
SATList* DeleteLiteral(SATList* s, int var);    // ɾ������Ԫ
status Print(SATList* s);                          // ��ӡ��
status IsEmptyClause(SATList* s);                  // �ж��Ƿ���ڿ��Ӿ�
status EvaluateClause();                              // �����������״̬
status RecordTruth(SATList* s, int* truth_table);  // ��¼���Ӿ���Ԫ�ص���ֵ
status RemoveVar(SATList* s, int var);             // ɾ����Ԫ�����Ӿ��븺��Ԫ
int PickVar(SATList* s);                    



////������������ĸ�����dpll
typedef struct DataNode{
    int value = 0;
    struct DataNode* next;
}DataNode;

typedef struct HeadNode{
    int num = 0;//����һ��ͳ��Ԫ�ظ�������
    struct HeadNode* down;//ͷ�������
    struct DataNode* right;//ͬһ���Ӿ��н������ָ��
}HeadNode;
HeadNode* CnfParser(string& filename);
void display();
bool DPLL(HeadNode* L, int* book);//�����㷨����
bool NewDPLL(HeadNode* L, int* book);
int SingleSpread(HeadNode* L, int* book);
int isHaveSingleClause(HeadNode* L);
void SimplifyCnf(HeadNode* L, int SC);
bool isemptyCnf(HeadNode* L);
bool isHaveEmptyClause(HeadNode* L);
HeadNode* merge(HeadNode* L, int v);
int SelectWord(HeadNode* L);
int SelectWord2(HeadNode* L);
void OutFileFun1(string _PATH, bool suc, int* book, int _Ctime, int FunNum, int cod);
void printList(HeadNode* L);
HeadNode* CopyList(HeadNode* L);
void FreeList(HeadNode* L);



int Digit(int a[][COL], int i, int j);
void randomFirstRow(int a0[], int n);
void createSudoku(int a[][COL]);
void createStartinggrid(const int a[][COL], int b[][COL], int numDigits);
void print(const int a[][COL]);
string ToCnf(int a[][COL],int holes);
string createSudokuToFile(int holes, int array[ROW][COL]);

void CoreFun(HeadNode* L, string& filename, int FunNum, int cod, int array[ROW][COL]);
bool isCorrect(string& filename);
#endif