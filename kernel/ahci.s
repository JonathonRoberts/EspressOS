global getabar
extern abar

getabar:
mov eax, 80030024h  ; PCI function address
mov dx, 0cf8h       ; config address io port
out dx, eax
mov dx, 0cfch       ; get data from config data port
in eax, dx          ; read DWORD into register eax
cli
hlt
ret
