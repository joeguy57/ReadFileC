/**
 * This file contains both typeDefs of our Struct a Boolean typ.
 *
 * It also declares all runnable code.
 *
 * Created by Joseph Menezes.
 * Created on 08/10/2020
 * Last edited 10/10/2020 5:08 AM
**/

#ifndef ASSIGNMENT2_MAIN_H
#define ASSIGNMENT2_MAIN_H

/**
 * Creates the nodes for each character
 */
typedef struct charNode{
    char letter;
    struct  charNode* next;
}charNode;

/**
 * Creates a Boolean data type to make true, false comparison
 */
typedef enum Boolean {
    False, True
}Boolean;



/**
 * Takes a file from the directory called testing.txt sees if the file can be opened
 * @param file - is an array of the file path
 * @return the file opened and read
 */
FILE* editFile(char* file);



/**
 * prints out the newly made list
 * @param start - a pointer to pointer variable that hase the new linked list stored.
 */
void displayList(charNode *  start);

/**
 * Creates a linked list of all the characters in a given file
 * @param file - a file that's already been read
 * @return a structured linked list
 */
struct charNode *createList(FILE * file);

/**
 * Deletes the next node after pNode
 * @param pNode a single node in a linked list
 */
void deleteNode(charNode *pNode);

/**
 * This method runs all the characters one by one, tries figure out
 * if it needs to follow any rules
 * @param textFile the linked list of all characters in that file
 * @return manipulated linked list completed with all the rules.
 */
struct charNode* applyRule(charNode *textFile);


/**
 * if c is followed by e,i or y replace with s else replace with k.
 * @param pointerChar node starting with the pointer character
 */
void ruleC(charNode * pointerChar);

/**
 * if a word ends with ed replace it with d
 * @param pointerChar node starting with the pointer character
 */
void ruleEndED(charNode *pointerChar);

/**
 * if word contains ph replace with f
 * @param pointerChar node starting with the Char x character
 */
void rulePh(charNode *pointerChar);

/**
 * check to see if character passed through is an alpha
 * @param alphaNum
 * @return a Boolean value
 */
enum Boolean isAlpha(char alphaNum);

/**
 * Checks to see if a word ends with e and is > than 3 in length
 * @param pointerChar node starting with the Char x character
 * @param wrdLength an integer of how long a word is
 */
void ruleLastThree(charNode *pointerChar, int wrdLength);

/**
 * Replaces all th with z
 * @param pointerChar node starting with the Char x character
 */
void ruleTh(charNode *pointerChar);

/**
 * Replace all w with v
 * @param pointerChar node starting with the Char x character
 */
void ruleW(charNode *pointerChar);

/**
 * repeated characters except for new lines are brought to one single one
 * @param pointerChar node starting with the Char x character
 */
void ruleDbleChar(charNode *pointerChar);

/**
 * Replace all ou with u
 * @param pointerChar node starting with the Char x character
 */
void ruleOu(charNode *pointerChar);

/**
 * replace all ea with a
 * @param pointerChar node starting with the Char x character
 */
void ruleEa(charNode *pointerChar);

#endif //ASSIGNMENT2_MAIN_H
