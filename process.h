//
// Created by Phinease on 2018-12-21.
//

#ifndef BRIDGE_PROCESS_H
#define BRIDGE_PROCESS_H

#endif //BRIDGE_PROCESS_H

#include "game.h"

extern int run[2];


clock_t start_t, end_t;
double total_t;
int yes;


void all();
void ask();
void game_open();
void game_close();


void all()
{
    start_t=clock();
    int i;
    for(i=0;i<run[1];i++){
        //game_id=mysql_search();
        //game_id++;
        //printf("GAME ID: %d\n",game_id);
        switch (run[0]){
            default:
                break;
            case 2:
                game_open();
                break;
            case 1:
                game_close();
                break;
        }
        //write_game();
    }
    //system("read -p 'Press Enter to continue...'");
    //system("clear");
    printf("Result: Games: %d times\t WE win rate: %.2f\tNS win rate: %.2f\n",run[1],(double) (data[0]*1000 / run[1])/1000,(double) (data[1]*1000 / run[1])/1000);
    end_t=clock();
    total_t=(double)(end_t-start_t)/CLOCKS_PER_SEC;
    printf("This spends %5.4f seconds, %4.3fs per game.",total_t,total_t/run[1]);
}

void ask()
{
    int i,wrong;
    printf("which player would you like it to be random?\n");
    for(i=0;i<4;i++){
        printf("Would player %s be random, type 2 for active Monte-Carol, 1 for yes, 0 for no:\n",Users_name[i]);
        scanf("%d",&player_random[i]);
        while(player_random[i] > 2 || player_random[i] < 0){
            while ((wrong = getchar()) != EOF && wrong != '\n'){
                ;
            }
            printf("Wrong enter, retry.\n");
            scanf("%d",&player_random[i]);
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
    printf("Would you like to see the errors?\n");
    printf("0 for yes, 1 for no\n");
    scanf("%d",&print_func[1]);
    while(print_func[1] <0 || print_func[1] > 1){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        printf("Wrong enter, retry.\n");
        scanf("%d",&print_func[1]);
    }
}


void game_open() //game1
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
    yes=win();
    if(yes==1){
        data[0]++;
        printf("SN win\tSN [%d]  WE [%d]\n",data[0],data[1]);
    }else if(yes==0){
        data[1]++;
        printf("WE win\tSN [%d]  WE [%d]\n",data[0],data[1]);
    }else{
        printf("Error.");
        system("read -p 'Press Enter to continue...'");
    }
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
    last_round();
    yes=win();
    if(yes==1){
        data[0]++;
    }else if(yes==0){
        data[1]++;
    }else{
        printf("Error.");
        system("read -p 'Press Enter to continue...'");
    }
}