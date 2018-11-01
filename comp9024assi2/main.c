//
//  main.c
//  comp9024assi2
//
//  Created by apple on 2018/10/1.
//  Copyright © 2018年 apple. All rights reserved.
//

#include <stdio.h>
#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"

/* …
 Time comlexity:
 For Task A:
 Time comlexity is : O(n^2)
 Explaination
 For fuction divisor() :O(n)
 For fuction newGraph() :O(n)
 For the double loop from 55 to 65 line:
        because the fuction judge function has limited range, it won't be larger than 10^2
 so the double loop complexity is O(n^2)
 For the double loop from 75 -85 lines : O(n^2)
 So the Task A complexity is O(n^2)
 
 For Task B:
 Time comlexity is :O(n^2)
 For the DFS search ,every node can be searched only once from one root so the time complexity is O(n)
 For the convert_stack_into_array() function, time complexity is O(n)
 Because we need to search from every root nodes.
 so the complextiy is O(n*n*n) = O(n^3);

 */

typedef struct {
    int list[1000];
    int now;
}arr;

void printpaorder(int v,int **matrix,Graph g,arr L);
int judge(int a,int b);
arr divisor(int argument);
int checkroot(int node,int **matrix,int v,Graph g);
void creatrootlist (int v,Graph g,int *root,int ** matrix);
int findnext(int **matrix,int now,int nownode,int v);
void printstack(stack dfs,arr L);
void convert_stack_into_array(stack dfs,arr L,int **list,int insertplace);

int main(int argc, const char * argv[]) {
    //Task A
    Graph g;
    int a = 0;
    a =atoi(argv[1]);
    arr L;
    L = divisor(a);
    L.list[L.now] = a;
    L.now += 1;
    g = newGraph(L.now);
    
    for (int i = 0; i < L.now; i++) {
        
        for (int m = i+1; m < L.now; m++) {
            if (L.list[m] % L.list[i] == 0 && judge(L.list[i], L.list[m])) {
                Edge e;
                e.v =i;
                e.w =m;
                insertEdge(g, e);
            }
            
        }

    }
    int v;
    v = numOfVertices(g);
    int **matrix;
    matrix = malloc(v*sizeof(int *));
    for (int i = 0; i < v; i++) {
        matrix[i] = calloc(v,sizeof(int));
    }
    for (int i = 0; i < v-1; i++) {
        int step =0;
        for (int j =i+1; j<v; j++) {
            if (adjacent(g, i, j)) {
                matrix[i][step] = j;
                step += 1;
            }
        }
    }
    
    
//Task B
//find root
    int *root;
    root = calloc(v, sizeof(int));
    int place = 0;
    for (int i =0; i < v; i++) {
        if(checkroot(i, matrix, v, g)){
            root[place] = i;
            place += 1;
        }
    }


//#####
//dfs
    int rot = 0;
    int **list;
    int stack_height_list[10000];
    int insertplace = 0;
    list = malloc(1000*sizeof(int*));
    while (rot<place) {
    stack dfs;
    dfs = newStack();
    StackPush(dfs, root[rot]);
   
    while (!StackIsEmpty(dfs)) {
        int now = 0;
        now = StackPop(dfs);
        StackPush(dfs, now);
        if (matrix[now][0]!=0) {
            StackPush(dfs, matrix[now][0]);
        }
        else{
            break;
        }
        
    }
    while (Stackheight(dfs) >=2) {
        int now = 0;
        int nownode = 0;
        nownode = StackPop(dfs);
        now = StackPop(dfs);
        StackPush(dfs, now);
        StackPush(dfs, nownode);
        if (matrix[nownode][0] == 0) {
            stack_height_list[insertplace] = Stackheight(dfs);
            convert_stack_into_array(dfs, L, list,insertplace);
            insertplace +=1;
            StackPop(dfs);
            if(matrix[now][findnext(matrix, now, nownode, v)] !=0 ){
                StackPush(dfs, matrix[now][findnext(matrix, now, nownode, v)]);
                continue;
            }
            continue;
        }
        if(matrix[now][findnext(matrix, now, nownode, v)] !=0){
            StackPop(dfs);
            int newnode = 0;
            newnode = matrix[now][findnext(matrix, now, nownode, v)];
            StackPush(dfs, matrix[now][findnext(matrix, now, nownode, v)]);
            while (matrix[newnode][0]!=0) {
                StackPush(dfs, matrix[newnode][0]);
                newnode =matrix[newnode][0];
            }
            continue;
        }
        if (matrix[now][findnext(matrix, now, nownode, v)] == 0) {
            StackPop(dfs);
            continue;
        }
        
        
    }

        rot +=1;
    }

    printpaorder(v, matrix, g, L);
    printf("\n");
    printf("Longest monotonically increasing sequences:\n");
    int max = 0;
    max  = stack_height_list[0];
    for (int i = 0 ; i < insertplace; i++) {
        if (stack_height_list[i] > max) {
            max = stack_height_list[i];
        }
    }
    for (int i = 0; i < insertplace; i++) {
        for (int j = 0; j < stack_height_list[i]; j++) {
            if (stack_height_list[i] == max) {
                
            
            if (j == stack_height_list[i]-1) {
                printf("%d\n",L.list[list[i][j]]);
                continue;
            }
            printf("%d < ",L.list[list[i][j]]);
        }
        }
    }

    free(matrix);
    free(list);
    free(root);
    return 0;
}






void printpaorder(int v,int **matrix,Graph g,arr L){
    printf("Partial order:\n");
    for (int m = 0; m < v ; m++){
        printf ("%d: ",L.list[m]);
        for (int i=0; i<v; i++) {
            if (L.list[matrix[m][i]]==1) {
                break;
            }
            printf ("%d ",L.list[matrix[m][i]]);
        }
        printf("\n");
    }
    
}
int judge(int a,int b){
    char stra[10],strb[10];
    sprintf(stra, "%d",a);
    sprintf(strb, "%d",b);
    int num = 0;
    for (int i = 0; i < strlen(stra); i++) {
        for (int j = 0 ; j < strlen (strb); j++) {
            if (stra[i] == strb[j]) {
                num += 1;
                break;
            }
        }
    }
    if (num == strlen(stra)) {
        return 1;
    }
    return 0;
}



arr divisor(int argument){
    arr L;
    int midium = 0,now =0;
    midium = argument / 2 + 1;
    for (int i = 1; i<midium; i++) {
        if (argument % i == 0) {
            L.list[now] =  i;
            now+=1;
            
        }
        L.now = now ;
    }
    return L;
}

int checkroot(int node,int **matrix,int v,Graph g){
    for (int i = 0; i < v; i++) {
        if (adjacent(g, i, node)) {
            return 0;
        }
    }
    return 1;
}

void creatrootlist (int v,Graph g,int *root,int ** matrix){
    int place = 0;
    for (int i =0; i < v; i++) {
        if(checkroot(i, matrix, v, g)){
            root[place] = i;
            place += 1;
        }
    }
}

int findnext(int **matrix,int now,int nownode,int v){
    for (int i = 0; 1<v; i++) {
        if (matrix[now][i] == nownode) {
            return i+1;
        }
    }
    return 0;
}

void printstack(stack dfs,arr L){
    int *line;
    int place = Stackheight(dfs) - 1;
    int length = Stackheight(dfs);
    line = calloc(length, sizeof(int));
    printf("stack: ");
    while (!StackIsEmpty(dfs)) {
        int node = 0;
        node = StackPop(dfs);
        line[place] = node;
        place -=1;
        printf("%d ,",L.list[node]);
    }
    for (int i =0; i < length; i++) {
        StackPush(dfs, line[i]);
    }
    printf ("\n");
    free(line);
}
void convert_stack_into_array(stack dfs,arr L,int **list,int insertplace){
    int *line;
    int place = Stackheight(dfs) - 1;
    int length = Stackheight(dfs);
    line = calloc(length, sizeof(int));
    while (!StackIsEmpty(dfs)) {
        int node = 0;
        node = StackPop(dfs);
        line[place] = node;
        place -=1;
    }
    for (int i =0; i < length; i++) {
        StackPush(dfs, line[i]);
    }
    list[insertplace] = line;
}
