; C. Dodgson ADD1.ASM First sample of an AL program 4/8/14
; Add the two integers in memory
; locations 38 and 3A (hex) and
; store the sum in address 3D

LDD R0, 38      ;R0 = mem[38]
LDD R1, 3A      ;R1 = mem[3A]
ADI R2, R1, R0  ;R2 = R1 + R0
STO R2, 3D      ;mem[3D] = R2
HLT             ;Stop the program
