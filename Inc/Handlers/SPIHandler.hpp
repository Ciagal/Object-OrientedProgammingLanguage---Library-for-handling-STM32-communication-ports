#ifndef SPI_HANDLER_HPP
#define SPI_HANDLER_HPP

#include "CommunicationBase.hpp"


namespace MC{

class SPIHandler : public CommunicationBase {
private:
    SPI_HandleTypeDef* m_spiHandle;
    uint32_t m_timeout;

public:
    // default constructor
    SPIHandler() : m_spiHandle(nullptr), m_timeout(HAL_MAX_DELAY) {}

    // parametric constructor
    SPIHandler(SPI_HandleTypeDef* handle, uint32_t timeout = HAL_MAX_DELAY)
        : m_spiHandle(handle), m_timeout(timeout) {}

    // setter
    void setConfig(SPI_HandleTypeDef* handle, uint32_t timeout = HAL_MAX_DELAY) {
        m_spiHandle = handle;
        m_timeout = timeout;
    }

    void init() override {
        if (m_spiHandle != nullptr) {
            HAL_SPI_Init(m_spiHandle);
        }
    }

    void transmit(uint16_t, const uint8_t* data, size_t size) override {
        if (m_spiHandle != nullptr) {
            HAL_SPI_Transmit(m_spiHandle, const_cast<uint8_t*>(data), size, m_timeout);
        }
    }

    void receive(uint16_t, uint8_t* buffer, size_t size) override {
        if (m_spiHandle != nullptr) {
            HAL_SPI_Receive(m_spiHandle, buffer, size, m_timeout);
        }
    }
};
}
#endif // SPI_HANDLER_HPP

