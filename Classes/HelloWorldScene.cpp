/****************************************************************************
 Copyright (c) 2020 ZenProgramming.com
 
 http://www.zenprogramming.com
 
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

#include <algorithm>
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename) {
	log("Error while loading: %s\n", filename);
	log("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
  // 1. super init first
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr) {
		problemLoading("'fonts/Marker Felt.ttf'");
	} else {
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	constexpr float BORDER_WIDTH = 50.0f;
	constexpr float BORDER_HEIGHT = 50.0f;
	constexpr float SPACING = 384.0f;

//	createRing();

	{
		auto ring = Ring::create();
		ring->setScale(0.75f);
		ring->setPosition(Vec2(192.0f, 192.0f));
		ring->addArmAt(true, 0);
		ring->addArmAt(false, 2);
		this->addChild(ring);

		//rings.push_back(std::shared_ptr<Ring>(ring));
		grid.emplace(std::make_pair(0, 0), ring);
	}

	{
		auto ring = Ring::create();
		ring->setScale(0.75f);
		ring->setPosition(Vec2(192.0f + 384.0 * 0.75f, 192.0f));
		ring->addArmAt(false, 1);
		ring->addArmAt(true, 3);
		this->addChild(ring);

		//rings.push_back(std::shared_ptr<Ring>(ring));
		grid.emplace(std::make_pair(1, 0), ring);
	}

  /////////////////////////////////////////////////////////////////////////////
  //
  //  Create a "one by one" touch event listener (processes one touch at a time)
  //
  /////////////////////////////////////////////////////////////////////////////

  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->setSwallowTouches(true);

  // triggered when pressed
  touchListener->onTouchBegan = [&](Touch* touch, Event* event) -> bool {
		bool consuming = false;

		std::for_each(grid.begin(), grid.end(), [&](std::pair<std::pair<int, int>, std::shared_ptr<Ring>> element) {
			Ring* ring = element.second.get();
			Rect ringbox = ring->getBoundingBox();
			if (ringbox.containsPoint(touch->getLocation())) {
				Rect leftRect(ringbox.getMinX(), ringbox.getMinY(), ringbox.getMidX() - ringbox.getMinX(), ringbox.getMaxY() - ringbox.getMinY());
				Rect rightRect(ringbox.getMidX(), ringbox.getMinY(), ringbox.getMaxX() - ringbox.getMidX(), ringbox.getMaxY() - ringbox.getMinY());

				if (leftRect.containsPoint(touch->getLocation())) {
					ring->rotateLeft();
					consuming = true;
				} else if (rightRect.containsPoint(touch->getLocation())) {
					ring->rotateRight();
					consuming = true;
				}
			}
		});

    return consuming;
  };

  // triggered when moving touch
  touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
  };

  // triggered when released
  touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
  };

  // add listener
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

/**
 *
 */
Ring* HelloWorld::createRing(std::map<std::string, std::string> properties) {
	std::map<std::string, std::string>::iterator itr;

	auto ring = Ring::create();
	ring->setScale(0.75f);

	// grid_x
	int grid_x;
	if ((itr = properties.find("grid_x")) != properties.end()) {
		grid_x = std::stoi(properties["grid_x"]);
		ring->setPositionX(192.0f + 384.0 * ring->getScale() * grid_x);
	}

	// grid_y
	int grid_y;
	if ((itr = properties.find("grid_y")) != properties.end()) {
		grid_y = std::stoi(properties["grid_y"]);
		ring->setPositionY(192.0f + 384.0 * ring->getScale() * grid_y);
	}

	// rotatable
	if ((itr = properties.find("rotatable")) != properties.end()) {
		ring->setRotatable(properties["rotatable"].compare("false") != 0);
	}

	if ((itr = properties.find("arm0")) != properties.end()) {
		ring->addArmAt(properties["arm0"].compare("-") != 0, 0);
	}

	if ((itr = properties.find("arm1")) != properties.end()) {
		ring->addArmAt(properties["arm1"].compare("-") != 0, 1);
	}

	if ((itr = properties.find("arm2")) != properties.end()) {
		ring->addArmAt(properties["arm2"].compare("-") != 0, 2);
	}

	if ((itr = properties.find("arm3")) != properties.end()) {
		ring->addArmAt(properties["arm3"].compare("-") != 0, 3);
	}

	this->addChild(ring);

	this->grid.emplace(std::make_pair(grid_x, grid_y), ring);

	return ring;
}

