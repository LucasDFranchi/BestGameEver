#include <array>
#include <cstdint>
#include <iostream>

#ifndef HEADER_GUARD
#define HEADER_GUARD
/**
 * @brief Header of a Mail message, holds some key information related to the
 * communication.
 *
 *        | CRC 4 bytes | Command 1 byte | Data Length 1 byte|
 *        CRC         -> Checksum of the body of a message.
 *        Command     -> Command associated with the message.
 *        Data Length -> Amount of bytes received on body message.
 */
class Header {
   private:
    uint32_t crc_;
    uint8_t command_;
    uint8_t data_length_;

   public:
    constexpr uint8_t static HEADER_SIZE = 7;
    Header(uint8_t *pointer_data);
    ~Header();
    uint32_t GetCRC(void) const &;
    uint8_t GetCommand(void) const &;
    uint8_t GetDataLength(void) const &;
};

#endif /* HEADER_GUARD */