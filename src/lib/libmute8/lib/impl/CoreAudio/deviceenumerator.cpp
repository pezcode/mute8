#include <impl/CoreAudio/deviceenumerator.h>

#include <impl/CoreAudio/audiodevice.h>
#include <Mmdeviceapi.h> // IMM interfaces
#include <comdef.h> // _COM_SMARTPTR_TYPEDEF
#include <comutil.h> // _bstr_t, _com_error
#include <algorithm> // copy_if
#include <cassert>

#include <iostream>

using namespace mute8;

//static const boost::none_t CoreDeviceEnumerator::tAny = boost::none;
//static const boost::none_t CoreDeviceEnumerator::tAny = boost::none;

CoreDeviceEnumerator::CoreDeviceEnumerator()
{
    /*
     * The multi-threaded apartment is intended for use by non-GUI threads. Threads in multi-threaded apartments should not perform UI actions.
     * This is because UI threads require a message pump, and COM does not pump messages for threads in a multi-threaded apartment.
     *
     * In addition to the flags already mentioned, it is a good idea to set the COINIT_DISABLE_OLE1DDE flag in the dwCoInit parameter.
     * Setting this flag avoids some overhead associated with Object Linking and Embedding (OLE) 1.0, an obsolete technology.
     */
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    comInit = SUCCEEDED(hr);
}

CoreDeviceEnumerator::~CoreDeviceEnumerator()
{
    if(comInit)
    {
        CoUninitialize();
    }
}

bool CoreDeviceEnumerator::populate()
{
    if(!comInit)
    {
        return false;
    }

    _COM_SMARTPTR_TYPEDEF(IMMDeviceEnumerator, __uuidof(IMMDeviceEnumerator));
    _COM_SMARTPTR_TYPEDEF(IMMDeviceCollection, __uuidof(IMMDeviceCollection));
    _COM_SMARTPTR_TYPEDEF(IMMDevice, __uuidof(IMMDevice));

    this->_devices.clear();

    try
    {
        HRESULT hr = S_OK;

        IMMDeviceEnumeratorPtr pEnumerator;
        hr = pEnumerator.CreateInstance(__uuidof(MMDeviceEnumerator));
        if(SUCCEEDED(hr))
        {
            assert(pEnumerator != nullptr);
            IMMDeviceCollectionPtr pCollection;
            hr = pEnumerator->EnumAudioEndpoints(eAll, DEVICE_STATEMASK_ALL, &pCollection);
            if(SUCCEEDED(hr))
            {
                assert(pCollection != nullptr);
                UINT count = 0;
                hr = pCollection->GetCount(&count);
                if(SUCCEEDED(hr))
                {
                    this->_devices.reserve(count);
                    IMMDevicePtr pDevice = nullptr;
                    for(UINT i = 0; i < count; i++)
                    {
                        hr = pCollection->Item(i, &pDevice);
                        if(SUCCEEDED(hr))
                        {
                            assert(pDevice != nullptr);
                            std::shared_ptr<IAudioDevice> nDevice = std::make_shared<CoreAudioDevice>(pDevice);
                            this->_devices.push_back(nDevice);
                        }
                    }
                    return true;
                }
            }
        }
    }
    catch(_com_error& e)
    {
        throw std::runtime_error(_bstr_t(e.ErrorMessage()));
    }

    return false;
}

std::vector<std::shared_ptr<IAudioDevice>> CoreDeviceEnumerator::devices(boost::optional<IAudioDevice::Type> type, boost::optional<IAudioDevice::State> state) const
{
std::vector<std::shared_ptr<IAudioDevice>> filtered;

    // back_inserter allows inserting without having to set vector size beforehand
    std::copy_if(this->_devices.begin(), this->_devices.end(), std::back_inserter(filtered), [type, state](const std::shared_ptr<IAudioDevice>& device) {
        return (!type || *type == device->getType()) && (!state || *state == device->getState());
    });

    return filtered;
}

size_t CoreDeviceEnumerator::count() const
{
    return this->_devices.size();
}

void CoreDeviceEnumerator::clear()
{
    this->_devices.clear();
}
