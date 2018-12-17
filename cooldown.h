#ifndef COOLDOWN_H
#define COOLDOWN_H
#include <QElapsedTimer>
#include <chrono>


class CoolDown
{
	bool started;
    QElapsedTimer timer;
    std::chrono::milliseconds timeout;
	std::chrono::milliseconds stopmem;
public:
    void setTimeout(std::chrono::milliseconds timeout);
	void interrupt();
	void start();
    void start(std::chrono::milliseconds timeout);
    bool isTimeout();
    CoolDown();
};

#endif // COOLDOWN_H
