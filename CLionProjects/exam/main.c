#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



struct question{
    char * quest;
    char ** answers;
    char correct;
} QUESTION;


struct exam {
    struct QUESTION * questions;
    int points;
} EXAM;


char ** loadQuestions( FILE * stream, struct EXAM * exam, int * lin )
{
    char tmp, **text;
    int i, lines = 0, line_buffor = 0, line_tmp = 0;

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

    text = (char ** ) malloc( lines * sizeof( char* ) );

    // Sprawdzenie powodzenia alokacji tablicy text
    if( text == NULL  )
        exit(1);

    //Wczytywanie wierszy do tablicy
    for ( i= 0; i < lines; i++) {
        text[i] = malloc(line_buffor* sizeof(char));
        fgets(text[i], line_buffor, stream);
    }

    *lin = lines;
    return text;

}


struct question newQuestion( char * quest, char ** answers, int correct  )
{
    struct question q;
    q.quest = quest;
    q.answers =  answers;
    q.correct = correct;
    return q;
}

void readQuestion( struct question q )
{
    char ans;
    printf("%s \n", q.quest);
    printf( "%s", q.answers );

}


int main(int argc, char *argv[])
{

    struct EXAM egzamin;
    FILE * fQuestions;
    int * lin;
    egzamin =  malloc( sizeof( EXAM ) );

    fQuestions = fopen( "questions.txt", "r");
    if( fQuestions == NULL )
        printf(" nie znaleziono pliku");
    else
    {
        printf(" odnaleziono plik \n");

        loadQuestions( egzamin.questions ,fQuestions, lin );

    }


    //readQuestion( current );
    return 0;
}
