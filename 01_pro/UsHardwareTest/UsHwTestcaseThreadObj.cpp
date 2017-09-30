#include "UsHwTestcaseThreadObj.h"

CUsHwTestcaseThreadObj::CUsHwTestcaseThreadObj()
{

}

uint CUsHwTestcaseThreadObj::UsHwStartTest()
{
    uint    uiRet = 0;

    uiRet = m_pwgtTestcase->UsHwStartTest();
    emit UsHwSetTestcaseResultSignal(m_pitemTestcaseResult, uiRet);

    return uiRet;
}

