#include "model.hpp"

Model::Model(): orientation(1.0f, 0.0f, 0.0f, 0.0f), position(0.f, 0.f, 0.f), scale(1.0f) {}
Model::Model (const std::string &fileName, glm::vec3 position) : orientation(1.0f, 0.0f, 0.0f, 0.0f), position(position), scale(1.0f)
{
    update_modelMat();
    glGenVertexArrays(1, &vao);
    assert(vao > 0);

    glBindVertexArray(vao);
    std::cout << "vao = " << vao << std::endl;

    assert(glGetError() == GL_NONE);

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);

    assert(vertexBuffer > 0 && indexBuffer > 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    ParseObj(fileName);

    int gVertexDataSizeInBytes, gNormalDataSizeInBytes;
    gVertexDataSizeInBytes = gVertices.size() * 3 * sizeof(GLfloat);
    gNormalDataSizeInBytes = gNormals.size() * 3 * sizeof(GLfloat);
    int indexDataSizeInBytes = gFaces.size() * 3 * sizeof(GLuint);
    GLfloat* vertexData = new GLfloat[gVertices.size() * 3];
    GLfloat* normalData = new GLfloat[gVertices.size() * 3];
    GLuint* indexData = new GLuint[gFaces.size() * 3];

    float minX = 1e6, maxX = -1e6;
    float minY = 1e6, maxY = -1e6;
    float minZ = 1e6, maxZ = -1e6;

    for (size_t i = 0; i < gVertices.size(); ++i)
    {
        vertexData[3 * i] = gVertices[i].x;
        vertexData[3 * i + 1] = gVertices[i].y;
        vertexData[3 * i + 2] = gVertices[i].z;

        minX = std::min(minX, gVertices[i].x);
        maxX = std::max(maxX, gVertices[i].x);
        minY = std::min(minY, gVertices[i].y);
        maxY = std::max(maxY, gVertices[i].y);
        minZ = std::min(minZ, gVertices[i].z);
        maxZ = std::max(maxZ, gVertices[i].z);
    }

    std::cout << "minX = " << minX << std::endl;
    std::cout << "maxX = " << maxX << std::endl;
    std::cout << "minY = " << minY << std::endl;
    std::cout << "maxY = " << maxY << std::endl;
    std::cout << "minZ = " << minZ << std::endl;
    std::cout << "maxZ = " << maxZ << std::endl;

    for (size_t i = 0; i < gNormals.size(); ++i)
    {
        normalData[3 * i] = gNormals[i].x;
        normalData[3 * i + 1] = gNormals[i].y;
        normalData[3 * i + 2] = gNormals[i].z;
    }

    for (size_t i = 0; i < gFaces.size(); ++i)
    {
        indexData[3 * i] = gFaces[i].vIndex[0];
        indexData[3 * i + 1] = gFaces[i].vIndex[1];
        indexData[3 * i + 2] = gFaces[i].vIndex[2];

        normalData[3 * gFaces[i].vIndex[0]] = gNormals[gFaces[i].nIndex[0]].x;
        normalData[3 * gFaces[i].vIndex[0] + 1] = gNormals[gFaces[i].nIndex[0]].y;
        normalData[3 * gFaces[i].vIndex[0] + 2] = gNormals[gFaces[i].nIndex[0]].z;

        normalData[3 * gFaces[i].vIndex[1]] = gNormals[gFaces[i].nIndex[1]].x;
        normalData[3 * gFaces[i].vIndex[1] + 1] = gNormals[gFaces[i].nIndex[1]].y;
        normalData[3 * gFaces[i].vIndex[1] + 2] = gNormals[gFaces[i].nIndex[1]].z;

        normalData[3 * gFaces[i].vIndex[2]] = gNormals[gFaces[i].nIndex[2]].x;
        normalData[3 * gFaces[i].vIndex[2] + 1] = gNormals[gFaces[i].nIndex[2]].y;
        normalData[3 * gFaces[i].vIndex[2] + 2] = gNormals[gFaces[i].nIndex[2]].z;
    }


    glBufferData(GL_ARRAY_BUFFER, gVertexDataSizeInBytes + gNormalDataSizeInBytes, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, gVertexDataSizeInBytes, vertexData);
    glBufferSubData(GL_ARRAY_BUFFER, gVertexDataSizeInBytes, gNormalDataSizeInBytes, normalData);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSizeInBytes, indexData, GL_STATIC_DRAW);

    // done copying; can free now
    delete[] vertexData;
    delete[] normalData;
    delete[] indexData;

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(gVertexDataSizeInBytes));

    faceCount = gFaces.size();
    texture_num = -1;
}

bool Model::ParseObj(const std::string& fileName)
{
	std::fstream myfile;

	gVertices.clear();
	gTextures.clear();
	gNormals.clear();
	gFaces.clear();
	
	// Open the input 
	myfile.open(fileName.c_str(), std::ios::in);

	if (myfile.is_open())
	{
		std::string curLine;

		while (getline(myfile, curLine))
		{
			std::stringstream str(curLine);
			GLfloat c1, c2, c3;
			std::string tmp;

			if (curLine.length() >= 2)
			{
				if (curLine[0] == 'v')
				{
					if (curLine[1] == 't') // texture
					{
						str >> tmp; // consume "vt"
						str >> c1 >> c2;
						gTextures.push_back(Texture(c1, c2));
					}
					else if (curLine[1] == 'n') // normal
					{
						str >> tmp; // consume "vn"
						str >> c1 >> c2 >> c3;
						gNormals.push_back(Normal(c1, c2, c3));
					}
					else // vertex
					{
						str >> tmp; // consume "v"
						str >> c1 >> c2 >> c3;
						gVertices.push_back(Vertex(c1, c2, c3));
					}
				}
				else if (curLine[0] == 'f') // face
				{
					str >> tmp; // consume "f"
					char c;
					int vIndex[3], nIndex[3], tIndex[3];
					str >> vIndex[0]; str >> c >> c; // consume "//"
					str >> nIndex[0];
					str >> vIndex[1]; str >> c >> c; // consume "//"
					str >> nIndex[1];
					str >> vIndex[2]; str >> c >> c; // consume "//"
					str >> nIndex[2];

					//assert(vIndex[0] == nIndex[0] &&
					//	vIndex[1] == nIndex[1] &&
					//	vIndex[2] == nIndex[2]); // a limitation for now

					// make indices start from 0
					for (int c = 0; c < 3; ++c)
					{
						vIndex[c] -= 1;
						nIndex[c] -= 1;
						tIndex[c] -= 1;
					}

					gFaces.push_back(Face(vIndex, tIndex, nIndex));
				}
				else
				{
					std::cout << "Ignoring unidentified line in obj file: " << curLine << std::endl;
				}
			}

			//data += curLine;
			if (!myfile.eof())
			{
				//data += "\n";
			}
		}

		myfile.close();
	}
	else
	{
		return false;
	}

	//assert(gVertices.size() == gNormals.size());

	return true;
}

void Model::draw (glm::mat4 viewingMat, glm::mat4 projectionMat)
{
	shader->use();

	shader->setMat4("modelingMatrix", modelMat);
	shader->setMat4("viewingMatrix", viewingMat);
	shader->setMat4("projectionMatrix", projectionMat);
	shader->setVec3("eyePos", eyePos);
	
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (texture_num >= 0)
	{
		shader->setInt("tex", texture_num);
		glActiveTexture(GL_TEXTURE0 + texture_num);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	
    glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, 0);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::attach_texture (const std::string &fileName)
{
	texture_num = texture_ctr ++;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + texture_num);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int width, height, nrChannels;
	unsigned char *data;

	data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Model::set_position(glm::vec3 position) {
    this->position = position;
    update_modelMat();
}

void Model::set_scale(glm::vec3 scale)
{
    this->scale = scale;
    update_modelMat();
}


void Model::set_orientation(glm::quat orientation) {
    orientation = glm::normalize(orientation);
    this->orientation = orientation;
    update_modelMat();
}

void Model::attach_shader (Shader * s)
{
	shader = s;
}

void Model::set_orientation(glm::vec3 const &axis, float radAngle, bool worldSpace)
{
    glm::vec3 axisNorm = glm::normalize(axis);

    axisNorm *= sin(radAngle / 2.0f);
    float scalar = cos(radAngle / 2.0f);

    glm::quat offset(scalar, axisNorm);

    if(worldSpace)
        orientation = offset * orientation;
    else
        orientation = orientation * offset;

    orientation = glm::normalize(orientation);
    update_modelMat();
}

void Model::update_modelMat()
{
    modelMat = glm::scale(glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(orientation), scale);
}


