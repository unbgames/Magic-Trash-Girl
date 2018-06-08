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

	if(this->_nodesVector.empty()){
		this->_objectVector.push_back(objectToInsert);
		objectToInsert->nodeAssociated = this;

		if((int)this->_objectVector.size() > this->_maxObjectsInQuadrant){
			if(this->_layer < this->_maxLayers - 1){
				this->_split();
			}
		}
	}else{

		/*
		 * 	quadrantes
		 * 	 |0|1|
		 * 	 |2|3|
		 */
		if((objectToInsert->posX + objectToInsert->width - 1 < this->_posX + this->_w/2) && (objectToInsert->posY + objectToInsert->height - 1 < this->_posY + this->_h/2) ){
			this->_nodesVector[0].insert(objectToInsert);
			return;
		}
		if((objectToInsert->posX >= this->_posX + this->_w/2) && (objectToInsert->posY + objectToInsert->height - 1 < this->_posY + this->_h/2) ){
			this->_nodesVector[1].insert(objectToInsert);
			return;
		}
		if((objectToInsert->posX + objectToInsert->width - 1 < this->_posX + this->_w/2) && (objectToInsert->posY >= this->_posY + this->_h/2) ){
			this->_nodesVector[2].insert(objectToInsert);
			return;
		}
		if((objectToInsert->posX >= this->_posX + this->_w/2) && (objectToInsert->posY >= this->_posY + this->_h/2) ){
			this->_nodesVector[3].insert(objectToInsert);
			return;
		}
		//objeto encontra-se entre 2 quadrantes
		this->_objectVector.push_back(objectToInsert);
		objectToInsert->nodeAssociated = this;
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
	//parei aqui, tratar split
}
