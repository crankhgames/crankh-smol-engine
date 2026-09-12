#pragma once

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <string_view>

#include "ECS/Entity.h"


namespace Core::Animation {


    class Animation {

    private:
        std::unordered_map<int, std::function<void(Core::ECS::Entity)>> m_FrameActivators {};
        int m_CurrentFrame {};
        int m_TotalFrames {};

        double m_CurrentTimer{};
        double m_Duration {1.0};

        double m_DelayBtwFrames{};

        bool m_Looping {false};
        bool m_Stopped {false};

        Core::ECS::Entity m_Entity {};

    public:
        Animation():
            m_FrameActivators{}, m_TotalFrames{1}, m_Duration{1.0}, m_DelayBtwFrames{m_Duration / m_TotalFrames}, m_Looping{false}, m_Stopped{false}, m_Entity{}
        {};

        Animation(const std::unordered_map<int, std::function<void(Core::ECS::Entity)>>& frameActivators, int totalFrames, double duration, bool looping, Core::ECS::Entity entity):
            m_FrameActivators{frameActivators},  m_TotalFrames{totalFrames}, m_Duration{duration}, m_DelayBtwFrames{duration / totalFrames}, m_Looping{looping}, m_Stopped{false}, m_Entity{entity}
        {};

        void reset(){
            m_CurrentFrame = 0;
            m_CurrentTimer = 0.0;
            m_Stopped = false;
            executeFrame();
        }

        bool isLooping() const {return m_Looping;}
        bool hasStopped() const {return m_Stopped;}

        void executeFrame(){
            m_FrameActivators[m_CurrentFrame](m_Entity);
        }

        void update(double ts){


            if (m_Stopped){
                return;
            }
            
            m_CurrentTimer += ts;
            if (m_CurrentTimer >= m_DelayBtwFrames){

                ++m_CurrentFrame;

                if (m_CurrentFrame >= m_TotalFrames){
                    if (m_Looping){
                        m_CurrentFrame = 0;
                    }
                    else{
                        stop();
                        return;
                    }
                }

                m_CurrentTimer = 0.0;
                
                if (m_FrameActivators.find(m_CurrentFrame) != m_FrameActivators.end()){
                    executeFrame();
                }

                
            }
        }

        void stop(){
            m_Stopped = true;
        }
    
    };


    class Animator{
    private:
        std::unordered_map<std::string, Animation> m_Animations{};
        //std::unordered_map<std::string, std::vector<std::pair<std::function<bool()>, std::string>>> m_TransitionChecks{};
        std::string m_CurrentAnimation {};


    public:
        Animator():
            m_Animations{}, m_CurrentAnimation{}
        {};

// ADD THIS TYPE
//const std::unordered_map<std::string, std::vector<std::pair<std::function<bool()>, std::string>>>& transitionChecks,
        Animator(const std::unordered_map<std::string, Animation>& animations,  std::string_view currentAnimation):
            m_Animations{animations}, m_CurrentAnimation{currentAnimation}
        {};

        void switchAnimation(std::string_view animationName){
            m_Animations[m_CurrentAnimation].stop();
            m_CurrentAnimation = animationName;
            m_Animations[m_CurrentAnimation].reset();
        }

        void update(double ts){
            
            //for (auto transition : m_TransitionChecks[m_CurrentAnimation]){
                //if (transition.first()){
                    //switchAnimation(transition.second);
                //}
            //}

            m_Animations[m_CurrentAnimation].update(ts);
        }

        std::string_view getCurrentAnimation() const {
            return m_CurrentAnimation;
        }

    };
};


