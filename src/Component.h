#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
    Component();
    virtual ~Component();

    int executionOrder;
    bool active;

    virtual void init();
    virtual void destroy();
    virtual void pretick();
    virtual void tick();
    virtual void posttick();
};

#endif // COMPONENT_H