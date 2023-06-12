#include "MailSystem.h"
#include "Utils.h"

#include <stdlib.h>

/**
 * @brief Construct a new Mail System:: Mail System object
 *
 */
MailSystem::MailSystem() {
  this->pending_mail_ = false;
  this->mail_ = nullptr;
}

/**
 * @brief Stores one byte each time that this function is called. This byte
 *        is stored on a FIFO.
 *
 * @param[in] byte Byte stored on FIFO.
 *
 * @retval True in case that the byte was stored False in case the FIFO is full.
 * @return bool
 */
bool MailSystem::AppendMessageByte(uint8_t byte) {
  return this->buffer_->Push(byte);
}

/**
 * @brief This function transform the FIFO buffer in Mail object.
 *
 * @retval True in case the Mail object was created correctly.
 * @return bool
 */
bool MailSystem::UpdateMail(void) {
  Header *unchecked_header = this->CreateUncheckedHeader_();

  Body *unchecked_body = nullptr;
  uint8_t *pointer_data = nullptr;

  do {
    if (this->pending_mail_) {
      break;
    }

    if (unchecked_header == nullptr) {
      break;
    }

    size_t size = (size_t)unchecked_header->GetDataLength();

    if (size > Body::MAXIMUM_BODY_SIZE) {
      break;
    }

    if (!this->ReadMessageData_(&pointer_data, size)) {
      break;
    }

    uint32_t calculated_crc =
        Utils::Checksum::Calculate((char *)pointer_data, size);

    if (calculated_crc != unchecked_header->GetCRC()) {
      break;
    }

    unchecked_body = this->CreateBody_(pointer_data, size);

    this->mail_.reset(new Mail);
    this->mail_.get()->UpdateMailHeader(unchecked_header);
    this->mail_.get()->UpdateMailBody(unchecked_body);
    this->pending_mail_ = true;
    free(pointer_data);

  } while (0);

  return true;
}

/**
 * @brief Create a header object, this object is used to validation
 *        and could be invalid.
 *
 * @retval Header Object.
 * @return Header pointer
 */
Header *MailSystem::CreateUncheckedHeader_(void) {
  uint8_t temp_array[Header::HEADER_SIZE] = {0};
  bool is_corrupted = false;

  for (uint8_t i = 0; i < Header::HEADER_SIZE; i++) {
    temp_array[i] = this->buffer_->Pop();
  }

  do {
    if (temp_array[0] != 0x01) {
      is_corrupted = true;
      break;
    }
    if (this->buffer_->empty()) {
      is_corrupted = true;
      break;
    }
  } while (0);
  std::cout << is_corrupted + 0x00 << std::endl;

  return is_corrupted ? nullptr : new Header(temp_array);
}

/**
 * @brief Stores the bytes received from the Serial into a heap buffer
 *
 * @param[out] pointer_data Output buffer that received the read bytes
 * @param[in] size Amount of bytes that should be written on the buffer in case
 * of success
 * @return bool
 * @retval True case the amount of bytes written is equal to size.
 */
bool MailSystem::ReadMessageData_(uint8_t **pointer_data, size_t size) {
  uint8_t data = 0x00;
  size_t written_bytes = 0;

  *pointer_data = (uint8_t *)calloc(size, sizeof(uint8_t));

  do {
    if (*pointer_data == nullptr) {
      break;
    }

    for (uint8_t i = 0; i < size; i++) {
      if (this->buffer_->empty()) {
        break;
      }
      data = this->buffer_->Pop();

      if (data == 0x03) {
        break;
      }

      (*pointer_data)[i] = data;
      written_bytes++;
    }

  } while (0);

  return written_bytes == size;
}

/**
 * @brief
 *
 */
void MailSystem::ConsumeMailData(void) { this->pending_mail_ = false; }

/**
 * @brief Create a Body object
 *
 * @return Body pointer
 * @retval Returns the body pointer if the body is valid otherwise nullptr
 */
Body *MailSystem::CreateBody_(uint8_t *pointer_data, size_t size) {
  return new Body(pointer_data, size);
}

/**
 * @brief
 *
 * @return uint32_t const&
 */
uint32_t MailSystem::GetCRC(void) const & {
  uint32_t ret = 0x00;

  if (this->mail_ != nullptr)
    ret = this->mail_->GetCRC();

  return ret;
}

/**
 * @brief Get the Command object
 *
 * @return uint8_t const&
 */
uint8_t MailSystem::GetCommand(void) const & {
  uint8_t ret = 0x00;

  if (this->mail_ != nullptr)
    ret = this->mail_->GetCommand();

  return ret;
}

/**
 * @brief Get the Data Length object
 *
 * @return uint8_t const&
 */
uint8_t MailSystem::GetDataLength(void) const & {
  uint8_t ret = 0x00;

  if (this->mail_ != nullptr)
    ret = this->mail_->GetDataLength();

  return ret;
}

/**
 * @brief Returns if there is any pending Mail
 *
 * @return bool
 * @retval True case there is a pending mail, otherwise false
 */
bool MailSystem::GetPendingMail(void) const & { return this->pending_mail_; }
