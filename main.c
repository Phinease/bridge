#include "process.h"

int run[2]={-1,-1};


int main(){
    srand(1);
    int wrong;
    printf("Which kinds of game you would like to play?\n\n");
    printf("1.Game closed no bid with random player\n");
    printf("2.Game open no bid with random player\n\n");
    printf("Choice by taping the number.\n");
    scanf("%d",&run[0]);
    while(run[0]<1 || run[0]>2){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        printf("Wrong enter, retry.\n");
        main();
        return -1;
    }
    printf("How many times would you like to play?\n");
    scanf("%d",&run[1]);
    while(run[1]<0){
        while ((wrong = getchar()) != EOF && wrong != '\n'){
            ;
        }
        //system("clear");
        printf("Wrong enter, retry.\n");
        scanf("%d",&run[1]);
    }
    ask();
    all();
    return 0;
}