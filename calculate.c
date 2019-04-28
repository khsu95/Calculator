#include<stdio.h>

#define MAX_SIZE 100

typedef enum
    {lparen, rparen, plus, minus, times, divide, mode, eos, operand}precedence;
precedence stack[MAX_SIZE];
char infix[MAX_SIZE+1];
char postfix[MAX_SIZE+1];
static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };

precedence get_token(char* psymbol, int* pn);
void push(int* ptop, precedence token);
precedence pop(int* ptop);
char print_token(precedence token);

void convert()
{
	char symbol; precedence token;
	int n = 0; int top = 0; int unary_switch = 1; int index = 0;
	stack[0] = eos;
	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
	{
		if (((token==plus)||(token==minus))&&(unary_switch==1))
		{
			if (token == minus)
				postfix[index++] = print_token(token);
			token = get_token(&symbol, &n);
		}
		unary_switch = 0;
		if (token == operand)
		{
			postfix[index++] = symbol;
			postfix[index++] = ' ';
		}
		else if (token == rparen)
		{
			while (stack[top] != lparen)
			{
				postfix[index++] = print_token(pop(&top));
				postfix[index++] = ' ';
			}
			pop(&top);
		}
		else
		{
			unary_switch =1;
			while (isp[stack[top]] >= icp[token])
			{
				postfix[index++] = print_token(pop(&top));
				postfix[index++] = ' ';
			}
			push(&top, token);
		}
	}
	while ((token = pop(&top)) != eos)
	{
		postfix[index++] = print_token(token);
		postfix[index++] = ' ';
	}
	postfix[index] = '\0';
}

char print_token(precedence token)
{
	switch (token)
	{
	case 0 : return 40;
	case 1 : return 41;
	case 2 : return 43;
	case 3 : return 45;
	case 4 : return 42;
	case 5 : return 47;
	case 6 : return 37;
	}
	
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
    }
	if (48 > (*psymbol) || (*psymbol) > 57)
	{
		printf("Wrong input\n");
		return eos;
	}
	else	return operand;
}

void push(int* ptop, precedence token)
{
	if (*ptop >= (MAX_SIZE - 1))
		printf("Stack is full\n");
	stack[++(*ptop)] = token;
	printf("push\n");
}

precedence pop(int* ptop)
{
	printf("pop\n");
	if (*ptop == -1)
	{
		printf("Stack is empty\n Your input is wrong\n");
		return eos;
	}
	return stack[(*ptop)--];
}

int main(void)
{
	printf("Puts your infix expression\n");
	fgets(infix, MAX_SIZE, stdin);
	printf("%s", infix);
	convert();
	printf("Given %s \n", infix);
	printf("%s", postfix);
	_getch();
	main();
}

