#include <Arduino.h>
#include <Util.h>
#include <array>
#include <unity.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void memcpy_default_case(void) {

  uint8_t foo[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  constexpr uint32_t sizeCpy = sizeof(foo) / sizeof(foo[0]);
  uint8_t bar[sizeCpy] = {0};

  Utils::MemorySafe::memcpy_s(bar, foo, sizeCpy);

  for (uint32_t i = 0; i < sizeCpy; i++) {
    TEST_ASSERT_EQUAL(bar[i], foo[i]);
  }
}

void memcpy_zero_size(void) {

  uint8_t foo[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  constexpr uint32_t sizeCpy = sizeof(foo) / sizeof(foo[0]);
  uint8_t bar[sizeCpy] = {0};
  TEST_ASSERT_EQUAL(Utils::MemorySafe::memcpy_s(bar, foo, 0), Utils::Error::FAIL);
}

void memcpy_output_nullptr(void) {

  uint8_t foo[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  constexpr uint32_t sizeCpy = sizeof(foo) / sizeof(foo[0]);
  uint8_t *bar = nullptr;
  TEST_ASSERT_EQUAL(Utils::MemorySafe::memcpy_s(bar, foo, sizeCpy), Utils::Error::FAIL);
}

void memcpy_input_nullptr(void) {

  uint8_t *foo = nullptr;
  constexpr uint32_t sizeCpy = 10;
  uint8_t bar[sizeCpy] = {0};
  TEST_ASSERT_EQUAL(Utils::MemorySafe::memcpy_s(bar, foo, sizeCpy), Utils::Error::FAIL);
}

void memcpy_test_cases(void) {
  memcpy_default_case();
  memcpy_zero_size();
  memcpy_output_nullptr();
  memcpy_input_nullptr();
}

void checksum_default_case(void) {
  char pIn[] = {
      0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x6D, 0x65,
      0x73, 0x73, 0x61, 0x67, 0x65, 0x20, 0x73, 0x65, 0x6E, 0x64, 0x20, 0x74,
      0x6F, 0x20, 0x74, 0x68, 0x65, 0x20, 0x54, 0x69, 0x74, 0x61, 0x6E, 0x69,
      0x75, 0x6D, 0x20, 0x66, 0x69, 0x72, 0x6D, 0x77, 0x61, 0x72, 0x65, 0x21,
  };
  const uint32_t calculated_crc = 0xB054451D;
  auto crc = Utils::Checksum::Calculate((char *)pIn, sizeof(pIn));
  TEST_ASSERT_EQUAL(calculated_crc, crc);
}

void checksum_error(void) {
  char pIn[] = {'0', '1', '2'};
  const uint32_t calculated_crc = 0xa8c9cd58;
  auto crc = Utils::Checksum::Calculate((char *)pIn, sizeof(pIn));
  std::cout << "Calculated CRC: " << std::hex << crc << std::endl;
  TEST_ASSERT_NOT_EQUAL(calculated_crc, crc);
}

void checksum_test_cases(void) {
  checksum_default_case();
  checksum_error();
}

void test_cases(void) {
  UNITY_BEGIN();
  RUN_TEST(memcpy_test_cases);
  RUN_TEST(checksum_test_cases);
  UNITY_END();
}

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  test_cases();

}

void loop() {}
