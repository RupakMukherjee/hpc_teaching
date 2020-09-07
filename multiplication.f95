program test

implicit none
  
real factorial

integer i, m

open(unit=10,file='test_result.dat',status='unknown')

m = xyz

factorial = 1.0

do i = 1, m

   factorial = factorial * float(i)

enddo

write(10,*) "The product of first", m, "integers is,", int(factorial)

end program test
