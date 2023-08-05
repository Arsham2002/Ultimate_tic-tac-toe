void run()
{
    int rule = 1;
    Game* game = NULL;// آدرس بازی ذخیره شده در این متغیر قرار میگیرد، هرچند این بخش کامل نشده است
    while (rule)
    {
        clearscreen();
        rule = showMenu();
        switch(rule)
        {
            case 1:
                game = newGame(NULL);
                break;
            case 2:
                scores();
                break;
            case 3:
                if(game == NULL)
                    printf("You don't have save game\n");
                else
                    game = newGame(game);
                break;
            case 4:
                help();
                break;
            case 0:
                break;
            default:
                printf("What do you mean!\n");
                break;
        }
        printf("OK? Enter:");
        getchar();
    }
    deleteGame;
}
int showMenu()
{
    int rule;
    printf("0: Exit \n1: start a new game \n2: score board \n3: continue \n4: help \nEnter your choice: ");
    scanf("%d", &rule);
    getchar();
    return rule;
}
void help()
{
    clearscreen();
    TicTacToe* jadval = newTicTacToe((TicTacToe*)malloc(sizeof(TicTacToe)));;
    drawTicTacToe(jadval);
    printf("Shoma be sorat nobati dar in zamin doz bazi mikonid \nnafare aval bazikon x ");
    printf("yeki az 9 mantaghehaye bozorg va yeki az 9 taye kochak an ra entekhab mikonad \nbazikon badi bayad ");
    printf("az yeki az khanehayi ke dar khane bozorg hamshomare ba \nkhaneye kochak bazi shode tavasote bazikone ghabli ");
    printf("entekhab konad va be hamin tartib \nharmantaghei ke tasahab shavad mesle in ast ke dar mantaghe bozorg");
    printf("shoma yek bazi kardeid \nharkas dar mantaghe bozorg 3 radif jor konad barande un dast mibashad.\n");
    deleteTicTacToe(jadval);
}
void scores()
{
    FILE* players = fopen("players.dat", "rb");
    if(players == NULL)
    {
        printf("can't open file\n");
        return;
    }
    char name[40];int ID, score;
    while(!feof(players))
    {
        fread(name, sizeof(char), 40, players);
        if(feof(players))
            break;
        fread(&ID, sizeof(int), 1, players);
        fread(&score, sizeof(int), 1, players);
        printf("%-40s ID: %d\t score:%d\n", name, ID, score);
    }
}