
    ORG     $8000
START   MOVE.W  X,-(sp)
        jsr     quad
        lea     2(sp),sp
        TRAP    #14

**************Quadratic****************
quad    Move.w  4(sp),d0
        Move.w  d0,d1
        muls    #2,d1
        muls    d0,d0
        muls    #5,d0
        sub.w   d1,d0
        add.w   #6,d0
        move.w  d0,d1
        rts
        

    ORG     $A000
X    DC.W    3

    END    START



*~Font name~Courier New~
*~Font size~16~
*~Tab type~1~
*~Tab size~4~
