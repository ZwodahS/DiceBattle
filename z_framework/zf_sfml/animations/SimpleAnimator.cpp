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
#include "SimpleAnimator.hpp"
#include "AnimationObject.hpp"
#include "SpriteAnimationObject.hpp"
#include "SpriteReferenceAnimationObject.hpp"
#include "TextAnimationObject.hpp"
#include "AnimatableObject.hpp"
SimpleAnimator::SimpleAnimator()
{
}

SimpleAnimator::~SimpleAnimator()
{
    for(int i = 0 ; i < objects.size() ; i++)
    {
        delete objects[i];
    }
}

void SimpleAnimator::draw(sf::RenderWindow& window, sf::Time delta)
{
    for(int i = 0 ; i < objects.size() ; i++)
    {
        objects[i]->draw(window,delta);
    }
}

void SimpleAnimator::update(sf::RenderWindow& window, sf::Time delta)
{
    for(int i = objects.size() - 1 ; i >= 0 ; i--)
    {
        if(objects[i]->update(window,delta))
        {
            delete objects[i];
            objects.erase(objects.begin() + i);
        }
    }
}

void SimpleAnimator::fade(sf::Sprite sprite, int targetAlpha, float time)
{
    SpriteAnimationObject* obj = new SpriteAnimationObject(sprite);
    FadeInstruction* fi = new FadeInstruction(sprite.getColor().a, targetAlpha, time);
    obj->setInstruction(fi);
    objects.push_back(obj);
}

void SimpleAnimator::fadeReference(sf::Sprite &sprite, int targetAlpha , float time)
{
    SpriteReferenceAnimationObject* obj = new SpriteReferenceAnimationObject(sprite);
    FadeInstruction* fi = new FadeInstruction(sprite.getColor().a, targetAlpha, time);
    obj->setInstruction(fi);
    objects.push_back(obj);
}

void SimpleAnimator::fadeReference(iAnimatable& animatable,int startingAlpha, int targetAlpha, float time)
{
    AnimatableObject* obj = new AnimatableObject(animatable);
    FadeInstruction* fi = new FadeInstruction(startingAlpha, targetAlpha, time);
    obj->setInstruction(fi);
    objects.push_back(obj);
}

void SimpleAnimator::moveTo(sf::Sprite sprite, sf::Vector2f target , float time)
{
    SpriteAnimationObject* obj = new SpriteAnimationObject(sprite);
    MoveToInstruction* mi = new MoveToInstruction(sprite.getPosition(),target,time);
    obj->setInstruction(mi);
    objects.push_back(obj);
}
void SimpleAnimator::moveReferenceTo(sf::Sprite &sprite, sf::Vector2f target , float time)
{
    SpriteReferenceAnimationObject* obj = new SpriteReferenceAnimationObject(sprite);
    MoveToInstruction* mi = new MoveToInstruction(sprite.getPosition(),target,time);
    obj->setInstruction(mi);
    objects.push_back(obj);
}

void SimpleAnimator::moveReferenceTo(iAnimatable& animatable, sf::Vector2f target, float time)
{
    AnimatableObject* obj = new AnimatableObject(animatable);
    MoveToInstruction* mi = new MoveToInstruction(animatable.getPosition(), target, time);
    obj->setInstruction(mi);
    objects.push_back(obj);
}

void SimpleAnimator::move(sf::Sprite sprite, sf::Vector2f moveVec, float duration)
{
    SpriteAnimationObject* obj = new SpriteAnimationObject(sprite);
    MoveInstruction* mi = new MoveInstruction(moveVec, duration);
    obj->setInstruction(mi);
    objects.push_back(obj);
}

void SimpleAnimator::move(sf::Text text, sf::Vector2f moveVec, float duration)
{
    TextAnimationObject* obj = new TextAnimationObject(text);
    MoveInstruction* mi = new MoveInstruction(moveVec, duration);
    obj->setInstruction(mi);
    objects.push_back(obj);
}

void SimpleAnimator::moveReference(iAnimatable& animatable, sf::Vector2f moveVec, float duration)
{
    AnimatableObject* obj = new AnimatableObject(animatable);
    MoveInstruction* mi = new MoveInstruction(moveVec, duration);
    obj->setInstruction(mi);
    objects.push_back(obj);
}

void SimpleAnimator::colorshift(sf::Sprite sprite, sf::Color& sourceColor, sf::Color& targetColor , float duration)
{
    SpriteAnimationObject* obj = new SpriteAnimationObject(sprite);
    obj->setInstruction(new ColorShiftInstruction(sourceColor, targetColor, duration));
    objects.push_back(obj);
}

void SimpleAnimator::colorshiftReference(sf::Sprite& sprite, sf::Color& sourceColor, sf::Color& targetColor , float duration)
{
    SpriteReferenceAnimationObject* obj = new SpriteReferenceAnimationObject(sprite);
    obj->setInstruction(new ColorShiftInstruction(sourceColor, targetColor, duration));
    objects.push_back(obj);
}

CompositeInstruction* SimpleAnimator::composite(bool ordered)
{
    return new CompositeInstruction(ordered);
}

void SimpleAnimator::composite(sf::Sprite sprite, CompositeInstruction* instruction)
{
    SpriteAnimationObject* obj = new SpriteAnimationObject(sprite);
    obj->setInstruction(instruction);
    objects.push_back(obj);
}

void SimpleAnimator::composite(iAnimatable* animatable, CompositeInstruction* instruction)
{
    AnimatableObject* obj = new AnimatableObject(animatable);
    obj->setInstruction(instruction);
    objects.push_back(obj);
}

void SimpleAnimator::compositeReference(iAnimatable& animatable, CompositeInstruction* instruction)
{
    AnimatableObject* obj = new AnimatableObject(animatable);
    obj->setInstruction(instruction);
    objects.push_back(obj);
}

void SimpleAnimator::compositeReference(sf::Sprite &sprite, CompositeInstruction* instruction)
{
    SpriteReferenceAnimationObject* obj = new SpriteReferenceAnimationObject(sprite);
    obj->setInstruction(instruction);
    objects.push_back(obj);
}

void SimpleAnimator::composite(sf::Text text, CompositeInstruction* instruction)
{
    TextAnimationObject* obj = new TextAnimationObject(text);
    obj->setInstruction(instruction);
    objects.push_back(obj);
}

CompositeInstruction* SimpleAnimator::createBounceEffect(float bounceDistance, float timePerBounce, int numberOfBounce)
{
    CompositeInstruction* ci = composite(true);
    for(int i = 0 ; i < numberOfBounce ; i++)
    {
        ci->move(sf::Vector2f(0, -bounceDistance), timePerBounce/2);
        ci->move(sf::Vector2f(0, bounceDistance), timePerBounce/2);
    }
    return ci;
}
