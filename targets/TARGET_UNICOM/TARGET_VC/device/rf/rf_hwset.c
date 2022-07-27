/*
 * Copyright (c) 2021 Vertexcom Technologies, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "rf_hwset.h"

rf_hwset_t rf_hwset = {
    .mSeriesNumber = 1234,
    .mDate = 20180425,
    .mFrequency = 915000000,
    .mXtalOffset = 128,
    .mPaSel = 1,
    .mTxPower = 20,
    .mTxPowerCalibOffset = 0,
    .mRssiOffset = 0,
    .mFec = 0,
    .mRfTestMode = 0,
    .mTempOffset = 0,
    .mELNARssiOffset = 0,
    .mFrontEndStateBits = 0,
    .mChipId = 0,
    .mBoardId = 0,
    .mCcaThreshold = -112,
    .mFec = 0,
    .mRfTestMode = 0,
    .mTempOffset = 0,
    .mCal[0] = 0xc8ffff,
    .mCal[1] = 0xffff0002,
    .mCal[2] = 0xdc438,
    .mCal[3] = 0x3200c8,
    .mCal[4] = 0x1810000,
    .mCal[5] = 0,
    .mCal[6] = 0,
    .mCal[7] = 0,
    .mCal[8] = 0,
    .mCal[9] = 0,
    .mCal[10] = 0,
    .mCal[11] = 0,
    .mCal[12] = 0x726556ff,
    .mCal[13] = 0x43786574,
    .mCal[14] = 0xff006d6f,
    .mCal[15] = 0xffffffff,
};
