/*
 *  Copyright (C) 2010-2011  Regents of the University of Michigan,
 *                           Hyun Min Kang, Matthew Flickenger, Matthew Snyder,
 *                           and Goncalo Abecasis
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "VcfFile.h"

VcfFile::VcfFile()
{
  myFilePtr = NULL;
  mySiteOnly = false;
}

VcfFile::~VcfFile()
{
  resetFile();
}


bool VcfFile::open(const char* filename, const char* mode)
{
    // Reset for any previously operated on files.
    resetFile();

    myFilePtr = ifopen(filename, mode);

    if(myFilePtr == NULL)
    {
        std::string errorMessage = "Failed to Open ";
        errorMessage += filename;
        errorMessage += " for ";
        errorMessage += mode;
        myStatus.setStatus(StatGenStatus::FAIL_IO, errorMessage.c_str());
        return(false);
    }

    return(true);
}

void VcfFile::close()
{
    resetFile();
}

void VcfFile::resetFile()
{
    // Close the file.
    if (myFilePtr != NULL)
    {
        // If we already have an open file, close it.
        ifclose(myFilePtr);
        myFilePtr = NULL;
    }
}