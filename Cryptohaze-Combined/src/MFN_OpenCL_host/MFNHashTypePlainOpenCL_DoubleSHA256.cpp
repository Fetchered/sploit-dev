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

#include "MFN_OpenCL_host/MFNHashTypePlainOpenCL_DoubleSHA256.h"
#include "GRT_OpenCL_host/GRTCLUtils.h"
#include "MFN_Common/MFNDebugging.h"
#include "MFN_Common/MFNDefines.h"
#include "MFN_OpenCL_host/MFNOpenCLMetaprograms.h"
#include "MFN_Common/MFNCommandLineData.h"
#include "CH_Common/CHCharsetNew.h"

// Ugly hack for now.  If true, pulls the kernel into the binary.
#define RELEASE_KERNEL 1

#if RELEASE_KERNEL
extern char MFNHashTypePlainOpenCL_DoubleSHA256_source[];
extern char MFN_OpenCL_Common_source[];
extern char MFN_OpenCL_SHA256_source[];
extern char MFN_OpenCL_PasswordCopiers_source[];
extern char MFN_OpenCL_BIN2HEX_source[];
#endif


#define reverse(x)(x>>24)|((x<<8) & 0x00FF0000)|((x>>8) & 0x0000FF00)|(x<<24);


MFNHashTypePlainOpenCL_DoubleSHA256::MFNHashTypePlainOpenCL_DoubleSHA256() :  MFNHashTypePlainOpenCL(32) {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::MFNHashTypePlainOpenCL_DoubleSHA256()\n");
    // Reverse the hash in the processing steps for hash matching.
    this->HashIsBigEndian = 1;
}

void MFNHashTypePlainOpenCL_DoubleSHA256::launchKernel() {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::launchKernel()\n");
    cl_event kernelLaunchEvent;
    cl_int errorCode;
    size_t numberWorkgroups;
    size_t numberWorkitems;

    numberWorkgroups = this->GPUBlocks * this->GPUThreads;
    numberWorkitems = this->GPUThreads;

    
    klaunch_printf("T %d: Platform/Device: %d/%d\n", this->threadId, this->openCLPlatformId, this->gpuDeviceId);
    klaunch_printf("T %d: Workgroups/Workitems: %d/%d\n", this->threadId, numberWorkgroups, numberWorkitems);

    // Copy the per-step value to the kernel
    errorCode = clSetKernelArg (this->HashKernel, 14, sizeof(cl_uint), &this->perStep);
    if (errorCode != CL_SUCCESS) {
        printf("Error 1: %s\n", print_cl_errstring(errorCode));
        exit(1);
    }

    errorCode = clEnqueueNDRangeKernel(this->OpenCL->getCommandQueue(),
            this->HashKernel,
            1 /* numDims */,
            NULL /* offset */,
            &numberWorkgroups,
            &numberWorkitems,
            NULL, NULL,
            &kernelLaunchEvent);
    
    if (errorCode != CL_SUCCESS) {
        printf("Error 2: %s\n", print_cl_errstring(errorCode));
        exit(1);
    }

    if (clWaitForEvents(1, &kernelLaunchEvent) != CL_SUCCESS) {
        printf("\nError on wait for event!\n");
        fflush(stdout);
    };
    // Release the event to prevent memory leaks.
    clReleaseEvent(kernelLaunchEvent);
}


std::vector<uint8_t> MFNHashTypePlainOpenCL_DoubleSHA256::preProcessHash(std::vector<uint8_t> rawHash) {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::preProcessHash()\n");
    
    uint32_t *hash32 = (uint32_t *)&rawHash[0];
    
    hash32[0] = reverse(hash32[0]);
    hash32[1] = reverse(hash32[1]);
    hash32[2] = reverse(hash32[2]);
    hash32[3] = reverse(hash32[3]);
    hash32[4] = reverse(hash32[4]);
    hash32[5] = reverse(hash32[5]);
    hash32[6] = reverse(hash32[6]);
    hash32[7] = reverse(hash32[7]);
    
    return rawHash;
}

std::vector<uint8_t> MFNHashTypePlainOpenCL_DoubleSHA256::postProcessHash(std::vector<uint8_t> processedHash) {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::postProcessHash()\n");

    uint32_t *hash32 = (uint32_t *)&processedHash[0];
    
    hash32[0] = reverse(hash32[0]);
    hash32[1] = reverse(hash32[1]);
    hash32[2] = reverse(hash32[2]);
    hash32[3] = reverse(hash32[3]);
    hash32[4] = reverse(hash32[4]);
    hash32[5] = reverse(hash32[5]);
    hash32[6] = reverse(hash32[6]);
    hash32[7] = reverse(hash32[7]);

    return processedHash;
}

void MFNHashTypePlainOpenCL_DoubleSHA256::copyConstantDataToDevice() {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::copyConstantDataToDevice()\n");

    cl_int errorCode;

    
    // Begin copying constant data to the device.
    errorCode = clEnqueueWriteBuffer (this->OpenCL->getCommandQueue(),
            this->DeviceBitmap8kb_Address,
            CL_TRUE /* blocking write */,
            0 /* offset */,
            8192 /* bytes to copy */,
            (void *)&this->sharedBitmap8kb_a[0],
            NULL, NULL, NULL /* event list stuff */);
    if (errorCode != CL_SUCCESS) {
        printf("Error: %s\n", print_cl_errstring(errorCode));
        exit(1);
    }
    
    errorCode = clEnqueueWriteBuffer (this->OpenCL->getCommandQueue(),
            this->DeviceBitmap16kb_Address,
            CL_TRUE /* blocking write */,
            0 /* offset */,
            16384 /* bytes to copy */,
            (void *)&this->sharedBitmap16kb_a[0],
            NULL, NULL, NULL /* event list stuff */);
    if (errorCode != CL_SUCCESS) {
        printf("Error: %s\n", print_cl_errstring(errorCode));
        exit(1);
    }

    errorCode = clEnqueueWriteBuffer (this->OpenCL->getCommandQueue(),
            this->DeviceBitmap32kb_Address,
            CL_TRUE /* blocking write */,
            0 /* offset */,
            32768 /* bytes to copy */,
            (void *)&this->sharedBitmap32kb_a[0],
            NULL, NULL, NULL /* event list stuff */);
    if (errorCode != CL_SUCCESS) {
        printf("Error: %s\n", print_cl_errstring(errorCode));
        exit(1);
    }
    
    errorCode = clEnqueueWriteBuffer (this->OpenCL->getCommandQueue(),
            this->DeviceBitmap256kb_a_Address,
            CL_TRUE /* blocking write */,
            0 /* offset */,
            256*1024 /* bytes to copy */,
            (void *)&this->globalBitmap256kb_a[0],
            NULL, NULL, NULL /* event list stuff */);
    if (errorCode != CL_SUCCESS) {
        printf("Error: %s\n", print_cl_errstring(errorCode));
        exit(1);
    }
    
    // Copy the values into a variable that can be accessed as a pointer.
    uint64_t localNumberHashes = this->activeHashesProcessed.size();
    uint64_t localNumberThreads = this->TotalKernelWidth;
    
    errorCode = 0;
    errorCode |= clSetKernelArg (this->HashKernel,  0, sizeof(cl_mem), &this->DeviceForwardCharsetAddress);
    errorCode |= clSetKernelArg (this->HashKernel,  1, sizeof(cl_mem), &this->DeviceReverseCharsetAddress);
    errorCode |= clSetKernelArg (this->HashKernel,  2, sizeof(cl_mem), &this->DeviceCharsetLengthsAddress);
    if (this->sharedBitmapSize == 8) {
        errorCode |= clSetKernelArg (this->HashKernel,  3, sizeof(cl_mem), &this->DeviceBitmap8kb_Address);
    } else if (this->sharedBitmapSize == 16) {
        errorCode |= clSetKernelArg (this->HashKernel,  3, sizeof(cl_mem), &this->DeviceBitmap16kb_Address);
    } else if (this->sharedBitmapSize == 32) {
        errorCode |= clSetKernelArg (this->HashKernel,  3, sizeof(cl_mem), &this->DeviceBitmap32kb_Address);
    } else {
        printf("Error: Invalid shared bitmap size!  Must be 8, 16, 32\n");
        exit(1);
    }
    
    errorCode |= clSetKernelArg (this->HashKernel,  4, sizeof(cl_ulong), &localNumberHashes);
    errorCode |= clSetKernelArg (this->HashKernel,  5, sizeof(cl_mem), &this->DeviceHashlistAddress);
    errorCode |= clSetKernelArg (this->HashKernel,  6, sizeof(cl_mem), &this->DeviceFoundPasswordsAddress);
    errorCode |= clSetKernelArg (this->HashKernel,  7, sizeof(cl_mem), &this->DeviceSuccessAddress);

    errorCode |= clSetKernelArg (this->HashKernel,  8, sizeof(cl_mem), &this->DeviceBitmap128mb_a_Address);
    errorCode |= clSetKernelArg (this->HashKernel,  9, sizeof(cl_mem), &this->DeviceBitmap128mb_b_Address);
    errorCode |= clSetKernelArg (this->HashKernel, 10, sizeof(cl_mem), &this->DeviceBitmap128mb_c_Address);
    errorCode |= clSetKernelArg (this->HashKernel, 11, sizeof(cl_mem), &this->DeviceBitmap128mb_d_Address);

    errorCode |= clSetKernelArg (this->HashKernel, 12, sizeof(cl_mem), &this->DeviceStartPointAddress);
    errorCode |= clSetKernelArg (this->HashKernel, 13, sizeof(cl_ulong), &localNumberThreads);
    
    errorCode |= clSetKernelArg (this->HashKernel, 15, sizeof(cl_mem), &this->DeviceStartPasswords32Address);
    errorCode |= clSetKernelArg (this->HashKernel, 16, sizeof(cl_mem), &this->DeviceBitmap256kb_a_Address);
    

    if (errorCode != CL_SUCCESS) {
        printf("Thread %d, dev %d: OpenCL error 5: %s. Exiting.\n",
                this->threadId, this->gpuDeviceId, print_cl_errstring(errorCode));
        exit(1);
    }
}

std::vector<std::string> MFNHashTypePlainOpenCL_DoubleSHA256::getHashFileNames() {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::getHashFileNames()\n");
    
    std::vector<std::string> returnHashFilenames;

#if !RELEASE_KERNEL    
    std::string hashFilename;
    
    hashFilename = "./src/MFN_OpenCL_device/MFNHashTypePlainOpenCL_DoubleSHA256.cl";
    returnHashFilenames.push_back(hashFilename);
#endif
    return returnHashFilenames;
}

std::string MFNHashTypePlainOpenCL_DoubleSHA256::getKernelSourceString() {
    std::string ReturnString;
    
#if RELEASE_KERNEL
    ReturnString += std::string(MFN_OpenCL_Common_source);
    ReturnString += std::string(MFN_OpenCL_SHA256_source);
    ReturnString += std::string(MFN_OpenCL_PasswordCopiers_source);
    ReturnString += std::string(MFN_OpenCL_BIN2HEX_source);
    ReturnString += std::string(MFNHashTypePlainOpenCL_DoubleSHA256_source);
#endif
    
    return ReturnString;
}

std::string MFNHashTypePlainOpenCL_DoubleSHA256::getHashKernelName() {
    trace_printf("MFNHashTypePlainOpenCL_DoubleSHA256::getHashKernelName()\n");
    
    std::string hashKernel = "MFNHashTypePlainOpenCL_DoubleSHA256";
    return hashKernel;
}

std::string MFNHashTypePlainOpenCL_DoubleSHA256::getDefineStrings() {
    std::string additionalDefines;
    MFNOpenCLMetaprograms DefineGen;
    int numberBitmaps = 0;
        
    int bitmapAValid = 0;
    int bitmapBValid = 0;
    int bitmapCValid = 0;
    int bitmapDValid = 0;
 
    if (this->isSingleCharset) {
        additionalDefines += 
                DefineGen.makePasswordNoMemSingleIncrementorsBE(
                this->passwordLength, this->VectorWidth, 
                this->Charset->getCharset());
    } else {
        additionalDefines += 
                DefineGen.makePasswordNoMemMultipleIncrementorsBE(
                this->passwordLength, this->VectorWidth, 
                this->Charset->getCharset());
    }
    
    if (this->DeviceBitmap128mb_a_Address != 0) {
        numberBitmaps++;
        bitmapAValid = 1;
    }
    if (this->DeviceBitmap128mb_b_Address != 0) {
        numberBitmaps++;
        bitmapBValid = 1;
    }
    if (this->DeviceBitmap128mb_c_Address != 0) {
        numberBitmaps++;
        bitmapCValid = 1;
    }
    if (this->DeviceBitmap128mb_d_Address != 0) {
        numberBitmaps++;
        bitmapDValid = 1;
    }

    klaunch_printf("numberBitmaps: %d\n", numberBitmaps);

    //additionalDefines += DefineGen.makeBitmapLookup(this->VectorWidth, numberBitmaps, "CheckPassword256");
    additionalDefines += 
        DefineGen.makeBitmapLookupEarlyOut(this->VectorWidth, 
            "CheckPassword256BE",
            'a', bitmapAValid, 
            'b', bitmapBValid, "",
            'c', bitmapCValid, "",
            'd', bitmapDValid, "",
            1);

    return additionalDefines;
}

