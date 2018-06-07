/*
 * quadtree.cpp
 *
 *  Created on: Jun 7, 2018
 *      Author: TMK
 */

#include "quadtree.h"
#include "game.h"

QuadTree::QuadTree(int layer, int maxLayers, int maxObjectsInQuadrant,float posX, float posY, int width, int height, QuadTree* fatherNode):
					_fatherNode(fatherNode),
					_layer(layer),
					_maxLayers(maxLayers),
					_maxObjectsInQuadrant(maxObjectsInQuadrant),
					_posX(posX),
					_posY(posY),
					_w(width),
					_h(height){

}

QuadTree::~QuadTree(){

}

void QuadTree::insert(ObjectQuadTree* objectToInsert){

	if(_nodesVector.empty()){
		_objectVector.push_back(objectToInsert);
		if(_objectVector.size() > this->_maxObjectsInQuadrant){
			if(this->_layer < this->_maxLayers - 1){
				this->_split();
			}
		}
	}else{
		//parei aqui, tratar qual quadrante q manda o object
	}

}

void QuadTree::clear(){

	if(!this->_objectVector.empty()){
		this->_objectVector.clear();
	}

	if(!this->_nodesVector.empty()){
		for(std::vector<QuadTree>::iterator it = this->_nodesVector.begin(); it != this->_nodesVector.end(); ++it){
			it->clear();
		}
		this->_nodesVector.clear();
	}
}

void QuadTree::_split(){

}
