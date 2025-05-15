// Thorlabs Kinesis device adapter for Micro-Manager
// Author: Mark A. Tsuchida
//
// Copyright 2019-2020 The Board of Regents of the University of Wisconsin
// System
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "KCubeStepper.h"

#include "DLLAccess.h"

#include "Thorlabs.MotionControl.KCube.StepperMotor.h"


static DLLAccess kinesisDll{ "Thorlabs.MotionControl.KCube.StepperMotor.dll" };


bool
KCubeStepperAccess::IsKinesisDriverAvailable() {
    return kinesisDll.IsValid();
}


short
KCubeStepperAccess::Kinesis_Open() {
    STATIC_DLL_FUNC(kinesisDll, SCC_Open, func);
    return func(CSerialNo());
}


short
KCubeStepperAccess::Kinesis_Close() {
    STATIC_DLL_FUNC(kinesisDll, SCC_Close, func);
    func(CSerialNo());
    return 0;
}


short
KCubeStepper::Kinesis_RequestSettings() {
    STATIC_DLL_FUNC(kinesisDll, SCC_RequestSettings, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_RequestStatusBits() {
    STATIC_DLL_FUNC(kinesisDll, SCC_RequestStatusBits, func);
    return func(CSerialNo());
}


bool
KCubeStepper::Kinesis_StartPolling(int intervalMs) {
    STATIC_DLL_FUNC(kinesisDll, SCC_StartPolling, func);
    return func(CSerialNo(), intervalMs);
}


void
KCubeStepper::Kinesis_StopPolling() {
    STATIC_DLL_FUNC(kinesisDll, SCC_StopPolling, func);
    func(CSerialNo());
}


short
KCubeStepper::Kinesis_GetHardwareInfo(char* modelNo, DWORD sizeOfModelNo,
    WORD* type, WORD* numChannels, char* notes, DWORD sizeOfNotes,
    DWORD* firmwareVersion, WORD* hardwareVersion, WORD* modificationState) {

    STATIC_DLL_FUNC(kinesisDll, SCC_GetHardwareInfo, func);
    return func(CSerialNo(), modelNo, sizeOfModelNo,
        type, numChannels, notes, sizeOfNotes, firmwareVersion,
        hardwareVersion, modificationState);
}


DWORD
KCubeStepper::Kinesis_GetStatusBits() {
    STATIC_DLL_FUNC(kinesisDll, SCC_GetStatusBits, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_EnableChannel() {
    STATIC_DLL_FUNC(kinesisDll, SCC_EnableChannel, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_DisableChannel() {
    STATIC_DLL_FUNC(kinesisDll, SCC_DisableChannel, func);
    return func(CSerialNo());
}


int
KCubeStepper::Kinesis_GetMotorTravelMode() {
    STATIC_DLL_FUNC(kinesisDll, SCC_GetMotorTravelMode, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_SetMotorTravelMode(int mode) {
    STATIC_DLL_FUNC(kinesisDll, SCC_SetMotorTravelMode, func);
    return func(CSerialNo(), static_cast<MOT_TravelModes>(mode));
}


short
KCubeStepper::Kinesis_ResetRotationModes() {
    STATIC_DLL_FUNC(kinesisDll, SCC_ResetRotationModes, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_SetRotationModes(int mode, int direction) {
    STATIC_DLL_FUNC(kinesisDll, SCC_SetRotationModes, func);
    return func(CSerialNo(), static_cast<MOT_MovementModes>(mode),
        static_cast<MOT_MovementDirections>(direction));
}

short
KCubeStepper::Kinesis_SetHomingParams(int direction, int limitSwitchMode, int offsetDistance, int velocity)
{
    STATIC_DLL_FUNC(kinesisDll, SCC_SetHomingParamsBlock, func);
    MOT_HomingParameters params;
    params.direction = (MOT_TravelDirection)direction;
    params.limitSwitch = (MOT_HomeLimitSwitchDirection)limitSwitchMode;
    params.offsetDistance = offsetDistance;
    params.velocity = velocity;

    return func(CSerialNo(), &params);
}

short
KCubeStepper::Kinesis_SetLimitSwitchParams(int ccwHardwareLimitMode, int ccwSoftwareLimitPosition,
    int cwHardwareLimitMode, int cwSoftwareLimitPosition, int softwareLimitMode)
{
    STATIC_DLL_FUNC(kinesisDll, SCC_SetLimitSwitchParams, func);
    return func(CSerialNo(), (MOT_LimitSwitchModes)cwHardwareLimitMode, (MOT_LimitSwitchModes)ccwHardwareLimitMode, cwSoftwareLimitPosition, ccwSoftwareLimitPosition, (MOT_LimitSwitchSWModes)softwareLimitMode);
}


short
KCubeStepper::Kinesis_RequestPosition() {
    STATIC_DLL_FUNC(kinesisDll, SCC_RequestPosition, func);
    return func(CSerialNo());
}


int
KCubeStepper::Kinesis_GetPosition() {
    STATIC_DLL_FUNC(kinesisDll, SCC_GetPosition, func);
    return func(CSerialNo());
}


long
KCubeStepper::Kinesis_GetPositionCounter() {
    STATIC_DLL_FUNC(kinesisDll, SCC_GetPositionCounter, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_MoveToPosition(int index) {
    STATIC_DLL_FUNC(kinesisDll, SCC_MoveToPosition, func);
    return func(CSerialNo(), index);
}


bool
KCubeStepper::Kinesis_CanHome() {
    STATIC_DLL_FUNC(kinesisDll, SCC_CanHome, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_Home() {
    STATIC_DLL_FUNC(kinesisDll, SCC_Home, func);
    return func(CSerialNo());
}


short
KCubeStepper::Kinesis_GetRealValueFromDeviceUnit(int deviceUnits,
    double* realValue, int unitType) {

    STATIC_DLL_FUNC(kinesisDll, SCC_GetRealValueFromDeviceUnit, func);
    return func(CSerialNo(), deviceUnits, realValue, unitType);
}


short
KCubeStepper::Kinesis_GetDeviceUnitFromRealValue(double realValue,
    int* deviceUnits, int unitType) {

    STATIC_DLL_FUNC(kinesisDll, SCC_GetDeviceUnitFromRealValue, func);
    return func(CSerialNo(), realValue, deviceUnits, unitType);
}
