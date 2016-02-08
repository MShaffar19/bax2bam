// Copyright (c) 2014-2015, Pacific Biosciences of California, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted (subject to the limitations in the
// disclaimer below) provided that the following conditions are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//  * Neither the name of Pacific Biosciences nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY PACIFIC
// BIOSCIENCES AND ITS CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL PACIFIC BIOSCIENCES OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// Author: Derek Barnett

#ifndef CCSCONVERTER_H
#define CCSCONVERTER_H

#include "ConverterBase.h"
#include "CCSSequence.hpp"
#include "HDFCCSReader.hpp"

class CcsConverter : public ConverterBase<CCSSequence, HDFCCSReader<CCSSequence>>
{
private:
    typedef HDFCCSReader<CCSSequence> HdfCcsReader;

public:
    CcsConverter(Settings& settings);
    ~CcsConverter(void);

protected:
    bool ConvertFile(HdfCcsReader* reader,
                     PacBio::BAM::BamWriter* writer);
    bool ConvertFile(HdfCcsReader* reader,
                     PacBio::BAM::BamWriter* writer,
                     PacBio::BAM::BamWriter* scrapsWriter);
    void SetSequenceAndQualities(PacBio::BAM::BamRecordImpl* bamRecord,
                                 const CCSSequence& smrtRecord,
                                 const int start,
                                 const int end);
    void AddRecordName(PacBio::BAM::BamRecordImpl* bamRecord,
                       const UInt holeNumber,
                       const int start,
                       const int end);
    void AddModeTags(PacBio::BAM::TagCollection* tags,
                     const CCSSequence& smrtRecord,
                     const int start,
                     const int end);
    HdfCcsReader* InitHdfReader(void);
    std::string HeaderReadType(void) const;
    std::string ScrapsReadType(void) const;
    std::string OutputFileSuffix(void) const;
    std::string ScrapsFileSuffix(void) const;

protected:
    PacBio::BAM::QualityValues recordQVs_;
};

#endif // CCSCONVERTER_H