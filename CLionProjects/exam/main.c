#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "exam.h"


void do_EXAM();

QUESTION * loadQuestions( FILE * stream  )
{
    char tmp, *text = NULL;
    int i = 0, lines = 0, line_buffor = 0, line_tmp = 0, pom = 0;


    while(!feof(stream)){
        tmp = fgetc(stream);
        // zliczanie znaków
        line_tmp++;
        if( tmp == '\n' || tmp == EOF ) {
            //zliczanie wierszy
            lines++;

            //wyszukiwanie wiersza zawierajacego najwięcej znaków
            if(line_tmp> line_buffor)
                line_buffor = line_tmp;
        }


    }


    rewind( stream );
    QUESTION * pyt = NULL;
    QUESTION * first = NULL;
    QUESTION *top = NULL;

    text = (char*)malloc(sizeof(char)*( line_buffor ));

    for ( i= 0; i < lines; i++) {


        switch ( i%6 )
        {

          // Add question
            case 0:
                pyt = ( QUESTION * ) malloc( sizeof( QUESTION ) );
                pyt->quest=(char*)malloc(sizeof(char)*( line_buffor ));
                fgets(pyt->quest, line_buffor, stream);

                if(!first)
                    first=pyt;
                pyt ->answers=(char**)malloc( sizeof(char*)*4 );
                break;

         // Add answers to array
            case 1:
            case 2:
            case 3:
            case 4:
                pom =(i%6)-1;
                pyt->answers[pom] = ( char * )malloc( sizeof(char)*line_buffor);
                fgets(pyt->answers[pom], line_buffor, stream);
                break;

         //add correct question
            case 5:
                fgets(text, line_buffor, stream);
                pyt->correct=atoi( text );
                pyt->next=top;
                top=pyt;
                break;
        }
    }

    return top;

}



void read_QUESTION( QUESTION * question)
{
    int i = 0;
    char labels[4] = {'1' , '2' , '3', '4'};
    char * text = question->quest;
    printf("%s",text);
    for ( ;  i < 4; i++) {
        printf("%c ) %s",labels[i],question->answers[i]);
    }

    printf("\n");
}

EXAM * init_EXAM()
{

    EXAM * exam;
    // pointer to file with questions
    FILE * fQuestions;
    QUESTION * tmp;

    exam =  ( EXAM *  ) malloc( sizeof( EXAM ) );

    fQuestions = fopen( "questions.txt", "r");

    if( fQuestions == NULL )
        printf(" nie znaleziono pliku");
    else
    {
        printf(" odnaleziono plik \n");
        exam->top = loadQuestions( fQuestions  );

    }
    tmp = exam->top;
    exam->total = 0;
    while( tmp )
    {
        exam->total++;
        tmp = tmp->next;
    }
    return exam;
}


char getChoice( )
{
    char  ch, ret;
    while ( (ch = getchar()) != '\n' && ch != EOF ){ ret = ch; }
    return ret;
}

void display_menu()
{

    printf("1 - nowy egazmin \n");
    printf("2 - ostatnie punkty i czas \n");
    printf("3 - losuj pytanie \n");
    printf("e - exit \n");
}


void Do_EXAM( EXAM * exam ) {
    int answer = 0;
    QUESTION * tmp = exam->top;
    printf(" Możesz zdobyc %d punktow \n", exam->total);
    while( tmp ) {
        read_QUESTION( tmp );

        do
        {
            answer =  getChoice() - '0';
        }
        while( answer != 1 && answer != 2 && answer != 3 && answer != 4);


        printf("your: %d, answer : %d \n", answer,tmp->correct);

        if ( answer == tmp->correct) {
            exam->points++;
            printf("masz punkciora \n");
        }

        tmp = tmp->next;
    }

    printf("Egzamin zakończony zdobyłeś : %d  puktow \n\n", exam->points);

}


void init_menu( EXAM * current_EXAM ) {
    char choice = NULL;

    while (1)
    {
        display_menu();
        choice = getChoice( );

        switch (choice) {
            case '1':
                Do_EXAM(current_EXAM);
                break;
            case '2':
                if (current_EXAM->points)
                    printf("twoj wynik z ostatniego testu to: %d", current_EXAM->points);
                else
                    printf("Nie rozwiązano testu");
                break;
            case '3':
                break;
            case 'e':
                system("pause ");
                exit(0);
            default:
                printf("niepoprawny symbol  \n");
                break;

         }
    }
}


int main(int argc, char *argv[])
{

    EXAM * exam = init_EXAM();


        init_menu( exam );

}
