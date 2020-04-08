#include "Object2D.h"

#include <Core/Engine.h>
using namespace glm;
Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}
Mesh* Object2D::CreateCircle(std::string name, glm::vec3 position, float radius, glm::vec3 color)
{
	int numberOfTriangles = 100;

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	const double PI = 3.141;
	const int frequency = 1; //make a vertex between each 1 triangle

	vertices.push_back(VertexFormat(glm::vec3(position.x, position.y, 0), color));

	for (int i = 0; i < numberOfTriangles; i++) {
		double currentX = position.x + (radius * cos(i * 2.0f * PI / numberOfTriangles));
		double currentY = position.y + (radius * sin(i * 2.0f * PI / numberOfTriangles));

		vertices.push_back(VertexFormat(glm::vec3(currentX, currentY, 0), color));

		if (i % frequency == 0) {
			indices.push_back(0);
			indices.push_back(i);
			indices.push_back(i + frequency);
		}
	}

	indices.push_back(0);
	indices.push_back(frequency);
	indices.push_back(numberOfTriangles);

	Mesh* circle = new Mesh(name);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Object2D::CreateQuad(std::string name, glm::vec3 color)
{
	vec3 n = vec3(0, 0, 1);
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(vec3(-1, -1, 0), color, n,vec2(0,1)),
		VertexFormat(vec3(1, -1, 0), color, n,vec2(1,1)),
		VertexFormat(vec3(1, 1, 0), color, n,vec2(1,0)),
		VertexFormat(vec3(-1, 1, 0), color, n,vec2(0,0))
	};
	std::vector<unsigned short> indices
	{
		0,1,2,
		0,3,2
	};

	Mesh* quad = new Mesh(name);

	quad->InitFromData(vertices, indices);
	return quad;
}
