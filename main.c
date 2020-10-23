/**
 * This program is gonna read a file and output the same file into euro english.
 *
 * Done by collecting characters into a linked list and further manipulating the characters to give us the appropriate
 * output.
 *
 * main is the last function in this file. line 219
 * Created by Joseph Menezes.
 * Created on 08/10/2020
 * Last edited 10/10/2020 5:08 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
//Reading the file
FILE *editFile(char *fileUse) {
    FILE *file = fopen(fileUse, "r");
    if (file) {
        return file;
    }//if
    printf("There was a problem when opening the text file.\nEnsure the path is used properly");
    return NULL;
}//editFile

//Edits/print for node
/**
 *Prints out the manipulated linked list.
 *
 * free the pointer to work as a garbage collector.
 * @param start The linked-list starting from the root node
 */
void displayList(charNode *start) {
    charNode *pointer = start;
    while (pointer != NULL) {
        printf("%c", pointer->letter);
        pointer = pointer->next;
    }//while
    free(pointer);
}//displayList

struct charNode *createList(FILE *fileUse) {
    char c;
    charNode *start = NULL;
    charNode *temp = NULL;
    charNode *pointer = NULL;
    while ((c = (char) fgetc(fileUse)) != EOF) {
        temp = (charNode *) malloc(sizeof(charNode));
        temp->letter = c;
        temp->next = NULL;

        if (start == NULL) {
            start = temp;
        } //if
        else {
            pointer = start;
            while (pointer->next != NULL) {
                pointer = pointer->next;
            }//while
            pointer->next = temp;
        }//else
    }//while
    free(temp);
    return start;
}//createList

/**
 * This function can be improved by sending the previous character instead.
 * Even better would have been to make a doubly linked list
 * @param pNode
 */
void deleteNode(charNode *pNode) {
    struct charNode *temp;
    temp = pNode->next;
    pNode->next = temp->next;
    free(temp);
}//deleteNode

//Node Manipulation
enum Boolean isAlpha(char alphaNum) {
    if ((alphaNum >= 'A' && alphaNum <= 'Z') || (alphaNum >= 'a' && alphaNum <= 'z')) {
        return True;
    }
    return False;
}//isAlpha

/**
 * Begins manipulating the characters in linked-list HEAD
 * in order to translate our text file into euroglish
 *
 * All functions running currently are case sensitive
 * @param textFile the read unedited file formatted into a linked list.
 * @return an edited linked list
 */
struct charNode *applyRule(charNode *textFile) {
    charNode *pointer = textFile;
    int count = 0;
    while (pointer != NULL && pointer->next != NULL) {
        count++;
        if (pointer->letter == 'C' || pointer->letter == 'c') {
            ruleC(pointer);
        }//if
        if (pointer->letter == 'p' || pointer->letter == 'P') {
            rulePh(pointer);
        }//if
        if (pointer->letter == 'e' || pointer->letter == 'E') {
            ruleEa(pointer);
        }//if
        if ((pointer->next->letter == 'e' || pointer->next->letter == 'E')) {
            ruleLastThree(pointer, count);
            ruleEndED(pointer);
        }//if
        if (pointer->letter == pointer->next->letter) {
            ruleDbleChar(pointer);
        }//if
        if (pointer->letter == 't' || pointer->letter == 'T') {
            ruleTh(pointer);
        }//if
        if (pointer->letter == 'W' || pointer->letter == 'w') {
            ruleW(pointer);
        }//if
        if (pointer->next->letter == 'o' || pointer->next->letter == 'O') {
            ruleOu(pointer);
        }//if
        if (!isAlpha(pointer->letter)) {
            count = 0;
        }//if
        pointer = pointer->next;
    }//while
    free(pointer);
    return (struct charNode *) textFile;
}//applyRule


void ruleEa(charNode *pointerChar) {
    if ((pointerChar->letter == 'e' || pointerChar->letter == 'E') &&
        (pointerChar->next->letter == 'a' || pointerChar->next->letter == 'A')) {
        deleteNode(pointerChar);
    }//if
}//ruleEa

/**
 * Have to send in the next letter to be deleted as the delete node deletes the next node
 * @param pointerChar - a node whose next character is 'o' or 'O'
 */
void ruleOu(charNode *pointerChar) {
    if ((pointerChar->next->letter == 'o' || pointerChar->next->letter == 'O') &&
        (pointerChar->next->next->letter == 'u' && pointerChar->next->next->letter == 'u')) {
        deleteNode(pointerChar);
    }//if
}//ruleOu


void ruleW(charNode *pointerChar) {
    if (pointerChar->letter == 'w') {
        pointerChar->letter = 'v';
    } //if
    else if (pointerChar->letter == 'W') {
        pointerChar->letter = 'V';
    }//if
}//ruleW

void ruleTh(charNode *pointerChar) {
    if (pointerChar->letter == 't' && (pointerChar->next->letter == 'h' || pointerChar->next->letter == 'H')) {
        pointerChar->letter = 'z';
        deleteNode(pointerChar);
    } //if
    else if (pointerChar->letter == 'T' && (pointerChar->next->letter == 'h' || pointerChar->next->letter == 'H')) {
        pointerChar->letter = 'Z';
        deleteNode(pointerChar);
    }//if
}//ruleTh

/**
 * Have to send in the next letter to be deleted as the delete node deletes the next node
 * @param pointerChar - a node whose next character is 'e' or 'E'
 */
void ruleEndED(charNode *pointerChar) {
    if (!(isAlpha(pointerChar->next->next->next->letter))) {
        if ((pointerChar->next->letter == 'e' || pointerChar->next->letter == 'E') && (pointerChar->next->next->letter == 'd') ||
            (pointerChar->next->next->letter == 'D')) {
            deleteNode(pointerChar);
        }//if
    }//if
}//ruleEndEd


void ruleDbleChar(charNode *pointerChar) {
    if (pointerChar->letter != '\n' && pointerChar->next->letter != '\n') {
        deleteNode(pointerChar);
    }
}//ruleDbleChar

/**
 * Have to send in the next letter to be deleted as the delete node deletes the next node
 * @param pointerChar - a node whose next character is 'e' or 'E'
 */
void ruleLastThree(charNode *pointerChar, int counter) {
    if (!(isAlpha(pointerChar->next->next->letter)) && counter >= 3) {
        deleteNode(pointerChar);
    }//if
}//ruleLastThree


void rulePh(charNode *pointerChar) {
    if (pointerChar->letter == 'p' && (pointerChar->next->letter == 'h' || pointerChar->next->letter == 'H')) {
        pointerChar->letter = 'f';
        deleteNode(pointerChar);
    } else if (pointerChar->letter == 'P' && (pointerChar->next->letter == 'H' || pointerChar->next->letter == 'h')) {
        pointerChar->letter = 'F';
        deleteNode(pointerChar);
    }
}//rulePh

void ruleC(charNode *pointerChar) {
    if (pointerChar->letter == 'C' &&
        (pointerChar->next->letter == 'e' || pointerChar->next->letter == 'i' || pointerChar->next->letter == 'y' ||
         pointerChar->next->letter == 'E' || pointerChar->next->letter == 'I' || pointerChar->next->letter == 'Y')) {
        pointerChar->letter = 'S';
    } else if (pointerChar->letter == 'C') {
        pointerChar->letter = 'K';
    } else if (pointerChar->letter == 'c' &&
               (pointerChar->next->letter == 'e' || pointerChar->next->letter == 'i' || pointerChar->next->letter == 'y' ||
                pointerChar->next->letter == 'E' || pointerChar->next->letter == 'I' || pointerChar->next->letter == 'Y')) {
        pointerChar->letter = 's';
    } else if (pointerChar->letter == 'c') {
        pointerChar->letter = 'k';
    }

}//ruleC

//main
int main() {
    charNode *linkedChar = NULL;
    FILE *readFile = editFile("C:\\Users\\josep\\Desktop\\AUCSC 370\\Assignment2\\testing.txt");
    linkedChar =  createList(readFile);
    displayList(applyRule(linkedChar));
    free(linkedChar);
    fclose(readFile);
    return 0;
}//main

