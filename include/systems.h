#pragma once

class LineSystem{
    public:
        virtual void update() = 0;
        virtual void test() = 0;
};

class PositionSystem{
    public:
        virtual void update() = 0;
        virtual void test() = 0;
};