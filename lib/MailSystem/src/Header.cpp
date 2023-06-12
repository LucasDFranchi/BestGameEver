#include "Header.h"

/**
 * @brief Construct a new Header:: Header object
 *
 * @param input
 */
Header::Header(uint8_t *pointer_data) {
  std::cout << "Object Header was created!" << std::endl;
  this->crc_ = (pointer_data[4] | (pointer_data[3] << 8) |
                (pointer_data[2] << 16) | (pointer_data[1] << 24));
  this->command_ = pointer_data[5];
  this->data_length_ = pointer_data[6];
}

/**
 * @brief Destroy the Header:: Header object
 *
 */
Header::~Header() { std::cout << "Object Header was deleted" << std::endl; }

/**
 * @brief Return the CRC of this header.
 *
 * @return uint32_t const&
 */
uint32_t Header::GetCRC(void) const & { return this->crc_; }

/**
 * @brief Get the Command of this header.
 *
 * @return uint8_t const&
 */
uint8_t Header::GetCommand(void) const & { return this->command_; }

/**
 * @brief Get the Data Length of this header.
 *
 * @return uint8_t const&
 */
uint8_t Header::GetDataLength(void) const & { return this->data_length_; }
