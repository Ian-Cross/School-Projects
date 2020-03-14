identification division.
program-id. Babylonian-sqrt.

environment division.
input-output section.
file-control.
  select standard-output assign to display.

data division.
file section.
fd standard-output.
  01 out-line picture X(100).
working-storage section.
77 diff pic v9(5) value .00100.
77 z    pic s9(11)v9(6).
77 k    pic s9999.
77 x    pic 9(11)v9(6).
77 y    pic 9(11)v9(6).
77 temp pic 9(11)v9(6).
77 flag pic 9 value 0.
01 title-line.
  02 filler pic X(9) value spaces.
  02 filler pic X(26) value 'Square-root Approximation'.
01 under-line.
  02 filler pic X(44) value '--------------------------------------------'.
01 prompt-line.
  02 filler pic X(29) value 'Enter a number (q to quit):'.
  02 filler pic X value space.
01 invalid-line.
  02 filler pic X value space.
  02 inv-z  pic -(11)9.9(6).
  02 filler pic X(15) value '  Invalid Input'.
01 abort-line.
   02 abo-z pic Z(11)9.9(6).
   02 filler pic X(38) value '  Attempt Aborted, too many iterations'.
01 print-line.
  02 filler pic X(7) value 'Input: '.
  02 pri-z  pic Z(11)9.9(6).
  02 filler pic X(3) value spaces.
  02 filler pic X(13) value 'Square Root: '.
  02 pri-y  pic Z(11)9.9(6).

*> A program that uses Babylonian estimation to calculate square roots.
procedure division.
  open output standard-output.
  *> Program intro
  write out-line from title-line after advancing 0 lines.
  write out-line from under-line after advancing 1 line.

  *> Run the program until the user quits
  perform until flag is equal 1
    write out-line from prompt-line after advancing 1 line
    accept z
    *> Only compute when a positive natural number is entered
    if z is greater than 0
    then
      *> Get the first approximation
      divide 2 into z giving x rounded
      
      *> Calculate to the 1000th element in the series
      *> If it still isn't close enough to the desired precision, quit
      perform varying k from 1 by 1
        until k is greater than 1000
        *> Get the next approximation
        compute y rounded = 0.5 * (x + z / x)
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
          move z to pri-z
          move y to pri-y
          write out-line from print-line after advancing 1 line
          exit perform
        end-if
      end-perform

      *> If it still isn't close enough to the desired precision, quit
      if k is greater than 1000
      then
        move z to abo-z
        write out-line from abort-line after advancing 1 line
      end-if

    else if z is equal 0
      display 'Quitting'
      move 1 to flag

    else
      move z to inv-z
      write out-line from invalid-line after advancing 1 line
    end-if
  end-perform.
  close standard-output.
stop run.
