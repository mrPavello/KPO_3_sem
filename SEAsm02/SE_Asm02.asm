.586P                               ; система команд (процессор Pentium)
.MODEL FLAT, STDCALL               ; модель памяти, соглашение о вызовах
includelib kernel32.lib            ; компоновщик: компановать с kernel32.lib

ExitProcess PROTO : DWORD          ; прототип функции ExitProcess
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD ; прототип API-функции MessageBoxA

.STACK 4096                         ; сегмент стека объемом 4096

.CONST                              ; сегмент констант

.DATA                               ; сегмент данных
MB_OK EQU 0                         ; EQU определяет константу
STR1 DB "Сложение 2 чисел", 0       ; строка + нулевой байт
STR2 DB "Результат сложения =  ", 0  ; строка + нулевой байт 
NUM1 DD 1                           
NUM2 DD 4
HW DD ?

.CODE                               ; сегмент кода

main PROC                           ; точка входа, начало процедуры main
START:                              ; метка
    mov eax,NUM1
    add eax,NUM2
    add eax, 30h 								    ; сложение 30h с результатом сложения
	mov STR2+21, al	
    INVOKE MessageBoxA, HW, OFFSET STR2, OFFSET STR1, MB_OK

    PUSH -1                         ; код возврата процесса Windows (параметр ExitProcess)
    call ExitProcess                ; завершение процесса Windows
main ENDP                           ; конец процедуры

end main                            ; конец модуля, точка входа main