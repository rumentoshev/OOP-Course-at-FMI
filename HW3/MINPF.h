#pragma once
#include "ExtrF.h"
#include "PFCollection.h"

class MINPF : public PF
{
public:
	MINPF(const PFCollection& functions);

	bool isDefined(int32_t num) const override;
	int32_t operator()(int32_t num) const override;

	PF* clone() const override;
private:

	PFCollection functions;
};