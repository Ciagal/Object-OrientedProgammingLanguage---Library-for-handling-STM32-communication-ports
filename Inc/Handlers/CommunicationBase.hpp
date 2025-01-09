#ifndef INC_COMMUNICATIONBASE_HPP_
#define INC_COMMUNICATIONBASE_HPP_

namespace MC{

class CommunicationBase {
public:
    virtual void init() = 0; //init metode
    virtual void transmit(uint16_t address, const uint8_t* data, size_t size) = 0;
    virtual void receive(uint16_t address, uint8_t* buffer, size_t size) = 0;
    virtual ~CommunicationBase() = default;
};

}

#endif /* INC_COMMUNICATIONBASE_HPP_ */
