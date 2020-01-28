/*
  File Name: news.flex
*/

import java.util.ArrayList;

%%

%class Lexer
%type Token
%line
%column

%eofval{
  printStack();
  return null;
%eofval};

%{
  private static ArrayList<String> tagStack = new ArrayList<String>();
  private static String output = "";
  private static String[] relaventTags = {"DOC","DOCNO","TEXT","DATE","HEADLINE","LENGTH","P"};
  private static final Token NOTHING = new Token(Token.NOTHING, "NOTHING" , -1,-1);

  private static Boolean contains(String[] values, String string) {
    for (String str : values) {
      if (str.equals(string)) return true;
    }
    return false;
  }

  private static String getTagName(String fullTag) {
    String tagName = fullTag.toUpperCase().split("</?|>| ")[1];
    return tagName;
  }

  private Token pushTag() {
    String tagName = getTagName(yytext());
    if (!contains(relaventTags,tagName)){
      output = tagName;
      return NOTHING;
    }
    tagStack.add(tagName);
    return new Token(Token.OPENTAG, tagName , yyline, yycolumn);
  }

  private void popTag() {
    tagStack.remove(tagStack.size()-1);
  }

  private Token checkTag() {
    String tagName = getTagName(yytext());
    if (!contains(relaventTags,tagName) || !output.equals("")){
      if (tagName.equals(output))
        output = "";
      return NOTHING;
    }

    if (tagName.equals(tagStack.get(tagStack.size()-1))) {
      popTag();
      return new Token(Token.CLOSETAG, tagName , yyline, yycolumn);
    } else {
      printStack();
      return new Token(Token.OPENTAG, "ERROR TAG-" + tagName , yyline, yycolumn);
    }
  }

  private static void printStack() {
    System.out.println(tagStack);
  }
%};


/* A line terminator is a \r (carriage return), \n (line feed), or \r\n. */
LineTerminator = \r|\n|\r\n

/* White space is a line terminator, space, tab, or form feed. */
WhiteSpace     = {LineTerminator} | [ \t\f]

/* A literal integer is is a number beginning with a number between
   one and nine followed by zero or more numbers between zero and
   nine or just a zero.  */
digit = [0-9]
number = ([-|\+]?{digit}+)|([-|\+]?{digit}*\.{digit}+)


punc = [\.\?\!:,;$\"\(\)\/]+ | -
hyphen = ([a-zA-Z0-9]+-[a-zA-Z0-9]*)+ | -
apostrophe = ([a-zA-Z0-9\-]+\'[a-zA-Z0-9\-]*)+ | \'

/* A identifier integer is a word beginning a letter between A and
   Z, a and z, or an underscore followed by zero or more letters
   between A and Z, a and z, zero and nine, or an underscore. */
letter = [a-zA-Z]
identifier = {letter}+
word = ({letter}|{digit})*{letter}({letter}|{digit})*

/* General Tags */
openTag = <[^\/>]*>
closeTag = <\/[^>]*>

%%

/*
   This section contains regular expressions and actions, i.e. Java
   code, that will be executed when the scanner matches the associated
   regular expression. */

{openTag}           { if (output.equals("")) return pushTag(); }
{closeTag}          { return checkTag(); }
{word}              { if (output.equals(""))
                        return new Token(Token.WORD, yytext(), yyline, yycolumn);
                    }
{number}            { if (output.equals(""))
                        return new Token(Token.NUMBER, yytext(), yyline, yycolumn);
                    }
{punc}              { if (output.equals(""))
                        return new Token(Token.PUNCTUATION, yytext(), yyline, yycolumn);
                    }
{hyphen}            { if (output.equals(""))
                        return new Token(Token.HYPHENATED, yytext(), yyline, yycolumn);
                    }
{apostrophe}+       { if (output.equals(""))
                        return new Token(Token.APOSTROPHIZED, yytext(), yyline, yycolumn);
                    }
{WhiteSpace}+      { /* skip whitespace */ }
"{"[^\}]*"}"       { /* skip comments */ }
.                  { return new Token(Token.ERROR, yytext(), yyline, yycolumn); }
