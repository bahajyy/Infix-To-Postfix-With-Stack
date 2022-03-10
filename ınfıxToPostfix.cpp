// Baha Jiyan Yılmaz
#include <iostream>
#include <string.h>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* newStack(unsigned capacity )
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); //creating new stack

    if (!stack)
    {
        return NULL;
    }
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*) malloc(stack->capacity * sizeof(int));

    if (!stack->array)
    {
        return NULL;
    }
    return stack;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ; //if stack is empty return -1
}

char topelement(struct Stack* stack)
{
    return stack->array[stack->top]; //return the top element
}

char pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ; //deleting elements from stack
    return '!';
}

void push(struct Stack* stack, char op)
{
    stack->array[++stack->top] = op; //adding elements to stack
}


int postfixequation(char* exp)
{
    Stack* stack = newStack(strlen(exp));
    int i;

    if (!stack)
    {
        return -1;
    }


    for (i = 0; exp[i]; ++i)
    {
        if(exp[i] == ';')continue; // ignoring the ";"
        else if (isdigit(exp[i]))
        {
            int num=0;
            while(isdigit(exp[i]))
            {
                num = num * 10 + (int)(exp[i] - '0');
                i++;
            }
            i=i-1;
            push(stack,num);
        }
        else
        {
            int val1 = pop(stack);
            int val2 = pop(stack);

            switch (exp[i])
            {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2/val1); break;
                case'^':push(stack, pow(val2,val1)); break;

            }
        }
    }
    return pop(stack);
}

int main()
{
    ofstream out;
    ifstream read_file;
    read_file.open("../equations.txt");

    if(!read_file.is_open())
    {
        cerr<<"Fail fail could not opened"<<endl;
        exit(1);
    }
    cout<<"File has opened"<<endl;
    string lines;
    string equ;
    while(getline(read_file,lines))
    {
        stringstream line_stream(lines);
        getline(line_stream,equ,'t');
    }
    read_file.close();
    int n = equ.length();
    char char_array[n+1];
    strcpy(char_array,equ.c_str());
    for (int i = 0; i <n ; i++)
    {
        if(char_array[i]==';')
        {
            memmove(char_array+i,char_array+i+1,1);
        }
    }
    cout<<char_array<<endl;
    cout << "Final number is  " << postfixequation(char_array) << endl;
    return 0;
}



