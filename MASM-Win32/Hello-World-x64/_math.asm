TITLE   MASM Tutorial (x64 version)

INCLUDE _header.inc


.DATA

.CODE
Fibonacci PROC
    ENTER 0, 0

    MOV RDX, 0
    MOV RAX, 1
    MOV RCX, 0Fh
l1: XADD RAX, RDX
    LOOP l1

    LEAVE
    RET
Fibonacci ENDP



END
