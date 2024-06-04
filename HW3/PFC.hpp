#pragma once
#include "PF.h"


template<typename FuncClass>
class PFC: public PF
{
public:
	PFC(const FuncClass& func);
	bool isDefined(int32_t num) const override;
	int32_t operator()(int32_t num) const override;

	PF* clone() const override;
private:
	FuncClass func;

};


template<typename FuncClass>
PFC<FuncClass>::PFC(const FuncClass& func):func(func){}

template<typename FuncClass>
int32_t PFC<FuncClass>::operator()(int32_t num) const
{
	if (!isDefined(num))
	{
		throw std::logic_error("Not Defined");
	}

	return func(num).result;
}

template<typename FuncClass>
PF* PFC<FuncClass>::clone() const
{
	return new (std::nothrow) PFC(*this);
}

template<typename FuncClass>
bool PFC<FuncClass>::isDefined(int32_t num) const
{
	return func(num).isDef;
}
