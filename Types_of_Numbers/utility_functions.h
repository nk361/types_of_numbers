#pragma once

class utility_functions
{
public:
	//adds any type values not found from the first list to the second list
	template <class MyType>
	std::vector<MyType> static add_missing(std::vector<MyType> const& list1, std::vector<MyType> const& list2)
	{
		std::vector<MyType> temp = list2;
		bool missing = true;
		for (size_t i = 0; i < list1.size(); i++, missing = true)
		{
			for (size_t j = 0; j < temp.size(); j++)
				if (list1[i] == temp[j])
					missing = false;
			if (missing)
				temp.push_back(list1[i]);
		}
		return temp;
	}
};
