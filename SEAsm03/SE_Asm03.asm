.586P                               ; система команд (процессор Pentium)
.MODEL FLAT, STDCALL               ; модель памяти, соглашение о вызовах
includelib kernel32.lib            ; компоновщик: компановать с kernel32.lib

ExitProcess PROTO : DWORD          ; прототип функции ExitProcess
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD ; прототип API-функции MessageBoxA

.STACK 4096                         ; сегмент стека объемом 4096

.CONST                              ; сегмент констант

.DATA                               ; сегмент данных
MB_OK EQU 0                         ; EQU определяет константу
STR1 DB "Шевчик Антон Владимирович 2 10", 0   ; строка + нулевой байт
STR2 DB "Результат проверки = ", 0           ; строка + нулевой байт
HW DD ?                             ; двойное слово длиной 4 байта, неинициализировано
myBytes BYTE 10h, 20h, 30h, 40h
myWords WORD 8Ah, 3Bh, 44h, 5Fh, 99h
myDoubles DWORD 1, 2, 3, 4, 5, 6
myPointer DWORD myDoubles
array DWORD  0, 1, 2, 3, 4, 5, 6, 7
sum DWORD ?
.CODE                               ; сегмент кода

main PROC                           ; точка входа, начало процедуры main
START:                              ; метка
    mov EBX, myPointer
    mov EAX, [EBX + 4]
    mov EDX, [EBX + 8]
    xor EAX, EAX                  ; Обнуляем EAX для суммы
    xor EBX, EBX                  ; Обнуляем EBX для проверки 0
    lea ESI, array                ; Загружаем адрес массива в ESI
    mov ECX, 8                    ; Устанавливаем счетчик для массива

CYCLE1:
    mov eax, [esi]
    add sum, eax
    add esi, 4
    loop CYCLE1
    mov ECX, 8                    ; Устанавливаем счетчик для массива
    lea ESI, array                ; Загружаем адрес массива в ESI

CYCLE2:
     mov eax, [esi]
     cmp eax, 0
     je IF_ZERO
     mov EBX,1
     loop CYCLE2
IF_ZERO:
    mov EBX,0

    add eax,30h 								 
	mov STR2+21, al	
    INVOKE MessageBoxA, HW, OFFSET STR2, OFFSET STR1, MB_OK

    PUSH -1                         ; код возврата процесса Windows (параметр ExitProcess)
    call ExitProcess                ; завершение процесса Windows
main ENDP                           ; конец процедуры

end main                            ; конец модуля, точка входа main