	BITS 16

	mov ax, 0x7c0
	mov ds, ax
	
	mov ax, 0xb800
	mov es, ax
	xor di, di
	
	mov ax, 3
	int 0x10
	
	mov ax, 0xf030
	stosw

	jmp $
	times 510 - ($ - $$) db 0
	db 0x55
	db 0xaa
	times (1024*1024) - ($ - $$) db 0xff

	
