//
// Created by Phinease on 2019-02-11.
//

#ifndef BRIDGE_DATA_ANALYSE_PROCESS_H
#define BRIDGE_DATA_ANALYSE_PROCESS_H
#endif //BRIDGE_DATA_ANALYSE_PROCESS_H


#include "game.h"
#include <time.h>


extern int run[2];


clock_t start_t, end_t;
double total_t;
int yes;


void all();
void ask(int signal);
void game_circle();
void analyse();
void ask_data();



void all()
{
    start_t=clock();
    int i;
    for(i=0;i<run[1];i++){
        //game_id=mysql_search();
        //game_id++;
        //printf("GAME ID: %d\n",game_id);
        game_circle();
        game_time++;
        //write_game();
    }
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
}


int debug_mode()
{
    int wrong,answer;
    printf("Debugging?(0 for yes, 1 for no)\n");
    scanf("%d",&answer);
    while(answer<0 || answer>7){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter, retry.\n");
        scanf("%d",&answer);
    }
    if(answer==0){
        srand(1);
        player_random[0]=2;
        player_random[1]=1;
        player_random[2]=2;
        player_random[3]=1;
        simulation_times=1000;
        run[1]=1000;
        print_func[0]=0;
        print_func[1]=0;
        print_func[2]=50;
        return 0;
    } else{
        return 1;
    }
}

void ask(int signal)
{
    if(signal==0) return;
    int i,j,wrong,all_random=0,attention=0;
    printf("How many times would you like to play?\n");
    printf("Considering the RAM,limited below 1000 times.\n");
    scanf("%d",&run[1]);
    while(run[1]<0 || run[1]>1000){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        printf("Wrong enter, retry.\n");
        scanf("%d",&run[1]);
    }
    printf("which player would you like it to be random?\n");
    printf("(5 for all random, 6 for all Monte-Carol)\n");
    printf("(7 for West-East Monte-Carol and South-North Random)\n");
    for(i=0;i<4;i++){
        printf("Would player %s be random, type 2 for active Monte-Carol, 1 for yes, 0 for no:\n",Users_name[i]);
        scanf("%d",&player_random[i]);
        while(player_random[i]<0 || player_random[i]>7){
            while ((wrong = getchar()) != EOF && wrong != '\n'){
                ;
            }
            printf("Wrong enter, retry.\n");
            scanf("%d",&player_random[i]);
        }
        if(player_random[i]==1 || player_random[i]==2) attention++;
        if(player_random[i]==5 || player_random[i]==6){
            wrong=player_random[i];
            all_random=wrong;
            for(j=0;j<4;j++){
                player_random[j]=wrong-4;
            }
            attention=4;
            break;
        }
        if(player_random[i]==7){
            player_random[0]=2;
            player_random[1]=1;
            player_random[2]=2;
            player_random[3]=1;
            attention=4;
            break;
        }
    }
    for(i=0;i<4;i++){
        if(player_random[i]==2){
            printf("Monte_Carol for how mant times of sampling?\n");
            scanf("%d",&simulation_times);
            while(simulation_times <0){
                while ((wrong = getchar()) != EOF && wrong != '\n'){
                    ;
                }
                printf("Wrong enter, retry.\n");
                scanf("%d",&simulation_times);
            }
            break;
        }
    }
    printf("Would you like to show all the procedure or just result?\n");
    printf("0 for just result, 1 for all procedure\n");
    scanf("%d",&print_func[0]);
    while(print_func[0] <0 || print_func[0] > 1){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter, retry.\n");
        scanf("%d",&print_func[0]);
    }
    if(attention==4 && print_func[0]==1){
        printf("Warning!!!\nThe automatic game is active.\n");
        printf("To see the procedure is not recommend and may influence the efficiency.\n");
        printf("0 for continue, 1 for reselect.\n");
        int warning;
        scanf("%d",&warning);
        while(warning <0 || warning > 1){
            while ((wrong = getchar()) != EOF && wrong != '\n'){
                ;
            }
            printf("Wrong enter, retry.\n");
            scanf("%d",&warning);
        }
        if(warning==1){
            ask(1);
            return;
        }
    }
    if(print_func[0]==0 && all_random!=5){
        printf("Would you like to check deviation?\n");
        printf("0 for yes, 1 for no\n");
        scanf("%d",&print_func[1]);
        while(print_func[1] <0 || print_func[1] > 1){
            while ((wrong = getchar()) != EOF && wrong != '\n'){
                ;
            }
            printf("Wrong enter, retry.\n");
            scanf("%d",&print_func[1]);
        }
        printf("How many percentage of deviation?\n");
        printf("This means the percentage of prediction whose exceeding parts don't suit the result.\n");
        printf("So enter a number between 0 and 100?\n");
        scanf("%d",&print_func[2]);
        while(print_func[2] <0 || print_func[2] > 100){
            while ((wrong = getchar()) != EOF && wrong != '\n'){
                ;
            }
            printf("Wrong enter, retry.\n");
            scanf("%d",&print_func[2]);
        }
    }
}


void game_circle()
{
    int i;
    initialization();
    free(p_of_data[game_time]);
    p_of_data[game_time]=(struct card_game_data*)malloc(sizeof(struct card_game_data));
    deal();
    //system("clear");
    process++; main_suit=4;
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
    if(print_func[0]==1) tricks();
    last_round();
    yes=win();
    if(print_func[0]==1) congratulation(yes);
    if(yes==0){
        win_rate[0]+=2;
        printf("NS win\tWE [%d]  NS [%d]  Game times [%d]\n",win_rate[1]/2,win_rate[0]/2,run[1]);
    }else if(yes==1){
        win_rate[1]+=2;
        printf("WE win\tWE [%d]  NS [%d]  Game times [%d]\n",win_rate[1]/2,win_rate[0]/2,run[1]);
    }else{
        win_rate[0]++;
        win_rate[1]++;
        printf("Even  \tWE [%d]  NS [%d]  Game times [%d]\n",win_rate[1]/2,win_rate[0]/2,run[1]);
    }
}


void analyse()
{
    printf("Result: Games: %d times\t ",run[1]);
    printf("WE win rate: %.2f%%\t",100*(float)win_rate[1]/(run[1]*2));
    printf("NS win rate: %.2f%%\n",100*(float)win_rate[0]/(run[1]*2));
    end_t=clock();
    total_t=(double)(end_t-start_t)/CLOCKS_PER_SEC;
    printf("This spends %5.4f seconds, %4.3fs per game.\n",total_t,total_t/run[1]);
    printf("%d deviations have happened.\n",print_func[3]);
}

void ask_data()
{
    char card_analyse[3];
    int wrong,c_num=-1;
    int time[13]={0};
    int card_info;
    int i;
    printf("Which card's data do you wanna verify?\n");
    printf("(C/D/H/S + 2/3/4/5/6/7/8/9/T/J/Q/K/A)\n");
    scanf("%s",card_analyse);
    while(card_analyse[2] != '\0'){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter, retry.\n");
        scanf("%s",card_analyse);
    }
    switch (card_analyse[0]){
        default:
            printf("Wrong enter, retry.\n");
            ask_data();
            break;
        case 'C':
            c_num=0;
            break;
        case 'D':
            c_num=1;
            break;
        case 'H':
            c_num=2;
            break;
        case 'S':
            c_num=3;
            break;
    }
    for(i=0;i<14;i++){
        if(card_analyse[1]==Height[i]){
            c_num+=i*4;
            break;
        }
    }
    printf("This is %d.%s data:\n",c_num,card_analyse);
    float per_simu[13]={0};
    int per_real[13]={0};
    for(i=0;i<run[1];i++){
        card_info=p_of_data[i]->card_round[c_num];
        per_simu[card_info]+=p_of_data[i]->card_simu[c_num];
        per_real[card_info]+=p_of_data[i]->card_real[c_num];
        time[card_info]++;
    }
    for(i=0;i<4;i++){
        printf("Round %2d \t\t\t",i+1);
    }
    printf("\n");
    for(i=0;i<4;i++){
        printf("%.2f\t\t\t\t",per_simu[i]);
    }
    printf("Simulation\n");
    for(i=0;i<4;i++){
        printf("%.2f -> %d/%d\t\t",(float)per_real[i]*100/time[i],per_real[i],time[i]);
    }
    printf("Real\n\n");
    for(i=4;i<8;i++){
        printf("Round %2d \t\t\t",i+1);
    }
    printf("\n");
    for(i=4;i<8;i++){
        printf("%.2f\t\t\t\t",per_simu[i]);
    }
    printf("Simulation\n");
    for(i=4;i<8;i++){
        printf("%.2f -> %d/%d\t\t",(float)per_real[i]*100/time[i],per_real[i],time[i]);
    }
    printf("Real\n\n");
    for(i=8;i<13;i++){
        printf("Round %2d \t\t\t",i+1);
    }
    printf("\n");
    for(i=8;i<13;i++){
        printf("%.2f\t\t\t\t",per_simu[i]);
    }
    printf("Simulation\n");
    for(i=8;i<13;i++){
        printf("%.2f -> %d/%d\t\t",(float)per_real[i]*100/time[i],per_real[i],time[i]);
    }
    printf("Real\n\n");
}

