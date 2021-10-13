DUART   EQU $C001
SRA     EQU 2
TBA     EQU 6
CL      EQU $0D
LF      EQU $0A

    ORG     $8000
START   MOVEA.L #WORD,A1
        BSR     PRINT
        TRAP    #14
        
WORD    DC.B CL,LF,'HELLO'
        DC.B 0

PRCH    MOVE.L  A0,-(A7)
        MOVE.W  D7,-(A7)
        MOVEA.L #DUART,A0
       
PRCH2   MOVE.B  SRA(A0),D7
        ANDI.B  #4,D7
        BEQ     PRCH2
        MOVE.B  D0,TBA(A0)
        MOVE.W  (A7)+,D7
        MOVE.L  (A7)+,A0
        RTS


PRINT   MOVE.L D0,-(A7)
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
