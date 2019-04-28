#include<stdio.h>
#include<conio.h>

#define MAX_SIZE 100

typedef enum
    {lparen, rparen, plus, minus, times, divide, mode, eos, operand}precedence;
precedence stack[MAX_SIZE];
char infix[MAX_SIZE];
char postfix[MAX_SIZE];
static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };

precedence get_token(char* psymbol, int* pn);
void push(int* ptop, precedence token);
precedence pop(int* ptop);

void convert()
{
	char symbol; precedence token;
	int n = 0; int top = 0; int unary_switch = 0; int index = 0;
	stack[0] = eos;
	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
	{
		printf("first token %d\n top is %d\n", symbol, top);
		if ((unary_switch == 1)&&(token!=operand))
		{
			printf("First if\n");
			if (token == minus) postfix[index++]=token;
			token = get_token(&symbol, &n);
			unary_switch -= 1;
		}
		if (token == operand)	postfix[index++]=token;
		else if (token == rparen)
		{
			printf("2nd if\n");
			while (stack[top] != lparen)
			{
				printf("First loop\n");
				postfix[index++] = pop(&top);
				postfix[index++] = ' ';
			}
			pop(&top);
		}
		else
		{
			printf("3rd if\n");
			unary_switch += 1;
			while (isp[stack[top]] >= icp[token])
			{
				printf("2nd loop\n");
				postfix[index++] = pop(&top); postfix[index++] = ' ';
			}
			printf("while break?\n");
			push(&top, token);
			printf("top is %d\n",top);
		}
	}
	while ((token = pop(&top)) != eos)
	{
		printf("3nd loop\n");
		postfix[index++] = token; 
		postfix[index++] = ' ';
		printf("%s\n %c \n", postfix, postfix[3]);
	}
	postfix[index] = '\n';
}

precedence get_token(char *psymbol, int *pn)
{
	*psymbol = infix[(*pn)++];
    switch(*psymbol)
    {
        case '(' : return lparen;
        case ')' : return rparen;
        case '+' : return plus;
        case '-' : return minus;
        case '*' : return times;
        case '/' : return divide;
        case '%' : return mode;
        case ' ' : return eos;
		case '\n': return eos;
        default  : return operand;
    }
}

void push(int* ptop, precedence token)
{
	if (*ptop >= (MAX_SIZE - 1)) printf("Stack is full\n");
	stack[++*ptop] = token;
	printf("push\n");
}

precedence pop(int* ptop)
{
	printf("pop\n");
	if (*ptop == -1)	printf("Stack is empty\n");
	return stack[(*ptop)--];
	printf("top is %d\n",*ptop);
}

int main(void)
{
	char postfix[MAX_SIZE];
	printf("Puts your infix expression\n");
	fgets(infix, MAX_SIZE, stdin);
	printf("%s", infix);
	convert();
	printf("Given %s \n", infix);
	printf("%s", postfix);
	_getch();
}

/*
int eval()
{
    precedence token; char symbol; int op1, op2;
	int n = 0; int top = -1; token = get_token(&symbol, &n);

    while(token!=eos)
    {
        if(token==operand) push(&top, symbol-'0');
        else
        {
            op2=pop(&top); op1=pop(&top);
            switch(token)
            {
                case plus   : push(&top, op1+op2); break;
                case minus  : push(&top, op1-op2); break;
                case times  : push(&top, op1*op2); break;
                case divide : push(&top, op1/op2); break;
                case mode   : push(&top, op1%op2);
            }
        }
        token=get_token(&symbol,&n);
    }
    return pop(&top);
}*/