    !
    ! Performs encryption and decryption of a message using the lucifer algorithm
    ! https://www.staff.uni-mainz.de/pommeren/Cryptology/Bitblock/2_Feistel/Lucifer.pdf
    !
    subroutine lucifer(decrypt, key, message)
      implicit none
      integer, intent(in) :: decrypt
      integer, dimension(0:7,0:15) :: k
      integer, dimension(0:7,0:7,0:1) :: m
      integer, intent(inout), dimension(0:127) :: key, message
      integer, dimension(0:7) :: o, pr, tr
      integer, dimension(0:7,0:7) :: sw
      integer, dimension(0:15) :: s0, s1
      integer :: h, h0, h1, ii, jj, jjj, kk, kc, ks, l , v

      m = reshape(message,(/8,8,2/))
      k = reshape(key,(/8,16/))

      ! diffusion pattern
      data o/7,6,2,1,5,0,3,4/

      ! inverse of fixed permutation
      data pr/2,5,4,0,3,1,7,6/

      ! S-box permutations
      data s0/12,15,7,10,14,13,11,0,2,6,3,1,9,4,5,8/
      data s1/7,2,14,9,3,11,0,4,12,13,1,10,6,15,8,5/

      h0=0
      h1=1

      kc=0
      if (decrypt == 1) then
        kc=8
      end if

      ! Iterate the 16 bytes
      do ii=1,16
        if (decrypt == 1) then
          kc = mod( kc+1, 16)
        end if
        ks=kc

        do jj=0,7
          l=0
          h=0

          do kk=0,3
            l = (l*2) + m(7-kk, jj, h1)
          end do

          do kk=4,7
            h = (h*2) + m(7-kk, jj, h1)
          end do

          v = ( ( s0(l) + (16 * s1(h)) ) * ( 1 - k(jj, ks) ) ) + ( ( s0(h) + (16 * s1(l)) ) * k(jj, ks) )

          do kk=0,7
            tr(kk)=mod(v,2)
            v=v/2
          end do

          do kk=0,7
            m(kk, mod(( o(kk) + jj ), 8), h0) = mod(k(pr(kk),kc) + tr(pr(kk)) + m(kk,mod(o(kk) + jj,8),h0), 2)
          end do

          if (jj < 7 .or. decrypt == 1) then
            kc = mod( kc+1, 16)
          end if
        end do

        jjj=h0
        h0=h1
        h1=jjj
      end do

      do jj=0,7
        do kk=0,7
          sw(kk,jj) = m(kk,jj,0)
          m(kk,jj,0) = m(kk,jj,1)
          m(kk,jj,1) = sw(kk,jj)
        end do
      end do

      message = reshape(m,(/128/))
      key = reshape(k,(/128/))

      return
    end subroutine lucifer


    !
    ! Convert a hexadecimal string into a binary string and return it
    !
    subroutine expand(binaryStr, hexStr, length)
      implicit none
      integer, intent(in) :: length
      integer, dimension(0:*), intent(in) :: hexStr
      integer, dimension(0:*), intent(out) :: binaryStr
      integer :: i, j, v

      do i=0, length-1
        v=hexStr(i)
        do j=0,3
          binaryStr( (3-j) + (i*4) ) = mod(v,2)
          v=v/2
        end do
      end do

      return
    end subroutine expand

    !
    ! Convert a binary string into a hexadecimal string and return it
    !
    subroutine compress(binaryStr, hexStr, length)
      implicit none
      integer, intent(in) :: length
      integer, dimension(0:*), intent(out) :: hexStr
      integer, dimension(0:*), intent(in) :: binaryStr
      integer :: i, j, v

      do i=0,length-1
        v=0
        do j=0,3
          v = (v * 2) + mod( binaryStr( j + (i*4) ), 2 )
          end do
        hexStr(i)=v
      end do

      return
    end subroutine compress

    ! key
    ! 0123456789ABCDEFFEDCBA9876543210
    ! plain
    ! AAAAAAAAAAAAAAAABBBBBBBBBBBBBBBB

    !
    ! Intake an Encryption key and a message, and produce the encrypted version
    ! perform a validation check to make sure the message was encrypted alright
    !
    program luc
      implicit none
      integer :: decrypt = 0, i, length = 0
      integer, dimension(0:31) :: hexKey, hexMessage = 0
      integer, dimension(0:127) :: key, message
      character(len=10) :: wordMessage

      write(*,998)
      write(*,999)
      ! prompt user for 'key' input
      write(*,1003)
      read(*,1004) (hexKey(i),i=0,31)

      ! prompt user for 'word' input
      call readWord(wordMessage)
      call word2hex(wordMessage, hexMessage, length)
      call printhex(hexMessage, length)

      ! convert hexadecimal key and message into binary representation
      call expand(message, hexMessage, 32)
      call expand(key, hexKey, 32)

      ! write(*,1000) (key(i), i=0,127)
      ! write(*,1001) (message(i), i=0,127)

      ! Encrypt the message
      call lucifer(decrypt, key, message)

      call compress(message, hexMessage, 32)
      write(*,1002) (hexMessage(i),i=0,31)

      ! decrypt the message
      decrypt=1
      call lucifer(decrypt, key, message)

      ! convert binary key and message into hexadecimal representation
      call compress(message, hexMessage, 32)
      call compress(key, hexKey, 32)

      write(*,1000)
      write(*,1007) (hexKey(i),i=0,31)
      write(*,1001)
      write(*,1007) (hexMessage(i),i=0,31)

998   format('Welcome to the Lucifer Cypher!')
999   format('Given a key and a phrase, this program will encrypt and decrypt that phrase')
1000  format('Encryption Key:'/16(i0))
1001  format('Message:'/16(i0))
1002  format('Encrypted Message '/32(z0))
1003  format(' Input a encryption key (128 bits): ')
1004  format(32z1.1)
1007  format(1x,32z1.1)

    end
