;--------------------------------------------------------------------------
; Array converter. NASM x64 (c) 2021 - by Mark Gordienko
;--------------------------------------------------------------------------
; To run:
; nasm -f elf64 <filename.s>
; ld <filename.o>
; ./a.out
;--------------------------------------------------------------------------
section .text
   global _start        ;must be declared for using gcc
        
_start:                 ;tell linker entry point
   mov r8d, 10          ;R8D is a loop counter
   mov esi, x           ;ESI will point to the current element of an array

   l1:                  ;loop entry
   mov ax, word [esi]   ;write current ESI value to AX and force it to be size of word 
   test r8d, 1          ;checking if current R8D value is odd
   jnz even             ;if R8D is even jump to "even" point
   jz odd               ;if R8D is odd jump to "odd" point

   even:                ;"even" point
   xor eax, 255         ;apply xor to EAX with 255 mask

   odd:                 ;"odd" point
   mov ebx, .buf+9      ;write buf address to EBX
   mov ecx, 10          ;ECX is a loop counter
   mov edi, 10          ;EDI is a divider
        .a:             ;number to ASCII string loop
        mov edx, 0      ;write 0 to EDX
        div edi         ;apply div to EAX/EDI. result will be stored in dl and EBX
        add edx, 48     ;add 48 to EDX to convert to ASCII
        mov [ebx], dl   ;write dl to EBX
        dec ebx         ;decrease EBX by 1
        loop .a         ;"a" loop end

   mov eax, 4           ;system call number (sys_print)
   mov ebx,1            ;set EBX 'stdout' arg
   mov ecx, .buf        ;set 'what to print' arg
   mov edx, 11          ;set the lenght of string to print
   int 0x80             ;call kernel
   
   add esi, 2           ;increase ESI by 2 (word is 2 bytes)

   dec r8d              ;decrese R8D by 1 to continue loop
   jnz l1               ;jmp to loop start if != 0
        
   mov eax,1            ;system call number (sys_exit)
   int 0x80             ;call kernel

section .data           
.buf            db      '0000000000',10,0
global x
x:    
   dw 1
   dw 2
   dw 3
   dw 4
   dw 5
   dw 6
   dw 7
   dw 8
   dw 9
   dw 10