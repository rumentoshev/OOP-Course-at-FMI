#include "Task.h"
#include "Constants.h"
#include <fstream>


Task::Task(const char* fileName):currNumToGenerate(INT32_MIN)
{
	loadInfo(fileName);
}

Task::Task(const Task& other)
{
	copyFrom(other);
}
Task::Task(Task&& other) noexcept
{
	moveFrom(std::move(other));
}

Task& Task::operator=(const Task& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;

}
Task& Task::operator=(Task&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Task::~Task()
{
	free();
}

void Task::moveFrom(Task&& other)
{
	function = other.function;
	other.function = nullptr;
}
void Task::copyFrom(const Task& other)
{
	function = other.function->clone();
}
void Task::free()
{
	delete function;
}

void Task::loadInfo(const char* fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open())
	{
		throw std::exception("File did not open!");
	}

	function = readFunctionFromFile(file);

	file.close();
}

PF* Task::readFunctionFromFile(std::istream& file)
{
	uint16_t T, N;

	file.read((char*)&N, sizeof(uint16_t));
	file.read((char*)&T, sizeof(uint16_t));

	if (N > 32)
	{
		throw std::logic_error("N > 32");
	}
	if (T == 0)
	{
		int32_t args[MAX_ARGS_NUM];
		int32_t res[MAX_ARGS_NUM];

		file.read((char*)&args, sizeof(int32_t) * N);
		file.read((char*)&res, sizeof(int32_t) * N);

		FuncType0 temp(args, res, N);
		return new PFC<FuncType0>(temp);
	}
	else if (T == 1 || T == 2)
	{
		int32_t args[MAX_ARGS_NUM];


		file.read((char*)&args, sizeof(int32_t)*N);

		if (T == 1)
		{
			FuncType1 temp(args, N);
			return new PFC<FuncType1>(temp);
		}
		else
		{
			FuncType2 temp(args, N);
			return new PFC<FuncType2>(temp);
		}
	}
	else if (T == 3 || T == 4)
	{
		PFCollection funcs;
		for (size_t i = 0; i < N; i++)
		{
			size_t index = 0;
			char buffer[MAX_BUFFER_SIZE];
			while (true)
			{
				file.read((char*)&buffer[index], sizeof(char));
				if (buffer[index++] == '\0')
				{
					std::ifstream fileNew(buffer, std::ios::binary);

					if (!fileNew.is_open())
					{
						throw std::exception("File did not open!");
					}

					funcs.addFunc(readFunctionFromFile(fileNew));

					fileNew.close();
					break;
				}
			}
			
		}

		if (T == 3)
		{
			return new MAXPF(funcs);
		}
		else
		{
			return new MINPF(funcs);
		}
	}
	else
	{
		throw std::logic_error("T is different from 0|1|2|3|4");
	}
}

void Task::printFromAtoB(int32_t A, int32_t B) const
{
	if (A > B)
	{
		int32_t temp = A;
		A = B;
		B = temp;
	}
	for (int32_t i = A; i <= B; i++)
	{
		try
		{
			std::cout << "| " << function->operator()(i) << " ";
		}
		catch (const std::logic_error& ex)
		{
			std::cout << "| " << i << " - Not def" << " ";
		}
		catch (...)
		{
			std::cout << "| " << i << " - Not def" << " ";
		}
	}
	std::cout << "|" << std::endl;
}

void Task::generateNextNum() const
{
	if (currNumToGenerate == INT32_MAX)
	{
		std::cout << "You have reached the limit of int32_t.";
		return;
	}
	if (!function->isDefined(currNumToGenerate))
	{
		++currNumToGenerate;

		generateNextNum();
	}
	else
	{
		std::cout << "The number is " << currNumToGenerate << " and the result is ";
		std::cout << function->operator()(currNumToGenerate) << std::endl;
		currNumToGenerate++;
	}
}