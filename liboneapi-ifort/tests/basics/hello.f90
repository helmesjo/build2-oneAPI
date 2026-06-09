! Minimal ifort compile smoke test.
program hello
  implicit none
  integer :: x
  x = 2 + 2
  if (x /= 4) stop 1
end program hello
