/* EEPROM Interface.
 * As this board has not an EEPROM, we use the last FLASH sector of the MCU
 * To store the data.
 * This functionality is currently used by MMLIB to store the maze.  
 */
#ifndef __EEPROM_H
#define __EEPROM_H

/**
 * Flash module organization.
 *
 * The memory organization is:
 * 4 sectors of 16KB
 * 1 sector of 64KB
 * 7 sectors of 128 KB 
 *
 * The linker file was modified to reserve the first memory page for EEPROM.
 *
 * @see Programming manual (PM0081) "Flash module organization"
 */
// TODO: remove FLASH_EEPROM_ADDRESS_MAZE. We keep this here as is still used in mmlib
#define FLASH_EEPROM_ADDRESS_MAZE ((uint32_t)(0x08000000 + 0xE0000))
#define FLASH_EEPROM_START_ADDRESS ((uint32_t)(0x08000000 + 0xE0000))


/** Flash results */
#define RESULT_OK 0
#define FLASH_WRONG_DATA_WRITTEN 0x80

/** Flash sector used as eeprom **/
#define FLASH_SECTOR 11
#define FLASH_PROGRAM_SIZE 2  // 2 is 32 bit


/**
 * @brief Function to save data on a page of EEPROM (erases EEPROM first).
 *
 * Note that this function is deprecated, as this MCU does not write/read on
 * flash pages but on sectors. Anyway, it still works so the HAL can be compatible with
 * mmlib (used in solve) calling internally eeprom_write()
 *
 * @param[in] page_address EEPROM page address to flash on.
 * @param[in] input_data Pointer to the data to be flashed.
 * @param[in] num_bytes Number of bytes to be flashed.
 * @return Flash state.
 */
uint32_t eeprom_flash_page(uint32_t page_address, uint8_t *input_data, uint16_t num_bytes);

/**
 * @brief Function to save data on the EEPROM (erases EEPROM first).
 *
 * Data is stored in the EEPROM in order starting in the beginning of the EEPROM sector.
 *
 * @param[in] input_data Pointer to the data to be flashed.
 * @param[in] num_bytes Number of bytes to be flashed.
 * @return Flash state.
 */
uint32_t eeprom_write(uint8_t *input_data, uint16_t num_bytes);

/**
 * @brief Function to read EEPROM data from a specific address.
 * 
 * Note that this function uses the absolute memory address in start_address, not
 * a relative address starting at the begining of the reserved. This function will be
 * deprecated, use eeprom_read with relative addresses instead.
 *
 * @param[in] start_address (absolute) Address to read from.
 * @param[in] num_elements Number of bytes to be read.
 * @param[out] output_data Pointer to a buffer to save the read data.
 */
void eeprom_read_data(uint32_t start_address, uint16_t num_bytes, uint8_t *output_data);

/**
 * @brief Function to read EEPROM data from a specific address.
 *
 * @param[in] start_address Address to read from (relative to the start of EEPROM).
 * @param[in] num_elements Number of bytes to be read.
 * @param[out] output_data Pointer to a buffer to save the read data.
 */
void eeprom_read(uint32_t start_address, uint16_t num_bytes, uint8_t *output_data);

/**
 * @brief Function to erase a page of EEPROM.
 * 
 * Note that this function is deprecated, as this MCU does not write/read on
 * flash pages but on sectors. Anyway, it still works so the HAL can be compatible with
 * mmlib (used in solve), calling internally eeprom_erase()
 *
 * @param[in] page_address EEPROM start address to be erased (not used internally).
 * @return Erase state.
 */
uint32_t eeprom_erase_page(uint32_t page_address);


/**
 * @brief Function to fully erase the EEPROM.
 * 
 * @return Erase state.
 */
uint32_t eeprom_erase(void);

#endif /* __EEPROM_H */
