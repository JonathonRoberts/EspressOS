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


//struct {
///* General Volume Boot Record */
//unsigned short bytes_per_sector;
//unsigned char sectors_per_cluster;
//unsigned short reserved_sector_count;
//unsigned char number_of_fats;
//unsigned short max_root_dir_entries;
//unsigned short sectors_per_fat;
//unsigned int root_dir_sector;
//unsigned char fat_type[8];
//unsigned short signature;
//unsigned int fat_base;
//// What sector does the FATs start at
//unsigned int data_start_addr;
//// What address does the data regions start at
//} fat12;
//
//char buffer[512];
//unsigned char partition1_type;
//unsigned int partition1_begin_sector;
//unsigned int global_offset;
//
///* read MBR */
//seek_from_start(0);
//read_from_io(buffer, 1, 512);
//partition1_begin_sector = load_int((buffer+446+8));
//global_offset = partition1_begin_sector*512;
//
///* read VBR into buffer */
//seek_from_start(global_offset);
//read_from_io(buffer, 1, 512);
//
///* VBR: volume boot record */
//fat12.bytes_per_sector = load_short(buffer+0x0b);
//fat12.sectors_per_cluster = buffer[0x0d];
//fat12.reserved_sector_count = load_short(buffer+0x0e);
//fat12.number_of_fats = buffer[0x10];
//fat12.max_root_dir_entries = load_short(buffer+0x11);
//fat12.sectors_per_fat = load_short(buffer+0x16);
//fat12.signature = load_short(buffer+0x1fe);
///* At what sector does the fat table begin? */
//fat12.fat_base = partition1_begin_sector + fat12.reserved_sector_count;
///* At what sector does the root directory start at? */
//fat12.root_dir_sector = fat12.fat_base + fat12.sectors_per_fat*fat12.number_of_fats;
///* At what address does the data region start at? */
//fat12.data_start_addr = fat12.root_dir_sector*fat12.bytes_per_sector +
//fat12.max_root_dir_entries*32;

typedef struct fat_BS
{
	uint8_t 	bootjmp[3];
	uint8_t 	oem_name[8];
	uint16_t        bytes_per_sector;
	uint8_t		sectors_per_cluster;
	uint16_t	reserved_sector_count;
	uint8_t		table_count;
	uint16_t	root_entry_count;
	uint16_t	total_sectors_16;
	uint8_t		media_type;
	uint16_t	table_size_16;
	uint16_t	sectors_per_track;
	uint16_t	head_side_count;
	uint32_t	hidden_sector_count;
	uint32_t	total_sectors_32;
	//extended fat12 and fat16 stuff
	uint8_t		bios_drive_num;
	uint8_t		flag;
	uint8_t		boot_signature;
	uint32_t	volume_id;
	uint8_t		fat_type_label[8];

}__attribute__((packed)) fat_BS_t;

struct fat_BS bootpartition;

void init_FAT()
{
volatile uint8_t *fspointer8 = (volatile uint8_t*) 0x7c00;
volatile uint16_t *fspointer16;
volatile uint32_t *fspointer32;
	bootpartition.bootjmp[0]=*fspointer8++;
	bootpartition.bootjmp[1]=*fspointer8++;
	bootpartition.bootjmp[2]=*fspointer8++;
	bootpartition.oem_name[0]=*fspointer8++;
	bootpartition.oem_name[1]=*fspointer8++;
	bootpartition.oem_name[2]=*fspointer8++;
	bootpartition.oem_name[3]=*fspointer8++;
	bootpartition.oem_name[4]=*fspointer8++;
	bootpartition.oem_name[5]=*fspointer8++;
	bootpartition.oem_name[6]=*fspointer8++;
	bootpartition.oem_name[7]=*fspointer8++;
	fspointer16 = (volatile uint16_t*) fspointer8;
	fspointer8+=2;
	bootpartition.bytes_per_sector=*fspointer16;
	bootpartition.sectors_per_cluster=*fspointer8++;
	fspointer16 = (volatile uint16_t*) fspointer8;
	fspointer8+=2;
	bootpartition.reserved_sector_count=*fspointer16++;
	bootpartition.table_count=*fspointer8++;
	fspointer16 = (volatile uint16_t*) fspointer8;
	fspointer8+=4;
	bootpartition.root_entry_count=*fspointer16++;
	bootpartition.total_sectors_16=*fspointer16;
	bootpartition.media_type=*fspointer8++;
	fspointer16 = (volatile uint16_t*) fspointer8;
	fspointer8+=6;
	bootpartition.table_size_16=*fspointer16++;
	bootpartition.sectors_per_track=*fspointer16++;
	bootpartition.head_side_count=*fspointer16++;
	fspointer32 = (volatile uint32_t*) fspointer8;
	fspointer8+=8;
	bootpartition.hidden_sector_count=*fspointer32++;
	bootpartition.total_sectors_32=*fspointer32;
	bootpartition.bios_drive_num=*fspointer8++;
	bootpartition.flag=*fspointer8++;
	bootpartition.boot_signature=*fspointer8++;
	fspointer32 = (volatile uint32_t*) fspointer8;
	fspointer8+=4;
	bootpartition.volume_id=*fspointer32;
	bootpartition.fat_type_label[0]=*fspointer8++;
	bootpartition.fat_type_label[1]=*fspointer8++;
	bootpartition.fat_type_label[2]=*fspointer8++;
	bootpartition.fat_type_label[3]=*fspointer8++;
	bootpartition.fat_type_label[4]=*fspointer8++;
	bootpartition.fat_type_label[5]=*fspointer8++;
	bootpartition.fat_type_label[6]=*fspointer8++;
	bootpartition.fat_type_label[7]=*fspointer8++;

	return;
}
#endif

