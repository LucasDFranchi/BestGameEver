#include <memory>

#include "Body.h"
#include "Header.h"

#ifndef MAIL_GUARD
#define MAIL_GUARD
/**
 * @brief Mail object holds the header and the body of a received message.
 */
class Mail {
   public:
    Mail();
    ~Mail();
    void UpdateMailHeader(Header *header);
    void UpdateMailBody(Body *body);
    bool GetMailBody(uint8_t *pOut);
    uint32_t GetCRC(void) const &;
    uint8_t GetCommand(void) const &;
    uint8_t GetDataLength(void) const &;

   private:
    std::unique_ptr<Header> header_;
    std::unique_ptr<Body> body_;
};

#endif /* MAIL_GUARD */