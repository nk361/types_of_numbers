#pragma once

class utility_functions
{
public:
	template <class my_type>
	std::vector<my_type> static add_item(my_type const& item, std::vector<my_type> list) { list.insert(list.end(), item); return list; }

	template <class my_type>
	std::vector<my_type> static add_missing(std::vector<my_type> const& list1, std::vector<my_type> const& list2)//adds characters not found from the first list to the second list
	{
		std::vector<my_type> temp = list2;
		bool missing = true;
		for (int i = 0; i < list1.size(); i++, missing = true)
		{
			for (int j = 0; j < temp.size(); j++)
				if (list1[i] == temp[j])
					missing = false;
			if (missing)
				temp.push_back(list1[i]);
		}
		return temp;
	}
};