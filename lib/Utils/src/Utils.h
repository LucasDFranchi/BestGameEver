#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>

/**
 * @brief Class that store Utils function used on several parts of the code.
 *
 */
class Utils {
public:
  /**
   * @brief Class that calculates the Checksum.
   *
   */
  class Checksum {
  public:
    static uint32_t Calculate(char *pIn, size_t size);
    static uint32_t CRCTable(uint32_t index);
  };
  /**
   * @brief Class that executes the memory operations in a safe way.
   *
   */
  class MemorySafe {
  public:
    static uint8_t memcpy_s(uint8_t *pOut, uint8_t *pIn, uint32_t size);
    static uint8_t memcmp_s(uint8_t *pOut, uint8_t *pIn, uint32_t size);
  };
  class Error {
  public:
    enum ErrorsList { SUCCESS = 0, FAIL };
  };
  class Time {
  private:
    std::chrono::system_clock::time_point start_;

  public:
    Time() { this->start_ = std::chrono::system_clock::now(); }
    uint32_t GetElapsedTime(std::chrono::system_clock::time_point now);
    std::chrono::system_clock::time_point GetTick(void);
  };
};
