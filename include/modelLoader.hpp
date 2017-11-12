#ifndef _MODEL_LOADER_HPP_
#define _MODEL_LOADER_HPP_

class Model;
#include <string>

namespace Loading
{
  /** \brief used to Load models

      \a model pointer to the location where the target model lies
      \a fileName string that indicates the fileName of the model data
   */
  void Load(Model*const model, const std::string& fileName);

  /** \brief class for loading models

      currently can only load .off files
      \todo implement more fileFormats
   */
  class ModelLoader
  {
  public:
    
    void Load(Model*const, const std::string& fileName) const;

  private:
    void LoadOff(Model*const, const std::string& fileName) const;
  };
}

#endif //_MODEL_LOADER_HPP_
