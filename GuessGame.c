#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>


void initialize_random(){
    srand(time(NULL));
}


char* chooseRandom(char a[300][50],int size){
    int x = rand()%size;
    return a[x];
}


char* createMask(char *a){
    initialize_random();
    int size = strlen(a);
    char temp[50];
    strcpy(temp,a);

    int first,second,third;

    if(size < 5){
        first = third = 0;
    }
    else{
        first = rand()%abs((size-2));
        second = rand()%abs((size));
        third = rand()%abs((size-4));
    }

    int i;
    for(i=0;temp[i]!='\0';i++){
        if(i!=first && i!=second && i!=third)
            temp[i] = '_';
    }

    return temp;
}


char* updateMask(char *original,char *masked,char guess){
    char temp[50];
    strcpy(temp,masked);

    int i;
    for(i=0;original[i]!='\0';i++){
        if(original[i] == guess){
            temp[i] = guess;
        }
    }

    return temp;
}


void guessGame(){

    system("cls");

    FILE *f = fopen("Words.txt","r");

    char temp[50];
    char movies[300][50];
    char selected_movie[50];
    char masked_version[50];
    char prev[50];
    int remaning_attempt = 5;
    char guess;
    printf("\n-------------------------------Guess Movies----------------------------\n\n");

    int i=0,count=0;

    while(1){
        fscanf(f,"%s",temp);

        if(strcmp(temp,";") == 0)
            break;

        strcpy(movies[i],temp);
        i++;
        count=count+1;
    }


    initialize_random();
    strcpy(selected_movie,chooseRandom(movies,count));
    strcpy(masked_version,createMask(selected_movie));

    while(remaning_attempt > 0){

        printf("\tMovie Name: %s                 Guess Remaning: %d\n",masked_version,remaning_attempt);
        printf("\tEnter Your Guess Character: ");
        fflush(stdin);
        guess = getchar();
        guess = toupper(guess);
        strcpy(prev,masked_version);
        strcpy(masked_version,updateMask(selected_movie,masked_version,guess));
        if(strcmp(prev,masked_version)==0){
            remaning_attempt--;
        }
        else{
            if(strcmp(selected_movie,masked_version)==0){
                printf("\n\tMovie Name:%s\n\tYou Won This Game!!!!!!",selected_movie);
                break;
            }
        }

        printf("\n-------------------------------------------------------------------\n");

    }

    if(remaning_attempt == 0){
        printf("\n\tMovie Name:%s\n\tYou Loose this Game!!!!  Better Luck Next Time",selected_movie);
    }

}

int main(){

    guessGame();

    char choice;
    fflush(stdin);
    printf("\n\n\tWant To Play Again(Y/N): ");
    choice = getchar();
    choice = toupper(choice);

    while(choice == 'Y'){
        guessGame();
        printf("\n\n\tWant To Play Again(Y/N): ");
        choice = getchar();
        choice = toupper(choice);
    }

    getch();
   	
return 0;
}
