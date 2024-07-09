%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int KEYWORD = 0;
int IDENTIFIER = 0;
int NUMBER = 0;
int OPERATOR = 0;
int COMPOUND_OPERATOR = 0;
int DELIMITER = 0;
int COMMENTS = 0;
int UNKNOWN = 0;
%}

%%

\(\*.*\*\) { COMMENTS++; printf("%s",yytext);}
and|array|begin|div|do|else|end|function|goto|if|label|not|of|or|procedure|program|then|type|var|while|read|write { KEYWORD++; }
[a-zA-Z][a-zA-Z0-9]* { IDENTIFIER++; }
[0-9]+(\.[0-9]+)? { NUMBER++; }
\+|\-|\*|\/|\<|\> { OPERATOR++; }
:=|<=|>=|<> { COMPOUND_OPERATOR++; }
\(|\)|\[|\]|\;|\:|\,|\. { DELIMITER++; }
[^ \t\n\r\f\v] { UNKNOWN++;}

%%

int yywrap() {
    return 1;
}
int main(int argc, char *argv[]) {
    FILE *stream;
    char line[10000];

    stream = fopen(argv[1], "r");

    while (fgets(line, sizeof(line), stream) != NULL) {
        yy_scan_string(line);
        yylex();
    }

    fclose(stream);

    printf("KEYWORD: %d\n", KEYWORD);
    printf("IDENTIFIER: %d\n", IDENTIFIER);
    printf("NUMBER: %d\n", NUMBER);
    printf("OPERATOR: %d\n", OPERATOR);
    printf("COMPOUND OPERATOR: %d\n", COMPOUND_OPERATOR);
    printf("DELIMITER: %d\n", DELIMITER);
    printf("COMMENTS: %d\n", COMMENTS);
    printf("UNKNOWN: %d\n", UNKNOWN);

    return 0;
}
