#pragma once


class IMaterial {
public:
  virtual ~IMaterial() = default;
  virtual void Create() {};
  virtual void Bind(const size_t &index) = 0;
  virtual void Update() {};
};