#include "wordinfo.h"

#include "common/RCStringConvert.h"
#include "common/RCStringToken.h"
#include "common/RCStringUtilA.h"
#include "web/post/RCWebPost.h"
#include "json/json.h"

BEGIN_NAMESPACE_RC

RCWordInfo::RCWordInfo()
{

}
RCWordInfo::~RCWordInfo()
{

}

bool RCWordInfo::Initialize()
{
    return true;
}
void RCWordInfo::Uninitialize()
{
    return;
}

bool RCWordInfo::GetWordInfo(const RCStringA& word, RCWordInfomation& wordInfo)
{
    if (word.empty())
    {
        return false;
    }
    RCWebPost postObj;
    RCString query = RCStringConvert::ConvertUTF8ToUnicode(word);
    postObj.AddPostParam(_T("query"), query);

    RCStringA respond;
    if (postObj.PostData(_T("mywebsvr.com"), _T("/transapi/transapi.php"), respond))
    {
        printf("%s\n", respond.c_str());

        Json::Reader jsonReader;
        Json::Value  jsonValue;
        if (!jsonReader.parse(respond, jsonValue) ||
            jsonValue.isNull() ||
            !jsonValue.isObject())
        {
            return false;
        }
        if (!jsonValue["error"].isNull())
        {
            RCStringA error = jsonValue["error"].asString();
            if (error != "0")
            {
                return false;
            }
        }
        if (!jsonValue["query"].isNull())
        {
            wordInfo.m_word = jsonValue["query"].asString();
        }
        if (!jsonValue["us_phonetic"].isNull())
        {
            wordInfo.m_us_phonetic = jsonValue["us_phonetic"].asString();
        }
        if (!jsonValue["phonetic"].isNull())
        {
            wordInfo.m_phonetic = jsonValue["phonetic"].asString();
        }
        if (!jsonValue["uk_phonetic"].isNull())
        {
            wordInfo.m_uk_phonetic = jsonValue["uk_phonetic"].asString();
        }
        return true;
    }
    else
    {
        return false;
    }
    return true;
}


END_NAMESPACE_RC
