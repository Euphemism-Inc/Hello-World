TITLE   MASM Tutorial (x64 version)

INCLUDE _header.inc


.DATA


.CODE

ULongToString PROC
	number EQU <rcx>
	stringPtr EQU <rdx>
	ENTER 0, 0


	LEAVE
	RET
ULongToString ENDP


END
