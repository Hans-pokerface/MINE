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

const int GRID_SIZE=8;
const int NUM=30;
const int MAXN=NUM;

/*---definition of struct---*/
typedef struct
{
    bool status;//true--in grid; false--out of grid
    int posx;//[0,7]
    int posy;//[0,7]
} MineInfo;
MineInfo MineList[MAXN];

bool MineGrid[GRID_SIZE][GRID_SIZE];//ture:there is a mine

char PlayerOp[GRID_SIZE][GRID_SIZE];//'o':unchosen; '+':chosen

#endif