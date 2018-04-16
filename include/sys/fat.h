/*
 * The FUGPL License
 * ===================
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software with only one restriction. No part of
 * it may be included in software projects that are solely distributed under
 * strong copyleft restricted licenses.  This license is *NOT* GPL compatible,
 * and that is it's only restriction.
 *
 * There otherwise exists no restrictions in using this software, including
 * without other limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _FAT_H_
#define _FAT_H_

#ifndef _FAT_H_
#include "fat.h"
#endif

void init_FAT();

/*
unsigned int fatnextcluster()
{
unsigned char FAT_table[cluster_size];
unsigned int fat_offset = active_cluster + (active_cluster / 2);// multiply by 1.5
unsigned int fat_sector = first_fat_sector + (fat_offset / cluster_size);
unsigned int ent_offset = fat_offset % cluster_size;

//at this point you need to read from sector "fat_sector" on the disk into "FAT_table".

unsigned short table_value = *(unsigned short*)&FAT_table[ent_offset];

if(current_cluster & 0x0001)
	table_value = table_value >> 4;
else
	table_value = table_value & 0x0FFF;

//the variable "table_value" now has the information you need about the next cluster in the chain.
}
*/

typedef struct fat_extBS_16
{
	//extended fat12 and fat16 stuff
	unsigned char		bios_drive_num;
	unsigned char		reserved1;
	unsigned char		boot_signature;
	unsigned int		volume_id;
	unsigned char		volume_label[11];
	unsigned char		fat_type_label[8];

}__attribute__((packed)) fat_extBS_16_t;

typedef struct fat_BS
{
	unsigned char 		bootjmp[3];
	unsigned char 		oem_name[8];
	unsigned short 	        bytes_per_sector;
	unsigned char		sectors_per_cluster;
	unsigned short		reserved_sector_count;
	unsigned char		table_count;
	unsigned short		root_entry_count;
	unsigned short		total_sectors_16;
	unsigned char		media_type;
	unsigned short		table_size_16;
	unsigned short		sectors_per_track;
	unsigned short		head_side_count;
	unsigned int 		hidden_sector_count;
	unsigned int 		total_sectors_32;

	//this will be cast to it's specific type once the driver actually knows what type of FAT this is.
	unsigned char		extended_section[54];

}__attribute__((packed)) fat_BS_t;

struct fat_BS bootpartition;
void init_FAT()
{
volatile char *fspointer = (volatile char*) 0x7c00;
	bootpartition.bootjmp[0]=*fspointer++;
	bootpartition.bootjmp[1]=*fspointer++;
	bootpartition.bootjmp[2]=*fspointer++;
	bootpartition.oem_name[0]=*fspointer++;
	bootpartition.oem_name[1]=*fspointer++;
	bootpartition.oem_name[2]=*fspointer++;
	bootpartition.oem_name[3]=*fspointer++;
	bootpartition.oem_name[4]=*fspointer++;
	bootpartition.oem_name[5]=*fspointer++;
	bootpartition.oem_name[6]=*fspointer++;
	bootpartition.oem_name[7]=*fspointer++;
	bootpartition.bytes_per_sector=*fspointer++;
	bootpartition.sectors_per_cluster=*fspointer++;
	bootpartition.reserved_sector_count=*fspointer++;
	bootpartition.table_count=*fspointer++;
	bootpartition.root_entry_count=*fspointer++;
	bootpartition.total_sectors_16=*fspointer++;
	bootpartition.media_type=*fspointer++;
	bootpartition.table_size_16=*fspointer++;
	bootpartition.sectors_per_track=*fspointer++;
	bootpartition.head_side_count=*fspointer++;
	bootpartition.hidden_sector_count=*fspointer++;
	bootpartition.total_sectors_32=*fspointer++;
return;
}
#endif

