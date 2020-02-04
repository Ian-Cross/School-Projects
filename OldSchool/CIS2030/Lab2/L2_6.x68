*L2_6.X68:template

	ORG	$8000

    MOVE.W D0,D1
    MULS #9,D1
    DIVS #5,D1
    ADD.W #32,D1
	TRAP	#14
	END	$8000

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
