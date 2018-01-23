#ifndef IDEVICEENUMERATOR_H
#define IDEVICEENUMERATOR_H

#include <iaudiodevice.h>
#include <vector>
#include <memory>

namespace mute8
{

class IDeviceEnumerator
{
public:

    virtual ~IDeviceEnumerator() = default;

    virtual bool populate() = 0;
    virtual std::vector<std::shared_ptr<IAudioDevice>> devices(IAudioDevice::Type type, IAudioDevice::State state) const = 0;
    virtual size_t count() const = 0;

    virtual void clear() = 0;
};

}

#endif // IDEVICEENUMERATOR_H
