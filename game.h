//
// Created by Phinease on 2019-02-11.
//


#ifndef BRIDGE_DATA_ANALYSE_GAME_H
#define BRIDGE_DATA_ANALYSE_GAME_H
#endif //BRIDGE_DATA_ANALYSE_GAME_H


/*
 * Rule basic: card_num based on a base 13
 * C/D/H/S(/N) -> 0/1/2/3(/4)
 * "2/3/4/5/6/7/8/9/T/J/Q/K/A" -> 0/1/2/3/4/5/6/7/8/9/10/11/12/13
 * Player:
 * 'W','N','E','S' -> "West","North","East","South" -> 0/1/2/3
 */


#include "ai.h"


int Users_Nums[4][13],Cards_played[4],bid_Suit[4],bid_Num[4],player_random[4]={-1,-1,-1,-1},card_using[13];
int main_suit,local_suit,process,game,winner,WE_tricks,NS_tricks;
int bid_num,bid_suit,bid_result,bid_win,bid_dead;
char *Users_name[4]={"Player West","Player North","Player East","Player South"};
char *Suits_fullname[5]={"Club","Diamond","Heart","Spade","none"};
char Height[13]={'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
char Suits_name[4]={'C','D','H','S'};
char U_N[4]={'W','N','E','S'};
int *p_c_using=card_using;
int simulation_times;


int win_rate[2]={0};
int print_func[4]={1,1,1,0};


void initialization();
void deal();
void bid();
void card(int num_user);
void bid_user(int user_num);
void print_card(int num_user);
void first_play_cards(int num_user);
void play_card(int num_user);
void wipe_card(int num_user,int c_num);
void compare_cards();
void show();
void last_round();
void tricks();
void error_show(int random,int user_num);
void call_cards(int num_user);
void check(int user_num,float p,int w,int last_winner);
void congratulation(int winner);
int win();



void initialization(){
    process=-1; WE_tricks=0; NS_tricks=0; winner=-1; game=0;
    bid_num=-1; bid_suit=-1; bid_win=-1; bid_result=-1; bid_dead=-1;
    int i,k;
    for(i=0;i<4;i++){
        for(k=0;k<13;k++){
            Users_Nums[i][k]=-1;
        }
        bid_Num[i]=-1;
        bid_Suit[i]=-1;
        Cards_played[i]=-1;
    }
}

void deal()
{
    int Poker[52],count[4]={0,0,0,0};
    int order[4][13];
    int num,i,q,k,t=0;
    for(i=0;i<52;i++){
        Poker[i]=i;
    }
    while (t<52){
        do{
            num=Poker[rand()%52];
        }while(num==-1);
        Users_Nums[t%4][count[t%4]++]=num;
        Poker[num]=-1;
        t++;
    }
    for(k=0;k<4;k++){
        count[0]=0;
        for(i=0;i<4;i++){
            for(q=0;q<13;q++){
                order[i][q]=-1;
            }
        }
        for(i=0;i<13;i++){
            num=Users_Nums[k][i];
            order[num%4][num/4]=1;
        }
        for(i=0;i<4;i++){
            for(q=0;q<13;q++){
                if(order[i][q]==1){
                    Users_Nums[k][count[0]++]=i+q*4;
                }
            }
        }
    }
}

void wipe_card(int num_user,int c_num){
    int i;
    for(i=0;i<13;i++){
        if(Users_Nums[num_user][i]==c_num){
            Users_Nums[num_user][i]=-1;
        }
        card_using[i]=-1;
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
        if(print_func[0]==1) printf("No one has given a propose. So we will deal again.\n\n\n");
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

void call_cards(int num_user){
    int i,q=0;
    for(i=0;i<13;i++){
        if(Users_Nums[num_user][i]!=-1){
            card_using[q++]=Users_Nums[num_user][i];
        }
    }
}

void card(int num_user)
{
    int i,num,count=1,line=0;
    printf("Cards of %s:\n",Users_name[num_user]);
    for(i=0;i<13;i++){
        if(Users_Nums[num_user][i]!=-1){
            num=Users_Nums[num_user][i];
            if(num%4!=line){
                printf("\n");
                line++;
            }
            card_using[count-1]=Users_Nums[num_user][i];
            printf("%d.%c%c\t",count++,Suits_name[num%4],Height[num/4]);
        }
    }
    printf("\n\n");
}

void print_card(int num_user)
{
    if(game==1){
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
    }else if(game==2){
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
    int card=-1,wrong;
    local_suit = -1;
    if(print_func[0]==1) {
        tricks();
        printf("Round%d -- First\n",process+1);
        print_card(num_user);
    }else{
        call_cards(num_user);
    }
    if(player_random[num_user]==2) {
        card = simulation(simulation_times,num_user);
    }else if (player_random[num_user]==1){
        card = random_player(p_c_using,1);
        if(print_func[0]==1) printf("Random: %d +1\n\n",card);
    }else {
        scanf("%d",&card);
        card--;
    }
    while(card_using[card]==-1 || card<0 || card>12){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("card_using[%d][%d]=%d\n",num_user,card,card_using[card]);
        printf("Wrong enter. Try again.\n");
        scanf("%d",&card);
    }
    local_suit=card_using[card]%4;
    Cards_played[num_user]=card_using[card];
    wipe_card(num_user,Cards_played[num_user]);
    //system("clear");
    //system("clear");
}

void play_card(int num_user)
{
    int i,q=0,card=-1,wrong;
    if(print_func[0]==1){
        show();
        printf("Round%d -- %s\n",process+1,Suits_fullname[local_suit]);
        print_card(num_user);
    }else{
        call_cards(num_user);
    }
    if(player_random[num_user]==2) {
        card = simulation(simulation_times,num_user);
    }else if (player_random[num_user]==1){
        card = random_player(p_c_using,0);
        if(print_func[0]==1) printf("Random: %d +1\n\n",card);
    }else {
        scanf("%d",&card);
        card--;
    }
    while(card_using[card]==-1 || card<0 || card>12){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter. Try again.\n");
        scanf("%d",&card);
    }
    if(card_using[card]%4==local_suit){
        Cards_played[num_user]=card_using[card];
        wipe_card(num_user,Cards_played[num_user]);
        //system("clear");
        //system("clear");
        return;
    }else{
        for(i=0;i<13;i++){
            if(card_using[i]==-1) {
                continue;
            } else if(card_using[i]%4==local_suit){
                q++;
                printf("card_using[%d].%d\n",i,card_using[i]);
                break;
            }
        }
    }
    if(q!=0){
        //system("clear");
        printf("You can not lay out this card. Try again.\n");
        printf("You played a %s %c, you have %d cards of %s,try again.\n\n",Suits_fullname[card_using[card]%4],Height[card_using[card]/4],q,Suits_fullname[local_suit]);
        system("read -p 'Press Enter to continue...'");
        play_card(num_user);
        return;
    } else{
        Cards_played[num_user]=card_using[card];
        wipe_card(num_user,Cards_played[num_user]);
        //system("clear");
        //system("clear");
    }
}

void compare_cards()
{
    int i,flag=0,max=0,last_winner;
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
    last_winner=winner;
    for(i=0;i<4;i++){
        if(verified[i]>max){
            max=verified[i];
            winner=i;
        }
    }
    for(i=0;i<4;i++){
        if(i==winner){
            p_of_data[game_time]->card_real[Cards_played[i]]=1;
        }else{
            p_of_data[game_time]->card_real[Cards_played[i]]=0;
        }
        p_of_data[game_time]->card_round[Cards_played[i]]=process;
    }
    if(print_func[0]==1) printf("%s has won.\n",Users_name[winner]);
    if(process!=12){
        for(i=0;i<4;i++){
            if(per_devia[i]>print_func[2] && (winner!=i && winner != (i+2)%4)) {
                if(print_func[1]==0){
                    printf("Deviation estimated. Would you like to check?(0 for yes)\n");
                    int yes;
                    scanf("%d",&yes);
                    if(yes == 0){
                        check(i,per_devia[i],winner,last_winner);
                    }
                }
                print_func[3]++;
            }
        }
    }
    //write_tour(winner);
    for(i=0;i<4;i++){
        Cards_played[i]=-1;
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
            printf("history: ");
            for(i=0;i<4;i++){
                if(Cards_played[i]!=-1){
                    printf("%c.%c%c\t",U_N[i],Suits_name[Cards_played[i]%4],Height[Cards_played[i]/4]);
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

int win()
{
    if(bid_win/2==0)
    {
        if(WE_tricks>=(bid_result!=-1)*bid_result+6){
            return 1;
        }else{
            return 0;
        }
    }else{
        if(NS_tricks>=(bid_result!=-1)*bid_result+6){
            return 0;
        }else{
            return 1;
        }
    }
}


void congratulation(int winner){
    tricks();
    if(winner==1){
        printf("Player Est and West win!!!\n");
    }else if(winner==0){
        printf("Player South and North win!!!\n");
    }else{
        printf("No5.Error.");
    }
}

void last_round()
{
    int i,k;
    if(print_func[0]==1) printf("last round: ");
    for(i=0;i<4;i++){
        for(k=0;k<13;k++){
            if(Users_Nums[i][k]!=-1){
                if(i==winner) local_suit=Users_Nums[i][k]%4;
                Cards_played[i]=Users_Nums[i][k];
                if(print_func[0]==1) printf("%c.%c%c\t",U_N[i],Suits_name[Users_Nums[i][k]%4],Height[Users_Nums[i][k]/4]);
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
        printf("The bid is %d, WE tricks is %d,NS tricks is %d\n",bid_result,WE_tricks,NS_tricks);
    }else{
        printf("WE %d\tNS %d\n",WE_tricks,NS_tricks);
    }
}


void error_show(int random,int user_num)
{
    printf("No6.Error\n");
    int c=card_using[random];
    printf("Error user %s:\n",Users_name[user_num]);
    printf("Random_player: %d\tCard: %d.%c%c\n\n",player_random[user_num],random,Suits_name[c%4],Height[c/4]);
    card(0); card(1); card(2); card(3);
    system("read -p 'Press Enter to continue...'");
}


void check(int user_num,float p,int w,int last_winner)
{
    printf("%s Robot: %.2f%%\twinner: %s\n",Users_name[user_num],p,Users_name[w]);
    printf("W: %c%c\t",Suits_name[Cards_played[0]%4],Height[Cards_played[0]/4]);
    printf("N: %c%c\t",Suits_name[Cards_played[1]%4],Height[Cards_played[1]/4]);
    printf("E: %c%c\t",Suits_name[Cards_played[2]%4],Height[Cards_played[2]/4]);
    printf("S: %c%c\n",Suits_name[Cards_played[3]%4],Height[Cards_played[3]/4]);
    printf("Last winner is %s\n",Users_name[last_winner]);
    printf("Local: %s\n",Suits_fullname[local_suit]);
    card(0); card(1); card(2); card(3);
    system("read -p 'Press Enter to continue...'");
}