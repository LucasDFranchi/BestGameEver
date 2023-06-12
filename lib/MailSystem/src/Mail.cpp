#include "Mail.h"

#include "memory"

/**
 * @brief Construct a new Mail:: Mail object
 *
 * @param input
 */
Mail::Mail() {
    std::cout << "Object Mail was created" << std::endl;
}

/**
 * @brief Destroy the Mail:: Mail object
 *
 */
Mail::~Mail() { std::cout << "Object Mail was deleted" << std::endl; }

/**
 * @brief Copies the bytes received from Serial buffer to the body of Mail.
 *
 * @param[in] body Array of bytes received via Serial.
 */
void Mail::UpdateMailHeader(Header *header) {
    this->header_.reset(header);
}

/**
 * @brief Copies the bytes received from Serial buffer to the body of Mail.
 *
 * @param[in] body Body object with all characters stored in it
 */
void Mail::UpdateMailBody(Body *body) {
    this->body_.reset(body);
}

/**
 * @brief Gets the CRC of the Mail message.
 *
 * @return Returns a uint32_t with the crc of the mail.
 */
uint32_t Mail::GetCRC(void) const & {
    uint32_t ret = 0x00;

    if (this->header_ != nullptr) {
        ret = this->header_.get()->GetCRC();
    }
    return ret;
}

/**
 * @brief Get the Command object
 *
 * @return Returns a uint8_t with the command of the mail.
 */
uint8_t Mail::GetCommand(void) const & {
    uint8_t ret = 0xFF;

    if (this->header_ != nullptr) {
        ret = this->header_.get()->GetCommand();
    }

    return ret;
}

/**
 * @brief Get the Data Length object
 *
 * @return Returns a uint32_t with the data length of the mail.
 */
uint8_t Mail::GetDataLength(void) const & {
    uint8_t ret = 0x00;

    if (this->header_ != nullptr) {
        ret = this->header_.get()->GetDataLength();
    }

    return ret;
}

/**
 * @brief Get the characters contained on the mail
 *
 * @param[out] pOut
 * @return bool
 * @retval True case the mail is not empty otherwise false
 */
bool Mail::GetMailBody(uint8_t *pOut) {
    bool ret = false;

    do {
        if (this->header_ == nullptr) {
            break;
        }
        if (this->body_ == nullptr) {
            break;
        }

        for (uint8_t i = 0; i < this->header_.get()->GetDataLength(); i++) {
            pOut[i] = this->body_.get()->GetMailDataByIndex(i);
        }

        ret = true;

    } while (0);

    return ret;
}