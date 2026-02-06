#include <stdint.h>
#include <cstring>
#include <iostream>

/**
 * This is a quick test for a PR in https://github.com/bertmelis/USBHostSerial
 */

#define F_SIZE 9999
uint8_t fakeResponses[F_SIZE];

static uint8_t* mockRingbufferReceiveUpTo(std::size_t* pxItemSize,
                                          std::size_t xMaxSize) {
  std::cout << "xMaxSize: " << xMaxSize << std::endl;
  static std::size_t offset = 0;

  if (offset >= sizeof(fakeResponses)) {
    return nullptr;  // no more data
  }

  std::size_t remaining = sizeof(fakeResponses) - offset;
  std::size_t chunkSize = remaining < xMaxSize ? remaining : xMaxSize;

  // simulate fixed 5-byte chunks
  if (chunkSize > 5) {
    chunkSize = 5;
  }

  *pxItemSize = chunkSize;

  uint8_t* ret = const_cast<uint8_t*>(fakeResponses + offset);
  offset += chunkSize;
  return ret;
}

std::size_t read(uint8_t* dest, std::size_t size) {
  std::size_t retVal = 0;
  std::size_t pxItemSize = 0;
  while (size > retVal) {
    void* ret = mockRingbufferReceiveUpTo(&pxItemSize, size - retVal);
    if (ret) {
      std::memcpy(dest + retVal, ret, pxItemSize);
      std::cout << "ret: " << (size_t)pxItemSize << std::endl;
      retVal += pxItemSize;
    } else {
      break;
    }
  }
  return retVal;
}

static void testRead() {
  for (int i = 0; i < F_SIZE; i++) {
    fakeResponses[i] = i;
  }

  uint8_t checkBuff[100]{};

  std::size_t bytes = read(checkBuff, sizeof(checkBuff));

  // basic checks
  if (bytes != 100) {
    std::cout << "Error: Len missmatch \n";
  }

  std::cout << "checkBuff \n";
  for (int i = 0; i < 100; ++i) {
    std::cout << (int)checkBuff[i] << " ";
  }

  std::cout << std::endl;
}