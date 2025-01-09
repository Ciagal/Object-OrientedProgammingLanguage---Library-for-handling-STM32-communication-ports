#ifndef UART_HANDLER_HPP
#define UART_HANDLER_HPP

#include "CommunicationBase.hpp"

namespace MC{

class UARTHandler : public CommunicationBase {
private:
    UART_HandleTypeDef* m_uartHandle;
    uint32_t m_timeout;

public:
    // default constructor
    UARTHandler() : m_uartHandle(nullptr), m_timeout(HAL_MAX_DELAY) {}

    // parametric constructor
    UARTHandler(UART_HandleTypeDef* handle, uint32_t timeout = HAL_MAX_DELAY)
        : m_uartHandle(handle), m_timeout(timeout) {}

    // setter
    void setConfig(UART_HandleTypeDef* handle, uint32_t timeout = HAL_MAX_DELAY) {
        m_uartHandle = handle;
        m_timeout = timeout;
    }

    void init() override {
        if (m_uartHandle != nullptr) {
            HAL_UART_Init(m_uartHandle);
        }
    }

    void transmit(uint16_t, const uint8_t* data, size_t size) override {
        if (m_uartHandle != nullptr) {
            HAL_UART_Transmit(m_uartHandle, const_cast<uint8_t*>(data), size, m_timeout);
        }
    }

    void receive(uint16_t, uint8_t* buffer, size_t size) override {
        if (m_uartHandle != nullptr) {
            HAL_UART_Receive(m_uartHandle, buffer, size, m_timeout);
        }
    }
};
}

#endif
