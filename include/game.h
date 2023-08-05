typedef struct
{
    int row;
    int col;
    char symbol;
}Mark;typedef struct 
{
    Mark paper[3][3][3][3];
    unsigned int X;
    unsigned int O;
}TicTacToe;
typedef struct
{
    TicTacToe game;
    Player playerX;
    Player playerO;
    char turn;
    unsigned int game_mode;
}Game;
Game* newGame(Game*);
bool chechForResult(const TicTacToe* const a, int);
TicTacToe* newTicTacToe();
bool Checkkhali(int regionbig, TicTacToe* jadval);
void drawTicTacToe(TicTacToe* const a);
void Selected(int* regionBig , int* regionSmall,TicTacToe* jadval, char symbol);
void Paksaziregion(TicTacToe* jadval, int regionBig, char ch2);
char Check(int answer[3][3]);
void deleteGame(Game* a);//void reset(Game* const a);void clearPaper(TicTacToe* a);
void deleteTicTacToe(TicTacToe* a);
#include "../src/game.c"