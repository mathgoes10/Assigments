//Matheus Lima
//Programming Assigment 2
//COP3052

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXPEOPLE 10
#define MAXCHAR 19


int numPeople;  // n
int numDontSit; // p //number of pairs that dont sit tog
char listPeople[MAXPEOPLE][MAXCHAR+1];//Everyone on Theater
int popcorn[MAXPEOPLE];//list of who has popcorn
typedef enum { false, true } bool;//custom boolean
bool enemies[MAXPEOPLE][MAXPEOPLE];

//Function Prototypes
bool isvalid(int listNames[]);
int numberOfpermutations(int listNames[], bool status[], int fixed);

int main(int argc, char *argv[]) {
   if (argc != 2) {
        return 1;
    }
    FILE *fp = fopen(argv[1], "r"); // open the input file for reading
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    //Scaning N inputs
    fscanf(fp, "%d %d", &numPeople, &numDontSit); 
    for (int i = 0; i < numPeople; i++) 
    { 
        fscanf(fp, "%s %d", listPeople[i], &popcorn[i]);
    }
    //Scanning P inputs
    for (int i = 0; i < numDontSit; i++)
    { // Temp variables to store the pairs:
        char person1[MAXCHAR+1], person2[MAXCHAR+1];
        fscanf(fp, "%s %s", person1, person2); 
      
        //index for the names for the array
        int index1, index2; 
        for (int j = 0; j < numPeople; j++) { 
        //Compare the names to find enemy's index:
        //First enemy:
            if (strcmp(listPeople[j], person1) == 0) index1 = j; 
        //Second enemy:
            if (strcmp(listPeople[j], person1) == 0) index2 = j;
        }//close of inner for

         //tagging each pair of enemies 
          enemies[index1][index2] = enemies[index2][index1] = true; 
      
    }//close of outer for
    fclose(fp); //closing input file

    int listNames[MAXPEOPLE]; //list of names 
  
    // Assigning a status of the permutation for each person, intializing it to false:
    bool status[MAXPEOPLE] = {false}; 
    printf("\n");
    printf("%d\n", numberOfpermutations(listNames, status, 0)); //Printing the number of valid permutations
    return 0; 
}

// isvalid checks if the permution is valid, given the restriction of popcorn and enemies.
bool isvalid(int listNames[])
{
    for (int i = 0; i < numPeople; i++) {
// checking if yourself, your right and your left  doesn't have popcorn
        if (!popcorn[listNames[i]] &&
            ((i == 0) || !popcorn[listNames[i - 1]]) &&
            ((i == numPeople - 1) || !popcorn[listNames[i + 1]])) {
            return false; 
// Not valid if someone can not get poporcorn
        }
//checking enemies in the left
        if (i > 0 && enemies[listNames[i]][listNames[i - 1]]) {
            return false; 
//Not valid if enemies sits besides each other
        }
//checking enemies in the right
        if (i < numPeople - 1 && enemies[listNames[i]][listNames[i + 1]]) {
            return false; 
//Not valid if enemies sits besides each other
        }
    }
    return true; 
//If there is no conflit for popcorn and enemies, permutation is valid
}

//Counting the number of permutations considering its validation from function isvalid();
int numberOfpermutations(int listNames[], bool status[], int fixed)
{
//Base Case //when permutation reaches its bottom (tree)
    if (fixed == numPeople) { 

        return isvalid(listNames) ? 1 : 0; 
//If valid return 1, if not return 0
    }
    int counter = 0; // count # of permutations

//Iterate through everyone
    for (int i = 0; i < numPeople; i++) { 

//checking status of the person, if true permuation was already calculated, if not add person to fix index
        if (!status[i]) {

//move person to fixed index
            listNames[fixed] = i;

//already calculated :
            status[i] = true; 
//calling itself:
            counter += numberOfpermutations(listNames, status, fixed + 1); 
//Go back to original combination by untagging person
            status[i] = false; 
        }//close of if
    }//close of for
    return counter; //# of valid permutes
}//close of function

