    ORG    $8024
    JMP    $9500


    ORG    $9000
START   andi    #%1101111111111111,SR
        move    #1234,D2
        TRAP    #5
        TRAP    #14
        
    ORG    $9500
T5      movem.l D0-D2,-(SP)
        cmpi.w  #0,D2
        beq     quit
        clr.l   D1
        move    D2,D1
        divs    #10,D1
        swap    D1
        move    D1,D0
        swap    D1
        move  D1,D2
        TRAP    #5
        add   #48,D0
        trap    #1
quit    movem.l (SP)+,D0-D2
        RTE

    END    START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
