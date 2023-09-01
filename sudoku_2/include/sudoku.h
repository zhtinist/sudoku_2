#include"def.h"
#include"create_new_game.h"

/*
* 函数名称: CreateBinary
* 接受参数: int
* 函数功能: 按照指定大小生成棋盘
* 返回值: void
*/
void CreateSudoku(int a[]){
	printf("         / \\ / \\ / \\ / \\ / \\  \n");
	printf("        | %d | %d | %d | %d | %d |  \n",a[1],a[2],a[3],a[4],a[5]);
	printf("       / \\ / \\ / \\ / \\ / \\ / \\  \n");
	printf("      | %d | %d | %d | %d | %d | %d |  \n",a[6],a[7],a[8],a[9],a[10],a[11]);
	printf("     / \\ / \\ / \\ / \\ / \\ / \\ / \\  \n");
	printf("    | %d | %d | %d | %d | %d | %d | %d |  \n",a[12],a[13],a[14],a[15],a[16],a[17],a[18]);
	printf("   / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\  \n");
	printf("  | %d | %d | %d | %d | %d | %d | %d | %d |  \n",a[19],a[20],a[21],a[22],a[23],a[24],a[25],a[26]);
	printf(" / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\  \n");
	printf("| %d | %d | %d | %d | %d | %d | %d | %d | %d |  \n",a[27],a[28],a[29],a[30],a[31],a[32],a[33],a[34],a[35]);
	printf(" \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ /  \n");
	printf("  | %d | %d | %d | %d | %d | %d | %d | %d |  \n",a[36],a[37],a[38],a[39],a[40],a[41],a[42],a[43]);
	printf("   \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ /  \n");
	printf("    | %d | %d | %d | %d | %d | %d | %d |  \n",a[44],a[45],a[46],a[47],a[48],a[49],a[50]);
	printf("     \\ / \\ / \\ / \\ / \\ / \\ / \\ /  \n");
	printf("      | %d | %d | %d | %d | %d | %d |  \n",a[51],a[52],a[53],a[54],a[55],a[56]);
	printf("       \\ / \\ / \\ / \\ / \\ / \\ /  \n");
	printf("        | %d | %d | %d | %d | %d |  \n",a[57],a[58],a[59],a[60],a[61],a[62]);
	printf("         \\ / \\ / \\ / \\ / \\ /  \n");
}


/*
cnfmaker 根据读入的棋盘生成对应的约束条件cnf
*/
int cnfmaker(char chess[],char* fileName){
//	char SE[88];
//	printf("请输入待解决蜂窝数独\n");
//	scanf("%s",SE);
	SATList* cnf = NULL, * lp;
	SATNode* dp;
	int* remember, i, j, k, rol;
	char name[200];
	int a[10]={0,5,6,7,8,9,8,7,6,5}; 
	int b[9][9]={{0,0,0,0,0,0,0,0,0},
				 {-1,0,1,0,0,0,0,0,0},
				 {-2,-1,0,1,2,0,0,0,0},
				 {-3,-2,-1,0,1,2,3,0,0},
				 {-4,-3,-2,-1,0,1,2,3,4},
				 {-3,-2,-1,0,1,2,3,0,0},
				 {-2,-1,0,1,2,0,0,0,0},
				 {-1,0,1,0,0,0,0,0,0},
				 {0,0,0,0,0,0,0,0,0}
				};
	int c[10]={0,1,3,5,7,9,7,5,3,1};			
	int d[10]={0,5,11,18,26,35,43,50,56,61};
	int num=0;
	FILE* fp;
	if(!(fp=fopen(fileName,"w"))){
		printf("文件打开错误!");
		return ERROR; 
	}
	for(i=5;i<66;i++){
		if(chess[i]!='0') num++;
	}
	fprintf(fp,"p cnf %d %d\n",549,7468+num);
	int receive[66]={0};
	num_position(chess,receive);
	for(i=0;receive[i]!=0;i++){
		fprintf(fp,"%d %d\n",resort(receive[i]),0);
	}
	//基本条件
	for(i=1;i<=9;i++){
		for(j=1;j<=a[i];j++){
			for(k=1;k<=9;k++){
				fprintf(fp,"%d ",resort(i*100+j*10+k));
			}
			fprintf(fp,"%d\n",0);
		}
	}
	for(i=1;i<=9;i++){
		for(j=1;j<=a[i];j++){
			for(k=1;k<=8;k++){
				for(int m=k+1;m<=9;m++){
					fprintf(fp,"%d %d %d\n",-resort(i*100+j*10+k),-resort(i*100+j*10+m),0);
				}
			}
		}
	}
	//
	for(i=1;i<=9;i++){
		for(j=1;j<=c[i];j++){
			for (k=1;k<=a[i];k++){
				fprintf(fp,"%d ",resort(i*100+k*10+5+b[i-1][j-1]));
			}
			fprintf(fp,"%d\n",0);
		}
		int m,n,l;
		for(m=1;m<=a[i]-1;m++){
			for(n=m+1;n<=a[i];n++){
				for(l=1;l<=9;l++){
					fprintf(fp,"%d %d ",-resort(i*100+m*10+l),-resort(i*100+n*10+l));
					fprintf(fp,"%d\n",0);
				}
			}
		}
	}
	//约束条件
	int cons1[10][2]={{1,6},{2,6},{3,6},{4,6},{2,7},{3,7},{4,7},{3,8},{4,8},{4,9}};
	int cons_1[5]={110,120,130,140,150};
	for(i=0;i<10;i++){
		for(j=0;j<2;j++){
			for(k=0;k<5;k++){
				fprintf(fp,"%d ",resort(cons_1[k]+cons1[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons2[6][2]={{2,7},{2,8},{3,7},{3,8},{1,7},{3,9}};
	int cons_2[6]={210,220,230,240,250,260};
	for(i=0;i<6;i++){
		for(j=0;j<2;j++){
			for(k=0;k<6;k++){
				fprintf(fp,"%d ",resort(cons_2[k]+cons2[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons3[3][2]={{1,8},{2,8},{2,9}};
	int cons_3[7]={310,320,330,340,350,360,370};
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			for(k=0;k<7;k++){
				fprintf(fp,"%d ",resort(cons_3[k]+cons3[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons4[2]={1,9};
	int cons_4[8]={410,420,430,440,450,460,470,480};
	for(i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<8;k++){
				fprintf(fp,"%d ",resort(cons_4[k]+cons4[j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	for(i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<8;k++){
				fprintf(fp,"%d ",resort(cons_4[k]+200+cons4[j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			for(k=0;k<7;k++){
				fprintf(fp,"%d ",resort(cons_3[k]+400+cons3[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	for(i=0;i<6;i++){
		for(j=0;j<2;j++){
			for(k=0;k<6;k++){
				fprintf(fp,"%d ",resort(cons_2[k]+600+cons2[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	for(i=0;i<10;i++){
		for(j=0;j<2;j++){
			for(k=0;k<5;k++){
				fprintf(fp,"%d ",resort(cons_1[k]+800+cons1[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}

	//左斜
	fprintf(fp,"%d %d %d %d %d %d\n",resort(515),resort(415),resort(315),resort(215),resort(115),0);
	int markl2[6]={610,520,420,320,220,120};
	int markl_2[3]={4,5,6};
	for(i=0;i<3;i++){
		for(j=0;j<6;j++){
			fprintf(fp,"%d ",resort(markl2[j]+markl_2[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markl3[7]={710,620,530,430,330,230,130};
	int markl_3[5]={3,4,5,6,7};
	for(i=0;i<5;i++){
		for(j=0;j<7;j++){
			fprintf(fp,"%d ",resort(markl3[j]+markl_3[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markl4[8]={810,720,630,540,440,340,240,140};
	int markl_4[7]={2,3,4,5,6,7,8};
	for(i=0;i<7;i++){
		for(j=0;j<8;j++){
			fprintf(fp,"%d ",resort(markl4[j]+markl_4[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markl5[9]={910,820,730,640,550,450,350,250,150};
	int markl_5[9]={1,2,3,4,5,6,7,8,9};
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			fprintf(fp,"%d ",resort(markl5[j]+markl_5[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markl6[8]={920,830,740,650,560,460,360,260};
	for(i=0;i<7;i++){
		for(j=0;j<8;j++){
			fprintf(fp,"%d ",resort(markl6[j]+markl_4[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markl7[7]={930,840,750,660,570,470,370};
	for(i=0;i<5;i++){
		for(j=0;j<7;j++){
			fprintf(fp,"%d ",resort(markl7[j]+markl_3[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markl8[6]={940,850,760,670,580,480};
	for(i=0;i<3;i++){
		for(j=0;j<6;j++){
			fprintf(fp,"%d ",resort(markl8[j]+markl_2[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	fprintf(fp,"%d %d %d %d %d %d\n",resort(955),resort(865),resort(775),resort(685),resort(595),0);
	//任两格不能填同一个数字约束（左斜）
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(510+i),-resort(410+i),0);
		fprintf(fp,"%d %d %d\n",-resort(510+i),-resort(310+i),0);
		fprintf(fp,"%d %d %d\n",-resort(510+i),-resort(210+i),0);
		fprintf(fp,"%d %d %d\n",-resort(510+i),-resort(110+i),0);
		fprintf(fp,"%d %d %d\n",-resort(410+i),-resort(310+i),0);
		fprintf(fp,"%d %d %d\n",-resort(410+i),-resort(210+i),0);
		fprintf(fp,"%d %d %d\n",-resort(410+i),-resort(110+i),0);
		fprintf(fp,"%d %d %d\n",-resort(310+i),-resort(210+i),0);
		fprintf(fp,"%d %d %d\n",-resort(310+i),-resort(110+i),0);
		fprintf(fp,"%d %d %d\n",-resort(210+i),-resort(110+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(610+i),-resort(520+i),0);
		fprintf(fp,"%d %d %d\n",-resort(610+i),-resort(420+i),0);
		fprintf(fp,"%d %d %d\n",-resort(610+i),-resort(320+i),0);
		fprintf(fp,"%d %d %d\n",-resort(610+i),-resort(220+i),0);
		fprintf(fp,"%d %d %d\n",-resort(610+i),-resort(120+i),0);
		fprintf(fp,"%d %d %d\n",-resort(520+i),-resort(420+i),0);
		fprintf(fp,"%d %d %d\n",-resort(520+i),-resort(320+i),0);
		fprintf(fp,"%d %d %d\n",-resort(520+i),-resort(220+i),0);
		fprintf(fp,"%d %d %d\n",-resort(520+i),-resort(120+i),0);
		fprintf(fp,"%d %d %d\n",-resort(420+i),-resort(320+i),0);
		fprintf(fp,"%d %d %d\n",-resort(420+i),-resort(220+i),0);
		fprintf(fp,"%d %d %d\n",-resort(420+i),-resort(120+i),0);
		fprintf(fp,"%d %d %d\n",-resort(320+i),-resort(220+i),0);
		fprintf(fp,"%d %d %d\n",-resort(320+i),-resort(120+i),0);
		fprintf(fp,"%d %d %d\n",-resort(220+i),-resort(120+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(710+i),-resort(620+i),0);
		fprintf(fp,"%d %d %d\n",-resort(710+i),-resort(530+i),0);
		fprintf(fp,"%d %d %d\n",-resort(710+i),-resort(430+i),0);
		fprintf(fp,"%d %d %d\n",-resort(710+i),-resort(330+i),0);
		fprintf(fp,"%d %d %d\n",-resort(710+i),-resort(230+i),0);
		fprintf(fp,"%d %d %d\n",-resort(710+i),-resort(130+i),0);
		fprintf(fp,"%d %d %d\n",-resort(620+i),-resort(530+i),0);
		fprintf(fp,"%d %d %d\n",-resort(620+i),-resort(430+i),0);
		fprintf(fp,"%d %d %d\n",-resort(620+i),-resort(330+i),0);
		fprintf(fp,"%d %d %d\n",-resort(620+i),-resort(230+i),0);
		fprintf(fp,"%d %d %d\n",-resort(620+i),-resort(130+i),0);
		fprintf(fp,"%d %d %d\n",-resort(530+i),-resort(430+i),0);
		fprintf(fp,"%d %d %d\n",-resort(530+i),-resort(330+i),0);
		fprintf(fp,"%d %d %d\n",-resort(530+i),-resort(230+i),0);
		fprintf(fp,"%d %d %d\n",-resort(530+i),-resort(130+i),0);
		fprintf(fp,"%d %d %d\n",-resort(430+i),-resort(330+i),0);
		fprintf(fp,"%d %d %d\n",-resort(430+i),-resort(230+i),0);
		fprintf(fp,"%d %d %d\n",-resort(430+i),-resort(130+i),0);
		fprintf(fp,"%d %d %d\n",-resort(330+i),-resort(230+i),0);
		fprintf(fp,"%d %d %d\n",-resort(330+i),-resort(130+i),0);
		fprintf(fp,"%d %d %d\n",-resort(230+i),-resort(130+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(720+i),0);
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(630+i),0);
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(540+i),0);
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(440+i),0);
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(340+i),0);
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(240+i),0);
		fprintf(fp,"%d %d %d\n",-resort(810+i),-resort(140+i),0);
		fprintf(fp,"%d %d %d\n",-resort(720+i),-resort(630+i),0);
		fprintf(fp,"%d %d %d\n",-resort(720+i),-resort(540+i),0);
		fprintf(fp,"%d %d %d\n",-resort(720+i),-resort(440+i),0);
		fprintf(fp,"%d %d %d\n",-resort(720+i),-resort(340+i),0);
		fprintf(fp,"%d %d %d\n",-resort(720+i),-resort(240+i),0);
		fprintf(fp,"%d %d %d\n",-resort(720+i),-resort(140+i),0);
		fprintf(fp,"%d %d %d\n",-resort(630+i),-resort(540+i),0);
		fprintf(fp,"%d %d %d\n",-resort(630+i),-resort(440+i),0);
		fprintf(fp,"%d %d %d\n",-resort(630+i),-resort(340+i),0);
		fprintf(fp,"%d %d %d\n",-resort(630+i),-resort(240+i),0);
		fprintf(fp,"%d %d %d\n",-resort(630+i),-resort(140+i),0);
		fprintf(fp,"%d %d %d\n",-resort(540+i),-resort(440+i),0);
		fprintf(fp,"%d %d %d\n",-resort(540+i),-resort(340+i),0);
		fprintf(fp,"%d %d %d\n",-resort(540+i),-resort(240+i),0);
		fprintf(fp,"%d %d %d\n",-resort(540+i),-resort(140+i),0);
		fprintf(fp,"%d %d %d\n",-resort(440+i),-resort(340+i),0);
		fprintf(fp,"%d %d %d\n",-resort(440+i),-resort(240+i),0);
		fprintf(fp,"%d %d %d\n",-resort(440+i),-resort(140+i),0);
		fprintf(fp,"%d %d %d\n",-resort(340+i),-resort(240+i),0);
		fprintf(fp,"%d %d %d\n",-resort(340+i),-resort(140+i),0);
		fprintf(fp,"%d %d %d\n",-resort(240+i),-resort(140+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(820+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(730+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(640+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(550+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(450+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(350+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(910+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(730+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(640+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(550+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(450+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(350+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(820+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(730+i),-resort(640+i),0);
		fprintf(fp,"%d %d %d\n",-resort(730+i),-resort(550+i),0);
		fprintf(fp,"%d %d %d\n",-resort(730+i),-resort(450+i),0);
		fprintf(fp,"%d %d %d\n",-resort(730+i),-resort(350+i),0);
		fprintf(fp,"%d %d %d\n",-resort(730+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(730+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(640+i),-resort(550+i),0);
		fprintf(fp,"%d %d %d\n",-resort(640+i),-resort(450+i),0);
		fprintf(fp,"%d %d %d\n",-resort(640+i),-resort(350+i),0);
		fprintf(fp,"%d %d %d\n",-resort(640+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(640+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(550+i),-resort(450+i),0);
		fprintf(fp,"%d %d %d\n",-resort(550+i),-resort(350+i),0);
		fprintf(fp,"%d %d %d\n",-resort(550+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(550+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(450+i),-resort(350+i),0);
		fprintf(fp,"%d %d %d\n",-resort(450+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(450+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(350+i),-resort(250+i),0);
		fprintf(fp,"%d %d %d\n",-resort(350+i),-resort(150+i),0);
		fprintf(fp,"%d %d %d\n",-resort(250+i),-resort(150+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(830+i),0);
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(740+i),0);
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(650+i),0);
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(560+i),0);
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(460+i),0);
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(360+i),0);
		fprintf(fp,"%d %d %d\n",-resort(920+i),-resort(260+i),0);
		fprintf(fp,"%d %d %d\n",-resort(830+i),-resort(740+i),0);
		fprintf(fp,"%d %d %d\n",-resort(830+i),-resort(650+i),0);
		fprintf(fp,"%d %d %d\n",-resort(830+i),-resort(560+i),0);
		fprintf(fp,"%d %d %d\n",-resort(830+i),-resort(460+i),0);
		fprintf(fp,"%d %d %d\n",-resort(830+i),-resort(360+i),0);
		fprintf(fp,"%d %d %d\n",-resort(830+i),-resort(260+i),0);
		fprintf(fp,"%d %d %d\n",-resort(740+i),-resort(650+i),0);
		fprintf(fp,"%d %d %d\n",-resort(740+i),-resort(560+i),0);
		fprintf(fp,"%d %d %d\n",-resort(740+i),-resort(460+i),0);
		fprintf(fp,"%d %d %d\n",-resort(740+i),-resort(360+i),0);
		fprintf(fp,"%d %d %d\n",-resort(740+i),-resort(260+i),0);
		fprintf(fp,"%d %d %d\n",-resort(650+i),-resort(560+i),0);
		fprintf(fp,"%d %d %d\n",-resort(650+i),-resort(460+i),0);
		fprintf(fp,"%d %d %d\n",-resort(650+i),-resort(360+i),0);
		fprintf(fp,"%d %d %d\n",-resort(650+i),-resort(260+i),0);
		fprintf(fp,"%d %d %d\n",-resort(560+i),-resort(460+i),0);
		fprintf(fp,"%d %d %d\n",-resort(560+i),-resort(360+i),0);
		fprintf(fp,"%d %d %d\n",-resort(560+i),-resort(260+i),0);
		fprintf(fp,"%d %d %d\n",-resort(460+i),-resort(360+i),0);
		fprintf(fp,"%d %d %d\n",-resort(460+i),-resort(260+i),0);
		fprintf(fp,"%d %d %d\n",-resort(360+i),-resort(260+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(930+i),-resort(840+i),0);
		fprintf(fp,"%d %d %d\n",-resort(930+i),-resort(750+i),0);
		fprintf(fp,"%d %d %d\n",-resort(930+i),-resort(660+i),0);
		fprintf(fp,"%d %d %d\n",-resort(930+i),-resort(570+i),0);
		fprintf(fp,"%d %d %d\n",-resort(930+i),-resort(470+i),0);
		fprintf(fp,"%d %d %d\n",-resort(930+i),-resort(370+i),0);
		fprintf(fp,"%d %d %d\n",-resort(840+i),-resort(750+i),0);
		fprintf(fp,"%d %d %d\n",-resort(840+i),-resort(660+i),0);
		fprintf(fp,"%d %d %d\n",-resort(840+i),-resort(570+i),0);
		fprintf(fp,"%d %d %d\n",-resort(840+i),-resort(470+i),0);
		fprintf(fp,"%d %d %d\n",-resort(840+i),-resort(370+i),0);
		fprintf(fp,"%d %d %d\n",-resort(750+i),-resort(660+i),0);
		fprintf(fp,"%d %d %d\n",-resort(750+i),-resort(570+i),0);
		fprintf(fp,"%d %d %d\n",-resort(750+i),-resort(470+i),0);
		fprintf(fp,"%d %d %d\n",-resort(750+i),-resort(370+i),0);
		fprintf(fp,"%d %d %d\n",-resort(660+i),-resort(570+i),0);
		fprintf(fp,"%d %d %d\n",-resort(660+i),-resort(470+i),0);
		fprintf(fp,"%d %d %d\n",-resort(660+i),-resort(370+i),0);
		fprintf(fp,"%d %d %d\n",-resort(570+i),-resort(470+i),0);
		fprintf(fp,"%d %d %d\n",-resort(570+i),-resort(370+i),0);
		fprintf(fp,"%d %d %d\n",-resort(470+i),-resort(370+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(940+i),-resort(850+i),0);
		fprintf(fp,"%d %d %d\n",-resort(940+i),-resort(760+i),0);
		fprintf(fp,"%d %d %d\n",-resort(940+i),-resort(670+i),0);
		fprintf(fp,"%d %d %d\n",-resort(940+i),-resort(580+i),0);
		fprintf(fp,"%d %d %d\n",-resort(940+i),-resort(480+i),0);
		fprintf(fp,"%d %d %d\n",-resort(850+i),-resort(760+i),0);
		fprintf(fp,"%d %d %d\n",-resort(850+i),-resort(670+i),0);
		fprintf(fp,"%d %d %d\n",-resort(850+i),-resort(580+i),0);
		fprintf(fp,"%d %d %d\n",-resort(850+i),-resort(480+i),0);
		fprintf(fp,"%d %d %d\n",-resort(760+i),-resort(670+i),0);
		fprintf(fp,"%d %d %d\n",-resort(760+i),-resort(580+i),0);
		fprintf(fp,"%d %d %d\n",-resort(760+i),-resort(480+i),0);
		fprintf(fp,"%d %d %d\n",-resort(670+i),-resort(580+i),0);
		fprintf(fp,"%d %d %d\n",-resort(670+i),-resort(480+i),0);
		fprintf(fp,"%d %d %d\n",-resort(580+i),-resort(480+i),0);
	}
	for(i=1;i<=9;i++){
		fprintf(fp,"%d %d %d\n",-resort(950+i),-resort(860+i),0);
		fprintf(fp,"%d %d %d\n",-resort(950+i),-resort(770+i),0);
		fprintf(fp,"%d %d %d\n",-resort(950+i),-resort(680+i),0);
		fprintf(fp,"%d %d %d\n",-resort(950+i),-resort(590+i),0);
		fprintf(fp,"%d %d %d\n",-resort(860+i),-resort(770+i),0);
		fprintf(fp,"%d %d %d\n",-resort(860+i),-resort(680+i),0);
		fprintf(fp,"%d %d %d\n",-resort(860+i),-resort(590+i),0);
		fprintf(fp,"%d %d %d\n",-resort(770+i),-resort(680+i),0);
		fprintf(fp,"%d %d %d\n",-resort(770+i),-resort(590+i),0);
		fprintf(fp,"%d %d %d\n",-resort(680+i),-resort(590+i),0);
	}
	//左斜约束条件
	int cons_l1[5]={510,410,310,210,110};
	for(i=0;i<10;i++){
		for(j=0;j<2;j++){
			for(k=0;k<5;k++){
				fprintf(fp,"%d ",resort(cons_l1[k]+cons1[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l2[6]={610,520,420,320,220,120};
	for(i=0;i<6;i++){
		for(j=0;j<2;j++){
			for(k=0;k<6;k++){
				fprintf(fp,"%d ",resort(cons_l2[k]+cons2[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l3[7]={710,620,530,430,330,230,130};
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			for(k=0;k<7;k++){
				fprintf(fp,"%d ",resort(cons_l3[k]+cons3[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l4[8]={810,720,630,540,440,340,240,140};
	for(i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<8;k++){
				fprintf(fp,"%d ",resort(cons_l4[k]+cons4[j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l6[8]={920,830,740,650,560,460,360,260};
	for(i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<8;k++){
				fprintf(fp,"%d ",resort(cons_l6[k]+cons4[j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l7[7]={930,840,750,660,570,470,370};
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			for(k=0;k<7;k++){
				fprintf(fp,"%d ",resort(cons_l7[k]+cons3[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l8[6]={940,850,760,670,580,480};
	for(i=0;i<6;i++){
		for(j=0;j<2;j++){
			for(k=0;k<6;k++){
				fprintf(fp,"%d ",resort(cons_l8[k]+cons2[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_l9[5]={950,860,770,680,590};
	for(i=0;i<10;i++){
		for(j=0;j<2;j++){
			for(k=0;k<5;k++){
				fprintf(fp,"%d ",resort(cons_l9[k]+cons1[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}

	//右斜
	fprintf(fp,"%d %d %d %d %d %d\n",resort(155),resort(265),resort(375),resort(485),resort(595),0);
	int markr1[5]={150,260,370,480,590};
	int markr2[6]={140,250,360,470,580,680};
	int markr9[5]={510,610,710,810,910};
	int markr_2[3]={4,5,6};
	for(i=0;i<3;i++){
		for(j=0;j<6;j++){
			fprintf(fp,"%d ",resort(markr2[j]+markr_2[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markr3[7]={130,240,350,460,570,670,770};
	int markr_3[5]={3,4,5,6,7};
	for(i=0;i<5;i++){
		for(j=0;j<7;j++){
			fprintf(fp,"%d ",resort(markr3[j]+markr_3[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markr4[8]={120,230,340,450,560,660,760,860};
	int markr_4[7]={2,3,4,5,6,7,8};
	for(i=0;i<7;i++){
		for(j=0;j<8;j++){
			fprintf(fp,"%d ",resort(markr4[j]+markr_4[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markr5[9]={110,220,330,440,550,650,750,850,950};
	int markr_5[9]={1,2,3,4,5,6,7,8,9};
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			fprintf(fp,"%d ",resort(markr5[j]+markr_5[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markr6[8]={210,320,430,540,640,740,840,940};
	for(i=0;i<7;i++){
		for(j=0;j<8;j++){
			fprintf(fp,"%d ",resort(markr6[j]+markr_4[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markr7[7]={310,420,530,630,730,830,930};
	for(i=0;i<5;i++){
		for(j=0;j<7;j++){
			fprintf(fp,"%d ",resort(markr7[j]+markr_3[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	int markr8[6]={410,520,620,720,820,920};
	for(i=0;i<3;i++){
		for(j=0;j<6;j++){
			fprintf(fp,"%d ",resort(markr8[j]+markr_2[i]));
		}
		fprintf(fp,"%d\n",0);
	}
	fprintf(fp,"%d %d %d %d %d %d\n",resort(515),resort(615),resort(715),resort(815),resort(915),0);

	//任两格不能填同一个数字约束（右斜）
	for(i=1;i<=9;i++){
		for(j=0;j<4;j++){
			for(k=j+1;k<5;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr1[j]+i),-resort(markr1[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<5;j++){
			for(k=j+1;k<6;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr2[j]+i),-resort(markr2[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<6;j++){
			for(k=j+1;k<7;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr3[j]+i),-resort(markr3[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<7;j++){
			for(k=j+1;k<8;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr4[j]+i),-resort(markr4[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<8;j++){
			for(k=j+1;k<9;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr5[j]+i),-resort(markr5[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<7;j++){
			for(k=j+1;k<8;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr6[j]+i),-resort(markr6[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<6;j++){
			for(k=j+1;k<7;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr7[j]+i),-resort(markr7[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<5;j++){
			for(k=j+1;k<6;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr8[j]+i),-resort(markr8[k]+i),0);
			}
		}
	}
	for(i=1;i<=9;i++){
		for(j=0;j<4;j++){
			for(k=j+1;k<5;k++){
				fprintf(fp,"%d %d %d\n",-resort(markr9[j]+i),-resort(markr9[k]+i),0);
			}
		}
	}

	//右斜约束
	int cons_r1[5]={150,260,370,480,590};
	for(i=0;i<10;i++){
		for(j=0;j<2;j++){
			for(k=0;k<5;k++){
				fprintf(fp,"%d ",resort(cons_r1[k]+cons1[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r2[6]={140,250,360,470,580,680};
	for(i=0;i<6;i++){
		for(j=0;j<2;j++){
			for(k=0;k<6;k++){
				fprintf(fp,"%d ",resort(cons_r2[k]+cons2[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r3[7]={130,240,350,460,570,670,770};
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			for(k=0;k<7;k++){
				fprintf(fp,"%d ",resort(cons_r3[k]+cons3[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r4[8]={120,230,340,450,560,660,760,860};
	for(i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<8;k++){
				fprintf(fp,"%d ",resort(cons_r4[k]+cons4[j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r6[8]={210,320,430,540,640,740,840,940};
	for(i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<8;k++){
				fprintf(fp,"%d ",resort(cons_r6[k]+cons4[j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r7[7]={310,420,530,630,730,830,930};
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			for(k=0;k<7;k++){
				fprintf(fp,"%d ",resort(cons_r7[k]+cons3[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r8[6]={410,520,620,720,820,920};
	for(i=0;i<6;i++){
		for(j=0;j<2;j++){
			for(k=0;k<6;k++){
				fprintf(fp,"%d ",resort(cons_r8[k]+cons2[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	int cons_r9[5]={510,610,710,810,910};
	for(i=0;i<10;i++){
		for(j=0;j<2;j++){
			for(k=0;k<5;k++){
				fprintf(fp,"%d ",resort(cons_r9[k]+cons1[i][j]));
			}
		}
		fprintf(fp,"%d\n",0);
	}
	
	fclose(fp);

	return 1; 
}
int resort(int x){
 	int i,j,k;
 	int d[10]={0,5,11,18,26,35,43,50,56,61};
 	k=x%10;
 	x=x/10;
	j=x%10;
 	x=x/10;
 	i=x;
 	return 9*d[i-1]+(j-1)*9+k;
}
// int resort(int x){
// 	int i,j,k;
// 	k=x%10;
//  	x=x/10;
//  	j=x%10;
//  	x=x/10;
//  	i=x;
// 	return (i-1)*81+(j-1)*9+k;
// }
int disresort(int x){
	for(int i=110;i<999;i++){
		if(resort(i)==x)
		return i;
	}
	return 0;
}

int num_position(char* input,int *output){
    char* pp=input+4;
    int pos=0;
    int p[12][12]={0};
    //读取数据
    for(int i=1;i<=5;i++) p[1][i]=*(++pp)-'0';
    for(int i=1;i<=6;i++) p[2][i]=*(++pp)-'0';
    for(int i=1;i<=7;i++) p[3][i]=*(++pp)-'0';
    for(int i=1;i<=8;i++) p[4][i]=*(++pp)-'0';
    for(int i=1;i<=9;i++) p[5][i]=*(++pp)-'0';
    for(int i=1;i<=8;i++) p[6][i]=*(++pp)-'0';
    for(int i=1;i<=7;i++) p[7][i]=*(++pp)-'0';
    for(int i=1;i<=6;i++) p[8][i]=*(++pp)-'0';
    for(int i=1;i<=5;i++) p[9][i]=*(++pp)-'0';
    //处理数据
    int num=0;
    for(int i=0;i<12;i++) 
        for(int j=0;j<12;j++)
            if(p[i][j]!=0) output[num++]=1*p[i][j]+100*i+j*10;
    return num;

}
int randnum(int low,int high){
	srand(time(0));
	return (rand() % (high - low + 1)) + low;
}
bool las_vegas(int n){
	SATList* CNFList = NULL;
	int* value_1;
	int num;
	for(int i=5;i<=65;i++)
		CHESS[i]='0';
	for(int i=0;i<n;i++){
		int m=randnum(5,64);
		if(CHESS[m]=='0'){
			CHESS[m]='0'+randnum(1,9);
		}
	}
	cnfmaker(CHESS,fileName);
	ReadFile(CNFList,fileName);
	value_1 = (int*)malloc(sizeof(int) * (boolCount + 1));
	for (int i = 1; i <= boolCount; i++) value_1[i] = 1;
	int result = DPLL(CNFList, value_1);
	if(result==1) return true;
	else return false;
}
// bool las_Vegas(int n){
// 	Sleep(1000);
// 	Sleep(1000);
// 	return true;
// }






























#define CORRECT 0
#define WRONG -1
static int T = 0;

//根据holes来挖洞
//此函数输出数独初盘，同时返回解析后的.cnf文件
string createSudokuToFile(int holes, int array[ROW][COL]) {
    int sudoku[ROW][COL]={0};
    int starting_grid[ROW][COL]={0};
    createSudoku(sudoku);//生成数独终盘
    createStartinggrid(sudoku,starting_grid,holes);//生成初盘
    memcpy(array, starting_grid, ROW*COL*sizeof(int));
    cout << "初始化后数独初盘为：" << endl;
    print(starting_grid);//输出初盘
    //转化为cnf文件
    string filename = ToCnf(starting_grid,holes);
    return filename;
}

int Digit(int a[][COL], int i, int j) {//递归填充数独元素
    if (i < ROW && j < COL) {
        int x,y,k;
        int check[COL+1]={CORRECT};//用于排除已经使用过的的数字
        for(x = 0 ; x < i ; x++)
            check[a[x][j]] = WRONG;//列已使用的数字置为WRONG
        for(x = 0 ; x < j ; x++)
            check[a[i][x]] = WRONG;//行使用过的数字置为WRONG
        for(x = i/3*3 ; x <= i; x++) {
            if(x == i)
                for(y = j/3*3 ; y < j; y++)
                    check[a[x][y]] = WRONG;
            else
                for(y = j/3*3 ; y < j/3*3 + 3; y++)
                    check[a[x][y]] = WRONG;
        }

        int flag = 0;
        for(k = 1; k <= COL && flag == 0 ; k++){//从check数组中查找安全的数字
            if(check[k] == CORRECT){
                flag = 1;
                a[i][j] = k;
                if(j == COL-1 && i != ROW-1){
                    if(Digit(a,i+1,0) == CORRECT) return CORRECT;
                    else flag = 0;
                }
                else if(j != COL-1){
                    if(Digit(a,i,j+1) == CORRECT) return CORRECT;
                    else flag = 0;
                }
            }
        }
        if( flag == 0 ) {
            a[i][j] = 0;
            return WRONG;
        }
    }
    return CORRECT;
}

void randomFirstRow(int a0[], int n) {//随机生成第一行
    int i,j;
    srand((unsigned)time(nullptr));
    for( i = 0 ; i < n ; i++){
        a0[i] = rand()%9 + 1;
        j = 0 ;
        while(j < i){
            if(a0[i] == a0[j]){
                a0[i] = rand()%9 + 1;
                j = 0;
            }
            else j++;
        }
    }
}

void createSudoku(int a[][COL]){ //生成数独
    randomFirstRow(a[0],COL);//随机生成第一行
    Digit(a,1,0);//递归生成后i行
}

void createStartinggrid(const int a[][COL], int b[][COL], int numDigits) {//随机生成初盘
    int i,j,k;
    srand((unsigned)time(nullptr));
    for( i = 0; i < ROW ; i ++)
        for( j = 0; j < COL ; j++)
            b[i][j] = a[i][j];

    //int c[numDigits][2];//此处可以采用c++中的new动态为二维数组分配内存
    int** c = new int* [numDigits];
    for(int i = 0; i < numDigits; i++){
        c[i] = new int [2];
    }
    int m,flag = 0;

    for( i = 0; i < numDigits ; i++) {
        j = rand()%9;
        k = rand()%9;

        flag = 0;
        for(m = 0; m < i ; m++)
            if( j == c[m][0] && k == c[m][1])
                flag = 1;

        if(flag == 0){
            b[j][k] = 0;
            c[i][0] = j;
            c[i][1] = k;
        }
        else
            i--;
    }
}

void print(const int a[][COL]){//打印数独数组
    int i,j;
    for( i = 0 ; i < ROW ; i++){
        for( j = 0 ; j < COL ; j++)
            printf("%d ", a[i][j]);
        cout<<endl;
    }
}

string ToCnf(int a[][COL],int holes) {
    ofstream in (".\\sudoku.cnf");//定义输入文件
    if(!in.is_open())
        cout<<"can't open!\n";
    in<<"p"<<" "<<"cnf"<<" "<<729<<" "<<8829+81-holes<<" "<<endl;
    //single clause
    for (int x = 0; x < ROW; ++x) {
        for (int y = 0; y < COL; ++y)
            if(a[x][y] != 0)
                in<<(x+1)*100 + (y+1)*10 + a[x][y]<<" "<<0<<endl;
    }
    //entry
    for (int x = 1; x <= 9; ++x) {
        for (int y = 1; y <= 9; ++y) {
            for (int z = 1; z <= 9; ++z)
                in << x * 100 + y * 10 + z << " ";
            in<<0;
            in<<endl;
        }
    }
    //row
    for (int y = 1; y <= 9; ++y) {
        for (int z = 1; z <= 9; ++z)
            for (int x = 1; x <= 8; ++x)
                for (int i = x+1; i <= 9; ++i)
                    in<<0 - (x*100 + y*10 + z)<<" "
                      <<0 - (i*100 + y*10 + z)<<" "<<0<<endl;
    }
    //column
    for (int x = 1; x <= 9; ++x) {
        for (int z = 1; z <=9 ; ++z)
            for (int y = 1; y <= 8; ++y)
                for (int i = y+1; i <= 9; ++i)
                    in<<0-(x*100 + y*10 + z)<<" "
                      <<0-(x*100 + i*10 + z)<<" "<<0<<endl;
    }
    //3*3 sub-grids
    for (int z = 1; z <= 9 ; ++z) {
        for (int i = 0; i <=2 ; ++i)
            for (int j = 0; j <=2 ; ++j)
                for (int x = 1; x <= 3 ; ++x)
                    for (int y = 1; y <= 3; ++y)
                        for (int k = y+1; k <= 3; ++k)
                            in<<0 - ((3*i+x)*100 + (3*j+y)*10 + z)<<" "
                              <<0-((3*i+x)*100 + (3*j+k)*10 + z)<<" "<<0<<endl;
    }
    for (int z = 1; z <= 9; z++) {
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int x = 1; x <= 3; x++)
                    for (int y = 1; y <= 3; y++)
                        for (int k = x + 1; k <= 3; k++)
                            for (int l = 1; l <= 3; l++)
                                in << 0 - ((3*i+x)*100 + (3*j+y)*10 + z) << ' '
                                   << 0 - ((3*i+k)*100 + (3*j+l)*10 + z) << ' ' << 0 <<endl;
    }
    in.close();
    return ".\\sudoku.cnf";//返回一个string类型的对象
}