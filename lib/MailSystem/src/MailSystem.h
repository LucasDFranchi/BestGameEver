#include "FIFO.hpp"
#include "Mail.h"
// #include "Utils.h"

#ifndef MAIL_SYSTEM_GUARD
#define MAIL_SYSTEM_GUARD

class MailSystem {
public:
  MailSystem();
  ~MailSystem(){};
  bool AppendMessageByte(uint8_t byte);
  bool UpdateMail(void);
  uint32_t GetCRC(void) const &;
  uint8_t GetCommand(void) const &;
  uint8_t GetDataLength(void) const &;
  bool GetPendingMail(void) const &;
  void ConsumeMailData(void);

private:
  constexpr uint16_t static MAXIMUM_FIFO_SIZE = 1024;
  FIFO<uint8_t> *buffer_ = new FIFO<uint8_t>(MAXIMUM_FIFO_SIZE);
  std::unique_ptr<Mail> mail_;
  Header *CreateUncheckedHeader_(void);
  Body *CreateBody_(uint8_t *pointer_data, size_t size);
  bool ReadMessageData_(uint8_t **pointer_data, size_t size);
  bool pending_mail_;
};

#endif /* MAIL_SYSTEM_GUARD */