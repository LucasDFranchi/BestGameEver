#include <array>
#include <iostream>

#ifndef BODY_GUARD
#define BODY_GUARD
/**
 * @brief Body object holds the data bytes of the message
 */
class Body {
   public:
    constexpr uint8_t static MAXIMUM_BODY_SIZE = 247;
    Body(uint8_t *pointer_data, uint8_t size);
    ~Body();
    uint8_t GetMailDataByIndex(uint8_t index) const &;

   private:
    std::array<uint8_t, Body::MAXIMUM_BODY_SIZE> body_;
};

#endif /* BODY_GUARD */