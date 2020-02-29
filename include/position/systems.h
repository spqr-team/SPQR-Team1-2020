#pragma once

class LineSystem{
    public:
        virtual void update() = 0;
        virtual void test() = 0;
        bool tookLine;
};

class PositionSystem{
    public:
        virtual void update() = 0;
        virtual void test() = 0;
};