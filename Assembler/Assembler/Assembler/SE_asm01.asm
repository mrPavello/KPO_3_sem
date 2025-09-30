.586P                              
.MODEL FLAT, STDCALL           
includelib kernel32.lib
includelib libucrt.lib
ExitProcess PROTO : DWORD   

.STACK 4096                      

.DATA                              
array DWORD 112, 23, 31, 4421, 52, 61, 7, 8, 9, 3
min DWORD ? 

.CODE                             

getmin PROC parm1 : DWORD, parm2 : DWORD 
	START:
		mov ecx, parm2
		mov esi, parm1
		mov eax, [esi]
		dec ecx
		add esi, 4
	CYCLE:
		mov edx, [esi]
		cmp eax, edx
		jl minimum
		mov eax, edx

	minimum:	
		add esi, 4
	loop CYCLE
	mov min, eax
	ret


	getmin ENDP

main PROC                           
	INVOKE getmin, OFFSET array, LENGTHOF array      
    PUSH 0            
    call ExitProcess    
main ENDP                        

END main                           
