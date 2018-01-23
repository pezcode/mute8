#ifndef IDEVICEENUMERATOR_H
#define IDEVICEENUMERATOR_H

// we need this to be able to declare constexpr of type boost::none_t
#define BOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE

#include <iaudiodevice.h>
#include <vector>
#include <memory>
#include <boost/optional.hpp>

namespace mute8
{

class IDeviceEnumerator
{
public:

    // make filters in devices() optional
    static constexpr auto any = boost::none;

    virtual ~IDeviceEnumerator() = default;

    virtual bool populate() = 0;
    virtual std::vector<std::shared_ptr<IAudioDevice>> devices(boost::optional<IAudioDevice::Type> type, boost::optional<IAudioDevice::State> state) const = 0;
    virtual size_t count() const = 0;

    virtual void clear() = 0;
};

}

#endif // IDEVICEENUMERATOR_H
