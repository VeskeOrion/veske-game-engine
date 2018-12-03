#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>


class Entity;


class Component {
public:
    Component();
    virtual ~Component();

    std::weak_ptr<Entity> entity;
    std::weak_ptr<Component> thisComponent;

    int executionOrder;
    bool active;

    virtual void init();
    virtual void destroy();
    virtual void pretick();
    virtual void tick();
    virtual void posttick();
};

#endif // COMPONENT_H