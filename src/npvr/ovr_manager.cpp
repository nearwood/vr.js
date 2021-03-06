/**
* Copyright 2013 Google Inc. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <npvr/ovr_manager.h>

using namespace npvr;

OVRManager *OVRManager::Instance()
{
	static OVRManager instance;
	return &instance;
}

OVRManager::OVRManager():
hmd_device_(NULL)
{
	ovr_Initialize(); //bool

	defaultOrientation = new ovrQuatf();
	defaultPosition = new ovrVector3f();

	int numHmds = ovrHmd_Detect();
	if (numHmds > 0)
	{
		ovrHmd device = ovrHmd_Create(0);
		if (device != NULL)
		{
			SetDevice(device);
		}
	}
}

OVRManager::~OVRManager()
{
	ovrHmd_Destroy(hmd_device_);
	ovr_Shutdown();
}

ovrHmd OVRManager::GetDevice() const
{
	return hmd_device_;
}

const ovrHmd OVRManager::GetDeviceInfo() const
{
	return hmd_device_;
}

void OVRManager::SetDevice(ovrHmd device)
{
	if (hmd_device_ == device)
	{
		return;
	}

	if (hmd_device_) {
		// Release existing device.
		ovrHmd_Destroy(hmd_device_);
		//delete sensor_fusion_;
	}
	if (!device) {
		return;
	}

	hmd_device_ = device;

	//returns bool
	ovrHmd_ConfigureTracking(hmd_device_, ovrTrackingCap_Orientation | 		ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position, 0);
}

bool OVRManager::DevicePresent() const {
	return hmd_device_ != NULL; //ovrHmd_Detect() > 0
}

ovrQuatf* OVRManager::GetOrientation() const
{
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd_device_, ovr_GetTimeInSeconds());

	if (ts.StatusFlags & (ovrStatus_OrientationTracked))
	{
		return &ts.HeadPose.ThePose.Orientation;
		//Posef pose = ts.HeadPose;
	} else {
		return defaultOrientation;
	}
}

void OVRManager::ResetOrientation()
{
	ovrHmd_RecenterPose(hmd_device_);
}

ovrVector3f* OVRManager::GetPosition() const
{
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd_device_, ovr_GetTimeInSeconds());

	if (ts.StatusFlags &  (ovrStatus_PositionTracked))
	{
		return &ts.HeadPose.ThePose.Position;
		//Posef pose = ts.HeadPose;
	} else {
		return defaultPosition; //TODO Use last position
	}
}

ovrHmd OVRManager::GetConfiguration() const
{
	ovrHmd test = hmd_device_;
	return test;
}