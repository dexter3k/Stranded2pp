// Build me:
// g++ -std=c++14 -Wall -Wextra -Wpedantic -I../source/ ./b3dpreview.cpp ../source/common/ByteBuffer.cpp ../source/common/FileSystem.cpp ../source/common/RingBuffer.cpp -o b3dpreview -lsfml-system -lsfml-graphics -lsfml-window

#include <cassert>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "common/FileSystem.h"
#include "common/ByteBuffer.h"

std::size_t getVerticeSize(uint32_t flags, uint32_t texCoords, uint32_t texCoordSize)
{
	std::size_t verticeSize = 4*3 + 4*texCoords*texCoordSize;
	if (flags & 1) {
		verticeSize += 4*3;
	}
	if (flags & 2) {
		verticeSize += 4*4;
	}
	
	return verticeSize;	
}

std::string getUnixPath(std::string filepath) {
	std::replace(filepath.begin(), filepath.end(), '\\', '/');

	return filepath;
}

std::string getBasePath(std::string const & filepath) {
	auto i = filepath.rfind('/');
	if (i == std::string::npos) {
		return std::string("./");
	}

	return filepath.substr(0, i+1);
}

class Model
{
public:
	struct Texture
	{
		sf::Texture texture;
		std::string filename;

		uint32_t flags, blend;

		float x, y;
		float scaleX, scaleY;
		float rotation;
	};

	struct Brush
	{
		std::string name;

		// float red, green, blue, alpha;
		float color[4];
		float shininess;

		uint32_t blend, fx;

		std::vector<unsigned> textures;
	};

	struct TriangleSet
	{
		int brushId;

		std::vector<uint32_t> triangles;
	};

	struct Mesh
	{
		int brushId;

		uint32_t flags;
		unsigned texCoords;
		unsigned texCoordSize;

		std::vector<float> vertices;
		std::vector<TriangleSet> triangleSets;
	};

	struct Node
	{
		std::string name;

		float x, y, z;
		float scaleX, scaleY, scaleZ;
		float qW, qX, qY, qZ;

		Mesh mesh;
		// Bone bone;
		// std::vector<Key> keys;
		std::vector<Node> nodes;

		unsigned frames;
		float fps;
	};

	std::vector<Texture> textures;
	std::vector<Brush> brushes;
	Node root;

	Model(std::string const & filename) :
		textures()
	{
		loadFromFile(filename);
	}

	void loadFromFile(std::string const & filename) {
		ByteBuffer buffer(fs::getFileSize(filename));
		if (!fs::loadFile(filename, buffer)) {
			std::exit(1);
		}

		auto tag = buffer.readString(4);
		std::size_t size = buffer.readInt32();
		assert(tag == "BB3D");
		assert(size == buffer.bytesLeftForReading());

		readBB3D(buffer);

		for (auto & texture : textures) {
			texture.texture.loadFromFile(getBasePath(filename) + getUnixPath(texture.filename));
			std::cout << "Loading " << getBasePath(filename) + getUnixPath(texture.filename) << std::endl;
		}
	}

	std::vector<Texture> const & getTextures() const { return textures; };
	std::vector<Brush> const & getBrushes() const { return brushes; };
	Node const & getRoot() const { return root; };
private:
	void readBB3D(ByteBuffer & buffer) {
		int version = buffer.readInt32();
		assert(version == 1);

		for (unsigned i = 0; i < 3; ++i) {
			if (buffer.bytesLeftForReading() == 0) {
				return;
			}

			auto tag = buffer.readString(4);
			std::size_t size = buffer.readUint32();
			assert(size <= buffer.bytesLeftForReading());

			if (tag == "TEXS") {
				readTEXS(buffer, size);
			} else if (tag == "BRUS") {
				readBRUS(buffer, size);
			} else if (tag == "NODE") {
				readNODE(buffer, root, size);
			} else {
				assert(false);
			}
		}
	}

	void readTEXS(ByteBuffer & buffer, std::size_t size) {
		std::size_t const end = buffer.bytesLeftForReading() - size;

		while (buffer.bytesLeftForReading() != end) {
			Texture texture;
			texture.filename = buffer.readCString();
			texture.flags = buffer.readUint32();
			texture.blend = buffer.readUint32();
			texture.x = buffer.readFloat();
			texture.y = buffer.readFloat();
			texture.scaleX = buffer.readFloat();
			texture.scaleY = buffer.readFloat();
			texture.rotation = buffer.readFloat();

			textures.push_back(texture);
		}
	}

	void readBRUS(ByteBuffer & buffer, std::size_t size) {
		std::size_t const end = buffer.bytesLeftForReading() - size;

		int32_t textureCount = buffer.readInt32();

		while (buffer.bytesLeftForReading() != end) {
			Brush brush;
			brush.name = buffer.readCString();
			brush.color[0] = buffer.readFloat();
			brush.color[1] = buffer.readFloat();
			brush.color[2] = buffer.readFloat();
			brush.color[3] = buffer.readFloat();
			brush.shininess = buffer.readFloat();
			brush.blend = buffer.readUint32();
			brush.fx = buffer.readUint32();
			brush.textures.resize(textureCount);
			for (int i = 0; i < textureCount; ++i) {
				brush.textures[i] = buffer.readInt32();
			}

			brushes.push_back(brush);
		}
	}

	void readNODE(ByteBuffer & buffer, Node & node, std::size_t size) {
		std::size_t const end = buffer.bytesLeftForReading() - size;

		node.name = buffer.readCString();
		node.x = buffer.readFloat();
		node.y = buffer.readFloat();
		node.z = buffer.readFloat();
		node.scaleX = buffer.readFloat();
		node.scaleY = buffer.readFloat();
		node.scaleZ = buffer.readFloat();
		node.qW = buffer.readFloat();
		node.qX = buffer.readFloat();
		node.qY = buffer.readFloat();
		node.qZ = buffer.readFloat();

		node.frames = 0;
		node.fps = 60.0f;

		while (buffer.bytesLeftForReading() != end) {
			auto tag = buffer.readString(4);
			std::size_t size = buffer.readUint32();
			assert(size <= buffer.bytesLeftForReading() - end);

			if (tag == "MESH") {
				readMESH(buffer, node, size);
			} else if (tag == "BONE") {
				readBONE(buffer, size);
			} else if (tag == "KEYS") {
				readKEYS(buffer, size);
			} else if (tag == "NODE") {
				Node subNode;
				readNODE(buffer, subNode, size);
				node.nodes.push_back(subNode);
			} else if (tag == "ANIM") {
				readANIM(buffer, node);
			} else {
				assert(false);
			}
		}
	}

	void readMESH(ByteBuffer & buffer, Node & node, std::size_t size) {
		std::size_t const end = buffer.bytesLeftForReading() - size;

		Mesh mesh;
		mesh.brushId = buffer.readInt32();

		auto tag = buffer.readString(4);
		size = buffer.readUint32();
		assert(tag == "VRTS");
		assert(size <= buffer.bytesLeftForReading() - end);
		readVRTS(buffer, mesh, size);

		while (buffer.bytesLeftForReading() != end) {
			tag = buffer.readString(4);
			size = buffer.readUint32();
			assert(tag == "TRIS");
			assert(size <= buffer.bytesLeftForReading() - end);

			readTRIS(buffer, mesh, size);
		}

		node.mesh = mesh;
	}

	void readVRTS(ByteBuffer & buffer, Mesh & mesh, std::size_t size) {
		std::size_t const end = buffer.bytesLeftForReading() - size;

		mesh.flags = buffer.readUint32();
		mesh.texCoords = buffer.readInt32();
		mesh.texCoordSize = buffer.readInt32();

		size = getVerticeSize(mesh.flags, mesh.texCoords, mesh.texCoordSize);
		std::size_t const remaining = buffer.bytesLeftForReading() - end;
		assert(remaining % size == 0);

		mesh.vertices.resize(remaining / 4);
		for (unsigned i = 0; i < remaining / 4; ++i) {
			mesh.vertices[i] = buffer.readFloat();
		}
	}

	void readTRIS(ByteBuffer & buffer, Mesh & mesh, std::size_t size) {
		std::size_t const end = buffer.bytesLeftForReading() - size;

		TriangleSet set;
		set.brushId = buffer.readInt32();

		std::size_t const remaining = buffer.bytesLeftForReading() - end;
		assert(remaining % 12 == 0);

		set.triangles.resize(remaining / 4);
		for (unsigned i = 0; i < remaining / 4; ++i) {
			set.triangles[i] = buffer.readInt32();
		}

		mesh.triangleSets.push_back(set);
	}

	void readBONE(ByteBuffer & buffer, std::size_t size) {
		buffer.skip(size);
	}

	void readKEYS(ByteBuffer & buffer, std::size_t size) {
		buffer.skip(size);
	}

	void readANIM(ByteBuffer & buffer, Node & node) {
		buffer.skip(4); // unused
		node.frames = buffer.readInt32();
		node.fps = buffer.readFloat();
	}
};

void showModel(std::string const & modelName) {
	Model model(modelName);

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 0;
	contextSettings.antialiasingLevel = 0;
	contextSettings.majorVersion = 2;
	contextSettings.minorVersion = 1;

	std::string title = ".b3d Preview: ";
	title += modelName;

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), title, sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);

	glDisable(GL_LIGHTING);

	glViewport(0, 0, window.getSize().x, window.getSize().y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5*sizeof(GLfloat), model.getRoot().mesh.vertices.data());
	glTexCoordPointer(2, GL_FLOAT, 5*sizeof(GLfloat), model.getRoot().mesh.vertices.data() + 3);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.setActive(false);

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.pushGLStates();
		window.clear(sf::Color(255, 255, 255));
		window.popGLStates();

		window.setActive(true);

		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, -2.0f, -60.0f);
		// glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
		glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
		// glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

		glPolygonMode(GL_BACK, GL_LINE);

		for (unsigned i = 0; i < model.getRoot().mesh.triangleSets.size(); ++i) {
			int brush = model.getRoot().mesh.triangleSets[i].brushId;
			if (brush == -1) {
				brush = model.getRoot().mesh.brushId;
			}
			if (brush != -1) {
				if (model.brushes[brush].textures.size() != 0) {
					sf::Texture::bind(&(model.textures[model.brushes[brush].textures[0]].texture));
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glColor4fv(model.brushes[brush].color);
				}
			} else {
				sf::Texture::bind(nullptr);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			}

			glDrawElements(
				GL_TRIANGLES,
				model.getRoot().mesh.triangleSets[i].triangles.size(),
				GL_UNSIGNED_INT, model.getRoot().mesh.triangleSets[i].triangles.data());
		}

		window.setActive(false);

		window.display();
	}
}

void printUsage(std::string const & filename) {
	std::cout << "Usage:\n"
		<< "\t" << filename << " <model.b3d>" << std::endl;
}

int main(int argc, char * argv[]) {
	std::vector<std::string> const arguments(argv, argv + argc);
	if (arguments.size() < 2) {
		printUsage(arguments[0]);
		std::exit(1);
	}

	showModel(arguments[1]);

	// auto const & root = model.getRoot();
	// std::cout << root.mesh.flags << std::endl;
	// std::cout << root.mesh.texCoords << std::endl;
	// std::cout << root.mesh.texCoordSize << std::endl;
	// for (unsigned i = 0; i < root.mesh.vertices.size(); ++i) {
	// 	std::cout << root.mesh.vertices[i] << std::endl;
	// }
	// std::cout << std::endl;

	// for (unsigned i = 0; i < root.mesh.triangleSets.size(); ++i) {
	// 	for (unsigned j = 0; j < root.mesh.triangleSets[i].triangles.size(); ++j) {
	// 		std::cout << root.mesh.triangleSets[i].triangles[j] << std::endl;
	// 	}
	// 	std::cout << std::endl;
	// }

	return 0;
}
