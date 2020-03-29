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

	{
		auto ring = Ring::create();
		ring->setPosition(Vec2(768.0f, 1024.0f));
		ring->addArmAt(true, 0);
		ring->addArmAt(false, 2);
		this->addChild(ring);

		rings.push_back(std::shared_ptr<Ring>(ring));
	}

	{
		auto ring = Ring::create();
		ring->setPosition(Vec2(1152.0f, 1024.0f));
		ring->addArmAt(false, 1);
		ring->addArmAt(true, 3);
		this->addChild(ring);

		rings.push_back(std::shared_ptr<Ring>(ring));
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
		for (auto& ring : rings) {
			Rect ringbox = ring->getBoundingBox();
			if (ringbox.containsPoint(touch->getLocation())) {
				Rect leftRect(ringbox.getMinX(), ringbox.getMinY(), ringbox.getMidX() - ringbox.getMinX(), ringbox.getMaxY() - ringbox.getMinY());
				Rect rightRect(ringbox.getMidX(), ringbox.getMinY(), ringbox.getMaxX() - ringbox.getMidX(), ringbox.getMaxY() - ringbox.getMinY());

				if (leftRect.containsPoint(touch->getLocation())) {
					ring->rotateLeft();
				} else if (rightRect.containsPoint(touch->getLocation())) {
					ring->rotateRight();
				}

				return true; // if you are consuming it
			}
		}

    return false;
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

