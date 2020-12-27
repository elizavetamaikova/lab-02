// Copyright 2020 elizavetamaikova
//
// Created by lizer on 14.12.2020.
//

#ifndef TEMPLATE_CACHEEXPLORATION_HPP
#define TEMPLATE_CACHEEXPLORATION_HPP

#include <iostream>
#include <vector>
#include <chrono>
#include <string>

struct Cache{
    std::string type;
    uint32_t number;
    double time;
};

class CacheExploration {
public:
    CacheExploration(uint32_t L1, uint32_t L3);
    ~CacheExploration();
    void WarmupDirect(uint32_t* array, uint32_t size);
    void WarmupReverse(uint32_t* array, uint32_t size);
    void WarmupRandom(uint32_t* array, uint32_t size);
    uint32_t* CreateArray(uint32_t size);
    void DirectTest();
    void ReverseTest();
    void RandomTest();
    void ClearOutput();
    void Graf();
    friend std::ostream& operator << (std::ostream &out, const CacheExploration& r);
private:
    std::vector<struct Cache> _result;
    std::vector<uint32_t> _mas;
};

#endif // TEMPLATE_CACHEEXPLORATION_HPP