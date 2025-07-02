//Tic-tac-toe with AI
#include <iostream>
#include <iomanip>
using namespace std;

void Intro(char &hpiece,char &apiece){
    char YN=0;
    char c=0;
    cout<<"Bob:\"Let's play a game I just bought from 千千.\""<<endl;
    cout<<"\"It's called \'The Legend of Zelda\'.\""<<endl<<"\"Though this game cost me $35.99, but it's worth. I really love Zelda.\""<<endl<<"\"I can't wait to play!!\""<<endl;
    while(c!='C')
    {
        cout<<"(press \"O\" to operate the game)"<<endl;
        cin>>c;
    }
    cout<<"(Operate the game. . .)"<<endl<<endl;
    cout<<"screen: \"Welcome to The Legend of Zelda---Tic Tac Toe version\""<<endl;
    cout<<"Bob:\"Wait, seriously? TIC TAC TOE?!?!\""<<endl;
    cout<<"screen: \"Here are nine areas you will discover in the game. Each area named a number,1 to 8.\" "<<endl;
    cout<<"0|1|2"<<endl;
    cout<<"-----"<<endl;
    cout<<"3|4|5"<<endl;
    cout<<"-----"<<endl;
    cout<<"6|7|8"<<endl;
    cout<<"screen: \"You two can separately choose where to go in each round, and mark that place by your own symbol: great CIRCLE and CROSS.\""<<endl;
    cout<<"screen: \"The first player will be represented by CIRCLE.\""<<endl;
    cout<<"screen: \"The second player will be represented by CROSS.\""<<endl;
    
    while((YN!='Y')&&(YN!='N'))
    {
        cout<<"Bob:\"Alright......Do you want to play first?\""<<endl<<"(Press \"Y\" or \"N\")"<<endl;
        cin>>YN;
    }
    if (YN=='Y')
    {
        hpiece='O';
        apiece='X';
        cout<<"Bob:\"OK, you get circle, I get cross.\""<<endl;
    }
    if (YN=='N')
    {
        hpiece='X';
        apiece='O';
        cout<<"Bob:\"OK, you get cross, I get circle.\""<<endl;
    }
    while(c!='S')
    {
        cout<<"(press \"S\" to start your adventure)"<<endl;
        cin>>c;
    }
    cout<<"screen: \"Start:\""<<endl;
}

void Board(char *board){    //顯示遊戲板塊
    cout<<board[0]<<"|"<<board[1]<<"|"<<board[2]<<endl;
    cout<<"-----"<<endl;
    cout<<board[3]<<"|"<<board[4]<<"|"<<board[5]<<endl;
    cout<<"-----"<<endl;
    cout<<board[6]<<"|"<<board[7]<<"|"<<board[8]<<endl;
}

bool Legal(char *board,int place){  //判定欲下之位置為空格
    bool legal=false;
    if (board[place]==' ')
        legal=true;
    else
        legal=false;
    return legal;
}
    
bool Line(char *board){ //  判定連線與否
    bool line=false;
    if(((board[0]!=' ')&&(board[0]==board[1])&&(board[1]==board[2]))||
       ((board[3]!=' ')&&(board[3]==board[4])&&(board[4]==board[5]))||
       ((board[6]!=' ')&&(board[6]==board[7])&&(board[7]==board[8]))||
       ((board[0]!=' ')&&(board[0]==board[3])&&(board[3]==board[6]))||
       ((board[1]!=' ')&&(board[1]==board[4])&&(board[4]==board[7]))||
       ((board[2]!=' ')&&(board[2]==board[5])&&(board[5]==board[8]))||
       ((board[0]!=' ')&&(board[0]==board[4])&&(board[4]==board[8]))||
       ((board[2]!=' ')&&(board[2]==board[4])&&(board[4]==board[6])))
    {
        line=true;
    }
    return line;
}

void Tie(char *board,char &over){   //判定平手
    int j=0;
    for(j=0;j<=8;j++)
    {
        if(*(board+j)==' ')
            break;
    }
    if(j==9)
    {
        over='T';
    }
}

void Hmove(char *board,char &over,char hpiece)  //人類下棋
{
    int place=0;
    for(;;){
        cout<<"Bob:\"What your next move?\""<<endl;
        cin>>place;
    if(Legal(board,place)==true)      //如果所選位置可以下
    {
        cout<<"Bob:\"What a move!\""<<endl;
        board[place]=hpiece;
        if(Line(board)==true)         //如果連線的話，人類獲勝
            over='H';
        if(over!='H')                 //如果人類已獲勝，不再判定平手與否，以免over=T覆蓋結果
            Tie(board,over);          //（當連線的最後一步棋也是場上的最後一個位置時，就會發生這種情況）
        
        break;
    }
    //如果所選位置不能下
    cout<<"screen:\"Wise move. But you have got to explore the virgin land, the new world.\""<<endl;
    }
}

int AI(char *AIboard,char hpiece,char apiece)   //AI判斷下哪兒
{
     char tempboard[9]={0}; //假想戰局
     int i=0;
    for(i=0;i<=8;i++)
     {
         tempboard[i]=AIboard[i];// 假想戰局複製現況戰局
     }

    for(i=0;i<=8;i++)  //Step1:檢查聽牌
     {
        if (Legal(tempboard,i)==1)
        {
            tempboard[i]=apiece;
            if (Line(tempboard)==true)
            {
                return i;
            }
         }
        tempboard[i]=AIboard[i]; // 假想戰局恢復到現況戰局
     }
 
    for(i=0;i<=8;i++)  //Step2:檢查對手是否聽牌
     {
         if (Legal(tempboard,i)==1)
         {
             tempboard[i]=hpiece;
             if (Line(tempboard)==true)
             {
                 return i;
             }
          }
         tempboard[i]=AIboard[i]; // 假想戰局恢復到現況戰局
     }
     
     int sequence[9]={4,0,2,6,8,1,3,5,7};   //Step3:前述條件不成立的最佳下法
     int s=4;
    for(i=0;i<=8;i++)
     {
         s=sequence[i];
         if (Legal(tempboard,s)==1)
         {
             return s;
         }
     }
    return s;
}

void Amove(char *board,char &over,char hpiece,char apiece){ //AI下棋
    cout<<"Bob:\"It's my turn, let's see......Here!\""<<endl;
    char AIboard[9]={0};
    for(int i=0;i<=8;i++)
     {
         AIboard[i]=board[i];   //AIboard也是現況戰局。多複製一次，避免假想戰局不小心影響現況戰局
     }
    board[AI(AIboard,hpiece,apiece)]=apiece;
    if (Line(board)==true)
        over='A';
    if(over!='A')
        Tie(board,over);
}

void Award(char over)   //依據over判定誰獲勝
{
    if(over=='H')
        cout<<"Bob:\"You win!\""<<endl;
    if(over=='A')
        cout<<"Bob:\"Oh...it’s a pity, good game.\""<<endl;
    if(over=='T')
        cout<<"screen:\"Tie.\""<<endl<<"Bob:\"What a poor game. I hate 千千.\""<<endl;
}

int main() {
    char board[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char hpiece=0;  //人類是哪方（圈或叉）
    char apiece=0;  //AI是哪方（圈或叉）
    char over=0;    //用以判定何時比賽結束、誰獲勝

    Intro(hpiece,apiece);
    if(hpiece=='O') //如果人類先
    {
        for(;;)
        {
            Hmove(board,over,hpiece);
            Board(board);
            if(over=='H'||over=='T')
                break;
            Amove(board,over,hpiece,apiece);
            Board(board);
            if(over=='A'||over=='T')
                break;
        }
    }
    if(apiece=='O') //如果AI先
    {
        for(;;)
        {
            Amove(board,over,hpiece,apiece);
            Board(board);
            if(over=='A'||over=='T')
                break;
            Hmove(board,over,hpiece);
            Board(board);
            if(over=='H'||over=='T')
                break;
        }
    }
    Award(over);
    return 0;
}
