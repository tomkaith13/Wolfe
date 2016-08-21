//
//  Timer.cpp
//  Wolfie
//
//  Created by BIBIN THOMAS on 8/18/16.
//  Copyright © 2016 BIBIN THOMAS. All rights reserved.
//

#include "Timer.h"


void Timer::start()
{
    mStarted = true;
    mTimeStart = std::chrono::steady_clock::now();
}

double Timer::stop()
{
    using namespace std::chrono;
    duration<double> timeSpan;
    
    mTimeEnd = steady_clock::now();
    
    timeSpan = duration_cast<duration<double>>(mTimeEnd - mTimeStart);
    
    return timeSpan.count();
}

void Timer::reset()
{
    mStarted = false;
}

double Timer::elaspedTime()
{
    using namespace std::chrono;
    
    return (duration_cast<duration<double>>(mTimeEnd - mTimeStart)).count();
}