******************************************************
* WIRE681.x68                                        *
*                                                    *
* This is a "wire" program.  It reads the 68681      *
* input port and updates the output port, simulating *
* wire connections, as follows:                      *
*                                                    *
*        IP0 ----> OP0                               *
*        IP1 ----> OP1                               *
*        IP2 ----> OP2                               *
*        IP3 ----> OP3                               *
*        IP4 ----> OP4                               *
*        IP5 ----> OP5                               *
******************************************************
DUART    EQU      $00C001     ;base address of 68681
IPR      EQU      13*2        ;input port register
OPR_SET  EQU      14*2        ;set bit command reg.
OPR_CLR  EQU      15*2        ;clear bit cmd. reg.

         ORG      $8000
WIRE681  MOVEA.L  #DUART,A0   ;A0 points to 68681
LOOP     MOVE.B   IPR(A0),D0  ;read input port
         ANDI.B   #$FF,D0     ;(mask if desired)
         BSR.S    OUT681      ;update output port
         BRA      LOOP        ;repeat

******************************************************
* OUT681 - OUTput data to 68681 output port          *
*                                                    *
*        ENTER:   D0[0:7] contains data to output    *
*                 A0 points to 68681 DUART           *
*        EXIT:    all registers intact               *
*        USES:    no subroutines                     *
******************************************************
OUT681   MOVE.B   D0,OPR_CLR(A0) ;clr. bits, set pins
         NOT.B    D0
         MOVE.B   D0,OPR_SET(A0) ;set bits, clr. pins
         NOT.B    D0             ;restore D0
         RTS
         END      WIRE681
