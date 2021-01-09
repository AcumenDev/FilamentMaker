//
// Created by vst on 4/22/17.
//

#ifndef TIMEUTILS_HPP
#define TIMEUTILS_HPP

class TimeUtils {

public:
    static bool isWorkTime(unsigned long prevMillis, unsigned long currentMillis, unsigned int interval) {
        if (currentMillis < prevMillis) {//проверка обнуления миллисекунд раз в 50 дней
            prevMillis = currentMillis;
        }
        return (currentMillis - prevMillis) >= interval;
    }
};


#endif //TIMEUTILS_HPP
