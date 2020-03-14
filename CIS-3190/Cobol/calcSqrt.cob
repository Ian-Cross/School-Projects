identification division.
program-id. calcSqrt.

data division.
working-storage section.
77 diff pic v9(5) value .00100.
77 k    pic s9999.
77 x    pic 9(11)v9(6).
77 y    pic 9(11)v9(6).
77 temp pic 9(11)v9(6).
linkage section.
77 inVal  pic s9(11)v9(6).
77 outVal pic Z(11)9.9(6).


procedure division using inVal, outVal.
  if inVal less than 0
  then
    move 0 to outVal
    exit program
  end-if.

  divide 2 into inVal giving x rounded.
  perform varying k from 1 by 1
    until k is greater than 1000
    compute y rounded = 0.5 * (x + inVal / x)
    subtract x from y giving temp

    if temp is less than 0
    then
      compute temp = -temp
    end-if

    if temp/(y+x) is greater than diff
    then
      move y to x
    else
      exit perform
    end-if
  end-perform.

  move y to outVal.

exit program.
