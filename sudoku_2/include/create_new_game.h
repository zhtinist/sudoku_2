#include"def.h"
//目前存入的终盘模版数,方便加入新的终盘
#define DATA 20
//初始的终盘用于生成游戏
char ending_game_data[DATA][70]={   "HQV1G4563263847554721632638975437915428625789634463217554876363452",
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