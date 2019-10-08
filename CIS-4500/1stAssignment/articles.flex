/*
  File Name: articles.flex
  JFlex specification
*/

%%

%class Lexer
%type Token
%line
%column

%eofval{
  return null;
%eofval};


/* A line terminator is a \r (carriage return), \n (line feed), or
   \r\n. */
LineTerminator = \r|\n|\r\n

/* White space is a line terminator, space, tab, or form feed. */
WhiteSpace     = {LineTerminator} | [ \t\f]

/* A literal integer is is a number beginning with a number between
   one and nine followed by zero or more numbers between zero and nine
   or just a zero.  */
digit = [0-9]
number = [-|+]?[0-9]+ | [-|+]?{digit}*.{digit}+

/* A identifier integer is a word beginning a letter between A and
   Z, a and z, or an underscore followed by zero or more letters
   between A and Z, a and z, zero and nine, or an underscore. */
letter = [a-zA-Z]
word = ({letter}|[0-9])+

Label = "$DOC".* | "$TITLE" | "$TEXT"
punc = [\.\?\!:,;$\"\(\)\/]+
/* apostrophe = ([a-zA-Z0-9]+\'[a-zA-Z0-9]*)+ | \' */
/* hyphen = ([a-zA-Z0-9]+-[a-zA-Z0-9]*)+ | - */

apostrophe = ([a-zA-Z0-9\-]+\'[a-zA-Z0-9\-]*)+ | \'
hyphen = ([a-zA-Z0-9\-]+-[a-zA-Z0-9\-]*)+ | -

%%

/*
   This section contains regular expressions and actions, i.e. Java
   code, that will be executed when the scanner matches the associated
   regular expression. */
{Label}            { return new Token(Token.LAB, yytext(), yyline, yycolumn); }
{number}           { return new Token(Token.NUM, yytext(), yyline, yycolumn); }
{word}             { return new Token(Token.WORD, yytext(), yyline, yycolumn); }
{punc}             { return new Token(Token.PUNC, yytext(), yyline, yycolumn); }
{apostrophe}+      { return new Token(Token.APOS, yytext(), yyline, yycolumn); }
{hyphen}           { return new Token(Token.HYPH, yytext(), yyline, yycolumn); }
{LineTerminator}   { return new Token(Token.NEW, yytext(), yyline, yycolumn); }
{WhiteSpace}       { /* skip whitespace */ }
"{"[^\}]*"}"       { /* skip comments */ }
.                  { return new Token(Token.ERROR, yytext(), yyline, yycolumn); }
