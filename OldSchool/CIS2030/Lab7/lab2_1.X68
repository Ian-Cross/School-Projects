
    ORG    $8000
START       MOVE.W  A,D0
            MOVE.W  B,D1
            MOVE.L  #0,D2
LOOP        MOVE.L  D1,D3
            ANDI.W  #1,D3
            BEQ.S   EVEN
            ADD.W   D0,D2
EVEN        LSL.W   #1,D0
            LSR.W   #1,D1
            CMPI    #1,D1
            BEQ     EXIT
            BRA     LOOP
EXIT        ADD.W   D0,D2
            TRAP    #14              

    ORG     $9000
A   DC.W    30
B   DC.W    25

    END    START        

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
