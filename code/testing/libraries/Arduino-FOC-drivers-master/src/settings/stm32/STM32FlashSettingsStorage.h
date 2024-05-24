
#pragma once

#include "../SettingsStorage.h"

#if defined(STM32G4xx)

#define PAGE_OF(x) (((uint32_t)x - FLASH_BASE) / FLASH_PAGE_SIZE)


class STM32FlashSettingsStorage : public SettingsStorage {
public:
    STM32FlashSettingsStorage(uint32_t address = FLASH_BASE + FLASH_SIZE - FLASH_PAGE_SIZE);
    ~STM32FlashSettingsStorage();

    void init() override;

    uint32_t _bank = FLASH_BANK_1; // TODO also support bank 2

protected:
    uint8_t readByte(uint8_t* valueToSet) override;
    uint8_t readFloat(float* valueToSet) override;
    uint8_t readInt(uint32_t* valueToSet) override;

    uint8_t writeByte(uint8_t value) override;
    uint8_t writeFloat(float value) override;
    uint8_t writeInt(uint32_t value) override;

    void beforeLoad() override;
    void beforeSave() override;
    void afterSave() override;

    void flushBuffer();
    void erasePage(uint32_t page);
    void reset();
    int readBytes(void* valueToSet, int numBytes);
    int writeBytes(void* value, int numBytes);

    uint32_t _address;
    uint8_t* _currptr;
    uint8_t* _writeptr;
    uint8_t _buffed = 0;
    uint32_t _page = 0;
    __attribute__((aligned(8))) union {
        uint8_t b[8];
        uint64_t l;
    }  _writeBuffer;    // 64-bit buffer
};


#endif