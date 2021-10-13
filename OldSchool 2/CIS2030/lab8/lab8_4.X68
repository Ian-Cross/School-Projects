
    ORG     $8000
START   MOVE.W  X,-(SP)
        MOVE.W  Y,-(SP)
        PEA     Z
        jsr     QUAD
        lea     8(SP),SP
        MOVE    Z,D5
        TRAP    #14

**************Quadratic****************
QUAD    LINK        A0,#-6
        MOVEM.L     D0-D2/A1,-(SP)
        MOVE.W      14(A0),D1
        MULU        D1,D1
        MOVE.W      D1,-2(A0)
        MOVE.W      12(A0),D1
        MULU        D1,D1
        MOVE.W      D1,-4(A0)
        MOVE.W      14(A0),D0
        MOVE.W      12(A0),D1
        MULU        D0,D1
        MULU        #2,D1
        MOVE.W      D1,-6(A0)
        MOVE        -2(A0),D0
        MOVE        -4(A0),D1
        MOVE        -6(A0),D2
        ADD.W       D1,D0
        ADD.W       D0,D2
        MOVEA.L     8(A0),A3
        MOVE.L      D2,(A3)
        MOVEM.L     (SP)+,D0-D2/A1
        UNLK        A0
        rts
        

    ORG     $A000
X       DC.W    4
Y       DC.W    5
Z       DS.L    1
        
    END    START





*~Font name~Courier New~
*~Font size~16~
*~Tab type~1~
*~Tab size~4~
