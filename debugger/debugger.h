#pragma once

class Debugger
{
public:
    bool doPause = false;
    bool doStep = false;
    bool doPrint = false;
    bool doTileRender = false;
    bool incrementPC = false;
    bool doPrint2;
};