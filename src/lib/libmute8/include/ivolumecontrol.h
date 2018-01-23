#ifndef IVOLUMECONTROL_H
#define IVOLUMECONTROL_H

namespace mute8
{

class IVolumeControl
{
public:

    virtual ~IVolumeControl() = default;

    virtual float getVolume() const = 0;
    virtual void setVolume(float volume) const = 0;

    virtual bool getMute() const = 0;
    virtual void setMute(bool mute) const = 0;
};

}

#endif // IVOLUMECONTROL_H
