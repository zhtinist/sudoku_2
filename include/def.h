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
////针对数独的dpll
//十字链表结构体
typedef struct SATNode{
	int data;  //数据域
	SATNode* next;
}SATNode;
typedef struct SATList {
	SATNode* head;  //表头
	SATList* next;
}SATList;

//函数声明
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
SATList* AddClause(SATList* s, int var);        // 增加单子句
SATList* IsUnitClause(SATList* s);              // 判断是否存在单子句
SATList* CopyS(SATList* s);                     // 复制表
SATList* CopyClause(SATList* s);                // 复制一个子句
SATList* DeleteClause(SATList* s);              // 删除一个子句
SATList* DeleteLiteral(SATList* s, int var);    // 删除负变元
status Print(SATList* s);                          // 打印表
status IsEmptyClause(SATList* s);                  // 判断是否存在空子句
status EvaluateClause();                              // 评估句子真假状态
status RecordTruth(SATList* s, int* truth_table);  // 记录单子句中元素的真值
status RemoveVar(SATList* s, int var);             // 删除变元所在子句与负变元
int PickVar(SATList* s);                    



////针对助教算例的高性能dpll
typedef struct DataNode{
    int value = 0;
    struct DataNode* next;
}DataNode;

typedef struct HeadNode{
    int num = 0;//多了一个统计元素个数的量
    struct HeadNode* down;//头结点向下
    struct DataNode* right;//同一个子句中结点向右指针
}HeadNode;
HeadNode* CnfParser(string& filename);
void display();
bool DPLL(HeadNode* L, int* book);//核心算法部分
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