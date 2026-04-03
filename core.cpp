#include <bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;const int MAXN=20;
const int SIZE=7;const int NUM=12;

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

int PlayerOp[SIZE][SIZE];//0--unchosen,1--chosen,2--end

/*---declaration of functions---*/
void ClearGrid();
void PrintGrid();
void RecordInGrid();
int RandomCreate(int);
void RandomMove();
int CheckNeighbors(int,int);
void EndofGame();
int DeleteMine();


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

int CheckNeighbors(int row,int col)
{
    for(int i=row-1;i<=row+1;i++)
    {
        for(int j=col-1;j<=col+1;j++)
        {
            if(i<0||i>=SIZE||j<0||j>=SIZE)
                continue;
            if(MineGrid[i][j].occupied==true)
                return 1;
        }
    }
    return 0;
}

void PrintGrid()
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<i+1<<" ";
        for(int j=0;j<SIZE;j++)
        {
            if(PlayerOp[i][j])
            {
                if(PlayerOp[i][j]==3)
                {
                    cout<<"? ";
                    continue;
                }
                if(CheckNeighbors(i,j))
                    cout<<"+ ";
                else
                    cout<<"- ";
            }
            else
                cout<<"o ";
        }
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
        if(MineGrid[x][y].occupied==false)
        {
            MineGrid[x][y].occupied=true;
            MineGrid[x][y].index=i;
        }
        else
        {
            int rst=MineGrid[x][y].index;
            MineGrid[x][y].occupied=false;

            while(RandomCreate(rst)); 
            x=MineList[rst].posx;
            y=MineList[rst].posy;
            MineGrid[x][y].occupied=true;
            MineGrid[x][y].index=rst;

            while(RandomCreate(i));
            x=MineList[i].posx;
            y=MineList[i].posy;
            MineGrid[x][y].occupied=true;
            MineGrid[x][y].index=i;
        }
    }
}

int RandomCreate(int i)
{   
    //create a mine, index of which is i.
    MineList[i].posx=rand()%7;
    MineList[i].posy=rand()%7;

    if(MineList[i].posx==SIZE/2&&MineList[i].posy==SIZE/2)
        return 1;

    for(int j=0;j<NUM;j++)
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

void RandomMove()
{
    for(int i=0;i<NUM;i++)
    {
        //randomly decide which direction to go.
        int Dir=rand()%4;
        if(MineList[i].status==false)
            continue;

        switch (Dir){
            case 0:
                MineList[i].posx++;
                //check if the mine is still in the grid.
                if(MineList[i].posx>=SIZE)
                    while(RandomCreate(i));                 
                break;
            case 1:
                MineList[i].posx--;
                if(MineList[i].posx<0)
                    while(RandomCreate(i));
                break;
            case 2:
                MineList[i].posy++;
                if(MineList[i].posy>=SIZE)
                    while(RandomCreate(i));
                break;
            case 3:
                MineList[i].posy--;
                if(MineList[i].posy<0)
                    while(RandomCreate(i));
                break;
            default:
                break;
        }
        if(MineList[i].posx==SIZE/2&&MineList[i].posy==SIZE/2)
            MineList[i].status=false;
    }
}

void PrintMine()
{
    cout<<"  ";
    for(int i=1;i<=SIZE;i++)
        cout<<i<<" ";
    cout<<endl;
    for(int i=0;i<SIZE;i++)
    {    
        cout<<i+1<<" ";
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
    ;
}

int main() 
{
    srand((unsigned)time(NULL));//do not use it in the loop

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        {
            if(i==SIZE/2&&j==SIZE/2)
                PlayerOp[i][j]=3;
            else
                PlayerOp[i][j]=0;
        }
    PrintGrid();

    ClearGrid();
    for(int i=0;i<NUM;i++)
    {
        int res=RandomCreate(i);
        if(res) i--;
    }
    RecordInGrid();
    //PrintMine();


    /*--testcode--
    for(int i=0;i<NUM;i++)
        cout<<current[i].posx<<' '<<current[i].posy<<endl;
    */

    int k=0;
    while(1)
    {
        int PlayerX,PlayerY;
        cin>>PlayerX>>PlayerY;
        PlayerX--; PlayerY--;
        if(PlayerX<0||PlayerX>=SIZE||PlayerY<0||PlayerY>=SIZE)
        {
            cout<<"Invalid input. Please enter again."<<endl;
            continue;
        }
        else if(PlayerX==SIZE/2&&PlayerY==SIZE/2)
        {
            cout<<"Invalid input. Please enter again."<<endl;
            continue;
        }
        else
        {
            if(PlayerOp[PlayerX][PlayerY]==1)
            {
                cout<<"You have chosen this place. Please enter again."<<endl;
                continue;
            }
        }


        if(MineGrid[PlayerX][PlayerY].occupied==true)
        {
            PlayerOp[PlayerX][PlayerY]=2;
            EndofGame();
            cout<<"Sorry. You lose!"<<endl;
            cout<<"The total number of steps is "<<k<<'.'<<endl;
        }
        else
        {
            k++;
            if(k%8==0)
            {
                char index='A'+DeleteMine();
                //cout<<"Delete mine "<<index<<endl;
            }
            PlayerOp[PlayerX][PlayerY]=1;
            ClearGrid();
            RandomMove();
            RecordInGrid();
            PrintGrid();
            //PrintMine();
        }
    }
}