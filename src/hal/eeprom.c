#include "eeprom.h"


/**
 * @brief Function to read EEPROM data from a specific address.
 *
 * @param[in] start_address Address to read from.
 * @param[in] num_elements Number of bytes to be read.
 * @param[out] output_data Pointer to a buffer to save the read data.
 */
void eeprom_read_data(uint32_t start_address, uint16_t num_bytes,
		      uint8_t *output_data)
{
  // FIXME: mock
}


/**
 * @brief Function to save data on a page of EEPROM.
 *
 * - Unlock flash.
 * - Erase page.
 * - Program flash memory word by word (32-bits) and verify that it is
 * written.
 *
 * @param[in] page_address Address of a EEPROM page to flash on.
 * @param[in] input_data Pointer to the data to be flashed.
 * @param[in] num_bytes Number of bytes to be flashed.
 * @return Flash state.
 */
uint32_t eeprom_flash_page(uint32_t page_address, uint8_t *input_data,
			   uint16_t num_bytes)
{

  // FIXME: mock
  return 0;
}


/**
 * @brief Function to erase a page of EEPROM.
 *
 * @param[in] page_address Address of the EEPROM page to erase.
 * @return Erase state.
 */
uint32_t eeprom_erase_page(uint32_t page_address)
{
  //FIXME: mock
  return 0;

}
