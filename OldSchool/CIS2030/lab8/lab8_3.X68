
    ORG     $8000
START   PEA     W
        PEA     X
        PEA     Y
        PEA     Z
        jsr     QUAD
        lea     16(SP),SP
        MOVE.L  W,D5
        TRAP    #14

**************Quadratic****************
QUAD    MOVEM    D0-D2/A0-A3,-(SP)
        MOVEA.L  18(SP),A0   ;Z
        MOVEA.L  22(SP),A1   ;Y
        MOVEA.L  26(SP),A2   ;X
        MOVEA.L  30(SP),A3  ;W
        MOVE.W  (A0),D0
        MOVE.W  (A1),D1
        MOVE.W  (A2),D2
        MULS    D0,D0       ;Z*Z
        MULS    D2,D1       ;X*Y
        MULS    #-4,D1      ;-4*Y  
        MULS    D2,D2       ;X*X
        MULS    #5,D2       ;5*X
        ADD.W   D1,D2   
        ADD.W   D0,D2
        MOVE.L  D2,(A3)
        MOVEM   (SP)+,D0-D2/A0-A3
        rts
        

    ORG     $A000
W       DS.L    1
X       DC.W    2
Y       DC.W    3
Z       DC.W    4
        
    END    START




*~Font name~Courier New~
*~Font size~16~
*~Tab type~1~
*~Tab size~4~
