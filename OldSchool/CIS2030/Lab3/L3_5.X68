*IAN CROSS LAB 3 BONUS

CODE    EQU     $8000
DATA    EQU     $9000

    ORG     CODE
START   MOVE.W      W,D0
    MOVE.B      W+1,D1
    MULU        D1,D0
    MOVE.W      W+2,D1
    EXT.W       D1
    DIVU        #$3,D1
    ADD.W       D0,D1
    MOVE.L      D1,W+3
    TRAP        #14
    
    ORG     DATA
W   DC.W    $5
    DC.B    $5
    DC.W    $9
    DS.L    1
    END     START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
