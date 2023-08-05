Game* newGame(Game* game1)
{
    Player* player1;
    Player* player2;
    TicTacToe* jadval;
    if(game1 == NULL)// اگر بازی ذخیره شده نباشد، malloc صورت میگیرد
    {
        player1 = newPlayer((Player*)malloc(sizeof(Player)));
        player2 = newPlayer((Player*)malloc(sizeof(Player)));
        jadval = newTicTacToe((TicTacToe*)malloc(sizeof(TicTacToe)));
    }
    else
    {
        *player1 = (*game1).playerX;
        *player2 = (*game1).playerO;
        *jadval = (*game1).game;
    }
    clearscreen();
    bool natije = true;//متغیر نتیجه نشان میدهد آیا در یکی از 9 منطقه کوچک برنده معلوم شده است یا خیر
    bool natijeasli = true;//این متغیر نشان میدهد در منطقه بزرگ آیا برنده معلوم شده است یا خیر
    drawTicTacToe(jadval);
    int regionBig;// این دو متغیر نشانی مناطقی هستند که بازیکن میخواهد در آن علامت بگذارد
    int regionSmall;
    printf("Choose the first regions for play (player x) \nFirst region of big table then the small one: ");
    scanf("%d %d", &regionBig, &regionSmall);
    getchar();
    Selected(&regionBig , &regionSmall, jadval, 'x');
    char ch = 'o', ch2;// کرکتر اولی حرکتی است که بازیکن جدید باید انجام دهد و کرکتر دوم حرکت بازیکن قبلی است
    int dast = 0;
    int doz[3][3] = {0};//این آرایه سه بعدی 9 خانه بزرگ زمین را مدل سازی میکند
    while(natijeasli)
    {
        while(natije)// هروقت بازیکنی در منطقه کوچکی برنده شود ازین حلقه خارج میشویم
        {
            clearscreen();
            drawTicTacToe(jadval);
            regionBig = regionSmall;
            printf("if you want to save this game enter -1 instead regionSmall\n");
            if(Checkkhali(regionBig, jadval))//اگر خانه ای که بازیکن جدید باید درآن بازی کند پر باشد وارد این اگر نمیشویم
            {
                printf("Enter your choice in region %d player %c: ", regionBig, ch);
                scanf("%d", &regionSmall);
            }
            else
            {
                printf("Enter another regionbig and small player %c: ", ch);
                scanf("%d %d", &regionBig, &regionSmall);
            }
            if(regionSmall == -1)// در صورت درخواست ذخیره وارد این اگر میشویم
            {
                Game* game = (Game*)malloc(sizeof(Game));
                (*game).turn = ch;
                (*game).playerX = *player1;
                (*game).playerO = *player2;
                (*game).game = *jadval;
                return game;
            }
            getchar();
            Selected(&regionBig , &regionSmall, jadval, ch);
            dast++;
            ch2 = ch;
            if(dast%2 != 0){ch = 'x';}
            else{ch = 'o';}
            natije = chechForResult(jadval , regionBig);
        }
        Paksaziregion(jadval, regionBig, ch2);

        int i, j;
        switch(regionBig)
        {
            case 1:
                i = 0;j = 0;
                break;
            case 2:
                i = 0;j = 1;
                break;
            case 3:
                i = 0;j = 2;
                break;
            case 4:
                i = 1;j = 0;
                break;
            case 5:
                i = 1;j = 1;
                break;
            case 6:
                i = 1;j = 2;
                break;
            case 7:
                i = 2;j = 0;
                break;
            case 8:
                i = 2;j = 1;
                break;
            case 9:
                i = 2;j = 2;
                break;
            default:
            break;
        }
        if(ch2 == 'x')
            doz[i][j] = 1;
        else   
            doz[i][j] = -1;
        if(dast>=6)// حداقل 6 بازی باید شده باشد که برنده ای داشته باشیم
        {
            char XorO = Check(doz);
            if(XorO != '0')
                natijeasli = false;
            if(XorO == 'x')
            {
                printf("Playerx won!!\n");
                ((*jadval).X)++;
            }
            if(XorO == 'o')
            {
                printf("playero won!!\n");
                ((*jadval).O)++;
            }
        }
        natije = true;
    }
    FILE* players = fopen("Players.dat" , "rb+");
    if((*jadval).X != 0)
        kasbemtiaz(player1 , players);
    else
        kasbemtiaz(player2 , players);
    fclose(players);
    deletePlayer(player1);deletePlayer(player2);
    deleteTicTacToe(jadval);
    return NULL;
}
void deleteGame(Game* game)
{
    free(game);
}
bool Checkkhali(int regionBig, TicTacToe* jadval)
{// این تابع چک میکند که آیا منطقه ای که بازیکن باید در آن بازی کند خالی است یا خیر
    int k,l;
    switch(regionBig)
    {
        case 1:
            k = 0;l = 0;
            break;
        case 2:
            k = 0;l = 1;
            break;
        case 3:
            k = 0;l = 2;
            break;
        case 4:
            k = 1;l = 0;
            break;
        case 5:
            k = 1;l = 1;
            break;
        case 6:
            k = 1;l = 2;
            break;
        case 7:
            k = 2;l = 0;
            break;
        case 8:
            k = 2;l = 1;
            break;
        case 9:
            k = 2;l = 2;
            break;
        default:
        break;
    }
    if((*jadval).paper[k][l][0][0].symbol != '0')
        return true;
    else
        return false;
}
TicTacToe* newTicTacToe(TicTacToe* jadval)//یک جدول خالی درست میکند
{
    (*jadval).X = 0;
    (*jadval).O = 0;
    for(int k = 0; k<3; k++)
        for(int l = 0; l<3; l++)
            for(int i = 0; i<3; i++)
                for(int j = 0; j<3; j++)
                {
                    (*jadval).paper[k][l][i][j].row = i;
                    (*jadval).paper[k][l][i][j].col = j;
                    (*jadval).paper[k][l][i][j].symbol = ' ';
                }
    return jadval;
}
void drawTicTacToe(TicTacToe* const jadval)//جدول را با تغییرات تا کنون را رسم میکند
{
    for(int k = 0; k<3; k++)
    {
        for(int i = 0; i<3; i++)
        {
            for(int l = 0; l<3; l++)
            {
                for(int j  = 0; j<3; j++)
                {
                    printf("%c ", (*jadval).paper[k][l][i][j].symbol);
                }
                if(l == 0 || l == 1)
                {
                    printf("!!!");
                }
            }
            puts("");
            if(i == 2 && (k == 0 || k == 1))
            {
                for(int w = 0; w<8; w++)
                    printf("!!!");
                puts("");
            }
        }
    }
}
void Selected(int* regionBig , int* regionSmall,TicTacToe* jadval, char symbol)
{//در این تابع در خانه منتخب حرکت بازیکن را ایفا میکند

    int k,l,i,j;
    switch(*regionBig)
    {
        case 1:
            k = 0;l = 0;
            break;
        case 2:
            k = 0;l = 1;
            break;
        case 3:
            k = 0;l = 2;
            break;
        case 4:
            k = 1;l = 0;
            break;
        case 5:
            k = 1;l = 1;
            break;
        case 6:
            k = 1;l = 2;
            break;
        case 7:
            k = 2;l = 0;
            break;
        case 8:
            k = 2;l = 1;
            break;
        case 9:
            k = 2;l = 2;
            break;
        default:
        break;
    }
    switch(*regionSmall)
    {
        case 1:
            i = 0;j = 0;
            break;
        case 2:
            i = 0;j = 1;
            break;
        case 3:
            i = 0;j = 2;
            break;
        case 4:
            i = 1;j = 0;
            break;
        case 5:
            i = 1;j = 1;
            break;
        case 6:
            i = 1;j = 2;
            break;
        case 7:
            i = 2;j = 0;
            break;
        case 8:
            i = 2;j = 1;
            break;
        case 9:
            i = 2;j = 2;
            break;
        default:
        break;
    }
    if((*jadval).paper[k][l][i][j].symbol == ' ')
        (*jadval).paper[k][l][i][j].symbol = symbol;
    else if((*jadval).paper[k][l][0][0].symbol == '0')
    {//وارد این در غیر اینصورت اگر میشویم اگر منطقه انتخاب شده کامل پر باشد
        printf("This regionBig is full. try again player %c \nTow region(Big & Small):  ", symbol);
        scanf("%d %d", regionBig, regionSmall);
        Selected(regionBig, regionSmall, jadval, symbol);
    }
    else
    {//وارد این درغیرصورت میشویم اگر خانه بازیکن اشتباها خانه پری را انتخاب کرده باشد
        printf("This regionsmall is full. try again player %c \none small region in %d: ", symbol, *regionBig);
        scanf("%d", regionSmall);
        Selected(regionBig, regionSmall, jadval, symbol);
    }

}
bool chechForResult(const TicTacToe* const jadval , int regionBig)
{//این تابع چک میکند که آیا در آخرین منطقه ای که در آن بازی شده برنده ای هست یا خیر
    int k,l;
    switch(regionBig)
    {
        case 1:
            k = 0;l = 0;
            break;
        case 2:
            k = 0;l = 1;
            break;
        case 3:
            k = 0;l = 2;
            break;
        case 4:
            k = 1;l = 0;
            break;
        case 5:
            k = 1;l = 1;
            break;
        case 6:
            k = 1;l = 2;
            break;
        case 7:
            k = 2;l = 0;
            break;
        case 8:
            k = 2;l = 1;
            break;
        case 9:
            k = 2;l = 2;
            break;
        default:
        break;
    }
    for(int i = 0; i<3; i++)
    {
        char symbol = (*jadval).paper[k][l][i][0].symbol;
        if(symbol != ' ')
            for(int j = 0; j<3; j++)
            {
                if(symbol != (*jadval).paper[k][l][i][j].symbol)
                    break;
                if(j == 2)
                    return false;
            }   
    }
    for(int j = 0; j<3; j++)
    {
        char symbol = (*jadval).paper[k][l][0][j].symbol;
        if(symbol != ' ')
            for(int i = 0; i<3; i++)
            {
                if(symbol != (*jadval).paper[k][l][i][j].symbol)
                    break;
                if(i == 2)
                    return false;
            }   
    }
    char symbol= (*jadval).paper[k][l][1][1].symbol;
    if(symbol == ' ')
        return true;
    for(int i = 0; i<3; i++)
    {
        int j = i;
        if(symbol != (*jadval).paper[k][l][i][j].symbol)
            break;
        if(i == 2)
            return false;
    }
    for(int i = 0; i<3; i++)
    {
        int j = 2-i;
        if(symbol != (*jadval).paper[k][l][i][j].symbol)
            break;
        if(i == 2)
            return false;
    }
    return true;
}
void Paksaziregion(TicTacToe* jadval, int regionBig, char ch2)
{// بعد از تصاحب یکی از منطقه ها آنرا از 0 و مرکزش را باعلامت  برنده آن منطقه پر میکند
    int k,l;
    switch(regionBig)
    {
        case 1:
            k = 0;l = 0;
            break;
        case 2:
            k = 0;l = 1;
            break;
        case 3:
            k = 0;l = 2;
            break;
        case 4:
            k = 1;l = 0;
            break;
        case 5:
            k = 1;l = 1;
            break;
        case 6:
            k = 1;l = 2;
            break;
        case 7:
            k = 2;l = 0;
            break;
        case 8:
            k = 2;l = 1;
            break;
        case 9:
            k = 2;l = 2;
            break;
        default:
        break;
    }
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(i != 1 || j != 1)
                (*jadval).paper[k][l][i][j].symbol = '0';
            else
                (*jadval).paper[k][l][1][1].symbol = ch2;
        }
    }
}
char Check(int answer[3][3])
{// این تابع چک میکند که آیا برنده نهایی معلوم شده است یا خیر
    for(int i = 0;i<3; i++)
    {
        int ch = answer[i][0];
        if(ch != 0)
        {
            for(int j = 0; j<3; j++)
            {
                if(answer[i][j]!=ch)
                    break;
                if(j == 2)
                {
                    if(ch == 1)
                        return 'x';
                    else
                        return 'o';
                }
            }
        }
    }
    for(int j = 0; j<3; j++)
    {
        int ch = answer[0][j];
        if(ch != 0)
        {
            for(int i = 0; i<3; i++)
            {
                if(answer[i][j]!=ch)
                    break;
                if(i == 2)
                {
                    if(ch == 1)
                        return 'x';
                    else
                        return 'o';
                }
            }
        }
    }
    int ch = answer[1][1];
    if(ch == 0)
        return '0';
    for(int i  = 0; i<3; i++)
    {
        int j = i;
        if(answer[i][j]!= ch)
            break;
        if(i == 2)
        {
            if(ch == 1)
                return 'x';
            else
                return 'o';
        }
    }
    for(int i  = 0; i<3; i++)
    {
        int j = 2-i;
        if(answer[i][j]!= ch)
            break;
        if(i == 2)
        {
            if(ch == 1)
                return 'x';
            else
                return 'o';
        }
    }
    return '0';
}
void deleteTicTacToe(TicTacToe* jadval)
{
    free(jadval);
}