#include "define.h"
#include "grid.h"
#include "mine.h"
#include "display.h"

int main() 
{
    srand((unsigned)time(NULL));//do not use it in the loop
    cout << fixed << setprecision(2);

    //initialize the grid of PlayerOp
    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++)
                PlayerOp[i][j]='o';

    //randomly distribute mines and record in grid
    for(int i=0;i<NUM;i++)
        MineList[i].status=false;
    for(int i=0;i<NUM;i++)
    {
        int res=RandomCreate(i);
        if(res) i--;
    }
    RecordInGrid();
    
    //the price of different props
    double CostofDelete[5]={10,40,100,200,300};//q
    int pDelete=0;
    double CostofReward[3]={5,15,40};//p
    int pReward=0;
    double CostofCombine[3]={5,15,40};//w
    int pCombine=0;
    
    int ExistMine=NUM;//mines in grid
    double odd;//=Mine/Spaces
    int AllSpace=GRID_SIZE*GRID_SIZE;
    int ErrorCode=-1,FailCode=0;//ErrorCode:feedback of input
    double eco=5;//overall ecomomy
    double incre=0;//increment of economy
    int TotalStep=0;//ever-increasing--total steps made
    int SuccStep=0,FailStep=0;//current continous steps
    int maxsucc=0,maxfail=0;//max continous steps

    char Lasten[10];//results of last ten rounds 
    int low=0,len=0;

    while(1)
    {
    loop:
        cout.flush();
        CLEAR_SCREEN;
        PrintGrid();
        //PrintMine();
        odd=1-(double)ExistMine/AllSpace;
    
        //print guide lines
        for(int i=1;i<=90;i++)
            cout<<'-';
        cout<<endl;

        cout <<"\033[1m"<< "Current success probability:" 
             << "\033[0;32m" <<odd*100 <<'%'<<"\033[0m" << endl;
        
        cout <<"\033[1m"<< "Economy:"<<"\033[0m"<< eco;
        if(incre>0)
            cout << "\033[32m"<<"(+"<<incre<<")" <<"\033[0m";
        else if(incre<0)
            cout << "\033[32m"<<"("<<incre<<")"<<"\033[0m";
        cout << endl;
        incre=0;

        cout <<"\033[1m"<< "Item shop:"<<"\033[0m"<<endl; 

        cout << "(PRESS 'q') 1. Delete 4 mines from the map.                      \t";
        if(pDelete<5)
            cout<<"Cost:"<<"\033[32m"<<CostofDelete[pDelete]<<"\033[0m"<<endl;
        else
            cout<<"MAX"<<endl;

        cout << "(PRESS 'p') 2. Increase foundamental reward by 1.                \t";
        if(pReward<3)
            cout<<"Cost:"<<"\033[32m"<<CostofReward[pReward]<<"\033[0m"<<endl;
        else
            cout<<"MAX"<<endl;

        cout << "(PRESS 'w') 2. Increase additional reward for continuous success.\t";
        if(pCombine<3)
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

        for(int i=1;i<=90;i++)
            cout<<'-';
        cout<<endl;

        
        switch(ErrorCode)
        {
            case 0://normal
                cout<<"\033[32m";
                cout<<"Successful! The position you chose is safe."<<endl;
                cout<<"\033[0m";
                break;
            case 1://buy prop
                cout<<"\033[34m";
                cout<<"The prop is working! Notice the change of price."<<endl;
                cout<<"\033[0m";
                break;
            case 2://no sufficient eco
                cout<<"\033[33m";
                cout<<"Sorry! You cannot afford this prop or it is sold out. Try something else."<<endl;
                cout<<"\033[0m";
                break;
            case 3://invalid input
                cout<<"\033[33m";
                cout<<"Sorry! The position you entered is out of range. Try something else."<<endl;
                cout<<"\033[0m";
                break;
            case 4://repetive input
                cout<<"\033[33m";
                cout<<"Sorry! You have chosen this position. Try something else."<<endl;
                cout<<"\033[0m";
                break;
            case 5://unsuccessful attempt
                cout << "\033[31m";
                cout<<"Bad luck! There is a mine at the position you chose."<<endl;
                cout<<"Mines have been rearranged..."<<endl;
                cout<<"\033[0m";
                break;
            default:
                cout << "\033[35m";
                cout<<"Welcome to the game!"<<endl;
                cout<<"\033[0m";
                break;
        }
        
        if(TotalStep>0&&TotalStep%10==0)
            cout<<"\033[1;35m"<<"YOU HAVE TRIED "<<TotalStep<<" STEPS"<<endl;
        cout<<"\033[0m";

        cout<<"Please choose a position or buy props: ";

        //read the coordinate or player's choice
        int PlayerX=-1,PlayerY=-1;
        string input;
        getline(cin,input);
        int length=input.size();
        for(int i=0;i<length;i++)
        {
            if(input[i]>='a'&&input[i]<='h')
                PlayerX=input[i]-'a';
            else if(input[i]>='A'&&input[i]<='H')
                PlayerX=input[i]-'A';
            else if(input[i]>='1'&&input[i]<='8')
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
                    ErrorCode=2;
                goto loop;
            }
            else if(input[i]=='p'||input[i]=='P')
            {
                if(eco>=CostofReward[pReward]&&pReward<3)
                {
                    ErrorCode=1;
                    incre=-CostofReward[pReward];
                    eco+=incre;
                    pReward++;
                }
                else
                    ErrorCode=2;
                goto loop;
            }
            else if(input[i]=='w'||input[i]=='W')
            {
                if(eco>=CostofCombine[pCombine]&&pCombine<3)
                {
                    ErrorCode=1;
                    incre=-CostofCombine[pCombine];
                    eco+=incre;
                    pCombine++;
                }
                else
                    ErrorCode=2;
                goto loop;
            }
        }

        if(PlayerX<0||PlayerY<0)
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
        //if fails
        if(MineGrid[PlayerX][PlayerY]==true)
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
            AllSpace=GRID_SIZE*GRID_SIZE;
            for(int i=1;i<=3;i++)
                cout<<"\033[1;31m"<<"BOOM!"<<"\033[0m"<<endl;
            Failure(PlayerX,PlayerY);
            SLEEP_SEC(1);

            for(int i=0;i<GRID_SIZE;i++)
                for(int j=0;j<GRID_SIZE;j++)
                        PlayerOp[i][j]='o';

            for(int i=0;i<NUM;i++)
                MineList[i].status=false;
            for(int i=0;i<ExistMine;i++)
            {
                int res=RandomCreate(i);
                if(res) i--;
            }
            RecordInGrid();
        }
        //if succeed
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

            FailCode=0,ErrorCode=0;
            SuccStep++,FailStep=0;
            maxsucc=max(SuccStep,maxsucc);
            AllSpace--;
            incre=(1+(SuccStep-1)*0.4*(pCombine+1))*(pReward+1);
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