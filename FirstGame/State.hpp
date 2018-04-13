//
//  State.h
//  FirstGame
//
//  Created by 周凯旋 on 4/12/18.
//  Copyright © 2018 Kaixuan Zhou. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#pragma once

namespace Sonar {
    class State{
    public:
        virtual void Init()=0;
        virtual void HandleInput()=0;
        virtual void Update( float dt)=0;
        virtual void Draw(float dt)=0;
        virtual void Pause(){}
        virtual void Resume(){}
    };
}


#endif /* State_h */
