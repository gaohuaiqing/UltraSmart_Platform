#ifndef CULTRASMARTLOG_H
#define CULTRASMARTLOG_H

#include <QObject>
#include <QString>

class CUltraSmartLog : public QObject
{
    Q_OBJECT

public:
    explicit CUltraSmartLog();
    virtual ~CUltraSmartLog();

    static CUltraSmartLog *Instance();

    void LogOut(char *fmt, ...);
    void ClearLog();
    uint StartLogToFile(const char *pFilePath);
    uint StopLogToFile();

private:
    FILE    *m_fileLog;

signals:
    void UsHwLogoutSignal(QString strLog);
    void UsHwClearLogSignal();
};

#define Logout      CUltraSmartLog::Instance()->LogOut
#define CleanLog    CUltraSmartLog::Instance()->ClearLog

#endif // CULTRASMARTLOG_H
