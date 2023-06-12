#include <Arduino.h>
#include <unity.h>
#include <array>
#include <iostream>
#include <MailSystem.h>

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void default_case(void)
{
  /**
   * @brief Default Case, should pass!
   *
   */
  // std::cout << "Default Case, should pass!" << std::endl;
  MailSystem m;
  std::array<uint8_t, 247> in = {
      0x01, 0xB0, 0x54, 0x45, 0x1D, 0x52, 0x30, 0x54, 0x68, 0x69,
      0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x6D, 0x65, 0x73,
      0x73, 0x61, 0x67, 0x65, 0x20, 0x73, 0x65, 0x6E, 0x64, 0x20,
      0x74, 0x6F, 0x20, 0x74, 0x68, 0x65, 0x20, 0x54, 0x69, 0x74,
      0x61, 0x6E, 0x69, 0x75, 0x6D, 0x20, 0x66, 0x69, 0x72, 0x6D,
      0x77, 0x61, 0x72, 0x65, 0x21, 0x03};

  for (int i = 0; i < 56; i++) {
    m.AppendMessageByte(in.at(i));
  }

  m.UpdateMail();

  if (m.GetPendingMail()) {
    std::cout << "CRC: " << std::hex << m.GetCRC() << std::endl;
    std::cout << "Command: " << std::hex << m.GetCommand() + 0x00
              << std::endl;
    std::cout << "Data Length: " << std::hex << m.GetDataLength() + 0x00
              << std::endl;
  } else {
    std::cout << " There is no pending Mail!" << std::endl;
  }
  TEST_ASSERT_EQUAL(m.GetCRC(), 0xb054451d);
  TEST_ASSERT_EQUAL(m.GetCommand(), 0x52);
  TEST_ASSERT_EQUAL(m.GetDataLength(), 0x30);
}

void setup()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(default_case);
}

void loop()
{
  UNITY_END();
}

    