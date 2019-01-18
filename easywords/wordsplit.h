/*****************************************************************************
*  ��Ȩ���У�C��2005-2017                                                   *
*  ��������Ȩ����                                                            *
******************************************************************************
*  ���� : ֣�ڳ�
*  �汾 : 1.0
*****************************************************************************/

#ifndef __RCWordSplit_h_
#define __RCWordSplit_h_ 1

#include "wordinfo.h"

#include "base/RCDefs.h"
#include "base/RCString.h"
#include "common/RCVector.h"

#include <map>

BEGIN_NAMESPACE_RC

/**
Just only support for multibytes encode style.
*/
struct RCWORD_METRIC
{
    RCStringA m_word;
    uint32_t m_wordLength;
};

class RCWordSplit
{
public:

    RCWordSplit();
    ~RCWordSplit();

    bool Initialize();
    void Uninitialize();

    bool SetDataByString(const RCStringA& srcString);

    bool SetDataByFile(const RCString& filePath);

    bool ProcessData(RCVector<RCWORD_METRIC>& wordsInfo,const RCString& outFilePath);

    bool IsWordsCharValid(char ch);

    bool WriteDataToOutput(const RCString& filePath, const RCStringA& output);

private:

    RCStringA m_dataSrc;

    RCVector<RCWORD_METRIC> m_wordsInfo;

    RCWordInfo m_wordExplain;
};
END_NAMESPACE_RC

#endif // __RCWordSplit_h_