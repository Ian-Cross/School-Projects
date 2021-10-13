*L6_2.x68     

	ORG	$8000
START  	MOVE.B  #$FF,D0
        LEA     pointer1,A0
        LEA     pointer2,A1	  
LOOP    MOVE.B  (A0)+,D1
        MOVE.B  (A1)+,D2
        CMP     D2,D1
        BEQ     IF
        MOVE.B  #$00,D0
IF      CMPI    #$0D,D1
        BEQ     EXIT
        CMPI    #$FF,D0
        BEQ     LOOP
EXIT    TRAP	#14

	ORG	$9000		
pointer1	DC.B	'AAAAA',$0D
    ORG $9020
pointer2    DC.B    'AAAAA',$0D

	END	START







*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
