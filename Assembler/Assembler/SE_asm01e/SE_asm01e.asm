.586P                             
.MODEL FLAT, STDCALL            
includelib kernel32.lib
includelib libucrt.lib
includelib ..\Debug\SE_asm01d.lib
ExitProcess PROTO : DWORD       
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD
EXTRN getmin : proc
EXTRN getmax : proc
EXTRN Print : proc
EXTRN PrintResult : proc
EXTRN Console1251 : proc

.STACK 4096                      

.CONST                            

.DATA                            
MB_OK EQU 0                       
HW DD ?                             
result DWORD ?
array DWORD  12, 2, 3, 4, 5, 6, 7,8,9,10
min DWORD ?
max DWORD ?
.CODE                             
 
main PROC                        
START:                         
    push LENGTHOF array											
	push OFFSET array
	call getmin
    mov min,eax
    push min
    call Print
    push LENGTHOF array											
	push OFFSET array
	call getmax
    mov max,eax
    push max
    call Print
    call Console1251
    push min
    push max
    call PrintResult
    PUSH -1                       
    call ExitProcess           
main ENDP                     
end main                        
