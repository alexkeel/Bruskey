#include <BuiltInFunction.hpp>

BuiltInFunction::BuiltInFunction(Identifier *functionName, std::vector<Expression *> *argumentList)
{
    if(functionName->toCode() == "Pause")
    {
        this->expression = "delay";
    }

    this->argumentList = argumentList;

    this->expression += "(";
    for(int i = 0; i < this->argumentList->size(); i++)
    {        
        if(i == this->argumentList->size() - 1)
        {
            this->expression += this->argumentList->at(i)->toCode();
        }
        else
        {
            this->expression += this->argumentList->at(i)->toCode() + ",";
        }        
    }
    this->expression += ")";
}

BuiltInFunction::BuiltInFunction(Identifier *functionName)
{
    if(functionName->toCode() == "ObstacleDetected")
    {
        this->expression = "initio_IrLeft() !=0 || initio_IrRight() !=0";
    }
    else if (functionName->toCode() == "Stop") 
    {
        this->expression = "initio_DriveForward(speed)";
    }
    else if(functionName->toCode() == "BlobVisible")
    {
        this->expression = "blobDetected(blob)";
    }
    else if(functionName->toCode() == "SpinLeft")
    {
        this->expression = "initio_SpinLeft(speed)";
    }
    else if(functionName->toCode() == "SpinRight")
    {
        this->expression = "initio_SpinRight(speed)";
    }
    else if (functionName->toCode() == "DriveForward") 
    {
        this->expression = "initio_DriveForward(speed)";
    }
    else if(functionName->toCode() == "DriveBackwards")
    {
        this->expression = "initio_DriveReverse(speed)";
    }
}

std::string BuiltInFunction::toCode() const
{
    return this->expression;
}