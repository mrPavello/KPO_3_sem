.586P                              
.MODEL FLAT, STDCALL           
includelib kernel32.lib  
includelib libucrt.lib
.STACK 4096                      

.CONST                           

.DATA                             
array DWORD  1, 2, 3, 4, 5, 6, 7,8,9,10
min DWORD ?
max DWORD ?
.CODE                            

getmin PROC parm:dword,parm2:dword
    mov EAX, [ESI]      
    mov min, EAX     
CYCLE:
    add ESI, 4          
    cmp ECX, 0           
    jz ENDD     
    mov EAX, [ESI]      
    cmp EAX, min         
    jge NEXT  
    mov min, EAX      
NEXT:
    loop CYCLE         
ENDD:
    ret                 
getmin ENDP

getmax PROC   parm:dword,parm2:dword
    mov EAX, [ESI]      
    mov min, EAX     

CYCLE:
    add ESI, 4          
    cmp ECX, 0           
    jz ENDD     
    mov EAX, [ESI]      
    cmp EAX, max         
    jle NEXT  
    mov max, EAX   
NEXT:
    loop CYCLE         
ENDD:
    ret                 
getmax ENDP
end
