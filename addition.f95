program test_addition

implicit none
  
real sum

integer i, n

open(unit=10,file='test_result.dat',status='unknown')

n = abc

sum =  0.0

do i = 1, n

   sum = sum + float(i)

enddo   

write(10,*) "The sum of first", n, "integers is,", int(sum)

end program test_addition
