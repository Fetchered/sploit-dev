/*
Cryptohaze Multiforcer & Wordyforcer - low performance GPU password cracking
Copyright (C) 2011  Bitweasil (http://www.cryptohaze.com/)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "MFN_CUDA_host/MFNHashTypePlainCUDA.h"
#include "CH_Common/CHHashImplementationMD5.h"


extern "C" cudaError_t MFNHashTypePlainCUDA_MD5_CopyValueToConstantById(
        uint32_t symbolId, void *hostDataAddress, size_t bytesToCopy);

extern "C" cudaError_t MFNHashTypePlainCUDA_MD5_LaunchKernel(uint32_t passwordLength, uint32_t Blocks, uint32_t Threads);

class MFNHashTypePlainCUDA_MD5 : public MFNHashTypePlainCUDA {

public:
    MFNHashTypePlainCUDA_MD5();
protected:
    // For reversing/finalizing
    CHHashImplementationMD5 MD5;

    std::vector<uint8_t> preProcessHash(std::vector<uint8_t> rawHash);
    
    std::vector<uint8_t> postProcessHash(std::vector<uint8_t> processedHash);

    void copyConstantDataToDevice();

    void launchKernel();

    /**
     * Prints debug data about the launch to verify the device has received
     * the same data.
     */
    void printLaunchDebugData();
};