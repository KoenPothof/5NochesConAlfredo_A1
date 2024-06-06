#include "TimerComponent.h"

float m_time_seconds;
float m_time_minutes;

TimerComponent::TimerComponent()
{
	m_time_seconds = 0.0f;
    m_time_minutes = 0.0f;
}

TimerComponent::~TimerComponent()
{
}

void TimerComponent::Update(float deltaTime)
{
    sleep(1);
    m_time_seconds++;

    if (m_time_seconds == 60) {
        m_time_minutes++;

        m_time_seconds = 0;
    }
}

void TimerComponent::Reset()
{
	m_time_seconds = 0.0f;
	m_time_minutes = 0.0f;
}

float TimerComponent::GetTime()
{
	return m_time_seconds, m_time_minutes;
}
