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

#ifndef NPVR_OVR_MANAGER_H_
#define NPVR_OVR_MANAGER_H_

#include "OVR.h"
#include "OVR_CAPI.h"

namespace npvr
{
	class OVRManager
	{
		public:
			virtual ~OVRManager();
			static OVRManager *Instance();
			ovrHmd GetDevice() const; //ovrHmd is typedef of ovrHmdDesc*
			const ovrHmd GetDeviceInfo() const; //ovrHmdDesc is typedef of ovrHmd
			bool DevicePresent() const;
			ovrQuatf* GetOrientation() const;
			void ResetOrientation();
			ovrVector3f* OVRManager::GetPosition() const;
			ovrHmd OVRManager::GetConfiguration() const;

		private:
			OVRManager();
			void SetDevice(ovrHmd device);
			ovrHmd hmd_device_;

			ovrQuatf* defaultOrientation;
			ovrVector3f* defaultPosition;
	};
}

#endif  // NPVR_OVR_MANAGER_H_
