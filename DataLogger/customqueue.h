#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H

#include <QByteArray>
#include <QSemaphore>
#include <QMutex>
#include <QQueue>

template <class T, int SIZE = 1024>
class CustomQueue
{
public:
    CustomQueue(int size = SIZE);
    void PutQueue(const T &item);
    T GetQueue();
    T Peek();
    bool IsEmpty() const { return m_queue.count() == 0; }
    int Count() const { return m_queue.count(); }
    void Clear() { m_queue.clear(); }

private:
    QQueue<T> m_queue;
    QSemaphore m_semProducer;
    QSemaphore m_semConsumer;
    QMutex m_mutex;
    int m_size;
};

template <class T, int SIZE>
CustomQueue<T, SIZE>::CustomQueue(int size)
    : m_semProducer(size), m_semConsumer(0), m_size(size)
{
}

template <class T, int SIZE>
void CustomQueue<T, SIZE>::PutQueue(const T &item)
{
    m_semProducer.acquire();
    m_mutex.lock();
    m_queue.enqueue(item);
    m_mutex.unlock();
    m_semConsumer.release();
}

template <class T, int SIZE>
T CustomQueue<T, SIZE>::GetQueue()
{
    T item;
    m_semConsumer.acquire();
    m_mutex.lock();
    item = m_queue.dequeue();
    m_mutex.unlock();
    m_semProducer.release();

    return item;
}

template <class T, int SIZE>
T CustomQueue<T, SIZE>::Peek()
{
    T item;
    m_semConsumer.acquire();
    m_mutex.lock();
    item = m_queue.head();
    m_mutex.unlock();
    m_semProducer.release();

    return item;
}

#endif // CUSTOMQUEUE_H
