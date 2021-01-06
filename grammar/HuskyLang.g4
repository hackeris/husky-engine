grammar HuskyLang;


statement:
    expression   EOF    #   ToExpression
    ;

expression
    :   logical   #   ToLogical
    ;

logical
    :   logical op=AND compare     #   LogicalOp
    |   logical op=OR compare     #   LogicalOp
    |   compare                 #   ToCompare
    ;

compare
    :   compare op=EQUAL plusOrMinus   #   CompareOp
    |   compare op=NEQ plusOrMinus     #   CompareOp
    |   compare op=GT plusOrMinus     #   CompareOp
    |   compare op=GTE plusOrMinus     #   CompareOp
    |   compare op=LT plusOrMinus     #   CompareOp
    |   compare op=LTE plusOrMinus     #   CompareOp
    |   plusOrMinus                 #   ToPlusOrMinus
    ;

plusOrMinus
    : plusOrMinus op=PLUS multOrDiv  # AddSubOp
    | plusOrMinus op=MINUS multOrDiv # AddSubOp
    | multOrDiv                   # ToMultOrDiv
    ;

multOrDiv
    : multOrDiv op=MULT powr # MultiDivOp
    | multOrDiv op=DIV powr  # MultiDivOp
    | unary                   # ToUnary
    ;

unary
    : op=MINUS powr       # UnaryOp
    | op=NOT powr         # UnaryOp
    | powr                # ToPower
    ;

powr
    : powr op=POW atom     # Power
    | atom            #   ToAtom
    ;

atom
    : literal                       # ToLiteral
    | identifier                    # ToIdentifier
    | functionName=identifier  LPAR argList? RPAR    # FuncCall
    | LPAR expression RPAR  # Braces
    | indexable=identifier '[' index=expression ']'   #ArrayIndex
    ;

argList
    :   argList ',' expression
    |   expression
    ;

identifier:
    ID;

literal:
    PI                    # ConstantPI
    | E                     # ConstantE
    | DOUBLE                # Double
    | INT                   # Int
    ;


INT    : [0-9]+;
DOUBLE : [0-9]+'.'[0-9]+;
PI     : 'pi';
E      : 'e';
POW    : '^';
ID     : [a-zA-Z_][a-zA-Z_0-9]*;
CHAR   : [a-zA-Z_0-9];

PLUS  : '+';
MINUS : '-';
MULT  : '*';
DIV   : '/';

EQUAL : '=';
GTE   : '>=';
GT    : '>';
LTE   : '<=';
LT    : '<';
NEQ   : '<>' | '!=';
AND   : '&';
OR    : '|';

NOT   : '!';

LPAR  : '(';
RPAR  : ')';

WS     : [ \t\r\n]+ -> skip;
NL     : '\n'   ->  skip;