subroutine eCalculation(n)
  implicit none
  integer, intent(in) :: n
  integer :: i,m,j,carry,temp
  integer, dimension (:), allocatable :: coef
  real :: test

  m = 4
  test = (n + 1) * 2.30258509

  do
    m = m+1
    if (m * (log(real(m)) - 1.0) + 0.5 * log(6.2831852 * real(m)) > test) exit
  end do

  allocate (coef(m))

  do j=2,m+1
    coef(j) = 1
  end do

  write(9,'(A)',advance='no') "2."
  do i=0,m+1
    carry = 0
    do j=m,1,-1
      temp = coef(j) * 10 + carry
      carry = temp / j
      coef(j) = temp - carry * j
    end do
    write(9,'(9I1)',advance='no') carry
  end do

end subroutine eCalculation

program calcE
  implicit none
  Character(len = 100) :: filename
  logical :: lexist

  write(*,*) "Welcome to Euler e Estimation"
  write(*,*) "Please enter a file for output:"
  read(*,'(A)') filename

  open(unit=9, file=filename, status='new', action='write')

  call eCalculation(100)

  close (9,status="keep")

  end
