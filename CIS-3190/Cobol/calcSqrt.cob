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

*> A program that uses Babylonian estimation to calculate a square root
procedure division using inVal, outVal.
  *> Make sure value wont produce complex numbers
  if inVal less than 0
  then
    move 0 to outVal
    exit program
  end-if.

  *> Get the first approximation
  divide 2 into inVal giving x rounded.

  *> Calculate to the 1000th element in the series
  *> If it still isn't close enough to the desired precision, quit
  perform varying k from 1 by 1
    until k is greater than 1000
    *> Get the next approximation
    compute y rounded = 0.5 * (x + inVal / x)
    subtract x from y giving temp

    if temp is less than 0
    then
      compute temp = -temp
    end-if

    *> If it is precise enough, provide the output and quit, otherwise continue
    if temp/(y+x) is greater than diff
    then
      move y to x
    else
      exit perform
    end-if
  end-perform.

  *> If it still isn't close enough to the desired precision, use what was close
  move y to outVal.

exit program.
