#include "UltraSmartLog.h"
#include <QDateTime>

CUltraSmartLog::CUltraSmartLog()
{
    m_fileLog = NULL;
}

CUltraSmartLog::~CUltraSmartLog()
{

}

CUltraSmartLog *CUltraSmartLog::Instance()
{
    static CUltraSmartLog   clUltraSmartLog;
    return &clUltraSmartLog;
}

void CUltraSmartLog::LogOut(char *fmt, ...)
{
    char        acBuffer[256];
    char        acLogBuff[512];
    va_list     args;
    int         n;

    QString     strTemp = "";
    QDateTime   timeCurrent;

    memset(acBuffer, 0, sizeof(acBuffer));
    memset(acLogBuff, 0, sizeof(acLogBuff));

    va_start(args, fmt);
    n = vsnprintf(acBuffer, sizeof(acBuffer), fmt, args);
    va_end(args);

    timeCurrent = QDateTime::currentDateTime();

    strTemp = timeCurrent.toString("yyyy-MM-dd hh:mm:ss");
    snprintf(acLogBuff, sizeof(acLogBuff), "%s    %s", strTemp.toStdString().data(), acBuffer);

    emit UsHwLogoutSignal(acLogBuff);

    // 如果需要保存到文件，则写入文件
    if (NULL != m_fileLog)
    {
        strTemp = acLogBuff;
        strTemp += "\n";
        fwrite(strTemp.toStdString().data(), sizeof(char), strlen(strTemp.toStdString().data()), m_fileLog);
        fflush(m_fileLog);
    }
}

void CUltraSmartLog::ClearLog()
{
    emit UsHwClearLogSignal();
}

uint CUltraSmartLog::StartLogToFile(const char *pFilePath)
{
    m_fileLog = fopen(pFilePath, "at+");
    if (NULL == m_fileLog)
    {
        return -1;
    }

    return 0;
}

uint CUltraSmartLog::StopLogToFile()
{
    if (NULL != m_fileLog)
    {
        fclose(m_fileLog);
        m_fileLog = NULL;
    }

    return 0;
}

