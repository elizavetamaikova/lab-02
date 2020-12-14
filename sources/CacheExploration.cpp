// Copyright 2020 elizavetamaikova
//
// Created by lizer on 14.12.2020.
//
#include "CacheExploration.hpp"
CacheExploration::CacheExploration(uint32_t L1, uint32_t L3){
  uint32_t current = L1 / 2;
  while (current < 3 * L3 / 2) {
    _mas.push_back(current * 256);
    current *= 2;
  }
  _mas.push_back(3 * L3 * 128);
  DirectTest();
  ReverseTest();
  RandomTest();
  ClearOutput();
}

CacheExploration::~CacheExploration() {
}

void CacheExploration::DirectTest() {
  uint32_t* array = nullptr;
  uint32_t ArraySize = _mas.size();
  uint32_t TestCount = 1000;
  uint32_t current = 0;
  uint32_t ArrayLength = 0;
  ArraySize += ArrayLength;
  current += current;
  int64_t EntireTime = 0;
  uint32_t ArrInc = 16;
  double TimeSub = 1000.0;

  struct Cache NewCacheExploration;

  for (uint32_t i = 0; i < ArraySize; ++i) {
    ArrayLength = _mas[i];
    array = CreateArray(ArrayLength);
    WarmupDirect(array, ArrayLength);
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < TestCount; ++j) {
      for (uint32_t k = 0; k < ArrayLength; k += ArrInc) current = array[k];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    EntireTime =
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
    NewCacheExploration.number = i;
    NewCacheExploration.time = static_cast<double>(EntireTime) / TimeSub;
    NewCacheExploration.type = "Direct";
    _result.push_back(NewCacheExploration);
    delete[] array;
  }
}

void CacheExploration::ReverseTest() {
  uint32_t* array = nullptr;
  uint32_t ArraySize = _mas.size();
  uint32_t TestCount = 1000;
  uint32_t current = 0;
  uint32_t ArrayLength = 0;
  ArraySize += ArrayLength;
  current += current;
  int64_t EntireTime = 0;
  uint32_t ArrInc = 16;
  double TimeSub = 1000.0;
  struct Cache NewCacheExploration;

  for (uint32_t i = 0; i < ArraySize; ++i) {
    ArrayLength = _mas[i];
    array = CreateArray(ArrayLength);
    WarmupReverse(array, ArrayLength);
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < TestCount; ++j) {
      for (uint32_t k = 0; k < ArrayLength; k += ArrInc)
        current = array[ArrayLength - k - 1];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    EntireTime =
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
    NewCacheExploration.number = i;
    NewCacheExploration.time = static_cast<double>(EntireTime) / TimeSub;
    NewCacheExploration.type = "Reverse";
    _result.push_back(NewCacheExploration);
    delete[] array;
  }
}

uint32_t RandomNumber(uint32_t lower, uint32_t upper){
  return lower + random() % (upper - lower + 1);
}

void CacheExploration::RandomTest() {
  uint32_t* array = nullptr;
  uint32_t ArraySize = _mas.size();
  uint32_t TestCount = 1000;
  uint32_t current = 0;
  uint32_t ArrayLength = 0;
  ArraySize += ArrayLength;
  current += current;
  int64_t EntireTime = 0;
  uint32_t ArrInc = 16;
  double TimeSub = 1000.0;
  struct Cache NewCacheExploration;

  for (uint32_t i = 0; i < ArraySize; ++i) {
    ArrayLength = _mas[i];
    array = CreateArray(ArrayLength);
    WarmupRandom(array, ArrayLength);
    auto start = std::chrono::high_resolution_clock::now();
    for (uint32_t j = 0; j < TestCount; ++j) {
      for (uint32_t k = 0; k < ArrayLength / ArrInc; ++k)
        current = array[RandomNumber(0, ArrayLength - 1)];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    EntireTime =
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
            .count();
    NewCacheExploration.number = i;
    NewCacheExploration.time = static_cast<double>(EntireTime) / TimeSub;
    NewCacheExploration.type = "Random";
    _result.push_back(NewCacheExploration);
    delete[] array;
  }
}

uint32_t* CacheExploration::CreateArray(uint32_t size) {
  uint32_t* array = new uint32_t[size];
  return array;
}

void CacheExploration::WarmupDirect(uint32_t* array, uint32_t size) {
  uint32_t current = 0;
  current += current;
  for (uint32_t i = 0; i < size; i += 16)
    current = array[i];
}

void CacheExploration::WarmupReverse(uint32_t* array, uint32_t size) {
  uint32_t current = 0;
  current += current;
  for (uint32_t i = 0; i < size ; i += 16)
    current = array[size - i - 1];
}

void CacheExploration::WarmupRandom(uint32_t* array, uint32_t size) {
  int size_int = static_cast<int>(size);
  uint32_t current = 0;
  current += current;
  for (int i = size_int; i > 0 ; i -= 16)
    current = array[RandomNumber(0, size - 1)];
}

void CacheExploration::ClearOutput() {
  std::string Out = "";
  uint32_t NumberOfWays = _result.size()/_mas.size();
  for (uint32_t j = 0; j < NumberOfWays; ++j) {
    Out += "investigation:\n";
    Out += " travel_variant: ";
    Out += _result[j*_result.size()/NumberOfWays].type;
    Out += "\n experiments\n";
    for (uint32_t i = (_result.size() / NumberOfWays) * j;
         i < (_result.size() / NumberOfWays) * (j + 1); ++i) {
      Out += "- experiment:\n";
      Out += "  number: ";
      Out += std::to_string(_result[i].number + 1);
      Out += "\n  input_data:\n   buffer_size: ";
      Out += std::to_string(_mas[i % _mas.size()] / 256);
      Out += " Kib\n";
      Out += "  results:\n   duration: ";
      Out += std::to_string(_result[i].time);
      Out += " ms\n";
    }
  }
  std::cout << Out;
}
void CacheExploration::Graf() {
  std::string Coord = "";
  for (auto i : _result) {
    Coord += "(";
    Coord += std::to_string(_mas[i.number] / 256);
    Coord += ";";
    Coord += std::to_string(i.time);
    Coord += ")";
  }
  std::cout << Coord << std::endl;
}

#include "CacheExploration.hpp"
