DUART   EQU $C001
SRA     EQU 2
TBA     EQU 6
CR      EQU $0D
LF      EQU $0A

    ORG     $8000
START   MOVEA.L #DUART,A0
        MOVE    #WORD,A3
        BSR     SCAN
        TRAP    #14
        
WORD    DS.B    20

PRCH    MOVE.L  A0,-(A7)
        MOVE.W  D7,-(A7)
        MOVEA.L #DUART,A0
       
PRCH2   MOVE.B  SRA(A0),D7
        ANDI.B  #1,D7
        BEQ     PRCH2
        MOVE.B  TBA(A0),D0
        MOVE.B  D0,(A3)+
        MOVE.W  (A7)+,D7
        MOVE.L  (A7)+,A0
        RTS


SCAN    MOVE.L D0,-(A7)
PR      MOVE.B (A1)+,D0
        BEQ     EXIT
        JSR     PRCH
        BRA     PR
        
EXIT    MOVE.L  (A7)+,D0
        RTS
    
    END    START









*~Font name~Courier New~
*~Font size~16~
*~Tab type~1~
*~Tab size~4~
