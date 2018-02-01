#ifndef COREVOLUMECONTROL_H
#define COREVOLUMECONTROL_H

#include <ivolumecontrol.h>
#include <Endpointvolume.h> // IAudioEndpointVolume
#include <comdef.h> // _COM_SMARTPTR_TYPEDEF

namespace mute8
{

class CoreVolumeControl : public IVolumeControl
{
public:

    _COM_SMARTPTR_TYPEDEF(IAudioEndpointVolume, __uuidof(IAudioEndpointVolume));

    CoreVolumeControl(const IAudioEndpointVolumePtr& volume);
    virtual ~CoreVolumeControl() = default;

    virtual float getVolume() const override;
    virtual void setVolume(float volume) const override;

    virtual bool getMute() const override;
    virtual void setMute(bool mute) const override;

private:

    IAudioEndpointVolumePtr pVolume;
};

}

#endif // COREVOLUMECONTROL_H
