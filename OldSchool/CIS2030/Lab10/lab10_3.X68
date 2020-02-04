DUART   EQU $C001
SRA     EQU 2
RBA     EQU 6
IPR     EQU $1A
OPR_SET EQU $1C
OPR_CLR EQU $1E

    ORG     $8000
START   MOVEA.L #DUART,A0
LOOP    MOVE.B  SRA(A0),D0
        ANDI.B  #1,D7
        BEQ     LOOP
        MOVE.B  RBA(A0),D0
        ANDI.B  #$FF,D0
        BSR.S   OUT
        BRA     LOOP
        TRAP    #14
        
OUT     MOVE.B  D0,OPR_CLR(A0)
        NOT.B   D0
        MOVE.B  D0,OPR_SET(A0)
        NOT.B   D0
        RTS
    
    END    START








*~Font name~Courier New~
*~Font size~16~
*~Tab type~1~
*~Tab size~4~
