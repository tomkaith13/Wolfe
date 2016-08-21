//
//  Timer.hpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/18/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>


class Timer
{
    
    std::chrono::steady_clock::time_point mTimeStart;
    std::chrono::steady_clock::time_point mTimeEnd;
    bool mStarted;
    
public:
    Timer(bool started = false): mStarted(started) {};
    void start();
    double stop();
    void reset();
    double elaspedTime();
};

#endif /* Timer_hpp */
