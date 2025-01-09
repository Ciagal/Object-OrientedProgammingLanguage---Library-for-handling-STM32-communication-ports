#ifndef I2C_HANDLER_HPP
#define I2C_HANDLER_HPP

#include "CommunicationBase.hpp"

namespace MC{

class I2CHandler : public CommunicationBase {
private:
    I2C_HandleTypeDef* m_i2cHandle;
    uint32_t m_timeout;

public:
    // default constructor
    I2CHandler() : m_i2cHandle(nullptr), m_timeout(HAL_MAX_DELAY) {}

    // parametric constructor
    I2CHandler(I2C_HandleTypeDef* handle, uint32_t timeout = HAL_MAX_DELAY)
        : m_i2cHandle(handle), m_timeout(timeout) {}

    // setter
    void setConfig(I2C_HandleTypeDef* handle, uint32_t timeout = HAL_MAX_DELAY) {
        m_i2cHandle = handle;
        m_timeout = timeout;
    }

    void init() override {
        if (m_i2cHandle != nullptr) {
            HAL_I2C_Init(m_i2cHandle);
        }
    }

    void transmit(uint16_t address, const uint8_t* data, size_t size) override {
        if (m_i2cHandle != nullptr) {
            HAL_I2C_Master_Transmit(m_i2cHandle, address, const_cast<uint8_t*>(data), size, m_timeout);
        }
    }

    void receive(uint16_t address, uint8_t* buffer, size_t size) override {
        if (m_i2cHandle != nullptr) {
            HAL_I2C_Master_Receive(m_i2cHandle, address, buffer, size, m_timeout);
        }
    }
};
}

#endif // I2C_HANDLER_HPP
