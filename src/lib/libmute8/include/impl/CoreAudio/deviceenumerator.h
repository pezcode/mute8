#ifndef COREDEVICEENUMERATOR_H
#define COREDEVICEENUMERATOR_H

#include <ideviceenumerator.h>

namespace mute8
{

class CoreDeviceEnumerator : public IDeviceEnumerator
{
public:

    CoreDeviceEnumerator();
    virtual ~CoreDeviceEnumerator();

    virtual bool populate() override;
    virtual void clear() override;
    virtual size_t count() const override;

    using IDeviceEnumerator::devices; // also use overloaded interface methods
    virtual DeviceList devices(boost::optional<IAudioDevice::Type> type, boost::optional<IAudioDevice::State> state) const override;
    virtual std::shared_ptr<IAudioDevice> defaultDevice(boost::optional<IAudioDevice::Type> type) const override;

private:

    DeviceList _devices;

    bool comInit;
};

}

#endif // COREDEVICEENUMERATOR_H
