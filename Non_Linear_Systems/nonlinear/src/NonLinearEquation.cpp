//
// Created by Rick Wang on 2019/12/2.
//

#include "../NonLinearEquation.h"

//Constructor
NonLinearEquation::NonLinearEquation()
{
    dim = 0;
    funPtrArray = nullptr;
    dfunPtrArray = nullptr;
    fpPtr = nullptr;
}

NonLinearEquation::NonLinearEquation(NonLinearEquation &copy)
{
    dim = copy.GetDimension();
    funPtrArray = copy.GetFunArray();
    dfunPtrArray = copy.GetDfunArray();
    fpPtr = copy.GetFpFun();
}

NonLinearEquation::NonLinearEquation(functions_type *funArray, functions_type **dfunArray,functions_type fixedPoint, int dimension)
{
    dim = dimension;
    funPtrArray = funArray;
    dfunPtrArray = dfunArray;
    fpPtr = fixedPoint;
}

NonLinearEquation::NonLinearEquation(functions_type *funArray, functions_type **dfunArray, int dimension)
{
    dim = dimension;
    funPtrArray = funArray;
    dfunPtrArray = dfunArray;
    fpPtr = nullptr;
}


NonLinearEquation::~NonLinearEquation()
{

}

int NonLinearEquation::GetDimension()
{
    return dim;
}

functions_type* NonLinearEquation::GetFunArray()
{
    return funPtrArray;
}

functions_type** NonLinearEquation::GetDfunArray()
{
    return dfunPtrArray;
}

functions_type NonLinearEquation::GetFpFun()
{
    return fpPtr;
}

//Set Member Functions
void NonLinearEquation::SetDimension(int dimension)
{
    this->dim = dimension;
}

void NonLinearEquation::SetFunArray(functions_type *funarray)
{
    this->funPtrArray = funarray;
}

void NonLinearEquation::SetDFunArray(functions_type **dfunarray)
{
    this->dfunPtrArray = dfunarray;
}

void NonLinearEquation::SetFpFun(functions_type fp)
{
    this->fpPtr = fp;
}

double* NonLinearEquation::GetFunctionValue(double *input)
{
    //the order of rows of input is consistent with the order of equation
    double* output = nullptr;
    output = new double[dim];

    for(int i=0;i<dim;i++)
    {
        output[i] = funPtrArray[i](input);
    }

    return output;

}

//overload for 1 dimension
double NonLinearEquation::GetFunctionValue(double input)
{
    if(dim>1){
        std::cout<<"Dimension is more than 1, please check"<<std::endl;
        return 0.0;
    }

    double* x = new double[1];
    x[0] = input;

    return funPtrArray[0](x);

}

//get fixed point function value
double NonLinearEquation::GetFpFunctionValue(double input)
{
    if(dim==1&&fpPtr!= nullptr)
    {
        return fpPtr(&input);
    }
    else{
        std::cout<<"Cannot get fixed point function value, please check"<<std::endl;
        return 0;
    }
}

double** NonLinearEquation::GetDfunctionValue(double *input)
{
    double** output = nullptr;
    output = new double*[dim];

    for(int i=0;i<dim;i++)
    {
        output[i] = new double[dim];
    }

    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
        {
            output[i][j] = dfunPtrArray[i][j](input);
        }

    return output;
}

//overload for 1 dimension
double NonLinearEquation::GetDfunctionValue(double input)
{
    if(dim>1){
        std::cout<<"Dimension is more thant 1, please check"<<std::endl;
        return 0.0;
    }

    double* x = new double[1];
    x[0] = input;

    return dfunPtrArray[0][0](x);
}



