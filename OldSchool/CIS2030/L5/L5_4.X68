
    ORG $8000
START   MOVE.W  NUM1,D0
        MOVE.W  NUM2,D1
        MOVE.W  NUM3,D2
IF      CMP     D1,D0
        BLT     ELSEIF
IF2     CMP     D2,D0
        BLT     ELSE
        MOVE.W  NUM1,BIGGEST
        BRA     EXIT
ELSE    MOVE.W  NUM3,BIGGEST
        BRA     EXIT
ELSEIF  CMP     D2,D1
        BLT     ELSE
        MOVE.W  NUM2,BIGGEST
EXIT    MOVE.W BIGGEST,D3
        TRAP    #14
        

    ORG $9000
NUM1    DC.W    -5
NUM2    DC.W    -10
NUM3    DC.W    -15
BIGGEST DS.W    1
    END START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
