/*
Carla Perez Gavilan, A01023033
09-09-2022
Analisis Lexico 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

// Respuestas de tokens
char tokens[8][5]={"OPREL", "ASIG", "OPAR", "ID", "ENT", "REAL", "ERR"};

// Lexema acumulado
char lexema[80];  
int indLexema=0;
int lineNum=0;

// Funcion para imprimir tokens
void imprimeTokLex(int nT){
    lexema[indLexema]='\0';
    printf("Token: %s, Lexema: %s, Numero de Linea: %d\n",tokens[nT],lexema, lineNum);
    indLexema=0;
}

int main(void)
{
    // Inicializacion
    FILE *textfile;
    int n; 
    char cadena[MAX_LINE_LENGTH];
    int contadorLinea = 0;

    // Leer archivo 
    textfile = fopen("sample.txt", "r");
    if(textfile == NULL)
    {
        return 1;
    }

    // Iterar linea por linea 
    while(fgets(cadena, MAX_LINE_LENGTH, textfile))
    {
    // inicializar indice de char en linea, estado y numtoken
    int ind=0;  
    int edo=0;  
    int numToken;

    // Imprimir linea
    printf("%d %s\n", contadorLinea, cadena);

    // Obtener tamano de la linea
    n = strlen(cadena);  

    while(ind < n)
        {
        switch(edo)
        {
        case 0: // OPREL or ASIG
            switch(cadena[ind])
            {
                case '<':
                    edo = 1;
                    lexema[indLexema++]='<';
                    break;
                case '>':
                    edo = 1;
                    lexema[indLexema++]='>';
                    break;
                case '=':
                    edo = 2;
                    lexema[indLexema++]='=';
                    break;
                case '+':
                    edo = 3;
                    lexema[indLexema++]='+';
                    break;
                case '-':
                    edo = 3;
                    lexema[indLexema++]='-';
                    break;
                case '%':
                    edo = 4;
                    lexema[indLexema++]='%';
                    break;
                case '/':
                    edo = 4;
                    lexema[indLexema++]='/';
                    break;
                case '*':
                    edo = 3;
                    lexema[indLexema++]='*';
                    break;
                case ' ':
                    edo = 0;
                    break;
                case '\n':
                    edo = 0;
                    break;
                default:
                    if(isdigit(cadena[ind])) 
                    {  
                        edo = 5;
                        lexema[indLexema++]=cadena[ind];
                    }
                    else
                    {
                        if(isalpha(cadena[ind]))
                        {
                            edo = 6;
                            lexema[indLexema++]=cadena[ind];
                        }
                        else
                        {
                            lexema[indLexema++]=cadena[ind];
                            imprimeTokLex(6);
                        }
                    }
                     break;
            }
            ind++;
            break;

        case 1: //llevo < o >
            if(cadena[ind]=='='){
                lexema[indLexema++]='=';
                ind++; 
                printf("case 1 inside if\n");
            }
            imprimeTokLex(0);
            printf("case 1\n");
            edo = 0;
            break;
        case 2: // ya llevaba =, debo revisar si es asig o comp
            if(cadena[ind]=='='){
                lexema[indLexema++]='=';
                imprimeTokLex(0);
                ind++;
                printf("case 2 inside if\n");
            }
            else{
                imprimeTokLex(1);
                printf("case 2 inside else\n");
            }
            edo = 0;
            break;
        case 3: // ya se reconocion +, - o * y falta ver si se repiten
            if(cadena[ind]==cadena[ind-1]){
                lexema[indLexema++]=cadena[ind];
                ind++;
            }
            edo = 4;
            break;
        case 4: // ya se reconocion % o /
            if(!isdigit(cadena[ind]) || !isalpha(cadena[ind])){
                lexema[indLexema++]=cadena[ind];
                imprimeTokLex(6);
                ind++;            
            }else{
                imprimeTokLex(2);
            }
            edo = 0;
            break;
        case 5: // es digito
            if(isdigit(cadena[ind])){
                lexema[indLexema++]=cadena[ind];
                ind++;
                edo = 5;            
            }
           if(isdigit(cadena[ind])){
                lexema[indLexema++]=cadena[ind];
                ind++;
                edo = 6; 
            }
            else{
                imprimeTokLex(4);
                edo = 0; 

            }
            break;
        case 6: // es letra o variable
            if(isdigit(cadena[ind]) || isalpha(cadena[ind])){
                lexema[indLexema++]=cadena[ind];
                ind++;
                edo = 6;            
            }
            else{
                imprimeTokLex(3);
                edo = 0; 
            }
            break;

        }  
    }
    }   
    fclose(textfile);
    return 0;
}




