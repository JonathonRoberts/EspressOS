uint16_t pciConfigReadWord (uint8_t bus, uint8_t dev,
                            uint8_t func, uint8_t offset)
{
   uint32_t address;
   uint32_t lbus  = (uint32_t)bus;
   uint32_t ldev = (uint32_t)dev;
   uint32_t lfunc = (uint32_t)func;
   uint16_t tmp = 0;

   /* create configuration address as per Figure 1 */
   address = (uint32_t)((lbus << 16) | (ldev << 11) |
             (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

   /* write out the address */
   outl (0xCF8, address);
   /* read in the data */
   /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
   tmp = (uint16_t)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
   return (tmp);
}
uint32_t pciConfigReadDWord (uint8_t bus, uint8_t dev,
                            uint8_t func, uint8_t offset)
{
   uint32_t address;
   uint32_t lbus  = (uint32_t)bus;
   uint32_t ldev = (uint32_t)dev;
   uint32_t lfunc = (uint32_t)func;
   uint32_t tmp = 0;

   /* create configuration address as per Figure 1 */
   address = (uint32_t)((lbus << 16) | (ldev << 11) |
             (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

   /* write out the address */
   outl (0xCF8, address);
   /* read in the data */
   /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
   tmp = (uint32_t)((inl (0xCFC) >> ((offset & 2) * 8)) & 0xffff);
   return (tmp);
}

struct pcidevice
{
	uint8_t bus;
	uint8_t device;
	uint16_t deviceid;
	uint16_t vendorid;
	uint8_t baseclass;
	uint8_t subclass;
	uint32_t abar;
};

struct pcidevice alldevices[10];
uint16_t enumeratepci()
{
	uint16_t count = 0;
	uint16_t vendor,tmp;
	int i, j;
	for(i=0;i<=255;i++)
	{
		for(j=0;j<=32;j++)
		{
			vendor = pciConfigReadWord(i,j,0,0);
			if(vendor!=0xFFFF)
			{
				alldevices[count].bus = i;
				alldevices[count].device = j;
				alldevices[count].vendorid = vendor;
				alldevices[count].deviceid = pciConfigReadWord(i,j,0,2);
				alldevices[count].abar = pciConfigReadWord(i,j,0,0x24);
				tmp = pciConfigReadWord(i,j,0,10);
				alldevices[count].baseclass = (tmp&0xFF00)>8;
				alldevices[count++].subclass = tmp&0x00FF;
			}
		}
	}
	return count;
}
