#pragma once

#include "Math/Math.h"
#include "ECS/Components.h"
#include "Animation/Interpolation.h"


namespace Core::ECS::Components {

    struct VirusComponent {
        Core::Math::Vec2 m_Start {};
        Core::Math::Vec2 m_End {};

        double m_Speed {1.0};

        Core::Animation::Interpolated<Core::Math::Vec2> m_CurrentPosition {};


        bool m_IsGoingFromStartToEnd {true};
        
        VirusComponent():
            m_Start{}, m_End{}, m_Speed{.5}, m_IsGoingFromStartToEnd{true}, m_CurrentPosition{{}, {}, 2.0}
        {};

        VirusComponent(const Core::Math::Vec2& start, const Core::Math::Vec2& end, double speed):
            m_Start{start}, m_End{end}, m_Speed{speed}, m_IsGoingFromStartToEnd{true}, m_CurrentPosition{start, end, 1.0 / speed}
        {};

        INIT_TYPE;

    };
}