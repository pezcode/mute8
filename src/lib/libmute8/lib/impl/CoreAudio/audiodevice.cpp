#include <impl/CoreAudio/audiodevice.h>

#include <impl/CoreAudio/volumecontrol.h>
#include <Mmdeviceapi.h> // IMM interfaces
#include <Endpointvolume.h> // IAudioEndpointVolume
#include <Functiondiscoverykeys_devpkey.h> // PKEY_Device_FriendlyName
#include <comdef.h> // _COM_SMARTPTR_TYPEDEF
#include <comutil.h> // _bstr_t
#include <stdexcept>
#include <cassert>

using namespace mute8;

CoreAudioDevice::CoreAudioDevice(const IMMDevicePtr& device)
{
    if(device == nullptr)
    {
        throw std::invalid_argument("device is null");
    }
    this->pDevice = device;

    HRESULT hr = this->pDevice->QueryInterface(IID_PPV_ARGS(&pEndpoint));
    if(FAILED(hr))
    {
        throw std::runtime_error("QueryInterface for IMMEndpoint failed");
    }

    assert(pEndpoint != nullptr);
}

std::string CoreAudioDevice::getId() const
{
    LPWSTR idUtf16 = nullptr;
    HRESULT hr = this->pDevice->GetId(&idUtf16);
    if(FAILED(hr))
    {
        throw std::runtime_error("GetId failed");
    }
    assert(idUtf16 != nullptr);
    //std::string id = this->encodeUtf8(idUtf16);
    // TODO use ConvertBSTRToString?
    std::string id = _bstr_t(idUtf16);
    CoTaskMemFree(idUtf16);
    //return id;
    return id;
}

std::string CoreAudioDevice::getName() const
{
    _COM_SMARTPTR_TYPEDEF(IPropertyStore, __uuidof(IPropertyStore));

    HRESULT hr = S_OK;

    IPropertyStorePtr pProperties;
    hr = this->pDevice->OpenPropertyStore(STGM_READ, &pProperties);
    if(FAILED(hr))
    {
        throw std::runtime_error("OpenPropertyStore failed");
    }
    assert(pProperties != nullptr);
    PROPVARIANT varName;
    PropVariantInit(&varName);
    hr = pProperties->GetValue(PKEY_Device_FriendlyName, &varName);
    if(FAILED(hr))
    {
        throw std::runtime_error("GetValue for PKEY_Device_FriendlyName failed");
    }
    assert(varName.vt == VT_LPWSTR);
    assert(varName.pwszVal != nullptr);
    std::string name = _bstr_t(varName.pwszVal);
    //std::string name = this->encodeUtf8(varName.pwszVal);
    PropVariantClear(&varName);
    return name;
}

IAudioDevice::Type CoreAudioDevice::getType() const
{
    EDataFlow flow;
    HRESULT hr = this->pEndpoint->GetDataFlow(&flow);
    if(FAILED(hr))
    {
        throw std::runtime_error("GetDataFlow failed");
    }

    switch(flow)
    {
        case eCapture:
            return tInput;
        case eRender:
            return tOutput;
        default:
            throw std::runtime_error("Invalid flow");
    }
}

IAudioDevice::State CoreAudioDevice::getState() const
{
    DWORD state = 0;
    HRESULT hr = this->pDevice->GetState(&state);
    if(FAILED(hr))
    {
        throw std::runtime_error("GetState failed");
    }

    switch(state)
    {
        case DEVICE_STATE_ACTIVE:
            return sActive;
        case DEVICE_STATE_DISABLED:
        case DEVICE_STATE_NOTPRESENT:
        case DEVICE_STATE_UNPLUGGED:
            return sDisabled;
        default:
            throw std::runtime_error("Invalid state");
    }
}

std::shared_ptr<IVolumeControl> CoreAudioDevice::getVolumeControl() const
{
    _COM_SMARTPTR_TYPEDEF(IAudioEndpointVolume, __uuidof(IAudioEndpointVolume));

    if(this->getState() != sActive)
    {
        // pDevice->Activate returns E_POINTER if there is no IAudioEndpointVolume
        // Shouldn't this be E_NOINTERFACE or E_NOTIMPL?
        // There are volume controls for all active devices so this is a bit of a hack
        // TODO fix this with proper hr check
        return nullptr;
    }

    IAudioEndpointVolumePtr pVolume;
    HRESULT hr = this->pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, reinterpret_cast<void**>(&pVolume));
    if(FAILED(hr))
    {
        throw std::runtime_error("Activate for IAudioEndpointVolume failed");
    }

    assert(pVolume != nullptr);
    return std::make_shared<CoreVolumeControl>(pVolume);
}

/*
std::string CoreAudioDevice::encodeUtf8(const std::wstring &strUtf16)
{
    if(strUtf16.empty())
        return std::string();

    int size = WideCharToMultiByte(CP_UTF8, 0, strUtf16.c_str(), static_cast<int>(strUtf16.size()), NULL, 0, NULL, NULL);
    std::string strUtf8(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, strUtf16.c_str(), static_cast<int>(strUtf16.size()), &strUtf8[0], size, NULL, NULL);
    return strUtf8;
}
*/
