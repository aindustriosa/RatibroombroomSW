/* Define memory regions. */
MEMORY
{
	eeprom (rx) : ORIGIN = 0x08000000, LENGTH = 16K
	rom (rx) : ORIGIN = 0x08000000 + 16K, LENGTH = 1008K
	ccm (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Include the common ld script. */
INCLUDE cortex-m-generic.ld
