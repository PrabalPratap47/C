%{
int ct = 0;
%}
%%
[a-zA-Z][a-zA-Z0-9]* {printf("identifiers\n"); ct++;}
[0-9]+ {printf("constants\n"); ct++;}
"\n" {printf("No. of tokens: %d", ct); ct = 0;}
%%
int yywrap(void)
{return 1;}
int main(int argc, char *argv[]) 
{
yyin = fopen(argv[1], "r");
yylex();
fclose(yyin);3
return 1;
}
