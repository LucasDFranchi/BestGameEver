#include "Body.h"

/**
 * @brief Construct a new Body:: Body object
 *
 * @param[in] body Body array
 * @param[in] size Num of bytes in body
 */
Body::Body(uint8_t *pointer_data, uint8_t size) {
  std::cout << "Object Body was created!" << std::endl;

  for (uint8_t i = 0; i < size; i++) {
    this->body_.at(i) = pointer_data[i];
  }
}

/**
 * @brief Destroy the Body:: Body object
 *
 */
Body::~Body() { std::cout << "Object Mail was deleted" << std::endl; }

/**
 * @brief Get the Mail Body object
 *
 * @retval Return the array with all characters stored on body
 * @return std::array<uint8_t, Body::MAXIMUM_BODY_SIZE>
 */
uint8_t Body::GetMailDataByIndex(uint8_t index) const & {
  return this->body_.at(index);
}