typedef struct
{
    char name[40];
    int ID;
}Player;
Player* newPlayer(Player* player);
void deletePlayer(Player* player);
void kasbemtiaz(Player* , FILE*);
#include "../src/player.c"