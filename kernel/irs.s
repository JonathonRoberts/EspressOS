global isr0
extern sponge

isr0:
	cli
	;call sponge
	hlt
	iretq
