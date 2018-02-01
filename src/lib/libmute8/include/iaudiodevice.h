#ifndef IAUDIODEVICE_H
#define IAUDIODEVICE_H

#include <ivolumecontrol.h>
#include <string>
#include <memory>

namespace mute8
{

class IAudioDevice
{
public:

    enum Type
    {
        tInput,
        tOutput
    };

    enum State
    {
        sActive,
        sDisabled
    };

    virtual ~IAudioDevice() = default;

    virtual std::string getId() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getAdapter() const = 0;
    virtual std::string getName() const = 0;
    virtual Type getType() const = 0;
    virtual State getState() const = 0;
    virtual std::shared_ptr<IVolumeControl> getVolumeControl() const = 0; // can return null_ptr
    virtual float getPeak() const = 0;
};

}

#endif // IAUDIODEVICE_H
