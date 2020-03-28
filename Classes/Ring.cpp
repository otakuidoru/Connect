/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Ring.h"

static const float DEGTORAD = 0.0174532925199432957f;
static const float RADTODEG = 57.295779513082320876f;

USING_NS_CC;

/**
 *
 */
Ring::Ring() : Node() {
}

/**
 *
 */
Ring::~Ring() {
}

/**
 * on "init" you need to initialize your instance
 */
bool Ring::init() {
	//////////////////////////////
	// 1. super init first
	if (!Node::init()) {
		return false;
	}

	this->selected = false;
	this->direction = 0;

	auto turnButtons = Sprite::create("left_right.png");
	turnButtons->setPositionNormalized(Vec2(0.5f, 0.5f));
	this->addChild(turnButtons);

	this->ring = Sprite::create("ring.png");
	this->ring->setPositionNormalized(Vec2(0.5f, 0.5f));
	this->addChild(this->ring);

  auto femaleCoupling = Sprite::create("female_coupling.png");
  femaleCoupling->setPositionNormalized(Vec2(0.5f, 0.5f));
  femaleCoupling->setAnchorPoint(Vec2(0, 0.5f));
  femaleCoupling->setRotation(0.0f);
  this->ring->addChild(femaleCoupling);

  auto maleCoupling = Sprite::create("male_coupling.png");
  maleCoupling->setPositionNormalized(Vec2(0.5f, 0.5f));
  maleCoupling->setAnchorPoint(Vec2(0, 0.5f));
  maleCoupling->setRotation(90.0f);
  this->ring->addChild(maleCoupling);

	this->setContentSize(this->ring->getContentSize());
	this->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->scheduleUpdate();

	return true;
}

/**
 *
 */
void Ring::rotateLeft() {
	this->direction = (this->direction - 1) % 4;
	if (this->direction < 0) {
		this->direction += 4;
	}
	switch (this->direction) {
		case 0: {
			this->ring->runAction(RotateTo::create(1.0f, 0.0f));
		} break;
		case 1: {
			this->ring->runAction(RotateTo::create(1.0f, 90.0f));
		} break;
		case 2: {
			this->ring->runAction(RotateTo::create(1.0f, 180.0f));
		} break;
		case 3: {
			this->ring->runAction(RotateTo::create(1.0f, 270.0f));
		} break;
	}
}

/**
 *
 */
void Ring::rotateRight() {
	this->direction = (this->direction + 1) % 4;
	if (this->direction < 0) {
		this->direction += 4;
	}
	switch (this->direction) {
		case 0: {
			this->ring->runAction(RotateTo::create(1.0f, 0.0f));
		} break;
		case 1: {
			this->ring->runAction(RotateTo::create(1.0f, 90.0f));
		} break;
		case 2: {
			this->ring->runAction(RotateTo::create(1.0f, 180.0f));
		} break;
		case 3: {
			this->ring->runAction(RotateTo::create(1.0f, 270.0f));
		} break;
	}
}

/**
 *
 */
void Ring::update(float dt) {
}

