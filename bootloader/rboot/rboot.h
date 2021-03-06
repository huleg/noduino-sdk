#ifndef __RBOOT_H__
#define __RBOOT_H__

//////////////////////////////////////////////////
// rBoot open source boot loader for ESP8266.
// Copyright 2015 Richard A Burton
// richardaburton@gmail.com
// See license.txt for license terms.
//////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

// uncomment to use only c code
// if you aren't using gcc you may need to do this
//#define BOOT_NO_ASM

// uncomment to have a checksum on the boot config
//#define BOOT_CONFIG_CHKSUM

// uncomment to enable big flash support (>1MB)
//#define BOOT_BIG_FLASH

// uncomment to include .irom0.text section in the checksum
// roms must be built with esptool2 using -iromchksum option
//#define BOOT_IROM_CHKSUM

// increase if required
#define MAX_ROMS 4

#define CHKSUM_INIT 0xef

#define SECTOR_SIZE 0x1000
#define BOOT_CONFIG_SECTOR 1

#define BOOT_CONFIG_MAGIC 0xe1
#define BOOT_CONFIG_VERSION 0x01

#define MODE_STANDARD 0x00
#define MODE_GPIO_ROM 0x01

// boot config structure
// rom addresses must be multiples of 0x1000 (flash sector aligned)
// without BOOT_BIG_FLASH only the first 8Mbit of the chip will be memory mapped
// so rom slots containing .irom0.text sections must remain below 0x100000
// slots beyond this will only be accessible via spi read calls, so
// use these for stored resources, not code
// with BOOT_BIG_FLASH the flash will be mapped in chunks of 8MBit, so roms can
// be anywhere, but must not straddle two 8MBit blocks
typedef struct {
	uint8 magic;		   // our magic
	uint8 version;		   // config struct version
	uint8 mode;			   // boot loader mode
	uint8 current_rom;	   // currently selected rom
	uint8 gpio_rom;		   // rom to use for gpio boot
	uint8 count;		   // number of roms in use
	uint8 unused[2];	   // padding
	uint32 roms[MAX_ROMS]; // flash addresses of the roms
#ifdef BOOT_CONFIG_CHKSUM
	uint8 chksum;		   // config chksum
#endif
} rboot_config;

#ifdef __cplusplus
}
#endif

#endif
