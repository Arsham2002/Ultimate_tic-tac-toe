Player* newPlayer(Player* player)
{// این تابع بازیکنان با نام جدید و کد جدید را در فایلی دیگر اضافه و یا بازیکنان قدیمی را وارد بازی میکند
    printf("Name of player: ");
    scanf("%40s", (*player).name);
    printf("And his/her ID: ");
    scanf("%d", &(*player).ID);
    FILE* file = fopen("Players.dat", "rb+");
    if(file == NULL)
    {
        fclose(file);
        FILE* file = fopen("Players.dat", "wb+");
        if(file == NULL)
        {
            printf("Can't save the player\n");
            return player;
        }
    }
    int id;
    char name[40];
    while(!feof(file))
    {
        fread(name, sizeof(char), 40, file);
        fread(&id, sizeof(int), 1, file);
        if(feof(file))
            break;
        if(id == (*player).ID && !strcmp(name, (*player).name))
        {
            fclose(file);
            return player;
        }
        fseek(file, sizeof(int), SEEK_CUR);
    }
    fwrite((*player).name, sizeof(char), 40, file);
    fwrite(&(*player).ID, sizeof(int), 1, file);
    int a = 0;
    fwrite(&a, sizeof(int), 1, file);
    fclose(file);
    return player;
}
void kasbemtiaz(Player* player, FILE* file)
{// این تابع قرار بود امتیاز برنده را در فایل بازیکنان یک واحد افزایش دهد،  اما متاسفانه درست کار نمیکند
    char name[40];int ID, emtiaz;
    while(!feof(file))
    {
        fread(name, sizeof(char), 40, file);
        if(feof(file))
            break;
        fread(&ID, sizeof(int), 1, file);
        fread(&emtiaz, sizeof(int),1, file);
        if(ID == (*player).ID && !strcmp(name, (*player).name))
        {
            emtiaz++;
            fseek(file, 0,SEEK_SET);
            while(!feof(file))
            {
                fread(name, sizeof(char), 40, file);
                if(feof(file))
                    break;
                fread(&ID, sizeof(int), 1, file);
                if(ID == (*player).ID && !strcmp(name, (*player).name))
                    fwrite(&emtiaz, sizeof(int), 1, file);
            }
        }
    }
}
void deletePlayer(Player* player)
{
    free(player);
}
