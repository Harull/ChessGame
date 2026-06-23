// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/InputSettings.h>

class DebugSettings
{
public:
	static bool bEnableDebugDraw;
};

bool CheckDevice(UWorld* _world, const EHardwareDevicePrimaryType& _toCheck);

//Utils
#define WORLD GetWorld()
#define GET_WORLD(variableName) TObjectPtr<UWorld> variableName = WORLD
#define CAST(classType, variableName, variable) TObjectPtr<classType> variableName = Cast<classType>(variable)
#define DELTATIME WORLD->DeltaTimeSeconds
#define SUBSYSTEM(type) WORLD->GetGameInstance()->GetSubsystem<type>()
#define WORLD_SUBSYSTEM(type) WORLD->GetSubsystem<type>()
#define GET_SUBSYSTEM(type, variableName) TObjectPtr<type> variableName = WORLD->GetGameInstance()->GetSubsystem<type>()
#define GET_WORLD_SUBSYSTEM(type, variableName) TObjectPtr<type> variableName = WORLD->GetSubsystem<type>()
#define UKSL UKismetSystemLibrary
#define UKML UKismetMathLibrary
#define ONE_FRAME_DELAY(worldContext, lambdaBody) if (!worldContext || !worldContext->GetWorld()) return; worldContext->GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]() { lambdaBody; }))
#define TIMER(worldContext, handleVariable, lambdaBody, delay) if (!worldContext || !worldContext->GetWorld()) return; worldContext->GetWorld()->GetTimerManager().SetTimer(handleVariable, FTimerDelegate::CreateLambda([this]() { lambdaBody; }), delay, false);
#define TIMER_LOOP(worldContext, handleVariable, lambdaBody, initialDelay, loopDelay) if (!worldContext || !worldContext->GetWorld()) return; worldContext->GetWorld()->GetTimerManager().SetTimer(handleVariable, FTimerDelegate::CreateLambda([this]() { lambdaBody; }), loopDelay, true, initialDelay);
#define GAMEINSTANCE Cast<USR_GameInstance>(WORLD->GetGameInstance())
#define PLAYER_PAWN WORLD->GetFirstPlayerController()->GetPawn()
#define PLAYER_CHARACTER WORLD->GetFirstPlayerController()->GetCharacter()
#define GET_PLAYER_PAWN(variableName) TObjectPtr<APawn> variableName = PLAYER_PAWN
#define GET_PLAYER_CHARACTER(variableName) TObjectPtr<ACharacter> variableName = PLAYER_CHARACTER
#define CDS(variable, type, name) variable = CreateDefaultSubobject<type>(name)
#define ATTACH_TO(variable, type, name, AttachTo) CDS(variable, type, name); variable->SetupAttachment(AttachTo)
#define ADD_COMPONENT(variable, type, name) CDS(variable, type, name); AddOwnedComponent(variable)
#define PLAYER_CONTROLLER Cast<ADynamicPlayerController>(WORLD->GetFirstPlayerController())
#define GET_PLAYER_CONTROLLER(variable) ADynamicPlayerController* variable = PLAYER_CONTROLLER


//Log
#define LOG_CUSTOM(message, color) if (true) UKSL::PrintString(this, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::color, 20.0f)
#define LOG(message) LOG_CUSTOM(message, Green)
#define LOG_WARN(message) LOG_CUSTOM(message, Yellow)
#define LOG_ERROR(message) LOG_CUSTOM(message, Red)
#define FRAME_LOG(message)  if (true) UKSL::PrintString(this, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::Magenta, DELTATIME)
#define FRAME_WLOG(world,message) if (true) UKSL::PrintString(world, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::Magenta, world->DeltaTimeSeconds)

//Debug (Do not use them in any skills)
#define DEBUG_CUBE(location, size, color) if (true) DrawDebugBox(WORLD, location, size, FQuat::Identity, color)
#define DEBUG_CUBE_TIME(location, size, color, lifeTime) if (true) DrawDebugBox(WORLD, location, size, FQuat::Identity, color, false, lifeTime)
#define DEBUG_SPHERE(location, radius, color) if (true) DrawDebugSphere(WORLD, location, radius, 12, color)
#define DEBUG_SPHERE_TIME(location, radius, color,lifeTime) if (true) DrawDebugSphere(WORLD, location, radius, 12, color, false,lifeTime)
#define DEBUG_LINE(startLocation, endLocation, color) if (true) DrawDebugLine(WORLD, startLocation, endLocation, color, false, 1.0f)
#define DEBUG_LINE_TIME(startLocation, endLocation, color, lifeTime) if (true) DrawDebugLine(WORLD, startLocation, endLocation, color, false, lifeTime)
#define DEBUG_CONE(location, direction, angle, length, color) if (true) DrawDebugCone(WORLD, location, direction, length, angle, angle, 12, color, false, 1.0f)
#define DEBUG_CONE_TIME(location, direction, angle, length, color, lifeTime) if (true) DrawDebugCone(WORLD, location, direction, length, angle, angle, 12, color, false, lifeTime)
#define DEBUG_RAY(startLocation, direction, length, color) if (true) DrawDebugLine(WORLD, startLocation, startLocation + direction * length, color, false, 1.0f)
#define DEBUG_RAY_TIME(startLocation, direction, length, color, lifeTime) if (true) DrawDebugLine(WORLD, startLocation, startLocation + direction * length, color, false, lifeTime)
#define DEBUG_TEXT(location, message, color, lifeTime) if (true) DrawDebugString(WORLD, location, message, nullptr, color, 1.0f, true)
#define DEBUG_TEXT_TIME(location, message, color, lifeTime) if (true) DrawDebugString(WORLD, location, message, nullptr, color, lifeTime, true)
#define DEBUG_ARROW(startLocation, endLocation, arrowSize, color) if (true) DrawDebugDirectionalArrow(WORLD, startLocation, endLocation, arrowSize, color)

//Skills usables debugs
#define WDEBUG_CUBE(world, size, color) if (true) DrawDebugBox(world, location, size, FQuat::Identity, color)
#define WDEBUG_CUBE_TIME(world,location, size, color, lifeTime) if (true) DrawDebugBox(world, location, size, FQuat::Identity, color, false, lifeTime)
#define WDEBUG_SPHERE(world,location, radius, color) if (true) DrawDebugSphere(world, location, radius, 12, color)
#define WDEBUG_SPHERE_TIME(world,location, radius, color,lifeTime) if (true) DrawDebugSphere(world, location, radius, 12, color, false,lifeTime)
#define WDEBUG_LINE(world,startLocation, endLocation, color) if (true) DrawDebugLine(world, startLocation, endLocation, color, false, 1.0f)
#define WDEBUG_LINE_TIME(world,startLocation, endLocation, color, lifeTime) if (true) DrawDebugLine(world, startLocation, endLocation, color, false, lifeTime)
#define WDEBUG_CONE(world,location, direction, angle, length, color) if (true) DrawDebugCone(world, location, direction, length, angle, angle, 12, color, false, 1.0f)
#define WDEBUG_CONE_TIME(world,location, direction, angle, length, color, lifeTime) if (true) DrawDebugCone(world, location, direction, length, angle, angle, 12, color, false, lifeTime)
#define WDEBUG_RAY(world,startLocation, direction, length, color) if (true) DrawDebugLine(world, startLocation, startLocation + direction * length, color, false, 1.0f)
#define WDEBUG_RAY_TIME(world,startLocation, direction, length, color, lifeTime) if (true) DrawDebugLine(world, startLocation, startLocation + direction * length, color, false, lifeTime)
#define WDEBUG_TEXT(world,location, message, color, lifeTime) if (true) DrawDebugString(world, location, message, nullptr, color, 1.0f, true)
#define WDEBUG_TEXT_TIME(world,location, message, color, lifeTime) if (true) DrawDebugString(world, location, message, nullptr, color, lifeTime, true)
#define WDEBUG_ARROW(world,startLocation, endLocation, arrowSize, color) if (true) DrawDebugDirectionalArrow(world, startLocation, endLocation, arrowSize, color)

//Commented debug settings::benabledebugdraw system, that is currently not working well
/*
////Log
//#define LOG_CUSTOM(message, color) if (DebugSettings::bEnableDebugDraw) UKSL::PrintString(this, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::color, 20.0f)
//#define LOG(message) LOG_CUSTOM(message, Green)
//#define LOG_WARN(message) LOG_CUSTOM(message, Yellow)
//#define LOG_ERROR(message) LOG_CUSTOM(message, Red)
//#define FRAME_LOG(message)  if (DebugSettings::bEnableDebugDraw) UKSL::PrintString(this, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::Magenta, DELTATIME)
//#define FRAME_WLOG(world,message) if (DebugSettings::bEnableDebugDraw) UKSL::PrintString(world, FPaths::GetBaseFilename(TEXT(__FILE__)) + "(" + FString::FromInt(__LINE__) + ")=> " + message, true, true, FColor::Magenta, world->DeltaTimeSeconds)
//
////Debug (Do not use them in any skills)
//#define DEBUG_CUBE(location, size, color) if (DebugSettings::bEnableDebugDraw) DrawDebugBox(WORLD, location, size, FQuat::Identity, color)
//#define DEBUG_CUBE_TIME(location, size, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugBox(WORLD, location, size, FQuat::Identity, color, false, lifeTime)
//#define DEBUG_SPHERE(location, radius, color) if (DebugSettings::bEnableDebugDraw) DrawDebugSphere(WORLD, location, radius, 12, color)
//#define DEBUG_SPHERE_TIME(location, radius, color,lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugSphere(WORLD, location, radius, 12, color, false,lifeTime)
//#define DEBUG_LINE(startLocation, endLocation, color) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(WORLD, startLocation, endLocation, color, false, 1.0f)
//#define DEBUG_LINE_TIME(startLocation, endLocation, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(WORLD, startLocation, endLocation, color, false, lifeTime)
//#define DEBUG_CONE(location, direction, angle, length, color) if (DebugSettings::bEnableDebugDraw) DrawDebugCone(WORLD, location, direction, length, angle, angle, 12, color, false, 1.0f)
//#define DEBUG_CONE_TIME(location, direction, angle, length, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugCone(WORLD, location, direction, length, angle, angle, 12, color, false, lifeTime)
//#define DEBUG_RAY(startLocation, direction, length, color) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(WORLD, startLocation, startLocation + direction * length, color, false, 1.0f)
//#define DEBUG_RAY_TIME(startLocation, direction, length, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(WORLD, startLocation, startLocation + direction * length, color, false, lifeTime)
//#define DEBUG_TEXT(location, message, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugString(WORLD, location, message, nullptr, color, 1.0f, true)
//#define DEBUG_TEXT_TIME(location, message, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugString(WORLD, location, message, nullptr, color, lifeTime, true)
//#define DEBUG_ARROW(startLocation, endLocation, arrowSize, color) if (DebugSettings::bEnableDebugDraw) DrawDebugDirectionalArrow(WORLD, startLocation, endLocation, arrowSize, color)
//
////Skills usables debugs
//#define WDEBUG_CUBE(world, size, color) if (DebugSettings::bEnableDebugDraw) DrawDebugBox(world, location, size, FQuat::Identity, color)
//#define WDEBUG_CUBE_TIME(world,location, size, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugBox(world, location, size, FQuat::Identity, color, false, lifeTime)
//#define WDEBUG_SPHERE(world,location, radius, color) if (DebugSettings::bEnableDebugDraw) DrawDebugSphere(world, location, radius, 12, color)
//#define WDEBUG_SPHERE_TIME(world,location, radius, color,lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugSphere(world, location, radius, 12, color, false,lifeTime)
//#define WDEBUG_LINE(world,startLocation, endLocation, color) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(world, startLocation, endLocation, color, false, 1.0f)
//#define WDEBUG_LINE_TIME(world,startLocation, endLocation, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(world, startLocation, endLocation, color, false, lifeTime)
//#define WDEBUG_CONE(world,location, direction, angle, length, color) if (DebugSettings::bEnableDebugDraw) DrawDebugCone(world, location, direction, length, angle, angle, 12, color, false, 1.0f)
//#define WDEBUG_CONE_TIME(world,location, direction, angle, length, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugCone(world, location, direction, length, angle, angle, 12, color, false, lifeTime)
//#define WDEBUG_RAY(world,startLocation, direction, length, color) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(world, startLocation, startLocation + direction * length, color, false, 1.0f)
//#define WDEBUG_RAY_TIME(world,startLocation, direction, length, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugLine(world, startLocation, startLocation + direction * length, color, false, lifeTime)
//#define WDEBUG_TEXT(world,location, message, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugString(world, location, message, nullptr, color, 1.0f, true)
//#define WDEBUG_TEXT_TIME(world,location, message, color, lifeTime) if (DebugSettings::bEnableDebugDraw) DrawDebugString(world, location, message, nullptr, color, lifeTime, true)
//#define WDEBUG_ARROW(world,startLocation, endLocation, arrowSize, color) if (DebugSettings::bEnableDebugDraw) DrawDebugDirectionalArrow(world, startLocation, endLocation, arrowSize, color)
*/

//Trace
#define LINETRACE_SINGLE(outHit,start, end) WORLD->LineTraceSingleByChannel(outHit,start,end,ECC_Visibility)
#define LINETRACE_SINGLE_CHANNEL(start,end, channel) FHitResult _result; WORLD->LineTraceSingleByChannel(_result,start,end,channel)
#define LINETRACE_SINGLE_HIT_CHANNEL(outHit,start, end, channel) WORLD->LineTraceSingleByChannel(outHit,start,end,channel)
#define LINETRACE_SINGLE_OBJECT(start, end, channel, debugType, outHit, traceColor, traceHitColor, drawTime) UKSL::LineTraceSingleForObjects(this, start, end, channel, false, {}, debugType, outHit, true, traceColor, traceHitColor, drawTime)
#define LINETRACE_MULTI(outHit,start, end) WORLD->LineTraceMultiByChannel(outHit,start,end,ECC_Visibility)
#define LINETRACE_MULTI_CHANNEL(start,end, channel) TArray<FHitResult> _result; WORLD->LineTraceMultiByChannel(_result,start,end,channel)
#define LINETRACE_MULTI_HIT_CHANNEL(outHit,start, end, channel) WORLD->LineTraceMultiByChannel(outHit,start,end,channel)

#define SPHERETRACE_SINGLE(start,end,radius,channel,actorToIgnore,outHit) UKSL::SphereTraceSingle(WORLD,start,end,radius,channel,true,actorToIgnore,EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_SINGLE_COMPLEX(start,end,radius,channel,actorToIgnore,outHit) UKSL::SphereTraceSingle(WORLD,start,end,radius,channel,true,actorToIgnore,EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_MULTI(start,end,radius,channel,outHit) UKSL::SphereTraceMulti(WORLD,start,end,radius,channel,true,{},EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_MULTI_COMPLEX(start,end,radius,channel,actorToIgnore,outHit) UKSL::SphereTraceMulti(WORLD,start,end,radius,channel,true,actorToIgnore,EDrawDebugTrace::ForOneFrame,outHit,true)
#define SPHERETRACE_MULTI_OBJECT(start,end,radius, channel, debugType, outHit, color, drawTime) UKSL::SphereTraceMultiForObjects(this, start, end, radius, channel, false, {}, debugType, outHit, true, color, FLinearColor::Green, drawTime)

//Inputs
#define USE_CONTROLLER CheckDevice(WORLD,EHardwareDevicePrimaryType::Gamepad)
#define USE_KEYBOARD CheckDevice(WORLD,EHardwareDevicePrimaryType::KeyboardAndMouse)