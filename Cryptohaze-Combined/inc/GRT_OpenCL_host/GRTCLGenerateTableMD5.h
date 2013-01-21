/*
Cryptohaze GPU Rainbow Tables
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

#ifndef _GRTCLGENERATETABLEMD5_H
#define _GRTCLGENERATETABLEMD5_H

#include "GRT_Common/GRTCharsetSingle.h"
#include "GRT_OpenCL_host/GRTCLGenerateTable.h"

typedef uint32_t UINT4;

// This is a generic class for all hash types.  Tweak as needed.
class GRTCLGenerateTableMD5 : public GRTCLGenerateTable {
private:

    
public:
    // Default constructor
    GRTCLGenerateTableMD5();
    
    std::vector<std::string> getHashFileName();
    std::string getHashKernelName();
    std::string getKernelSourceString();

};

#endif
