#include <bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int SIZE=7;
const int NUM=28;
const int MAXN=NUM;

/*---definition of struct---*/
typedef struct
{
    bool status;//true--in grid; false--out of grid
    int posx;//[0,6]
    int posy;//[0,6]
} MineInfo;
MineInfo MineList[MAXN];

typedef struct
{
    bool occupied;//true--mine in palce; false--no mine
    int index;//if occupied, record which mine is there
}GridInfo;
GridInfo MineGrid[SIZE][SIZE];

char PlayerOp[SIZE][SIZE];//0--unchosen,1--chosen,2--end

/*---declaration of functions---*/
void ClearGrid();
void PrintGrid();
void RecordInGrid();
int RandomCreate(int,int);
void EndofGame();
int DeleteMine();
void Failure();


/*---implement of functions---*/
void ClearGrid()
{
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            MineGrid[i][j].occupied=false;
}

int DeleteMine()
{
    for(int i=0;i<NUM;i++)
    {
        if(MineList[i].status==true)
        {
            MineList[i].status=false;
            return i;
        }
    }
    return -1;
}

void PrintGrid()
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<SIZE;j++)
            cout<<PlayerOp[i][j]<<' ';
        cout<<endl;
    }
}

void RecordInGrid() 
{
    ClearGrid();
    for(int i=0;i<NUM;i++)
    {
        if(MineList[i].status==false)
            continue;
        
        int x=MineList[i].posx;
        int y=MineList[i].posy;
        MineGrid[x][y].occupied=true;
        MineGrid[x][y].index=i;
    }
}

int RandomCreate(int i,int num)
{   
    //create a mine, index of which is i.
    MineList[i].posx=rand()%7;
    MineList[i].posy=rand()%7;

    if(MineList[i].posx==SIZE/2&&MineList[i].posy==SIZE/2)
        return 1;

    for(int j=0;j<num;j++)
    {
        //check if there is repetition in the coordinate.
        if(j!=i&&MineList[j].status==true
               &&MineList[i].posx==MineList[j].posx
               &&MineList[i].posy==MineList[j].posy)
        {
            return 1;//exit with failure sign.
        }
    }    
    MineList[i].status=true;
    return 0;//exit with success sign.
}

void PrintMine()
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<SIZE;j++)
        {
            if(i==SIZE/2&&j==SIZE/2)
            {
                cout<<"? ";
            }
            else
            {
                if(MineGrid[i][j].occupied==true)
                {
                    char s=MineGrid[i][j].index+'A';
                    cout<<s<<' ';   
                }             
                else
                    cout<<"0 ";
            }
        }
        cout<<endl;
    }
}

void EndofGame()
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<SIZE;j++)
        {
            if(MineGrid[i][j].occupied==true)
            {
                cout << "\033[31m" << "● " << "\033[0m";
            }             
            else
            {
                if(PlayerOp[i][j]=='+')
                    cout<<"\033[1;34m"<<PlayerOp[i][j]<<' '<<"\033[0m";
                else
                    cout<<PlayerOp[i][j]<<' ';
            }
        }
        cout<<endl;
    }
}

void Failure(int x,int y)
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<(char)(i+'A')<<" ";
        for(int j=0;j<SIZE;j++)
        {
            if(i==x&&j==y)
            {
                cout << "\033[31m" << "X " << "\033[0m";
            }
            else
            {
                if(MineGrid[i][j].occupied==true)
                {
                    cout << "\033[31m" << "● " << "\033[0m";
                }             
                else
                    cout<<PlayerOp[i][j]<<' ';
            }
        }
        cout<<endl;
    }
}

int main() 
{
    srand((unsigned)time(NULL));//do not use it in the loop
    cout << fixed << setprecision(2);

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        {
            if(i==SIZE/2&&j==SIZE/2)
                PlayerOp[i][j]='?';
            else
                PlayerOp[i][j]='o';
        }

    for(int i=0;i<NUM;i++)
        MineList[i].status=false;
    for(int i=0;i<NUM;i++)
    {
        int res=RandomCreate(i,NUM);
        if(res) i--;
    }
    RecordInGrid();

    /*--testcode--
    for(int i=0;i<NUM;i++)
        cout<<current[i].posx<<' '<<current[i].posy<<endl;
    */

    
    double CostofDelete[5]={5,20,50,150,500};//q
    int pDelete=0;
    double CostofReward[4]={5,15,40,80};//p
    int pReward=0;
    double CostofCombine[4]={5,15,40,80};//w
    int pCombine=0;
    
    int ExistMine=NUM;
    double odd;
    int AllSpace=SIZE*SIZE-1;
    int ErrorCode=-1,FailCode=0;
    double eco=5;//overall ecomomy
    double incre=0;
    int TotalStep=0;//ever-increasing--total steps made
    int SuccStep=0,FailStep=0;//
    int maxsucc=0,maxfail=0;

    char Lasten[10]; 
    int low=0,len=0;

    while(1)
    {
    loop:
        cout.flush();
        system("cls");
        PrintGrid();
        //PrintMine();
        odd=1-(double)ExistMine/AllSpace;
    
        for(int i=1;i<=90;i++)
            cout<<'-';
        cout<<endl;

        cout <<"\033[1m"<< "Current success probability:" << "\033[0;32m" <<odd*100 <<'%'<<"\033[0m" << endl;
        
        cout <<"\033[1m"<< "Economy:"<<"\033[0m"<< eco;
        if(incre>0)
            cout << "\033[32m"<<"(+"<<incre<<")" <<"\033[0m";
        else if(incre<0)
            cout << "\033[32m"<<"("<<incre<<")"<<"\033[0m";
        cout << endl;

        cout <<"\033[1m"<< "Item shop:"<<"\033[0m"<<endl; 

        cout << "(PRESS 'q') 1. Delete 4 mines from the map.                      \t";
        if(pDelete<5)
            cout<<"Cost:"<<"\033[32m"<<CostofDelete[pDelete]<<"\033[0m"<<endl;
        else
            cout<<"MAX"<<endl;

        cout << "(PRESS 'p') 2. Increase foundamental reward by 1.                \t";
        if(pReward<4)
            cout<<"Cost:"<<"\033[32m"<<CostofReward[pReward]<<"\033[0m"<<endl;
        else
            cout<<"MAX"<<endl;

        cout << "(PRESS 'w') 2. Increase additional reward for continuous success.\t";
        if(pCombine<4)
            cout<<"Cost:"<<"\033[32m"<<CostofCombine[pCombine]<<"\033[0m"<<endl;
        else
            cout<<"MAX"<<endl;
        cout <<"\033[1m"<< "Max continuous success:"<<"\033[0;32m"<<maxsucc<<"\033[0m"<<endl;
        cout <<"\033[1m"<< "Max continuous failure:"<<"\033[0;32m"<<maxfail<<"\033[0m"<<endl;
        cout <<"\033[1m"<< "Last 10 attempts:"<<"\033[0;32m";
        for(int i=0;i<len;i++)
            cout<<Lasten[(low+i)%10]<<' ';
        cout<<endl;
        cout<<"\033[0m";

        incre=0;

        for(int i=1;i<=90;i++)
            cout<<'-';
        cout<<endl;

        cout << "\033[31m";
        switch(ErrorCode)
        {
            case 0://normal
                cout<<"Successful! The position you chose is safe."<<endl;
                break;
            case 1://buy prop
                cout<<"The prop is working! Notice the change of price."<<endl;
                break;
            case 2://no sufficient eco
                cout<<"Sorry! You cannot afford this prop or it is sold out. Try something else."<<endl;
                break;
            case 3://invalid input
                cout<<"Sorry! The position you entered is out of range. Try something else."<<endl;
                break;
            case 4://repetive input
                cout<<"Sorry! You have chosen this position. Try something else."<<endl;
                break;
            case 5://unsuccessful attempt
                cout<<"Bad luck! There is a mine at the position you chose."<<endl;
                cout<<"Mines have been rearranged..."<<endl;
                break;
            default:
                cout<<"Welcome to the game!"<<endl;
                break;
        }
        
        if(TotalStep>0&&TotalStep%10==0)
            cout<<"\033[1;35m"<<"YOU HAVE TRIED "<<TotalStep<<" STEPS"<<endl;
        cout<<"\033[0m";

        cout<<"Please choose a position or buy props: ";

        int PlayerX=-1,PlayerY=-1;
        string input;
        getline(cin,input);
        int length=input.size();
        for(int i=0;i<length;i++)
        {
            if(input[i]>='a'&&input[i]<='g')
                PlayerX=input[i]-'a';
            else if(input[i]>='A'&&input[i]<='G')
                PlayerX=input[i]-'A';
            else if(input[i]>='1'&&input[i]<='7')
                PlayerY=input[i]-'1';
            else if(input[i]=='q'||input[i]=='Q')
            {
                if(eco>=CostofDelete[pDelete]&&pDelete<5)
                {
                    ErrorCode=1;
                    for(int times=1;times<=4;times++)                  
                        DeleteMine();
                    RecordInGrid();                   
                    ExistMine-=4;
                    incre=-CostofDelete[pDelete];
                    eco+=incre;
                    pDelete++;
                }
                else
                {
                    ErrorCode=2;
                }
                goto loop;
            }
            else if(input[i]=='p'||input[i]=='P')
            {
                if(eco>=CostofReward[pReward]&&pReward<4)
                {
                    ErrorCode=1;
                    incre=-CostofReward[pReward];
                    eco+=incre;
                    pReward++;
                }
                else
                {
                    ErrorCode=2;
                }
                goto loop;
            }
            else if(input[i]=='w'||input[i]=='W')
            {
                if(eco>=CostofCombine[pCombine]&&pCombine<4)
                {
                    ErrorCode=1;
                    incre=-CostofCombine[pCombine];
                    eco+=incre;
                    pCombine++;
                }
                else
                {
                    ErrorCode=2;
                }
                goto loop;
            }
        }



        if(PlayerX<0||PlayerY<0)
        {
            ErrorCode=3;
            continue;
        }

        if(PlayerX==SIZE/2&&PlayerY==SIZE/2)
        {
            ErrorCode=3;
            continue;
        }
        else
        {
            if(PlayerOp[PlayerX][PlayerY]=='+')
            {
                ErrorCode=4;
                continue;
            }
        }

        TotalStep++;
        if(MineGrid[PlayerX][PlayerY].occupied==true)
        {
            if(len<10)
            {
                Lasten[len]='F';
                len++;
            }
            else
            {
                Lasten[low%10]='F';
                low++;
            }

            if(FailCode==1)
                FailStep++;
            else
                FailStep=1;
            maxfail=max(FailStep,maxfail);
            ErrorCode=5;
            FailCode=1;
            
            SuccStep=0;
            ExistMine=NUM-4*pDelete;
            AllSpace=SIZE*SIZE-1;
            for(int i=1;i<=3;i++)
                cout<<"\033[1;31m"<<"BOOM!"<<"\033[0m"<<endl;
            Failure(PlayerX,PlayerY);
            this_thread::sleep_for(chrono::seconds(1));

            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                {
                    if(i==SIZE/2&&j==SIZE/2)
                        PlayerOp[i][j]='?';
                    else
                        PlayerOp[i][j]='o';
                }

            for(int i=0;i<NUM;i++)
                MineList[i].status=false;
            for(int i=0;i<ExistMine;i++)
            {
                int res=RandomCreate(i,ExistMine);
                if(res) i--;
            }
            RecordInGrid();
        }
        else
        {
            if(len<10)
            {
                Lasten[len]='S';
                len++;
            }
            else
            {
                Lasten[low%10]='S';
                low++;
            }

            FailCode=0;
            ErrorCode=0;
            SuccStep++;
            maxsucc=max(SuccStep,maxsucc);
            FailStep=0;
            AllSpace--;
            incre=(1+(SuccStep-1)*0.6*(pCombine+1))*(pReward+1);
            eco+=incre;
            PlayerOp[PlayerX][PlayerY]='+';
            if(SuccStep==8)
            {
                cout<<"\033[1;33m"<<"Congratulations!"<<"\033[0m"<<endl;
                cout<<"Your LUCKY NUMBER(total attempts) is: " <<"\033[1;33m"<<TotalStep<<"\033[0m"<<endl;
                EndofGame();
                cout<<"Enter '0' to exit..."<<endl;
                int endchar;
                cin>>endchar;
                return 0;
            }
        }
    }
}