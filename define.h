#ifndef DEFINE_H
#define DEFINE_H
#include <iostream>  //cin,cout
#include <cstdlib>   //rand(),system()
#include <ctime>     //time()
#include <iomanip>   //setpercision()
#include <string>    //string,getline()
#include <algorithm> //max()
#include <climits>   //optional()
#include <cctype>    //optional

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN system("cls")
#define SLEEP_SEC(sec) Sleep(sec * 1000)  
#else
#include <unistd.h>
#define CLEAR_SCREEN system("clear")
#define SLEEP_SEC(sec) sleep(sec)
#endif

using namespace std;

const int GRID_SIZE=7;
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
GridInfo MineGrid[GRID_SIZE][GRID_SIZE];

char PlayerOp[GRID_SIZE][GRID_SIZE];//0--unchosen,1--chosen,2--end

#endif