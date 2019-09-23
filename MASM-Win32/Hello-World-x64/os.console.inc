; This file contains all windows procedures and constants
; Struct definition in assembly: http://www.asmcommunity.net/forums/topic/?id=4739
; Of course inside wrappers that handle errors.

INVALID_HANDLE_VALUE EQU -1

GetLastError PROTO
	; Nothing
; DWORD WINAPI GetLastError(void);

EXIT_SUCCESS EQU 0
EXIT_FAILURE EQU 1
ExitProcess PROTO
	; uExitCode:DWORD

STD_INPUT_HANDLE	EQU	-10
STD_OUTPUT_HANDLE	EQU	-11
STD_ERROR_HANDLE	EQU	-12
GetStdHandle PROTO
	; nStdHandle:DWORD
; HANDLE WINAPI GetStdHandle(
;    _In_  DWORD nStdHandle							; STD_OUTPUT_HANDLE, etc..
; );

WriteConsoleA PROTO
	; hConsoleOutput:DWORD
	; lpBuffer:DWORD
	; nNumberOfCharsToWrite:DWORD
	; lpNumberOfCharsWritten:DWORD
	; lpReserved:DWORD
; WriteConsole(
;    _In_        HANDLE hConsoleOutput,				; OUTPUT STREAM -> STD_OUTPUT_HANDLE's handle, received from GetStdHandle
;    _In_        const VOID *lpBuffer,				; PTR to the BYTE string, null terminated
;    _In_        DWORD nNumberOfCharsToWrite,		; Number of chars to write - thus the length of the string, minus the '0'
;    _Out_       LPDWORD lpNumberOfCharsWritten,	; PTR to a DWORD in memory that will contain the number of chars written after execution
;    _Reserved_  LPVOID lpReserved					; Reserved and must be null...


GetConsoleScreenBufferInfo PROTO
	; hConsoleOutput:DWORD
	; lpConsoleScreenBufferInfo:QWORD
; BOOL WINAPI GetConsoleScreenBufferInfo(
;   _In_  HANDLE                      hConsoleOutput,			; Handle from GetStdHandle(...)
;   _Out_ PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo ; Place to store output.
; );


SMALL_RECT struct
	Left   dw ?
	Top    dw ?
	Right  dw ?
	Bottom dw ?
SMALL_RECT ends
; typedef struct _SMALL_RECT {
;     SHORT Left;
;     SHORT Top;
;     SHORT Right;
;     SHORT Bottom;
; } SMALL_RECT;


COORD struct
	X dw ?
	Y dw ?
COORD ends
; typedef struct _COORD {
;     SHORT X;
;     SHORT Y;
; } COORD, *PCOORD;


CONSOLE_SCREEN_BUFFER_INFO struct
	dwSize              COORD <>
	dwCursorPosition    COORD <>
	wAttributes         dw ?
	srWindow            SMALL_RECT <>
	dwMaximumWindowSize COORD <>
CONSOLE_SCREEN_BUFFER_INFO ends 
; typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
;     COORD      dwSize;
;     COORD      dwCursorPosition;
;     WORD       wAttributes;
;     SMALL_RECT srWindow;
;     COORD      dwMaximumWindowSize;
; } CONSOLE_SCREEN_BUFFER_INFO;