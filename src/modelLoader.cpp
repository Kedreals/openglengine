#include "modelLoader.hpp"
#include "model.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

static Loading::ModelLoader m_s_ModelLoader;

namespace Loading
{

  void Load(Model*const model, const std::string& fileName)
  {
    m_s_ModelLoader.Load(model, fileName);
  }
  
  void ModelLoader::Load(Model*const model, const std::string& fileName) const 
  {
    std::string extension = fileName.substr(fileName.rfind("."));
    if(extension == ".off")
      LoadOff(model, fileName);
  }

  void LogModelBuffer(const std::vector<Vertex>& vertexValues, const std::vector<unsigned int>& indexValues)
  {
    for(size_t i = 0; i < vertexValues.size(); ++i)
      std::clog << "Vertex" << i << ":  " << vertexValues[i];

    for(size_t i = 0; i < indexValues.size(); ++i){
      if(i%3 == 0)
	std::clog << "Face" << i/3 << ": ";
      std::clog << indexValues[i] << ", ";
      if(i%3 == 2)
	std::clog << "\n";
    }
  }
  
  void ModelLoader::LoadOff(Model*const model, const std::string& fileName) const
  {
    std::ifstream stream;

    stream.open(fileName);
    char check[3];
    stream.read(check, 3);
    if(!(check[0] == 'O' && check[1] == 'F' && check[2] == 'F'))
      {
	std::cerr << "ERROR: " << fileName << " could not be loaded\n";
	stream.close();
	return;
      }

    int vertices, faces, edges;
    stream >> vertices >> faces >> edges;
    std::clog << "try to read (" << vertices << ", " << faces << ", " << edges << ") many vertices, faces, edges out of the .off file " << fileName << "\n";

    for(int i = 0; i < vertices; ++i)
      {
	float x, y, z;
	stream >> x >> y >> z;
	glm::vec3 pos(x, y, z);
	glm::vec3 col(std::abs(x),std::abs(y),std::abs(z));
	col = col*2.0f;
	
	Vertex v(pos, col, Vertex::Flags::Color);
	model->m_vertecies.push_back(v);
      }

    for(int i = 0; i < faces; ++i)
      {
	int count, a, b, c;
	stream >> count >> a >> b >> c;
	
	if(count != 3)
	  {
	    std::cerr << "ERROR: " << fileName << " is not an triangulation\n";
	    stream.close();
	    return;
	  }
	model->m_indices.push_back(a);
	model->m_indices.push_back(b);
	model->m_indices.push_back(c);
      }

    //    LogModelBuffer(model->m_vertecies, model->m_indices);
    
    stream.close();
  }
}
