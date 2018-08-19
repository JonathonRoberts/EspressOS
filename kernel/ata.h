#define ATA_DATA 0x1f0
#define ATA_ERROR 0x1f1
#define ATA_COUNT 0x1f2
#define ATA_SEC 0x1f3
#define ATA_CYLLOW 0x1f4
#define ATA_CYLHI 0x1f5
#define ATA_DRIVE 0x1f6
#define ATA_COMMAND 0x1f7

#define ATA_STATUS 0x1f7
#define ATA_CONTROL 0x3f6

#define ATA_STATUS_ERR 1
#define ATA_STATUS_DRQ 8
#define ATA_STATUS_SRV 0x10
#define ATA_STATUS_DF  0x20
#define ATA_STATUS_RDY 0x40
#define ATA_STATUS_BSY 0x80
int ata_identify()
{
	if(inb(ATA_STATUS)==0xFF){kprint(0x2,"FLOATING BUS 0x1f0\n");return 0;}
	outb(ATA_DRIVE,0xA0);
	outb(ATA_COUNT,0);
	outb(ATA_SEC,0);
	outb(ATA_CYLLOW,0);

	outb(ATA_DATA,0);
	outb(ATA_ERROR,0);

	outb(ATA_COMMAND,0xEC);
	if(inb(ATA_STATUS == 0)){
		kprint(0x2,"Drive does not exist");
	}
	io_wait();
	io_wait();
	io_wait();
	io_wait();
	io_wait();
	if(inb(ATA_STATUS & ATA_STATUS_ERR)) kprint (0x2, "ERR");
	if(inb(ATA_STATUS & ATA_STATUS_DRQ)) kprint (0x2, "DRQ");
	if(inb(ATA_STATUS & ATA_STATUS_SRV)) kprint (0x2, "SRV");
	if(inb(ATA_STATUS & ATA_STATUS_DF)) kprint (0x2, "DF");
	if(inb(ATA_STATUS & ATA_STATUS_RDY)) kprint (0x2, "RDY");
	if(inb(ATA_STATUS & ATA_STATUS_BSY)) kprint (0x2, "BSY");
	if(inb(ATA_CYLLOW)==0xC3){kprint(0x2,"SATA\n");}
	return 0;
}

int ata_reset()
{
	outb(ATA_CONTROL, 4);
	outb(ATA_CONTROL, 0);
	inb(ATA_COMMAND);
	inb(ATA_COMMAND);
	inb(ATA_COMMAND);
	inb(ATA_COMMAND);
}
int ata_lba_read48c(uint64_t lba, uint16_t count, uint64_t buffer)
{
	uint16_t *pointer = (uint16_t*) buffer;

	outb(ATA_DRIVE, 0x40);
	outb(ATA_COUNT, count >> 8);
	outb(ATA_SEC, lba >> 24);
	outb(ATA_CYLLOW, lba >> 32);
	outb(ATA_CYLHI, lba >> 40);
	outb(ATA_COUNT, count);
	outb(ATA_SEC, lba);
	outb(ATA_CYLLOW, lba >> 8);
	outb(ATA_CYLHI, lba >> 16);
	outb(ATA_COMMAND, 0x24);

	//while(inb(ATA_COMMAND)&0x80)
	//{
	//}
	inb(ATA_COMMAND);
	inb(ATA_COMMAND);
	inb(ATA_COMMAND);
	inb(ATA_COMMAND);
	while(inb(ATA_COMMAND&0x8))
	{
		sponge();
	}
	int i;
	for(i=0;i<256*count;i++)
	*pointer++ = inw(ATA_DATA);

	return 1;
}
