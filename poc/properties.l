%{
int withinL10nNoteParan = 0;
%}
digit [0-9]
number [0-9]+
char [a-zA-Z]
string ("_"|{digit}|{char})+
line [^\n]+
stringlist ({string}",")*{string}
commentstartline "# LOCALIZATION NOTE ("{stringlist}")"
commentline #.*

%%

{commentstartline} {
    printf("comment: %s", yytext + strlen("# LOCALIZATION NOTE ("));
    withinL10nNoteParan = 1;
}

) {
    if (withinL10nNoteParan)
    {
        withinL10nNoteParan = 0;
        yytext - 1;
    }
}