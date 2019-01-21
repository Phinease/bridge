//
// Created by Phinease on 2018-12-21.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef BRIDGE_GAME_H
#define BRIDGE_GAME_H

#endif //BRIDGE_GAME_H
#include "ai.h"


int Users_Nums[4][4][13],Cards_played[4],bid_Suit[4],bid_Num[4],card_num[13],player_random[4]={-1,-1,-1,-1};
int main_suit,local_suit,process,game,winner,WE_tricks,NS_tricks;
int bid_num,bid_suit,bid_result,bid_win,bid_dead;
char *Users_name[4]={"Player West","Player North","Player East","Player South"};
char U_N[4]={'W','N','E','S'};
char *Suits_name[4]={"C","D","H","S"};
char *Suits_fullname[5]={"Club","Diamond","Heart","Spade","none"};
char *Height[14]={"?","2","3","4","5","6","7","8","9","T","J","Q","K","A"};


int data[2]={0};
int print_func[3]={1,1,1};


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
void tricks();
int win();
void error_show(int random,int user_num);


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
    if(print_func[0]==1) printf("Give your proposition by typing the number.\n");
    if(print_func[0]==1) printf("1.Club 2.Diamond 3.Heart 4.Spade\n5.Pass 6.No suit\n");
    scanf("%d",&q);
    while(q<1 || q>6){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        if(print_func[1]==1) printf("You can not propose this, retry.\n");
        bid_user(user_num);
        return;
    }
    switch(q){
        default:
            if(print_func[0]==1) printf("How big you want it to be?\n");
            scanf("%d",&bid_Num[user_num]);
            while(bid_Num[user_num]<1 || bid_Num[user_num]>7){
                while ((wrong = getchar()) != EOF && wrong != '\n'){
                    ;
                }
                //system("clear");
                if(print_func[1]==1) printf("You can not propose this, retry.\n");
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
                        if(print_func[1]==1) printf("You can not propose this, retry.\n");
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
            if(print_func[0]==1) printf("How big you want it to be?\n");
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
                if(print_func[1]==1) printf("You can not propose this, retry.\n");
                bid_user(user_num);
                return;
            }
            if(bid_Num[user_num]>7){
                //system("clear");
                if(print_func[1]==1) printf("This proposition is impossible.\n");
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
        if(print_func[0]==1) printf("No one has given a propose. So we will redeal.\n\n\n");
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
        if(print_func[0]==1) printf("%s has won, so the main suit of this game is %s.\n\n",Users_name[i],Suits_fullname[bid_Suit[i]]);
        main_suit=bid_Suit[i];
        bid_result=bid_Num[i];
        bid_win=i;
        bid_dead=(bid_win+2)%4;
        process++;
    }
}

void card(int num_user,int print_func)
{
    int i,q,k=0;
    if(print_func==1) printf("Cards of %s:\n",Users_name[num_user]);
    for(i=0;i<4;i++){
        for(q=0;q<13;q++){
            if(Users_Nums[num_user][i][q]!=-1){
                card_num[k]=i+Users_Nums[num_user][i][q]*4;
                if(print_func==1) printf("%d.%s%s\t",k+1,Suits_name[i],Height[Users_Nums[num_user][i][q]]);
                k++;
            }
        }
        if(print_func==1) printf("\n");
    }
}

void print_card(int num_user)
{
    if(game==0){
        switch(process){
            default:
                if(num_user==bid_win){
                    card(bid_dead,print_func[0]); card(bid_win,print_func[0]);
                }else if(num_user==bid_dead){
                    card(bid_win,print_func[0]); card(bid_dead,print_func[0]);
                }else{
                    card(bid_dead,print_func[0]); card(num_user,print_func[0]);
                }
                break;
            case -1:
                card(num_user,print_func[0]);
                break;
            case 0:
                if(num_user==(bid_win+1)%4){
                    card(num_user,print_func[0]);
                }else if(num_user==bid_win){
                    card(bid_dead,print_func[0]); card(bid_win,print_func[0]);
                }else if(num_user==bid_dead){
                    card(bid_win,print_func[0]); card(bid_dead,print_func[0]);
                }else{
                    card(bid_dead,print_func[0]); card(num_user,print_func[0]);
                }
                break;
        }
    }else if(game==1){
        card((num_user+3)%4,print_func[0]);
        card((num_user+2)%4,print_func[0]);
        card((num_user+1)%4,print_func[0]);
        card(num_user,print_func[0]);
    }else{
        card(num_user,print_func[0]);
    }

}

void first_play_cards(int num_user)
{
    int card,wrong;
    local_suit = -1;
    tricks();
    if(print_func[0]==1) printf("Round%d -- First\n",process+1);
    print_card(num_user);
    if(player_random[num_user]==2) {
        card = simulation(1000,num_user);
    }else if (player_random[num_user]==1){
        card = randomPlayer(num_user,0);
        if(print_func[0]==1) printf("random: %d\n\n",card);
    }else {
        scanf("%d",&card);
    }
    while(card_num[card-1]==-1 || card<1 || card>13){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        if(print_func[1]==1) printf("Wrong enter. Try again.\n");
        scanf("%d",&card);
    }
    local_suit=card_num[card-1]%4;
    Cards_played[num_user]=card_num[card-1];
    wipe_card(num_user,card);
    //system("clear");
    //system("clear");
}

void play_card(int num_user)
{
    int i,q=0,card=-1,wrong;
    show();
    if(print_func[0]==1) printf("Round%d -- %s\n",process+1,Suits_fullname[local_suit]);
    print_card(num_user);
    if(player_random[num_user]==2) {
        card = simulation(1000,num_user);
    }else if (player_random[num_user]==1){
        card = randomPlayer(num_user,1);
        if(print_func[0]==1) printf("random: %d\n\n",card);
    }else {
        scanf("%d",&card);
    }
    while(card_num[card-1]==-1 || card<1 || card>13){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        if(print_func[1]==1) printf("Wrong enter. Try again.\n");
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
        if(print_func[1]==1) printf("You can not lay out this card. Try again.\n");
        if(print_func[1]==1) printf("You played a %s %s, you have %d cards of local suit,try again.\n\n",Suits_fullname[card_num[card-1]%4],Height[card_num[card-1]/4],q);
        error_show(card,num_user);
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
    if(print_func[0]==1) printf("%s has won.\n",Users_name[winner]);
    //write_tour(winner);
    for(i=0;i<4;i++){
        Cards_played[i]=0;
    }
    if (winner == 0 || winner == 2){
        WE_tricks++;
    } else if (winner == 1 || winner == 3){
        NS_tricks++;
    }
}

void show()
{
    int i;
    switch (process){
        default:
            if(print_func[0]==1) printf("history: ");
            for(i=0;i<4;i++){
                if(Cards_played[i]!=0){
                    if(print_func[0]==1) printf("%c.%s%s\t",U_N[i],Suits_name[Cards_played[i]%4],Height[Cards_played[i]/4]);
                }
            }
            if(print_func[0]==1) printf("\n");
            break;
        case -1:
            for(i=0;i<4;i++){
                if(bid_Num[i]!=-1 && bid_Num[i]!=0){
                    if(print_func[0]==1) printf("%s has proposed %s %d.\n",Users_name[i],Suits_fullname[bid_Suit[i]],bid_Num[i]);
                }else if(bid_Num[i]==0){
                    if(print_func[0]==1) printf("%s has passed.\n",Users_name[i]);
                }
            }
            if(print_func[0]==1) printf("\n");
            break;
    }
}

int win()
{
    tricks();
    if(bid_win/2==0)
    {
        if(WE_tricks>=(bid_result!=-1)*bid_result+6){
            if(print_func[0]==1) printf("Player Est and West win!!!\n");
            return 1;
        }else{
            if(print_func[0]==1) printf("Player South and North win!!!\n");
            return 0;
        }
    }else{
        if(NS_tricks>=(bid_result!=-1)*bid_result+6){
            if(print_func[0]==1) printf("Player South and North win!!!\n");
            return 0;
        }else{
            if(print_func[0]==1) printf("Player Est and West win!!!\n");
            return 1;
        }
    }
}

void last_round()
{
    int i,q,k;
    if(print_func[0]==1) printf("last round: ");
    for(i=0;i<4;i++){
        for(q=0;q<4;q++){
            for(k=0;k<13;k++){
                if(Users_Nums[i][q][k]!=-1){
                    Cards_played[i]=Users_Nums[i][q][k]*4+q;
                    if(print_func[0]==1) printf("%c.%s%s\t",U_N[i],Suits_name[q],Height[Users_Nums[i][q][k]]);
                }
            }
        }
    }
    if(print_func[0]==1) printf("\n");
    compare_cards();
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
    //system("clear");

}

void tricks()
{
    if(bid_result!=-1){
        if(print_func[0]==1) printf("The bid is %d, WE tricks is %d,NS tricks is %d.\n",bid_result,WE_tricks,NS_tricks);
    }else{
        if(print_func[0]==1) printf("WE %d\tNS %d.\n",WE_tricks,NS_tricks);
    }
}


int StrToInt(const char *str)
{
    int n = 0;
    while (*str != 0)
    {
        int c = *str - '0';
        n = n * 10 + c;
        ++str;
    }
    return n;
}

void error_show(int random,int user_num)
{
    int c=card_num[random-1];
    printf("Error user %s:\n",Users_name[user_num]);
    printf("Random_player: %d\tCard: %d.%s%s\n\n",player_random[user_num],random,Suits_name[c%4],Height[c/4]);
    card(0,1); card(1,1); card(2,1); card(3,1);
    system("read -p 'Press Enter to continue...'");
}