#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QObject>
#include <QThread>

class ProTreeThread : public QThread
{
    Q_OBJECT
public:
    ProTreeThread();

protected:
    virtual void run() override;
};

#endif // PROTREETHREAD_H
