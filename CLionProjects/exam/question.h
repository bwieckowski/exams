//
// Created by Bartek on 10.05.2018.
//

#ifndef EXAM_QUESTION_H
#define EXAM_QUESTION_H

#endif //EXAM_QUESTION_H


typedef  struct QUESTION {
    char * quest;
    char ** answers;
    int correct;
    struct QUESTION * next;
}  QUESTION;
