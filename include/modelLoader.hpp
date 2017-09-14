#ifndef _MODEL_LOADER_HPP_
#define _MODEL_LOADER_HPP_

class Model;
#include <string>

namespace Loading
{
  void Load(Model*const, const std::string& fileName);
  
  class ModelLoader
  {
  public:
    
    void Load(Model*const, const std::string& fileName) const;

  private:
    void LoadOff(Model*const, const std::string& fileName) const;
  };
}

#endif //_MODEL_LOADER_HPP_
