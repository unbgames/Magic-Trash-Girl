/*
 * quadtree.h
 *
 *  Created on: Jun 7, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_QUADTREE_H_
#define SOURCE_HEADERS_QUADTREE_H_

#include "globals.h"
#include <vector>
#include "animatedsprite.h"
#include <memory>

class QuadTree;

struct ObjectQuadTree {
	// não sei se index eh melhor que iterator aqui, estou usando index, mas iterators seriam melhores pois eu sei que o tamanho do vetor não será modificado
	std::weak_ptr<AnimatedSprite> associatedSprite;

	float posX, posY;

	int width, height;

	QuadTree* nodeAssociated;

	ObjectQuadTree(std::weak_ptr<AnimatedSprite> associatedSprite, float posX, float posY, int width, int height ):
		associatedSprite(associatedSprite), posX(posX), posY(posY), width(width), height(height), nodeAssociated(nullptr)
	{}
};

class QuadTree{
public:

	QuadTree(int layer, int maxLayers, int maxObjectsInQuadrant,float posX, float posY, int width, int height, QuadTree* fatherNode = nullptr);

	~QuadTree();

	void insert(ObjectQuadTree* objectToInsert); //nao implementado

	void clear();

	void runTreeCheckColisions(ObjectQuadTree* objectToCheck);

private:

	void _split(); //nao implementado

	QuadTree* _fatherNode;

	/*
	 * 	quadrantes
	 *   |0|1|
	 *   |2|3|
	 */

	std::vector<QuadTree> _nodesVector;

	//utilizando raw vectors porque os objetos são Local variables e tem scope e tempo de vida delimitados
	std::vector<ObjectQuadTree*> _objectVector;

	int _layer;
	int _maxLayers;
	int _maxObjectsInQuadrant;
	float _posX, _posY;
	int _w, _h;

};



#endif /* SOURCE_HEADERS_QUADTREE_H_ */
