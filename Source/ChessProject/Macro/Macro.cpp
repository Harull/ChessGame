// Fill out your copyright notice in the Description page of Project Settings.
#include "Macro.h"
#include "GameFramework/InputDeviceSubsystem.h"

bool DebugSettings::bEnableDebugDraw = true; // ou false par défaut

bool CheckDevice(UWorld* _world, const EHardwareDevicePrimaryType& _toCheck)
{
    APlayerController* _playerController = _world->GetFirstPlayerController();
    const FPlatformUserId& _id = _playerController->GetPlatformUserId();
    UInputDeviceSubsystem* _system = UInputDeviceSubsystem::Get();
    if (!_system) return false;

    FHardwareDeviceIdentifier _deviceId = _system->GetMostRecentlyUsedHardwareDevice(_id);
    return _deviceId.PrimaryDeviceType == _toCheck;
}
