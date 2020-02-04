    ORG    $802A
    JMP    $9200
    
    ORG    $8030
    JMP    $9500


    ORG    $9000
START   TRAP    #7
        TRAP    #6
        TRAP    #14
        
    ORG    $9200
        ORi.W    #%0010000000000000,(A7)
        RTE
        
    ORG    $9500
        andi.W    #%1101111111111111,(A7)
        RTE

    END    START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
