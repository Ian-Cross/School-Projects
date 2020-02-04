******************************************************
* TWOHZ.x68                                          *
*                                                    *
* This program uses the 68681 timer to create a 2 Hz *
* square wave on OP3.  If the 68681 X1 input is      *
* driven at 3.6864 MHz, then the frequency on OP3    *
* equals                                             *
*                                                    *
*       3686400 / 2 / 16 / COUNT                     *
*                                                    *
* where COUNT is the 16-bit integer in the timer     *
* registers CTUR and CTLR.  CTUR holds the upper     *
* byte, CTLR holds the lower byte.                   *
******************************************************
DUART    EQU      $00C001  ;68681 base address
ISR      EQU      $A
STOP     EQU      $1E
ACR      EQU      4*2      ;auxiliary control reg.
CTUR     EQU      6*2      ;counter/timer upper reg.
CTLR     EQU      7*2      ;counter/timer lower reg.
OPCR     EQU      13*2     ;output port config. reg.
COUNT    EQU      14400 
OPR_SET  EQU      $1C
OPR_CLR  EQU      $1E

         ORG      $8000
TWOHZ    MOVEA.L  #DUART,A0
         MOVE.W   #COUNT,D0
         MOVEP.W  D0,CTUR(A0)
         MOVE.B   #$70,ACR(A0)   ;crystal clock / 16
         
LOOP     MOVE.B   ISR(A0),D0
         ANDI.B   #8,D0
         BEQ      LOOP
         TST.B    STOP(A0)
         CMPI.B   #1,D2
         BEQ      OFF
         BRA      ON
         
OFF      MOVE.B #$FF,D0
         MOVE.B D0,$C01F
         NOT.B  D0
         MOVE.B #0,D2
         BRA LOOP

ON       MOVE.B #$00,D0
         MOVE.B D0,OPR_CLR(A0)
         NOT.B  D0
         MOVE.B D0,OPR_SET(A0)
         MOVE.B #1,D2
         BRA LOOP

         END      TWOHZ



*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
