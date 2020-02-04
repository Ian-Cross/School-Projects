*IAN CROSS LAB 3 BONUS

CODE    EQU     $8000
DATA    EQU     $9000

    ORG     CODE
START   MOVE.W      W,D0
    MOVE.B      Y,D1
    EXT.W       D1
    MULS        D1,D0
    MOVE.W      X,D2
    DIVU        #$3,D2
    ADD.W       D0,D2
    EXT.L       D2
    MOVE.L      D2,Z
    TRAP        #14
    
    ORG     DATA
W   DC.W    $4
Y   DC.B    -3
X   DC.W    $9
Z   DS.L    1
    END     START



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
