*L6_3.x68     

	ORG	$8000
START  	MOVEA.L #MATRIX,A0
        MOVE.B  #0,D0 ;I
        MOVE.B  #0,D1 ;J
LOOP    ADD.B   #4,D1 ; number of collumns
        MOVE.B	(A0,D0.L),D2
	    ADD.B   #$1,D0
	    MOVE.B	(A0,D1.L),D3
	    ADD.B   #$1,D0
	    CMPI    #$3
	    BRA     LOOP
	    TRAP	#14

**** 4 x 4 matrix ****

	ORG	$9000		
MATRIX	DC.B	1 ,2 ,3 ,4
	    DC.B	5 ,6 ,7 ,8
	    DC.B	9 ,10,11,12
	    DC.B	13,14,15,16
	END	START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
