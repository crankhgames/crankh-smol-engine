#pragma once


namespace Core::Animation {

    template <typename T>
    class Interpolated{
    private:
        T m_Start {};
        T m_End {};

        double m_Duration {1.0};
        double m_Timer {};

        bool m_HasEnded{true};

    public:
        Interpolated():
            m_Start{}, m_End{}, m_Duration{1.0}, m_Timer{0.0}, m_HasEnded{false}
        {};
        Interpolated(const T& start, const T& end, double duration):
            m_Start{start}, m_End{end}, m_Duration{duration}, m_Timer{0.0}, m_HasEnded{false}
        {};

        void increment(double amount){
            if (!m_HasEnded){
                m_Timer += amount;
                if (m_Timer > m_Duration) {
                    m_Timer = m_Duration;
                    m_HasEnded = true;
                }
            }
        }

        T getValue() const{
            return m_Start + (m_End - m_Start) * m_Timer / m_Duration;
        }

        operator T() const {return getValue();}

        void setTarget(const T& target){
            m_Start = getValue();
            m_End = target;
            m_Timer = 0.0;
            m_HasEnded = false;
        }

        bool hasEnded() const {
            return m_HasEnded;
        }

    };
}