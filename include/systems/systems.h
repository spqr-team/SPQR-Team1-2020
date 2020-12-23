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
        virtual void goCenter() = 0;
        virtual void centerGoal() = 0;
};

class LineSystemEmpty : public LineSystem{
    public:
        void update() override;
        void test() override;
};

class PositionSystemEmpty : public PositionSystem{
    public:
        void update() override;
        void test() override;
        void goCenter() override;
        void centerGoal() override;
};