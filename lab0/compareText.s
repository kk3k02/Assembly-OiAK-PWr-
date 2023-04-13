SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
STDOUT = 1
SYSREAD = 3
STDIN = 0

.global _start


.text

msg: .ascii "Write text(5): \n"
msg_len = . - msg

msg2: .ascii "Text is the same \n"
msg2_len = .- msg2

msg3: .ascii "Different text \n"
msg3_len = .- msg3


.data

txt: .ascii "abcde"
txt_len = . - txt

buf: .ascii "     "
buf_len = . - buf

_start:

#Wyswietlanie msg
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg2_len, %edx
int $0x80

#Wczytywanie tekstu do buf
mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

#Ustawienie licznika petli (dlugosc rowna txt_len)
mov $buf_len, %esi

#Ustawienie wskaznikow na 1 element txt i buf
mov $buf, %ebx
mov $txt, %ecx

#Petla sprawdzajaca znak po znaku
loop:
mov (%ebx), %al #Kopiowanie bitu do rejestru al
mov (%ecx), %dl #Kopiowanie bitu do rejestru dl
cmp %dl, %al #Porownywanie bitow

jne different #Jesli bity sa rozne skacze do different

#Przesuwanie wskaznikow na nastepne
inc %ebx 
inc %ecx

#Zmniejszanie licznika petli o 1
dec %esi

jnz loop #Powrot na poczatek petli

#Wyswietlanie msg2
equals:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg2, %ecx
mov $msg2_len, %edx
int $0x80
jmp exit

#Wyswietlanie msg3
different:
mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg3, %ecx
mov $msg3_len, %edx
int $0x80

#Wyjscie 
exit:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80