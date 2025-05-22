/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Joel Sarmiento
 *
 * This file contains the main and PrintStack functions. main is a simple text
 * editor with redo and undo features that are implemented using stacks.
 * PrintStack prints out the reversed contents of a stack
 *
 */

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

/* PrintStack
 *  parameters:
 *      s -- a stack to be printed
 *  return value: void
 *
 *  This function uses a temporary stack to reverse the contents of the
 *  original stack and outputs them
 */
void PrintStack(stack<string> *s ) {
    stack<string> newStack;
    int count = 0;
    
    //push contents of original stack onto new stack
    while (!s->empty()) {
        newStack.push(s->top());
        s->pop();
        count++;
    }
    
    //prints contents of temporary stack (original stack in reverse)
    for (int i = 0; i < count; i++) {
        string word = newStack.top();
        cout << word;
        if (i < count - 1) {
            cout << " ";
        }
        s->push(word);
        newStack.pop();
    }
}

const int MAX_NUM_LINES = 1000;
const int MIN_NUM_LINES = 1;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  This function implements a simple text editor that has undo and redo
 *  features
 */
int main(int argc, char **argv) {
    // these are the two stacks used to store the typed words and the undone
    // words
    
    stack<string> typing, undo;
    string command, word, line;
    int numLines;
    
    //user inputs number of lines
    cin >> numLines;
    cin.ignore();
    assert((numLines >= MIN_NUM_LINES) && (numLines <= MAX_NUM_LINES));
    
    for (int i = 0; i < numLines; i++) {
        getline(cin, line);
        stringstream ss(line);
        ss >> command >> word;
        
        
        //type command
        if (command == "t") {
            //push word onto typing stack
            typing.push(word);
        }
        
        
        //undo command
        if (command == "u") {
            if (typing.empty()) {
                cout << "nothing to undo on command " << i + 1 << endl;
            } else {
                //push word on top of typing stack to undo stack
                undo.push(typing.top());
                
                //remove word from top of typing stack
                typing.pop();
            }
        }
        
        
        //redo command
        if (command == "r") {
            if (undo.empty()) {
                cout << "nothing to redo on command " << i + 1 << endl;
            } else {
                //push word from top of undo stack to typing stack
                typing.push(undo.top());
                
                //pop word from top of undo stack
                undo.pop();
            }
        }
    }
    
    //prints typing stack on a line
    PrintStack(&typing);
    cout << endl;
    
    //prints undo stack on a line
    PrintStack(&undo);
    cout << endl;
    

    return 0;
}

