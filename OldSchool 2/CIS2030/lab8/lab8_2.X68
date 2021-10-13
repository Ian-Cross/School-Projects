
    ORG     $8000
START   MOVE.W  X,-(SP)
        MOVE.W  Y,-(SP)
        MOVE.W  Z,-(SP)
        jsr     QUAD
        lea     6(SP),SP
        TRAP    #14

**************Quadratic****************
QUAD    MOVE.W  4(SP),D2
        MOVE.W  6(SP),D3
        MOVE.W  8(SP),D4
        MULS    D2,D2
        MULS    D4,D3
        MULS    #2,D3
        MULS    D4,D4
        MULS    #5,D4
        SUB.W   D3,D4
        ADD.W   D2,D4
        MOVE.W  D4,D1
        rts
        

    ORG     $A000
X       DC.W    2
Y       DC.W    3
Z       DC.W    4
        
    END    START



*~Font name~Courier New~
*~Font size~16~
*~Tab type~1~
*~Tab size~4~
