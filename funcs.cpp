//https://contest.yandex.ru/contest/29396/problems/A/

#include "funcs.h"
#include <bits/stdc++.h>

void parseInput(std::istream & input,
                 std::vector<std::pair<int,bool>> & events){
    int n;
    input>>n;
    events.reserve(2*n);
    int l,r;
    for(int i = 0; i<n; ++i){
        input>>l>>r;
        if(l!=r){
            events.emplace_back(l,false);
            events.emplace_back(r,true);
        }
    }
}

void parseFile(std::istream & input, std::ostream & output){
    std::vector<std::pair<int,bool>> events;
    parseInput(input,events);

    std::sort(events.begin(), events.end());

    int countOfBeginnings = 0;
    int paintedLen = 0;
    int prevPos = events[0].first;
    for(const auto & event:events){
        if(countOfBeginnings>0)
            paintedLen+=event.first - prevPos;
        prevPos = event.first;
        countOfBeginnings+=event.second ? -1 : 1;
    }
    output<<paintedLen<<std::endl;
}
