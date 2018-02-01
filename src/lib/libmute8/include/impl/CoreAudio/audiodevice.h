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

    virtual std::string getId() const override;
    virtual std::string getDescription() const override;
    virtual std::string getAdapter() const override;
    virtual std::string getName() const override;
    virtual Type getType() const override;
    virtual State getState() const override;
    virtual std::shared_ptr<IVolumeControl> getVolumeControl() const override;
    virtual float getPeak() const override;

private:

    _COM_SMARTPTR_TYPEDEF(IMMEndpoint, __uuidof(IMMEndpoint));

    IMMDevicePtr pDevice;
    IMMEndpointPtr pEndpoint;

    std::string getStringProperty(const PROPERTYKEY& property) const;
};

}

#endif // COREAUDIODEVICE_H
