#include "process.h"

int run[2]={-1,-1};
int data_check;


int main(){
    srand(2);
    int wrong,signal;
    for(int i=0;i<1000;i++){
        p_of_data[i]=NULL;
    }
    printf("Which kinds of game you would like to play?\n\n");
    printf("1.Game closed no bid with random player\n");
    printf("2.Game open no bid with random player\n\n");
    printf("Choice by taping the number.\n");
    scanf("%d",&game);
    while(game<1 || game>2){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        printf("Wrong enter, retry.\n");
        main();
        return -1;
    }
    signal=debug_mode();
    ask(signal);
    all();
    analyse();
    do{
        printf("Do you wanna check the data?(0 for yes,1 for no)\n");
        scanf("%d",&data_check);
        if(data_check==0){
            ask_data();
        }
    } while(data_check!=1);
    return 0;
}