#ifndef SHT35_HPP
#define SHT35_HPP


namespace MC {

class SHT35 {
private:
    I2CHandler* m_i2cHandler;
    const uint8_t SHT35_ADDRESS = 0x44 << 1; // I2C addres for sensor SHT35

public:
    // constructor
    SHT35(I2CHandler* i2cHandler) : m_i2cHandler(i2cHandler) {}

    // function to read temp and hum
    void read(float& temperature, float& humidity) {
        uint8_t cmd[2] = {0x2C, 0x06}; // High Repeatability Measurement
        uint8_t data[6]; // Buffer

        // transmision to sensor
        m_i2cHandler->transmit(SHT35_ADDRESS, cmd, sizeof(cmd));

        HAL_Delay(20);

        // receive from sensor
        m_i2cHandler->receive(SHT35_ADDRESS, data, sizeof(data));

        // example calibration
        uint16_t rawTemp = (data[0] << 8) | data[1];
        uint16_t rawHum = (data[3] << 8) | data[4];

        temperature = -45.0 + 175.0 * ((float)rawTemp / 65535.0);
        humidity = 100.0 * ((float)rawHum / 65535.0);
    }
};
} // namespace MC

#endif // SHT35_HPP
