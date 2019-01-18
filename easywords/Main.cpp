#include <stdio.h>
#include <Windows.h>
#include "wordsplit.h"
#include "wordinfo.h"

BEGIN_NAMESPACE_RC
void TestProc()
{
    RCWordSplit spl;
    spl.Initialize();
    spl.SetDataByFile(_T("kungfupanda_s1-2.txt"));
    RCVector<RCWORD_METRIC> result;
    spl.ProcessData(result,_T("kungfupanda_s1-2_result.txt"));
    spl.Uninitialize();
}
END_NAMESPACE_RC


int main()
{
    RC::TestProc();
    return 0;
}