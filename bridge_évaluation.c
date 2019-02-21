#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int Users_Nums[4][4][13],Cards_played[4],bid_Suit[4],bid_Num[4],card_num[13],player_random[4]={-1,-1,-1,-1};
int main_suit,local_suit,process,game,winner,WE_tricks,NS_tricks;
int bid_num,bid_suit,bid_result,bid_win,bid_dead;
char *Users_name[4]={"Player West","Player North","Player East","Player South"};
char *Suits_name[4]={"C","D","H","S"};
char *Suits_fullname[5]={"Club","Diamond","Heart","Spade","none"};
char *Height[14]={"?","2","3","4","5","6","7","8","9","T","J","Q","K","A"};


void initialization();
void deal();
void bid();
void bid_user(int user_num);
void print_card(int num_user);
void first_play_cards(int num_user);
void play_card(int num_user);
void wipe_card(int num_user,int card);
void compare_cards();
void show();
void last_round();
void win();
int randomPlayer(int player, int firstOrNot);
void tricks();


void game_bid_close();
void game_bid_open();
void game_open();
void game_close();


int main(){
    srand(time(NULL));
    int i,k,wrong;
    printf("Which kinds of game you would like to play?\n\n");
    printf("1.Game open with bid  2.Game close with bid\n");
    printf("3.Game open without bid  4.Game close without bid\n");
    printf("5.Game open no bid with random player\n");
    printf("6.Game closed no bid with random player\n\n");
    printf("Choice by taping the number.\n");
    scanf("%d",&i);
    while(i<1 || i>6){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        printf("Wrong enter, retry.\n");
        main();
        return -1;
    }
    switch (i){
        default:
            break;
        case 1:
            game_bid_open();
            break;
        case 2:
            game_bid_close();
            break;
        case 3:
            game_open();
            break;
        case 4:
            game_close();
            break;
        case 5:
            printf("which player would you like it to be random?\n");
            for(i=0;i<4;i++){
                printf("Would player %s be random, type 1 for yes, 0 for no:\n",Users_name[i]);
                scanf("%d",&player_random[i]);
                while(player_random[i] != 0 && player_random[i] != 1){
                    while ((wrong = getchar()) != EOF && wrong != '\n'){
                        ;
                    }
                    printf("Wrong enter, retry.\n");
                    scanf("%d",&player_random[i]);
                }
            }
            game_open();
            break;
        case 6:
            printf("which player would you like it to be random?\n");
            for(i=0;i<4;i++){
                printf("Would player %s be random, type 1 for yes, 0 for no:\n",Users_name[i]);
                scanf("%d",&player_random[i]);
                while(player_random[i] != 0 && player_random[i] != 1){
                    while ((wrong = getchar()) != EOF && wrong != '\n'){
                        ;
                    }
                    printf("Wrong enter, retry.\n");
                    scanf("%d",&player_random[i]);
                }
            }
            game_close();
            break;
    }
    return 0;
}


void initialization(){
    process=-1; WE_tricks=0; NS_tricks=0; winner=-1; game=0;
    bid_num=-1; bid_suit=-1; bid_win=-1; bid_result=-1; bid_dead=-1;
    int i,q,k;
    for(i=0;i<4;i++){
        for(q=0;q<4;q++){
            for(k=0;k<13;k++){
                Users_Nums[i][q][k]=-1;
            }
        }
        bid_Num[i]=-1;
        bid_Suit[i]=-1;
    }
}
int randomPlayer (int player, int firstOrNot) {
    int nbCard = 0, localNbCard = 0, result;
    for(int i =0; i < 4; i++) {
        for(int j =0; j<13; j++) {
            if(Users_Nums[player][i][j] != -1) {
                nbCard++;
            }
        }
    }
    if(firstOrNot == 0) {
        result = rand()%nbCard+1;
        printf("%d\n", result);
        return result;
    }
    else {
        for(int i =0; i < 13; i++) {
            if(Users_Nums[player][local_suit][i] != -1) {
                localNbCard++;
            }
        }
        if(localNbCard==0) {
            result = (rand()%nbCard)+1;
            printf("%d\n", result);
            return result;
        }
        else {
            nbCard = 0;
            for(int i =0; i < local_suit; i++) {
                for(int j =0; j<13; j++) {
                    if(Users_Nums[player][i][j] != -1) {
                        nbCard++;
                    }
                }
            }
            result = nbCard + (rand()%localNbCard)+1;
            printf("%d\n",result);
            return result;
        }
    }
}

void deal()
{
    int Poker[52],Allcards[52],Users_Cards[4][13],count[4]={0,0,0,0};
    int num,i=0,q=0,k=0,t=0,temp=0;
    for(i=1;i<=52;i++){
        Poker[q]=i;
        q++;
    }
    for(i=0;i<52;i++){
        Allcards[i]=0;
    }
    while (t<52){
        num=Poker[rand()%52];
        for(q=0;q<52;q++){
            if(num!=Allcards[q]){
                temp++;
            }
        }
        if(temp==52 && num!=0){
            Allcards[t]=num;
            t++;
            Users_Cards[t%4][count[t%4]++]=num;
        }
        temp=0;
    }
    for(i=0;i<4;i++){
        for(q=0;q<4;q++){
            count[q]=0;
        }
        for(q=0;q<13;q++){
            Users_Nums[i][Users_Cards[i][q]%4][count[Users_Cards[i][q]%4]]=Users_Cards[i][q]/4;
            if(Users_Cards[i][q]/4==0){
                Users_Nums[i][Users_Cards[i][q]%4][count[Users_Cards[i][q]%4]]=13;
            }
            count[Users_Cards[i][q]%4]++;
        }
    }
    for(i=0;i<4;i++){
        for(t=0;t<4;t++){
            for(q=0;q<13;q++){
                for(k=q;k<13;k++){
                    if(Users_Nums[i][t][k]>Users_Nums[i][t][q]){
                        temp=Users_Nums[i][t][k];
                        Users_Nums[i][t][k]=Users_Nums[i][t][q];
                        Users_Nums[i][t][q]=temp;
                    }
                }
            }
        }
    }
}

void wipe_card(int num_user,int card){
    int i,q;
    for(i=0;i<4;i++){
        for(q=0;q<13;q++){
            if(i+Users_Nums[num_user][i][q]*4==card_num[card-1]){
                Users_Nums[num_user][i][q]=-1;
            }
        }
    }
    for(i=0;i<13;i++){
        card_num[i]=-1;
    }
}

void bid_user(int user_num)
{
    int i,q,wrong;
    bid_Num[user_num]=-1;
    show();
    print_card(user_num);
    printf("Give your proposition by typing the number.\n");
    printf("1.Club 2.Diamond 3.Heart 4.Spade\n5.Pass 6.No suit\n");
    scanf("%d",&q);
    while(q<1 || q>6){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        printf("You can not propose this, retry.\n");
        bid_user(user_num);
        return;
    }
    switch(q){
        default:
            printf("How big you want it to be?\n");
            scanf("%d",&bid_Num[user_num]);
            while(bid_Num[user_num]<1 || bid_Num[user_num]>7){
                while ((wrong = getchar()) != EOF && wrong != '\n'){
                    ;
                }
                //system("clear");
                printf("You can not propose this, retry.\n");
                bid_user(user_num);
                return;
            }
            for(i=0;i<1;){
                if(bid_Num[user_num]<=bid_num){
                    if(bid_Num[user_num]==bid_num && q-1>bid_suit){
                        bid_num=bid_Num[user_num];
                        bid_suit=q-1;
                        i++;
                    }else{
                        //system("clear");
                        printf("You can not propose this, retry.\n");
                        bid_user(user_num);
                        return;
                    }
                }else{
                    bid_num=bid_Num[user_num];
                    bid_suit=q-1;
                    i++;
                }
            }
            bid_Suit[user_num]=q-1;
            bid_result=1;
            //system("clear");
            //system("clear");
            break;
        case 5:
            bid_result=0;
            bid_Num[user_num]=0;
            bid_num=bid_Num[user_num];
            //system("clear");
            //system("clear");
            break;
        case 6:
            printf("How big you want it to be?\n");
            scanf("%d",&bid_Num[user_num]);
            if(bid_Num[user_num]>=bid_num && bid_suit!=4){
                bid_num=bid_Num[user_num];
                bid_suit=4;
                bid_result=1;
                bid_Suit[user_num]=4;
                //system("clear");
                //system("clear");
            }else if(bid_Num[user_num]>bid_num && bid_suit==4){
                bid_num=bid_Num[user_num];
                bid_suit=4;
                bid_result=1;
                bid_Suit[user_num]=4;
                //system("clear");
                //system("clear");
            }else{
                //system("clear");
                printf("You can not propose this, retry.\n");
                bid_user(user_num);
                return;
            }
            if(bid_Num[user_num]>7){
                //system("clear");
                printf("This proposition is impossible.\n");
                bid_user(user_num);
                return;
            }
            break;
    }
}

void bid()
{
    int i,q=0,k=0;
    for(i=0;i<4;i++){
        bid_result=-1;
        bid_user(i);
        if(bid_result==0){
            q++;
        }else if(bid_result==1){
            q=0;
        }
    }
    if(q==4){
        //system("clear");
        printf("No one has given a propose. So we will redeal.\n\n\n");
        initialization();
        deal();
        bid();
    }else{
        k+=q;
        while(k!=3){
            for(i=0;i<4;i++){
                bid_result=-1;
                bid_user(i);
                if(bid_result==0){
                    k++;
                }else if(bid_result==1){
                    k=0;
                }
                if(k==3){
                    break;
                }
            }
        }
        for(i=0;i<4;i++){
            if(bid_Num[i]!=0){
                break;
            }
        }
        //system("clear");
        printf("%s has won, so the main suit of this game is %s.\n\n",Users_name[i],Suits_fullname[bid_Suit[i]]);
        main_suit=bid_Suit[i];
        bid_result=bid_Num[i];
        bid_win=i;
        bid_dead=(bid_win+2)%4;
        process++;
    }
}

void card(int num_user)
{
    int i,q,k=0;
    printf("Cards of %s:\n",Users_name[num_user]);
    for(i=0;i<4;i++){
        for(q=0;q<13;q++){
            if(Users_Nums[num_user][i][q]!=-1){
                card_num[k]=i+Users_Nums[num_user][i][q]*4;
                printf("%d.%s%s\t",k+1,Suits_name[i],Height[Users_Nums[num_user][i][q]]);
                k++;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_card(int num_user)
{
    if(game==0){
        switch(process){
            default:
                if(num_user==bid_win){
                    card(bid_dead); card(bid_win);
                }else if(num_user==bid_dead){
                    card(bid_win); card(bid_dead);
                }else{
                    card(bid_dead); card(num_user);
                }
                break;
            case -1:
                card(num_user);
                break;
            case 0:
                if(num_user==(bid_win+1)%4){
                    card(num_user);
                }else if(num_user==bid_win){
                    card(bid_dead); card(bid_win);
                }else if(num_user==bid_dead){
                    card(bid_win); card(bid_dead);
                }else{
                    card(bid_dead); card(num_user);
                }
                break;
        }
    }else if(game==1){
        card((num_user+3)%4);
        card((num_user+2)%4);
        card((num_user+1)%4);
        card(num_user);
    }else{
        card(num_user);
    }

}

void first_play_cards(int num_user)
{
    int card,wrong;
    extern int local_suit;
    local_suit = -1;
    tricks();
    printf("This is Round%d, your turn now.\n",process+1);
    printf("The main suit of this game is %s.\n", Suits_fullname[main_suit]);
    print_card(num_user);
    printf("Please lay out your card by taping its number.\n");
    if(player_random[num_user]==1) {
        card = randomPlayer(num_user,0);
    }
    else {
        scanf("%d",&card);
    }
    while(card_num[card-1]==-1 || card<1 || card>13){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter. Try again.\n");
        scanf("%d",&card);
    }
    local_suit=card_num[card-1]%4;
    Cards_played[num_user]=card_num[card-1];
    wipe_card(num_user,card);
    //system("clear");
    //system("clear");
    printf("The local suit is %s.\n",Suits_fullname[local_suit]);
}

void play_card(int num_user)
{
    int i,q=0,card=-1,wrong;
    show();
    printf("This is Round%d, your turn now.\n",process+1);
    printf("The main suit of this game is %s.\n", Suits_fullname[main_suit]);
    printf("The suit of this turn is %s.\n",Suits_fullname[local_suit]);
    print_card(num_user);
    printf("Please lay out your card by taping its number.\n");
    if(player_random[num_user]==1) {
        printf("Random User : ");
        card = randomPlayer(num_user,1);
    }
    else {
        scanf("%d",&card);
    }

    while(card_num[card-1]==-1 || card<1 || card>13){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter. Try again.\n");
        scanf("%d",&card);
    }
    if(card_num[card-1]%4==local_suit){
        Cards_played[num_user]=card_num[card-1];
        wipe_card(num_user,card);
        //system("clear");
        //system("clear");
        return;
    }else{
        for(i=0;i<13;i++){
            if(card_num[i]==-1) {
                continue;
            } else if(card_num[i]%4==local_suit){
                q++;
            }
        }
    }
    if(q!=0){
        //system("clear");
        printf("You can not lay out this card. Try again.\n");
        printf("You played a %s %s, you have %d cards of local suit,try again.\n\n",Suits_fullname[card_num[card-1]%4],Height[card_num[card-1]/4],q);
        play_card(num_user);
        return;
    } else{
        Cards_played[num_user]=card_num[card-1];
        wipe_card(num_user,card);
        //system("clear");
        //system("clear");
    }
}

void compare_cards()
{
    int i,flag=0,max=0;
    extern int winner;
    int verified[4]={-1,-1,-1,-1};
    for(i=0;i<4;i++){
        if(Cards_played[i]%4==main_suit){
            flag++;
            verified[i]=Cards_played[i]/4;
        }
    }
    if(flag==0){
        for(i=0;i<4;i++){
            if(Cards_played[i]%4==local_suit){
                verified[i]=Cards_played[i]/4;
            }
        }
    }
    for(i=0;i<4;i++){
        if(verified[i]==0){
            winner=i;
            break;
        }else if(verified[i]>max){
            max=verified[i];
            winner=i;
        }
    }
    printf("%s has won.\n",Users_name[winner]);
    for(i=0;i<4;i++){
        Cards_played[i]=0;
    }
    if (winner == 0 || winner == 2){
        WE_tricks++;
        printf("Player West and Est have got a trick.\n\n");
    } else if (winner == 1 || winner == 3){
        NS_tricks++;
        printf("Player North and South have got a trick.\n\n");
    }
}

void show()
{
    int i;
    switch (process){
        default:
            tricks();
            for(i=0;i<4;i++){
                if(Cards_played[i]!=0){
                    printf("%s played a %s%s.\n",Users_name[i],Suits_name[Cards_played[i]%4],Height[Cards_played[i]/4]);
                }
            }
            printf("\n");
            break;
        case -1:
            for(i=0;i<4;i++){
                if(bid_Num[i]!=-1 && bid_Num[i]!=0){
                    printf("%s has proposed %s %d.\n",Users_name[i],Suits_fullname[bid_Suit[i]],bid_Num[i]);
                }else if(bid_Num[i]==0){
                    printf("%s has passed.\n",Users_name[i]);
                }
            }
            printf("\n");
            break;
    }
}

void win()
{
    int i;
    tricks();
    if(bid_win/2==0)
    {
        if(WE_tricks>=(bid_result!=-1)*bid_result+6){
            for(i=0;i<3;i++) printf("Player Est and West win!!!\n");
        }else{
            for(i=0;i<3;i++) printf("Player South and North win!!!\n");
        }
    }else{
        if(NS_tricks>=(bid_result!=-1)*bid_result+6){
            for(i=0;i<3;i++) printf("Player South and North win!!!\n");
        }else{
            for(i=0;i<3;i++) printf("Player Est and West win!!!\n");
        }
    }
}

void last_round()
{
    int i,q,k;

    for(i=0;i<4;i++){
        for(q=0;q<4;q++){
            for(k=0;k<13;k++){
                if(Users_Nums[i][q][k]!=-1){
                    Cards_played[i]=Users_Nums[i][q][k]*4+q;
                    printf("%s played has a %s%s.\n",Users_name[i],Suits_name[q],Height[Users_Nums[i][q][k]]);
                }
            }
        }
    }
    compare_cards();
    tricks();
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
    //system("clear");

}

void game_bid_close() //game0
{
    int i;
    initialization();
    deal();
    bid();
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
    first_play_cards((bid_win+1)%4);
    for(i=2;i<5;i++) play_card((bid_win+i)%4);
    compare_cards();
    process++;
    for(i=0;i<11;i++){
        first_play_cards((0+winner)%4);
        play_card((1+winner)%4);
        play_card((2+winner)%4);
        play_card((3+winner)%4);
        compare_cards();
        process++;
    }
    tricks();
    last_round();
    win();
}

void game_bid_open() //game1
{
    int i;
    initialization();
    game=1;
    deal();
    bid();
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
    first_play_cards((bid_win+1)%4);
    for(i=2;i<5;i++) play_card((bid_win+i)%4);
    compare_cards();
    process++;
    for(i=0;i<11;i++){
        first_play_cards((0+winner)%4);
        play_card((1+winner)%4);
        play_card((2+winner)%4);
        play_card((3+winner)%4);
        compare_cards();
        process++;
    }
    tricks();
    last_round();
    win();
}

void game_open() //gmae1
{
    int i;
    initialization();
    deal();
    //system("clear");
    game=1; process++; main_suit=4;
    first_play_cards(0);
    for(i=1;i<4;i++) play_card(i);
    compare_cards();
    process++;
    for(i=0;i<11;i++){
        first_play_cards((0+winner)%4);
        play_card((1+winner)%4);
        play_card((2+winner)%4);
        play_card((3+winner)%4);
        compare_cards();
        process++;
    }
    tricks();
    last_round();
    win();
}

void game_close() //game2
{
    int i;
    initialization();
    deal();
    //system("clear");
    game=2; process++; main_suit=4;
    first_play_cards(0);
    for(i=1;i<4;i++) play_card(i);
    compare_cards();
    process++;
    for(i=0;i<11;i++){
        first_play_cards((0+winner)%4);
        play_card((1+winner)%4);
        play_card((2+winner)%4);
        play_card((3+winner)%4);
        compare_cards();
        process++;
    }
    tricks();
    last_round();
    win();
}

void tricks()
{
    if(bid_result!=-1){
        printf("The bid is %d, WE tricks is %d,NS tricks is %d.\n\n",bid_result,WE_tricks,NS_tricks);
    }else{
        printf("WE tricks is %d,NS tricks is %d.\n\n",WE_tricks,NS_tricks);
    }
}
