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

    virtual bool populate();
    virtual std::vector<std::shared_ptr<IAudioDevice>> devices(IAudioDevice::Type type, IAudioDevice::State state) const;
    virtual size_t count() const;

    virtual void clear();

private:

    std::vector<std::shared_ptr<IAudioDevice>> _devices;

    bool comInit;
};

}

#endif // COREDEVICEENUMERATOR_H
