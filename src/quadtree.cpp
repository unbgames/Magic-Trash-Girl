/*
 * quadtree.cpp
 *
 *  Created on: Jun 7, 2018
 *      Author: TMK
 */

#include "quadtree.h"
#include "game.h"

int QuadTree::numberQuadtrees = 0;

QuadTree::QuadTree(const QuadTree &QuadTree2):
					_fatherNode(QuadTree2._fatherNode),
					_layer(QuadTree2._layer),
					_maxLayers(QuadTree2._maxLayers),
					_maxObjectsInQuadrant(QuadTree2._maxObjectsInQuadrant),
					_posX(QuadTree2._posX),
					_posY(QuadTree2._posY),
					_w(QuadTree2._w),
					_h(QuadTree2._h){
	numberQuadtrees++;
}

QuadTree::QuadTree(int layer, int maxLayers, int maxObjectsInQuadrant,float posX, float posY, int width, int height, QuadTree* fatherNode):
					_fatherNode(fatherNode),
					_layer(layer),
					_maxLayers(maxLayers),
					_maxObjectsInQuadrant(maxObjectsInQuadrant),
					_posX(posX),
					_posY(posY),
					_w(width),
					_h(height){
	//std::cout << "quadtree criada layer:: " << this->_layer << "  posX :: " << this->_posX << "    posY:: " << this->_posY << std::endl;
	numberQuadtrees++;
}

QuadTree::~QuadTree(){
	//std::cout << "quadtree destructor" << std::endl;
	numberQuadtrees--;
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
	this->_nodesVector.emplace_back(QuadTree(this->_layer+1, this->_maxLayers, this->_maxObjectsInQuadrant, this->_posX, this->_posY, this->_w/2, this->_h/2, this));
	this->_nodesVector.emplace_back(QuadTree(this->_layer+1, this->_maxLayers, this->_maxObjectsInQuadrant, this->_posX + this->_w/2, this->_posY, this->_w/2, this->_h/2, this));
	this->_nodesVector.emplace_back(QuadTree(this->_layer+1, this->_maxLayers, this->_maxObjectsInQuadrant, this->_posX, this->_posY + this->_h/2, this->_w/2, this->_h/2, this));
	this->_nodesVector.emplace_back(QuadTree(this->_layer+1, this->_maxLayers, this->_maxObjectsInQuadrant, this->_posX + this->_w/2, this->_posY + this->_h/2, this->_w/2, this->_h/2, this));

	std::vector<ObjectQuadTree*> auxVector = this->_objectVector;

	this->_objectVector.clear();

	for( std::vector<ObjectQuadTree*>::iterator it = auxVector.begin(); it != auxVector.end(); ++it){
		this->insert(*it);
	}

}

void QuadTree::runTreeCheckColisionsFull(){

	float auxX,auxY;
	int auxW,auxH;

	for( std::vector<ObjectQuadTree*>::iterator it = this->_objectVector.begin(); it != this->_objectVector.end(); ++it){

		(*it)->associatedSprite.lock()->getPosSize(&auxX,&auxY,&auxW,&auxH);

		for( std::vector<ObjectQuadTree*>::iterator it2 = it; it2 != this->_objectVector.end(); ++it2){

			if(!((*it)->associatedSprite.lock() == (*it2)->associatedSprite.lock())){
				if((*it2)->associatedSprite.lock()->checkColision(auxX, auxY, auxW, auxH, 0, 0)){
					(*it2)->associatedSprite.lock()->resolveColision((*it)->associatedSprite.lock()->getObjectType());
					(*it)->associatedSprite.lock()->resolveColision((*it2)->associatedSprite.lock()->getObjectType());
				}
			}

		}

		if(this->_fatherNode){
			this->_fatherNode->runTreeCheckColisionsForOneNode((*it));
		}

	}

	for(std::vector<QuadTree>::iterator it3 = this->_nodesVector.begin(); it3 != this->_nodesVector.end(); ++it3){
		(it3)->runTreeCheckColisionsFull();
	}
}

void QuadTree::runTreeCheckColisionsForOneNode(ObjectQuadTree* objectToCheck){

	float auxX,auxY;
	int auxW,auxH;

	objectToCheck->associatedSprite.lock()->getPosSize(&auxX,&auxY,&auxW,&auxH);

	for( std::vector<ObjectQuadTree*>::iterator it = this->_objectVector.begin(); it != this->_objectVector.end(); ++it){

		if(!(objectToCheck->associatedSprite.lock() == (*it)->associatedSprite.lock())){
			if((*it)->associatedSprite.lock()->checkColision(auxX, auxY, auxW, auxH, 0, 0)){
				(*it)->associatedSprite.lock()->resolveColision(objectToCheck->associatedSprite.lock()->getObjectType());
				objectToCheck->associatedSprite.lock()->resolveColision((*it)->associatedSprite.lock()->getObjectType());
			}
		}

	}

	if(this->_fatherNode){
		this->_fatherNode->runTreeCheckColisionsForOneNode(objectToCheck);
	}
}
