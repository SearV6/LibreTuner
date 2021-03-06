#ifndef LT_ELM_DATALINK_H
#define LT_ELM_DATALINK_H

#include "../network/command/elm327.h"
#include "datalink.h"

namespace lt
{

class ElmDataLink : public DataLink
{
public:
    explicit ElmDataLink(const std::string & name, std::string port = "",
                         int baudrate = 115200);

    DataLinkType type() const override;

    NetworkProtocol supportedProtocols() const override;

    // Stub. Returns nullptr
    network::CanPtr can(uint32_t baudrate) override;

    network::IsoTpPtr isotp(const network::IsoTpOptions & options) override;

    std::string port() const override { return port_; }

    std::vector<std::string> ports() override;

    void setPort(const std::string & port) override;

    // If the device has not been initialized, initializes it
    network::Elm327Ptr createDevice();

    inline void setBaudrate(int baudrate) override;

    int baudrate() override;

    DataLinkFlags flags() const noexcept override;

private:
    std::string port_;
    std::weak_ptr<network::Elm327> device_;
    int uartBaudrate_{0}; // Baudrate of 0 to keep unchanged
};

} // namespace lt

#endif // LT_ELM_DATALINK_H
