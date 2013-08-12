/*
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 * 
 * Copyright (C) 2013 ZwodahS(ericnjf@gmail.com) 
 * zwodahs.wordpress.com
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE **** YOU WANT TO.
 * 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. 
 */
#ifndef _ZF_SFML_ANIMATIONS_SIMPLEANIMATOR_H_
#define _ZF_SFML_ANIMATIONS_SIMPLEANIMATOR_H_
#include "FadeInstruction.hpp"
#include "MoveToInstruction.hpp"
#include "CompositeInstruction.hpp"
#include "ColorShiftInstruction.hpp"
#include "iAnimatable.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
// use this class to do simple animations for particles and entity that does not have collision 
class AnimationObject;
class SimpleAnimator
{
    // DO NOT reuse ANY instruction.
    public:
        SimpleAnimator();
        ~SimpleAnimator();
        // update the simple animator. All managed objects will be updated.    
        void update(sf::RenderWindow& window, sf::Time delta);
        // draw all the objects managed by this animators.
        void draw(sf::RenderWindow& window, sf::Time delta);
        // fade a sprite
        void fade(sf::Sprite sprite,int targetAlpha,float time);
        void fadeReference(sf::Sprite& sprite, int targetAlpha, float time);
        void fadeReference(iAnimatable& animatable,int startingAlpha, int targetAlpha, float time);
        // move a sprite to a position
        void moveTo(sf::Sprite sprite,sf::Vector2f target, float time);
        void moveReferenceTo(sf::Sprite &sprite, sf::Vector2f target, float time);
        void moveReferenceTo(iAnimatable& animatable, sf::Vector2f target, float time);
        // move a sprite by a vector. The vector is defined in pixel per sec.
        void move(sf::Sprite sprite, sf::Vector2f moveVec, float duration);
        void move(sf::Text text, sf::Vector2f moveVec, float duration);
        void moveReference(iAnimatable& animatable, sf::Vector2f moveVec, float duration);
        /**
         * Color shifting animations.
         * The object needs to have a getColor() function.
         */
        void colorshift(sf::Sprite sprite, sf::Color& sourceColor, sf::Color& targetColor, float duration);
        void colorshiftReference(sf::Sprite& sprite, sf::Color& sourceColor, sf::Color& targetColor, float duration);
        // easy to construct a one-liner
        // sa.composite(sprite, sa.composite()->move(...)->fade(...));
        CompositeInstruction* composite(bool ordered = false); // use this to construct the instructionn for the method below.
        void composite(sf::Sprite sprite, CompositeInstruction* instruction);
        // use this to delete the iAnimatable after the animation completes.
        void composite(iAnimatable* animatable, CompositeInstruction* instruction);
        void compositeReference(sf::Sprite &sprite, CompositeInstruction* instruction);
        void compositeReference(iAnimatable& animatable, CompositeInstruction* Instruction);
        //TODO : make the same functions for text.
        void composite(sf::Text text, CompositeInstruction* instruction);


        /**
         * A simple composite instruction for bouncing.
         */
        CompositeInstruction* createBounceEffect(float bounceDistance, float timePerBounce, int numberOfBounce);
        std::vector<AnimationObject*> objects;
    private:

};
#endif
