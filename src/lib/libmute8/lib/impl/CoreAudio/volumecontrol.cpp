#include <impl/CoreAudio/volumecontrol.h>

#include <stdexcept>
#include <cassert>

using namespace mute8;

CoreVolumeControl::CoreVolumeControl(const IAudioEndpointVolumePtr& volume) : pVolume(volume)
{
    if(volume == nullptr)
    {
        throw std::invalid_argument("volume is null");
    }
}

float CoreVolumeControl::getVolume() const
{
float volume;

    HRESULT hr = this->pVolume->GetMasterVolumeLevelScalar(&volume);
    if(FAILED(hr))
    {
        throw std::runtime_error("GetMasterVolumeLevelScalar failed");
    }

    assert(volume >= 0.0f && volume <= 1.0f);
    return volume;
}

void CoreVolumeControl::setVolume(float volume) const
{
    if(!(volume >= 0.0f && volume <= 1.0f))
    {
        throw std::invalid_argument("volume is not in [0, 1]");
    }

    HRESULT hr = this->pVolume->SetMasterVolumeLevelScalar(volume, NULL);
    if(FAILED(hr))
    {
        throw std::runtime_error("SetMasterVolumeLevelScalar failed");
    }
}

bool CoreVolumeControl::getMute() const
{
BOOL mute = FALSE;

    HRESULT hr = this->pVolume->GetMute(&mute);
    if(FAILED(hr))
    {
        throw std::runtime_error("GetMute failed");
    }

    assert(mute == TRUE || mute == FALSE);
    return static_cast<bool>(mute);
}

void CoreVolumeControl::setMute(bool mute) const
{
    HRESULT hr = this->pVolume->SetMute(static_cast<BOOL>(mute), NULL);
    if(FAILED(hr))
    {
        throw std::runtime_error("SetMute failed");
    }
}
