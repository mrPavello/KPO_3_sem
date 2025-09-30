.586P                               ; система команд (процессор Pentium)
.MODEL FLAT, STDCALL               ; модель памяти, соглашение о вызовах
includelib kernel32.lib            ; компоновщик: компановать с kernel32.lib

ExitProcess PROTO : DWORD          ; прототип функции ExitProcess
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD ; прототип API-функции MessageBoxA

.STACK 4096                         ; сегмент стека объемом 4096

.CONST                              ; сегмент констант

.DATA                               ; сегмент данных
MB_OK EQU 0                         ; EQU определяет константу
STR1 DB "Моя первая программа", 0   ; строка + нулевой байт
STR2 DB "Привет всем!", 0           ; строка + нулевой байт
HW DD ?                             ; двойное слово длиной 4 байта, неинициализировано

.CODE                               ; сегмент кода

main PROC                           ; точка входа, начало процедуры main
START:                              ; метка
    INVOKE MessageBoxA, HW, OFFSET STR2, OFFSET STR1, MB_OK

    PUSH -1                         ; код возврата процесса Windows (параметр ExitProcess)
    call ExitProcess                ; завершение процесса Windows
main ENDP                           ; конец процедуры

end main                            ; конец модуля, точка входа main