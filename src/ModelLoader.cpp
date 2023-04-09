#include "ModelLoaderh.h"
#include "OBJLoader.h"

void ModelLoader::init()
{
}

void ModelLoader::update()
{
}

void ModelLoader::render()
{
}

void ModelLoader::destroy()
{
}

LoadData
ModelLoader::load(std::string objFileName) {

  //temporal load Data
  LoadData LD;
  objl::Loader loader;

  bool Model = loader.LoadFile(objFileName);

  if (Model) {
    int totalVertices = loader.LoadedVertices.size();
    int totalIndices = loader.LoadedIndices.size();
    int loadedVertices = 0;

    LD.name = objFileName;

    WARNING("ModelLoader::Load() [Load of file " << objFileName.c_str() << "] \n");

    LD.vertex.resize(totalVertices);

    for (int i = 0; i < totalVertices; ++i) {
      LD.vertex[i].Pos.x = loader.LoadedVertices[i].Position.X;
      LD.vertex[i].Pos.y = loader.LoadedVertices[i].Position.Y;
      LD.vertex[i].Pos.z = loader.LoadedVertices[i].Position.Z;

      LD.vertex[i].Tex.x = loader.LoadedVertices[i].TextureCoordinate.X;
      LD.vertex[i].Tex.y = loader.LoadedVertices[i].TextureCoordinate.Y;
    }

    LD.index.resize(totalIndices);

    for (int i = 0; i < totalIndices; ++i) {
      LD.index[i] = loader.LoadedIndices[i];
    }

    LD.name = objFileName;
    LD.numVertex = totalVertices;
    LD.numIndex = totalIndices;
  }
  else {
    WARNING("ModelLoader::Load() [File dont exist " << objFileName.c_str() << "] \n");
  }

  return LD;
}