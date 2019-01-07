#include "wordsplit.h"

#include "common/RCStringConvert.h"
#include "common/RCStringToken.h"
#include "common/RCStringUtilA.h"

BEGIN_NAMESPACE_RC

RCWordSplit::RCWordSplit()
{

}
RCWordSplit::~RCWordSplit()
{

}

bool RCWordSplit::Initialize()
{
    return m_wordExplain.Initialize();
}
void RCWordSplit::Uninitialize()
{
    m_wordExplain.Uninitialize();
}

bool RCWordSplit::SetDataByString(const RCString& srcString)
{
    m_dataSrc = "";
    if (srcString.empty())
    {
        return false;
    }
    m_dataSrc = RCStringConvert::ConvertUnicodeToUTF8(srcString);

    if (m_dataSrc.empty())
    {
        return false;
    }

    return true;
}

bool RCWordSplit::SetDataByFile(const RCString& filePath)
{
    m_dataSrc = "";
    bool isSuccess = false;
    HANDLE hFile = ::CreateFile(filePath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER fileSize = { 0 };
        ::GetFileSizeEx(hFile, &fileSize);
        ::SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

        BYTE* pData = new(std::nothrow) BYTE[fileSize.LowPart + 1];
        if (pData == NULL)
        {
            return false;
        }
        memset(pData, 0x00, fileSize.LowPart + 1);
        ULONG bytesRead = 0;
        ::ReadFile(hFile, pData, fileSize.LowPart, &bytesRead, NULL);
        ::CloseHandle(hFile);

        if (bytesRead == fileSize.QuadPart)
        {
            RCStringA dataSrc = (const char*)pData;
            m_dataSrc = RCStringConvert::ConvertUnicodeToUTF8(RCStringConvert::MultiByteToUnicodeString(dataSrc));
        }
        delete pData;
    }
    if (!m_dataSrc.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool RCWordSplit::ProcessData(RCVector<RCWORD_METRIC>& wordsInfo, const RCString& outFilePath)
{
    if (m_dataSrc.empty())
    {
        return false;
    }
    RCString outputFilePath = outFilePath;
    if (outFilePath.empty())
    {
        outputFilePath = _T("out.txt");
    }

    RCStringA outputStr;
    uint32_t length = m_dataSrc.length();
    const char* pSrc = m_dataSrc.c_str();
    char curWord[200] = { 0 };
    uint32_t curWordLength = 0;
    wordsInfo.clear();
    for (uint32_t i = 0; i < length; i++)
    {
        char curChar = pSrc[i];
        if (!IsWordsCharValid(curChar))
        {
            if (curWordLength)
            {
                RCWORD_METRIC wm;
                wm.m_word = curWord;
                wm.m_wordLength = curWordLength;
                wordsInfo.push_back(wm);

                outputStr += curWord;
 
                RCWordInfomation wi;
                if (m_wordExplain.GetWordInfo(wm.m_word, wi))
                {
                    outputStr += '[';
                    if (!wi.m_us_phonetic.empty())
                    {
                        outputStr += wi.m_us_phonetic;
                    }
                    else if (!wi.m_uk_phonetic.empty())
                    {
                        outputStr += wi.m_uk_phonetic;
                    }
                    else if (!wi.m_phonetic.empty())
                    {
                        outputStr += wi.m_phonetic;
                    }
                    else
                    {
                        outputStr += "x";
                    }
                    outputStr += ']';
                }
            }
            curWord[0] = '\0';
            curWordLength = 0;
            outputStr.append(1,curChar);
        }
        else
        {
            if (curWordLength < ((sizeof(curWord) / sizeof(char))-1))
            {
                curWord[curWordLength] = curChar;
                curWordLength++;
                curWord[curWordLength] = '\0';
            }
            else
            {
                return false;
            }
        }
    }
    WriteDataToOutput(outputFilePath, outputStr);
    return true;
}

bool RCWordSplit::WriteDataToOutput(const RCString& filePath,const RCStringA& output)
{
    bool ret = false;
    HANDLE hFile = ::CreateFile(filePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        DWORD dwWrited = 0;
        ::WriteFile(hFile, (LPCVOID)output.c_str(), output.length(), &dwWrited, NULL);
        ::CloseHandle(hFile);
        return true;
    }
    else
    {
        return false;
    }
}
bool RCWordSplit::IsWordsCharValid(char ch)
{
    char sz_lowercase[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    char sz_uppercase[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    char sz_symbol[] = {'\''};
    for (uint32_t i = 0; i < (sizeof(sz_lowercase) / sizeof(char)); i++)
    {
        if (sz_lowercase[i] == ch)
        {
            return true;
        }
    }
    for (uint32_t i = 0; i < (sizeof(sz_uppercase) / sizeof(char)); i++)
    {
        if (sz_uppercase[i] == ch)
        {
            return true;
        }
    }
    for (uint32_t i = 0; i < (sizeof(sz_symbol) / sizeof(char)); i++)
    {
        if (sz_symbol[i] == ch)
        {
            return true;
        }
    }
    return false;
}
END_NAMESPACE_RC
