      !
      ! Input a ASCII word from the command line
      !
      subroutine readWord(string)
        implicit none
        character(len=10), intent(out) :: string

        write(*,1005)
        read(*,*) string

1005    format(' Input a message to be encrypted (8-10 char): ')
        return
      end subroutine readWord

      !
      ! Convert ascii word into hexadecimal
      !
      subroutine word2hex(string, hexMessage, length)
        implicit none
        character(len=10), intent(in) :: string
        integer, intent(out) :: length
        integer, intent(out), dimension(0:31) :: hexMessage
        character :: c

        integer :: i, charVal, h1, h2, pos
        integer :: strLen = len(string)

        do i=1, strLen
          ! convert character to ascii value
          c = string(i:i)
          if (c == '') then
            exit
          end if
          charVal = ichar(c)

          ! Calculate hex value from ascii
          h1 = charVal / 16
          h2 = mod(charVal, 16)

          ! Insert hex into hex string
          pos = (i-1) * 2
          hexMessage(pos) = h1
          hexMessage(pos+1) = h2
          length = length + 2
        end do
        return
      end subroutine word2hex

      !
      ! Print out the given integer array in base 16 hexadecimal format
      !
      subroutine printhex(hexMessage, length)
        integer, intent(in), dimension(0:31) :: hexMessage
        integer, intent(in) :: length

        write(*,1002) (hexMessage(i), i=0, length-1)
1002    format('Your message in hexadecimal: '/32(z0))

      end subroutine printhex
