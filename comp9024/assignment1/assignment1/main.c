//
//  main.c
//  assignment1
//
//  Created by apple on 2018/8/21.
//  Copyright © 2018年 apple. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "cardRecord.h"
#include "cardLL.h"

void printHelp(void);
void CardLinkedListProcessing(void);

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        int times;
        times = atoi(argv[1]);
        char ID[10];
        double amount;
        char arrayid[10][10];
        double arramount[10];
        double sum1 = 0.0;
        
        for (int i = 0; i < times; i++)
        {
            printf("Enter card ID: ");
            scanf("%s",ID);
            while (atoi(ID) > 99999999 || atoi(ID) < 10000000)
            {
                printf("Not valid. Enter a valid value: ");
                scanf("%s",ID);
            }
            strcpy(arrayid[i],ID);
            
            printf("Enter amount: ");
            scanf("%lf",&amount);
            while (amount >250.00 || amount <-2.35)
            {
                printf("Not valid. Enter a valid value: ");
                scanf("%lf",&amount);
                
            }
            arramount[i] = amount;
        }
        
        for (int i = 0; i < times; ++i)
        {
            printf("-----------------\n");
            printf("Card ID: %s\n", arrayid[i]);
            printf("Balance: $%.2lf\n", arramount[i]);
            if (arramount[i]<5.00)
            {
                printf("Low balance\n");
            }
            printf("-----------------\n");
            sum1 += arramount[i];
        }
        sum1 = sum1/2;
        printf("Number of cards on file: %d\n", times);
        printf("Average balance: $%.2lf\n",sum1 );
        
    }
    else {
        CardLinkedListProcessing();
        
    }
    
    return 0;
}






/* Code for Stages 2 and 3 starts here */

void CardLinkedListProcessing() {
    int op, ch;
    
    List list = newLL(); // create a new linked list
    
    while (1) {
        printf("Enter command (a,g,p,q,r, h for Help)> ");
        
        do {
            ch = getchar();
        } while (!isalpha(ch) && ch != '\n');  // isalpha() defined in ctype.h
        op = ch;
        // skip the rest of the line until newline is encountered
        while (ch != '\n') {
            ch = getchar();
        }
        
        switch (op) {
                
            case 'a':
            case 'A':
            {
            
                float Amount ;
                int ID ;
                printf("Enter card ID: ");
                ID = readInt();
                while (ID > 99999999 || ID < 10000000 )
                {
                    printf("Not valid. Enter a valid value: ");
                    ID = readInt();
                }
                printf("Enter amount: ");
                Amount = readFloat();
                while (Amount >250.00 || Amount <-2.35)
                {
                    printf("Not valid. Enter a valid value: ");
                    Amount = readFloat();
                    
                }
                
                
                insertLL(list, ID, Amount);
                
            }
                break;
            
                
                
            
                
            case 'g':
            case 'G':
                {
                    float *n = NULL;
                    int * L = NULL;
                    getAverageLL(list, L, n);
                }
                
                break;
                
            case 'h':
            case 'H':
                printHelp();
                break;
                
            case 'p':
            case 'P':
            {showLL(list);}
                
                break;
                
            case 'r':
            case 'R':
            {
                printf("Enter card ID: ");
                int ID;
                scanf("%d",&ID);
                removeLL(list, ID);
                
                
            }
                /*** Insert your code for removing a card record ***/
                
                break;
                
            case 'q':
            case 'Q':
                dropLL(list);     // destroy linked list before returning
                printf("Bye.\n");
                return;
        }
    }
}

void printHelp() {
    printf("\n");
    printf(" a - Add card record\n" );
    printf(" g - Get average balance\n" );
    printf(" h - Help\n");
    printf(" p - Print all records\n" );
    printf(" r - Remove card\n");
    printf(" q - Quit\n");
    printf("\n");
}
