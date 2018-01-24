#ifndef COREAUDIODEVICE_H
#define COREAUDIODEVICE_H

#include <iaudiodevice.h>
#include <Mmdeviceapi.h> // IMM interfaces
#include <comdef.h> // _COM_SMARTPTR_TYPEDEF
#include <string>

namespace mute8
{

class CoreAudioDevice : public IAudioDevice
{
public:

    _COM_SMARTPTR_TYPEDEF(IMMDevice, __uuidof(IMMDevice));

    CoreAudioDevice(const IMMDevicePtr& device);
    virtual ~CoreAudioDevice() = default;

    virtual std::string getId() const;
    virtual std::string getName() const;
    virtual Type getType() const;
    virtual State getState() const;
    virtual std::shared_ptr<IVolumeControl> getVolumeControl() const;

private:


    _COM_SMARTPTR_TYPEDEF(IMMEndpoint, __uuidof(IMMEndpoint));

    IMMDevicePtr pDevice;
    IMMEndpointPtr pEndpoint;

    std::string encodeUtf8(const std::wstring& wstr) const;
};

}

#endif // COREAUDIODEVICE_H
