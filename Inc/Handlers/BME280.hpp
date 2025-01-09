#ifndef BME280_HPP
#define BME280_HPP


namespace MC {
class BME280 {
private:
    SPIHandler* m_spiHandler; // SPIHandler object
    GPIO_TypeDef* m_csPort;   // Port CS
    uint16_t m_csPin;         // Pin CS

    void select() {
        HAL_GPIO_WritePin(m_csPort, m_csPin, GPIO_PIN_RESET); // on CS
    }

    void deselect() {
        HAL_GPIO_WritePin(m_csPort, m_csPin, GPIO_PIN_SET); // off CS
    }

public:
    // constructor
    BME280(SPIHandler* spiHandler, GPIO_TypeDef* csPort, uint16_t csPin)
        : m_spiHandler(spiHandler), m_csPort(csPort), m_csPin(csPin) {}

    void initialize() {
        // config
        writeRegister(0xF2, 0x01); // Humidity oversampling x1
        writeRegister(0xF4, 0x27); // Pressure i temperature oversampling x1, normal mode
        writeRegister(0xF5, 0xA0); // Config register
    }

    uint8_t readRegister(uint8_t reg) {
        select();
        uint8_t receivedData = 0;
        uint8_t sendData = reg | 0x80; // MSB on 1, to read from register
        m_spiHandler->transmit(0, &sendData, 1);
        m_spiHandler->receive(0, &receivedData, 1);
        deselect();
        return receivedData;
    }

    void writeRegister(uint8_t reg, uint8_t value) {
        select();
        uint8_t data[] = {static_cast<uint8_t>(reg & 0x7F), value}; // MSB on 0 to write to register
        m_spiHandler->transmit(0, data, sizeof(data));
        deselect();
    }

    float readTemperature() {
        uint8_t msb = readRegister(0xFA);
        uint8_t lsb = readRegister(0xFB);
        uint8_t xlsb = readRegister(0xFC);

        int32_t rawTemp = ((msb << 16) | (lsb << 8) | xlsb) >> 4;
        //example calculations
        return rawTemp / 100.0f;
    }
};
}

#endif // BME280_HPP
