#ifndef LT_PASSTHRU_H
#define LT_PASSTHRU_H

#include "../j2534/j2534.h"
#include "datalink.h"

#include <memory>
#include <vector>

namespace lt
{
class PassThruLink : public DataLink
{
public:
    explicit PassThruLink(j2534::Info && info);

    DataLinkType type() const override { return DataLinkType::PassThru; };

    void setPort(const std::string & port) noexcept override { port_ = port; }

    std::string port() const override { return port_; }

    NetworkProtocol supportedProtocols() const override;

    network::CanPtr can(uint32_t baudrate) override;

    // Creates ISO-TP interface from J2534 device if available or uses built-in ISO-TP stack with CAN.
    network::IsoTpPtr isotp(const network::IsoTpOptions & options) override;

    DataLinkFlags flags() const noexcept override;

private:
    std::string port_;
    // device_ must be destructed before interface_
    std::weak_ptr<j2534::Device> device_;
    j2534::J2534Ptr interface_;
    j2534::Info info_;

    void checkInterface();
    j2534::DevicePtr getDevice();
};
using PassThruLinkPtr = std::unique_ptr<PassThruLink>;

// Returns a vector of all installed PassThru drivers
std::vector<PassThruLinkPtr> detect_passthru_links();
} // namespace lt

#endif // LT_PASSTHRU_H
