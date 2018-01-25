#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXSIZE 75

char postfix[MAXSIZE];
float operand;
float fraction;
float ans;

typedef struct{
    char key[MAXSIZE];
    float value;
    struct expretion *next;
} expretion;

typedef struct{
    expretion *head;
    expretion *tail;
} linkedlist;
linkedlist listOfSymbol;

void intializelinkedlist(linkedlist *l){
    l->head=NULL;
    l->tail=NULL;
}

expretion* addNewNode(char *keyword,float value){
    expretion *newNode =(expretion*)malloc(sizeof(expretion));
    strcpy(newNode->key,keyword);
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}

void addhead(linkedlist *l,char * key,float value){
    expretion *newNode=addNewNode(key,value);
    newNode->next=l->head;
    l->head=newNode;
    if(!l->tail)
        l->tail=newNode;
}

void addtail(linkedlist *l,char * key,float value){
     expretion *newn=addNewNode(key,value);
    if(l->head==NULL)
        l->tail = l->head = newn;
        else{
            expretion *OldTail = l->tail;
            l->tail=newn;
            OldTail->next=newn;
        }
}

void display_poly (linkedlist *l){
    expretion *n = l->head;
    if(n==NULL)
        printf("empty");
    while(n!=NULL){
        printf("%s\n",n->key);
        printf("%f\n",n->value);
        n = n->next;
    }
}

expretion* searchSymbol(linkedlist *l,char *keyword){
    expretion* ptrReqSymbol=l->head;
    while(ptrReqSymbol){
        if(strcmp(keyword,ptrReqSymbol->key)==0)
            return ptrReqSymbol;
        ptrReqSymbol=ptrReqSymbol->next;
    }
    return NULL;
}

typedef struct{
    char items[MAXSIZE];
    int top;
}Stack;

typedef struct{
    int top2;
    float str[MAXSIZE];
}Stack2;

void initialize(Stack *ptr){
    ptr->top=-1;
}

void initialize2(Stack2 *ptr){
    ptr->top2=-1;
}

void push(char x, Stack *ptr){
    if(!isFull(ptr)){
    ptr->top++;
    ptr->items[ptr->top]=x;

    }
    else printf("can't add this value, stack full\n");
}

void push2(float x, Stack2 *ptr){
    if(!isFull2(ptr)){
    ptr->top2++;
    ptr->str[ptr->top2]=x;

    }
    else printf("can't add this value, stack full\n");
}

int isFull(Stack *ptr){
    if(ptr->top < MAXSIZE )
        return 0;
    else
        return 1;
}

int isFull2(Stack2 *ptr){
    if(ptr->top2 < MAXSIZE )
        return 0;
    else
        return 1;
}

char pop(Stack *ptr){
    if(!isEmpty(ptr)){
    char x;
    x=ptr->items[ptr->top];
    ptr->top--;
    return x;
    }
    else{
        printf("can't pop any value stack is empty\n");
        return -1;
    }
}

float pop2(Stack2 *ptr){
    if(!isEmpty2(ptr)){
    float x;
    x=ptr->str[ptr->top2];
    ptr->top2--;
    return x;
    }
    else{
        printf("can't pop any value stack is empty\n");
        return -1;
    }
}

int isEmpty(Stack *ptr){
    if(ptr->top==-1)
        return 1;
    else
        return 0;
}

int isEmpty2(Stack2 *ptr){
    if(ptr->top2==-1)
        return 1;
    else
        return 0;
}

char top(Stack *ptr){
    char x= pop(ptr);
    push(x,ptr);
    return x;
}

float top2(Stack2 *ptr){
    float x= pop2(ptr);
    push2(x,ptr);
    return x;
}

void ValidationExpression(char *ptr){

    if(equalValidation(ptr)==-1)
            printf("Invalid input: You have entered more than 1 equal in your expression!\n TRY AGAIN!\n");
        else if(equalValidation(ptr)==0)
            printf("Invalid input: You haven't entered equal in your expression!\n TRY AGAIN!\n");
        else{
                int x=equalValidation(ptr);
                char LHS[MAXSIZE];
                strncpy(LHS,ptr,x);
                int i=0;
                while(LHS[i]==' '){
                    i++;
                }
                char newLHS[MAXSIZE];
               strcpy(newLHS,LHS+i);
               strcpy(LHS,newLHS);
                if(LHS[x-1]==' '){
                   LHS[x-1]='\0';
                    int i=strlen(LHS)-1;
                while(LHS[i]==' '){
                    LHS[i]='\0';
                    i--;
                }
}
                else{
                      LHS[x]='\0';
                }
                if(lhsValidation(LHS)==-1){
                      printf("Invalid input: Left hand side of your expression can't contain operator or digits!\n TRY AGAIN!\n");
                }
                else if(lhsValidation(LHS)==-2){
                  printf("Invalid input: name of variables must have no spaces!\n TRY AGAIN!\n");
                }
                   else{
                        char RHS[MAXSIZE];
                        int i;
                        int j=0;
                        if(ptr[x+1]==' '){
                        for(i=x+2;i<strlen(ptr);i++){
                             RHS[j]=ptr[i];
                              j++;
                        }
                        }
                        else{
                            for(i=x+1;i<strlen(ptr);i++){
                             RHS[j]=ptr[i];
                              j++;
                        }
                        }
                            RHS[j]='\0';
                        if(rhsValidation(RHS)==-1)
                             printf("Invalid input: There is an error in the right hand side of your expression , this error is indicated in the previous line !\n TRY AGAIN!\n");
                            else{
                                    int type;
                                    type=typeOfExpression(RHS);
                            if(type==1)
                                type1(RHS,LHS);
                             else if(type==2)
                                    type2(RHS,LHS);
                                    else
                                        type3(RHS,LHS);
                            }
                       }
        }
}

int isOperator(char x){

     if(x == '+' || x == '-' || x == '^' || x == '*' || x == '/' || x ==')' || x =='(')
        return 1;
     else
        return 0; //invalid
}

int dotValidation(char *ptrRHS){
    int i , j;
    int dotCounter;
    int type = typeOfExpression(ptrRHS);

    if(type == 1){
            i = 0;
            dotCounter = 0;
            while(ptrRHS[i] != '\0'){
                if(ptrRHS[i] == '.')
                    dotCounter++;
                 i++;
            }
               if(dotCounter>1){
                    printf("Invalid expression: Multiple dot for same number \n");
                    return 0;
        }
        else
            return 1; // valid
        }
    else if(type == 2 || type == 3){
                i = 0 ;
                dotCounter = 0;
                while(ptrRHS[i] != '\0'){
                    if(ptrRHS[i] == '.')
                        dotCounter++;
                    else if(isOperator(ptrRHS[i])){
                        if(dotCounter>1){
                            printf("Invalid expression: Multiple dot for same number \n");
                            return 0;
                }
                else{
                    dotCounter = 0;
                }
        }
                    i++;
                        }
                        return 1;
                    }
                }

int equalValidation(char *ptr, int *ptrIndexEqual){
     int i=0;
     int indexEqual;
     int counter=0;
     for(i;i<(strlen(ptr));i++){
        if(ptr[i]=='='){
            indexEqual=i;
            counter++;
        }
        }
     if(counter==1)
        return indexEqual;
     else if(counter==0)
        return counter;
     else
        return -1;
}

int lhsValidation(char *ptrLHS){
    int x=strlen(ptrLHS);
    int i=0;
    int flag=0;
    for(i;i<x;i++){
        if(ptrLHS[i]=='+'||ptrLHS[i]=='-'||ptrLHS[i]=='*'||ptrLHS[i]=='/'||ptrLHS[i]=='^'||isdigit(ptrLHS[i])){
           return -1;
        }
        if(ptrLHS[i]==' '){
            return -2;
        }
    }
    return 0;
}

int rhsValidation(char *ptrRHS){
    int x=strlen(ptrRHS);
    int i=0;
    int resultParenthese;
    int resultdot;
    //check that first and last element are not operator
    if(ptrRHS[i]=='+'||ptrRHS[i]=='-'||ptrRHS[i]=='^'||ptrRHS[i]=='*'||ptrRHS[i]=='/'||ptrRHS[i]==')'||ptrRHS[x-1]=='+'||ptrRHS[x-1]=='-'||ptrRHS[x-1]=='^'||ptrRHS[x-1]=='*'||ptrRHS[x-1]=='/'||ptrRHS[x-1]=='('){
        printf("your expression can't start or end with this operator\n");
        return -1;
    }
    for(i;i<x;i++){
        if(ptrRHS[i]=='+'||ptrRHS[i]=='-'||ptrRHS[i]=='^'||ptrRHS[i]=='*'||ptrRHS[i]=='/'||ptrRHS[i]=='('){
            if(ptrRHS[i+1]=='+'||ptrRHS[i+1]=='-'||ptrRHS[i+1]=='^'||ptrRHS[i+1]=='*'||ptrRHS[i+1]=='/'||ptrRHS[i+1]==')'){
                 printf("there is 2 operators can't be after each other\n");
                 return -1;
            }
        }
         if(ptrRHS[i]=='!'||ptrRHS[i]=='@'||ptrRHS[i]=='#'||ptrRHS[i]=='$'||ptrRHS[i]=='&'||ptrRHS[i]=='{'||ptrRHS[i]=='}'||ptrRHS[i]=='['||ptrRHS[i]==']'||ptrRHS[i]==';'||ptrRHS[i]==':'||ptrRHS[i]=='>'||ptrRHS[i]=='<'||ptrRHS[i]=='?'||ptrRHS[i]=='"'||ptrRHS[i]==','||ptrRHS[i]=='['||ptrRHS[i]==']'||ptrRHS[i]==';'||ptrRHS[i]==':'||ptrRHS[i]=='>'||ptrRHS[i]=='<'||ptrRHS[i]=='?'||ptrRHS[i]=='"'||ptrRHS[i]=='%'){
             printf("invalaid symbol!\n");
             return -1;
         }
         if((ptrRHS[i]>='a' && ptrRHS[i]<='z') || (ptrRHS[i]>='A' && ptrRHS[i]<='Z')){
            if(isdigit(ptrRHS[i+1])||isdigit(ptrRHS[i-1])){
                printf("symbol can't contain digits! if u want to muultiply symbol and digits u must put between them'*'!\n");
             return -1;
            }
         }
         if(ptrRHS[i]=='('){
                if(isdigit(ptrRHS[i-1])||(ptrRHS[i-1]>='a' && ptrRHS[i-1]<='z') || (ptrRHS[i-1]>='A' && ptrRHS[i-1]<='Z')){
                   printf(" invalaid input! if u want to multiply parenthese and digits u must put between them'*'!\n");
             return -1;
             }
             else{
                    int j=i;
                 printf("yes\n");
                while(ptrRHS[j-1]==' '){
                        printf("\nyes");
                    j++;
                }
                if(ptrRHS[j]=='('){
                    return -1;
                }
             }
         }
         if(ptrRHS[i]==')'){
                if(isdigit(ptrRHS[i+1])||(ptrRHS[i+1]>='a' && ptrRHS[i+1]<='z') || (ptrRHS[i+1]>='A' && ptrRHS[i+1]<='Z')){
                   printf(" invalaid input! if u want to multiply parenthese and digits u must put between them'*'!\n");
             return -1;
             }
           if(ptrRHS[i]==')'&&ptrRHS[i+1]=='('){
                 printf(" invalaid input! if u want to multiply parenthese and digits u must put between them'*'!\n");
             return -1;
             }

         }
    }
resultdot=dotValidation(ptrRHS);
    if(resultdot==0)
        return -1;
    else{
   resultParenthese= parenthesesValidation(ptrRHS);
   if(resultParenthese==1)
    return 1;
   else{
    printf("there is error in the entered parentheses\n");
    return -1;
   }
    }}

int  parenthesesValidation(char *ptrRHS){
    int x=strlen(ptrRHS);
    int open=0;
    int close=0;
    int i=0;
    int counter=0;
    for(i;i<x;i++){
        if(ptrRHS[i]=='('){
            open++;
            counter++;
           }
           else if(ptrRHS[i]==')'){
                if(open!=0){
                    open--;
                    close++;
                }
            else
                    return -1;
           }
    }
    if(counter==close)
        return 1;
    else
        return -1;
}

int isalphabithec(char *c){
    int x=strlen(c);
    int i=0;
    for(i=0;i<x;i++){
    if( (c[i]>='a' && c[i]<='z') || (c[i]>='A' && c[i]<='Z'))
       return 1;
    }
    return 0;
}

int typeOfExpression(char *ptr){
    int x=strlen(ptr);
    int flagOperator=0;
    int flagSymbol=0;
    int i=0;
    for(i=0;i<x;i++){
        if(ptr[i]=='+'||ptr[i]=='-'||ptr[i]=='^'||ptr[i]=='*'||ptr[i]=='/')
            flagOperator=1;
        else if(!isdigit(ptr[i])&&ptr[i]!='.'&&ptr[i]!='('&&ptr[i]!=')'&&ptr[i]!=' ')
                flagSymbol=1;
    }
    if(flagOperator==1&&flagSymbol==1)
        return 3;
    if(flagOperator==1&&flagSymbol==0)
        return 2;
    if(flagOperator==0&&flagSymbol==1)
        return 1;
    else
        return 1;
}

void type1(char *ptrRHS,char* ptrLHS){
    int x=strlen(ptrRHS);
    char symbolValue[MAXSIZE];
    int i=0;
    int j=0;
    double result;
    expretion *ifFound;
    for(i=0;i<x;i++){
        if(ptrRHS[i]!='('&&ptrRHS[i]!=')'&&ptrRHS[i]!=' '){
        symbolValue[j]=ptrRHS[i];
        j++;
        }
    }
    symbolValue[j]='\0';
    if(isalphabithec(symbolValue)==0){
        result =atof(symbolValue);
        ifFound=searchSymbol(&listOfSymbol,ptrLHS);
        if(ifFound!=NULL)
                ifFound->value=result;
        else
            addtail(&listOfSymbol,ptrLHS,result);
      printf("The value of entered expression =%.2f\n",result);
    }
    else{
        ifFound=searchSymbol(&listOfSymbol,symbolValue);
        if(ifFound==NULL)
            printf("ERROR Invalid Symbol %s\n",symbolValue);
        else{
            result=ifFound->value;
            ifFound=searchSymbol(&listOfSymbol,ptrLHS);
            if(ifFound!=NULL)
                ifFound->value=result;
        else
            addtail(&listOfSymbol,ptrLHS,result);
        printf("The value of entered expression =%.2f\n",result);
        }
    }
}

void type2(char *ptrRHS,char* ptrLHS){
    expretion *ifFound;
    convertInfixToPostfix(ptrRHS,postfix);
    evaluatePostfix();
    ifFound=searchSymbol(&listOfSymbol,ptrLHS);
    if(ifFound!=NULL)
                ifFound->value=ans;
        else
            addtail(&listOfSymbol,ptrLHS,ans);
}

void type3(char *ptrRHS,char* ptrLHS){
    int x=strlen(ptrRHS);
    char newEpression[MAXSIZE];
    char symbolValue[MAXSIZE];
    char convertToStringValue[MAXSIZE];
    expretion *ifFound;
    int i=0;
    int j=0;
    int k=0;
    int l=0;
    float result;
    char newvalue;
    while(ptrRHS[i]!='\0'){
            if( (ptrRHS[i]>='a' && ptrRHS[i]<='z') || (ptrRHS[i]>='A' && ptrRHS[i]<='Z')){
                    k=0;
                while((ptrRHS[i]>='a' && ptrRHS[i]<='z') || (ptrRHS[i]>='A' && ptrRHS[i]<='Z')){
                    symbolValue[k]=ptrRHS[i];
                    i++;
                    k++;
                }
                symbolValue[k]='\0';
                ifFound=searchSymbol(&listOfSymbol,symbolValue);
                if(ifFound==NULL){
            printf("ERROR Invalid Symbol %s\n",symbolValue);
            return;
                   }

            else{
                result=ifFound->value;
                sprintf(convertToStringValue,"%f",result);
                l=0;
                while(convertToStringValue[l]!='\0'){
                        newEpression[j]=convertToStringValue[l];
                        j++;
                        l++;
                }
            }
            }
            else{
                newEpression[j]=ptrRHS[i];
                j++;
                i++;
            }
    }
    newEpression[j]='\0';
    type2(newEpression,ptrLHS);
    }

int priority(char x){
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
        if(x == '^')
        return 3;
}

void convertInfixToPostfix(char *ptr,char postfix2[]){
    char *e;
    e= ptr;
    char x;
    int i=0;
    Stack convertInfix;
    initialize(&convertInfix);
    while(*e != '\0'){
        if(isalnum(*e)){
        if(!isalnum(*(e+1))&&*(e+1)!='.'){
            postfix2[i]=*e;
            i++;
            postfix2[i]=' ';
            i++;
        }
        else{
             postfix2[i]=*e;
            i++;
        }
        }
        else if(*e == '.'){
           postfix2[i]=*e;
            i++;

        }
        else if(*e == '(')
            push(*e,&convertInfix);

        else if(*e == ')'){

            while((x = pop(&convertInfix)) != '('){
                    postfix2[i]=x;
                    i++;
                  }
        }
        else
        {
           if(isEmpty(&convertInfix))
            push(*e,&convertInfix);
           else{
            while(priority(convertInfix.items[convertInfix.top]) >= priority(*e)){

                postfix2[i]=(pop(&convertInfix));
                i++;
            }
            push(*e,&convertInfix);
           }
        }
        e++;
    }
    while(!isEmpty(&convertInfix))
    {
       postfix2[i]=(pop(&convertInfix));
                i++;
    }
    postfix2[i]='\0';
}

int skip_blanks(int n){
  while (postfix[n] == ' ') n++;
  return n;
}

int get_operand(int n){
  operand = 0;
  fraction =0;
  int x=1;
  while (postfix[n] >= '0' && postfix[n] <= '9')
  {
      //multiple digits
    operand *= 10;
    operand += postfix[n]-'0';
    n++;
  }
  if(postfix[n]=='.'){
        n=n+1;
      while (postfix[n] >= '0' && postfix[n] <= '9')
  {
      //if(postfix[n]=='.')
    fraction += ((postfix[n]-'0')*(pow(0.1,x)));
    x++;
    n++;
  }
  operand+=fraction;
  }
  return n;
}

int isoperand(int i){
  char x = postfix[i];
  if(x>='0' && x<='9')
  return 1;
  else
  return 0;
}

float operate(float op1,float op2,char a){
  switch(a){
   case '+':return op2+op1;
   case '-':return op2-op1;
   case '*':return op2*op1;
   case '/':return op2/op1;
   case '^':return pow(op2,op1);
   }
  return nan("?");
}

void evaluatePostfix(){

     int i=0;
  float op1,op2;
  Stack2 postfixEvaluation;
  initialize2(&postfixEvaluation);

  while(1){

    i = skip_blanks(i);
    if ( postfix[i] == '\0')
      break;

    else if(isoperand(i)){

      i = get_operand(i);
      push2(operand,&postfixEvaluation);

    }
    else{

     op1=pop2(&postfixEvaluation);
     op2=pop2(&postfixEvaluation);
     ans=operate(op1,op2, postfix[i]);
     push2(ans,&postfixEvaluation);
     i++;

    }
  }
  printf("The value of entered expression= %.2f\n",ans);
}

int main(){
    char expression[MAXSIZE];
    intializelinkedlist(&listOfSymbol);
     while(1){
        printf("Enter the expression (or \"end\" to exit):");
        gets(expression);
        if(strcmp(expression,"end") == 0)
            break;
        else
            ValidationExpression(expression);
     }
    return 0;
}
