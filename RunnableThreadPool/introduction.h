#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QRunnable>

class Introduction : public QRunnable
{
public:
    Introduction();

    void run();
};

#endif // INTRODUCTION_H
