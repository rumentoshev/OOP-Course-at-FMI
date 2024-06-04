#pragma once
#include "PF.h"
#include "PFC.hpp"
#include "MAXPF.h"
#include "MINPF.h"
#include "FuncType0.h"
#include "FuncType1.h"
#include "FuncType2.h"
#include "Constants.h"


class Task
{
public:
	Task(const char* fileName);

	Task(const Task& other);
	Task(Task&& other) noexcept;

	Task& operator=(const Task& other);
	Task& operator=(Task&& other) noexcept;

	~Task() noexcept;

	void printFromAtoB(int32_t A, int32_t B) const;
	void generateNextNum() const;

private:
	PF* function;
	mutable int32_t currNumToGenerate;

	void moveFrom(Task&& other);
	void copyFrom(const Task& other);
	void free();

	void loadInfo(const char* fileName);
	PF* readFunctionFromFile(std::istream& file);
};