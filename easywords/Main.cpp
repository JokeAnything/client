#include <stdio.h>
#include <Windows.h>
#include "wordsplit.h"
#include "wordinfo.h"

BEGIN_NAMESPACE_RC
void TestProc()
{
    RCWordSplit spl;
    spl.Initialize();
    //RCString str = _T("The group performs songs like \"We're Not Gonna Take It\" by the band Twisted Sister and \"Rock and Roll All Nite\" by KISS in their one of a kind style.");
    //spl.SetDataByString(str);

    spl.SetDataByFile(_T("kungfupanda.txt"));
    RCVector<RCWORD_METRIC> result;
    spl.ProcessData(result,_T("result.txt"));
    spl.Uninitialize();

    //RCWordInfo wordInfo;
    //RCWordInfomation info;
    //wordInfo.Initialize();
    //wordInfo.GetWordInfo("love", info);
    //wordInfo.Uninitialize();
}
END_NAMESPACE_RC


int main()
{
    RC::TestProc();
    return 0;
}