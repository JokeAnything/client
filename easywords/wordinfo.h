/*****************************************************************************
*  ��Ȩ���У�C��2005-2017���Ϻ�������������Ƽ����޹�˾                        *
*  ��������Ȩ����                                                            *
******************************************************************************
*  ���� : ֣�ڳ�
*  �汾 : 3.4
*****************************************************************************/

#ifndef __RCWordInfo_h_
#define __RCWordInfo_h_ 1

#include "base/RCDefs.h"
#include "base/RCString.h"
#include "common/RCVector.h"
#include <map>

BEGIN_NAMESPACE_RC

struct RCWordInfomation
{
    RCStringA m_word;
    RCStringA m_us_phonetic;
    RCStringA m_uk_phonetic;
    RCStringA m_phonetic;
};
class RCWordInfo
{
public:

    RCWordInfo();
    ~RCWordInfo();

    bool Initialize();
    void Uninitialize();

    bool GetWordInfo(const RCStringA& word, RCWordInfomation& wordInfo);

private:

};
END_NAMESPACE_RC

#endif // __RCWordInfo_h_