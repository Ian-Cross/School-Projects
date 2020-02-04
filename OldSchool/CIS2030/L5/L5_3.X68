
    ORG $8000
START   MOVE.B  #$30,D0
        ADD.B   HEX,D0
        MOVE.B  D0,CHAR
        CMP     #$39,D0
        BLE     EXIT
        ADD.B   #$7,CHAR
        MOVE.B  CHAR,D1
EXIT    TRAP    #14

    ORG $9000
HEX     DC.B    $4
CHAR    DS.B    1
        END START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
