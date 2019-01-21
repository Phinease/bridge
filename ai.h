 //
// Created by Phinease on 2018-12-21.
//

#ifndef BRIDGE_AI_H
#define BRIDGE_AI_H

#endif //BRIDGE_AI_H


struct simulate{
    int u_card[4][4][13];
    int p_card[4];
    int c_num[13];
    int suit;
    int num_user;
    int flag;
};

struct simulate a,b,*p1=&a,*p2=&b;
extern int Users_Nums[4][4][13],local_suit,Cards_played[4];


int simulation(int times,int player);
int randomPlayer (int player, int firstOrNot);


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
            return result;
        }
    }
}

int rp (int player, int firstOrNot,int suit) {
    int nbCard = 0, localNbCard = 0, result;
    for(int i =0; i < 4; i++) {
        for(int j =0; j<13; j++) {
            if(a.u_card[player][i][j] != -1) {
                nbCard++;
            }
        }
    }
    if(firstOrNot == 0) {
        result = rand()%nbCard+1;
        return result;
    }
    else {
        for(int i =0; i < 13; i++) {
            if(a.u_card[player][suit][i] != -1) {
                localNbCard++;
            }
        }
        if(localNbCard==0) {
            result = (rand()%nbCard)+1;
            return result;
        }
        else {
            nbCard = 0;
            for(int i =0; i < suit; i++) {
                for(int j =0; j<13; j++) {
                    if(a.u_card[player][i][j] != -1) {
                        nbCard++;
                    }
                }
            }
            result = nbCard + (rand()%localNbCard) +1;
            return result;
        }
    }
}



void wc(int num_user, int card)
{
    int i,q;
    for(i=0;i<4;i++){
        for(q=0;q<13;q++){
            if(i+a.u_card[num_user][i][q]*4==a.c_num[card-1]){
                a.u_card[num_user][i][q]=-1;
            }
        }
    }
    for(i=0;i<13;i++){
        a.c_num[i]=-1;
    }
}



void c()
{
    int num_user=a.num_user%4;
    int i,q,k=0;
    for(i=0;i<4;i++){
        for(q=0;q<13;q++){
            if(a.u_card[num_user][i][q]!=-1){
                a.c_num[k]=i+a.u_card[num_user][i][q]*4;
                k++;
            }
        }
    }
}


int fpc()
{
    int num_user=a.num_user%4;
    int card;
    a.suit = -1;
    c();
    card = rp(num_user,0,a.suit);
    a.suit=a.c_num[card-1]%4;
    a.p_card[num_user]=a.c_num[card-1];
    wc(num_user,card);
    return card;
}



int pc()
{
    int num_user=a.num_user%4;
    int card;
    c();
    card = rp(num_user,1,a.suit);
    a.p_card[num_user]=a.c_num[card-1];
    wc(num_user,card);
    return card;
}



int cc(int player)
{
    int i,max=0;
    int winner_s=-1;
    int verified[4]={-1,-1,-1,-1};
    for(i=0;i<4;i++){
        if(a.p_card[i]%4==a.suit){
            verified[i]=a.p_card[i]/4;
        }
    }
    for(i=0;i<4;i++){
        if(verified[i]==0){
            winner_s=i;
            break;
        }else if(verified[i]>max){
            max=verified[i];
            winner_s=i;
        }
    }
    /*
    for(i=0;i<4;i++){
        printf("user played cards.%d -- %s%s\n",i,Suits_name[a.p_card[i]%4],Height[a.p_card[i]/4]);
    }
     */
    if (winner_s == player){
        return 1;
    } else {
        return 0;
    }
}

int min_card(int num_user)
{
    int min_suit[4]={0};
    int i,j,min,result,suit=0;
    for(i=0;i<4;i++)
    {
        min=14;
        for(j=0;j<13;j++){
            if(a.u_card[num_user][i][j]<min && a.u_card[num_user][i][j]!=-1){
                min=a.u_card[num_user][i][j];
            }
        }
        min_suit[i]=min;
    }
    if(a.suit==-1){
        min=14;
        for(i=0;i<4;i++){
            if(min_suit[i]<min){
                min=min_suit[i];
                suit=i;
            }
        }
        result=min*4+suit;
    }else if (min_suit[a.suit]!=14 && min_suit[a.suit]!=-1){
        result=min_suit[a.suit]*4+a.suit;
    }else{
        min=14;
        for(i=0;i<4;i++){
            if(min_suit[i]<min){
                min=min_suit[i];
                suit=i;
            }
        }
        result=min*4+suit;
    }
    int q,k=0;
    for(i=0;i<4;i++){
        for(q=0;q<13;q++){
            if(a.u_card[num_user][i][q]!=-1){
                a.c_num[k]=i+a.u_card[num_user][i][q]*4;
                k++;
            }
            if(result==a.c_num[k-1]){
                return k;
            }
        }
    }
    return -1;
}

int simulation(int times,int player)
{
    int win_num[13]={0};
    int i,j,k;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            for(k=0;k<13;k++){
                b.u_card[i][j][k]=Users_Nums[i][j][k];
            }
        }
        b.p_card[i]=Cards_played[i];
    }
    for(i=0;i<13;i++){
        b.c_num[i]=-1;
    }
    b.suit=local_suit;
    b.num_user=player;
    b.flag=0;
    for(i=0;i<4;i++){
        if(b.p_card[i]==0) b.flag++;
    }
    int card=-1,max=0,tour,result=0;
    for(tour=0;tour<times;tour++){
        memcpy(p1,p2, sizeof(b));
        if(a.flag==4){
            card = fpc();
            a.num_user++;
            a.flag--;
        }
        for(i=0;i<a.flag;i++,a.num_user++){
            if(a.num_user==player){
                card = pc();
            }else{
                pc();
            }
        }
        if(cc(player)==1){
            win_num[card]++;
        }
    }
    for(i=0;i<13;i++){
        if(win_num[i]>max){
            max=win_num[i];
            result=i;
        }
    }
    if (result==0){
        memcpy(p1,p2, sizeof(b));
        result=min_card(player);
    }
    //printf("Simulation: %d\n\n",result);
    return result;
}