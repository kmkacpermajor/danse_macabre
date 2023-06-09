#include "model.h"

void Model::loadModel(std::string plik) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    if (scene == NULL) {
        std::cout << importer.GetErrorString() << std::endl;
        return;
    }

    for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++) {
        aiMesh* mesh = scene->mMeshes[meshIndex];

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D vertex = mesh->mVertices[i];
            verts.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

            aiVector3D normal = mesh->mNormals[i];
            norms.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

            aiVector3D texCoord = mesh->mTextureCoords[0][i];
            texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
    }
}
