#include "core/Utils/StringUtils.h"
#include <iostream>
namespace core
{

namespace __string_utils_internal
{
const char	white_space[] = {' ','\t'};
const char	new_line[] = {'\n'};

inline bool	isWhiteSpace(char ch)
{
	unsigned i;
	for(i = 0;i<sizeof(white_space);i++)
		if(white_space[i] == ch)
			return true;
	return false;
}

inline bool isNewLineDelim(char ch)
{
	unsigned i;
	for(i = 0;i<sizeof(new_line);i++)
		if(new_line[i] == ch)
			return true;
	return false;
}

inline bool isDelim(char ch)
{
	return isWhiteSpace(ch) || isNewLineDelim(ch);
}
}

EString	trim_leading_spaces(const EString& str)
{
	EString ret(str);
	EString::iterator it = ret.begin();
	for(;(it!=ret.end())&&__string_utils_internal::isWhiteSpace(*it);it++);
	ret.erase(ret.begin(),it);
	return ret;
}

EString	trim_tailing_spaces(const EString& str)
{
	EString ret(str);
	EString::reverse_iterator it = ret.rbegin();
	for(;(it!=ret.rend())&&__string_utils_internal::isWhiteSpace(*it);it++);
	ret.erase(it.base(),ret.end());
	return ret;
}

EString remove_empty_lines(const EString& str)
{
	EString ret(str);
	EString::iterator it = ret.begin();
	EString::iterator beg = it;
	while(true)
	{
		for(;(it!=ret.end())&&__string_utils_internal::isWhiteSpace(*it);it++);
		if(__string_utils_internal::isNewLineDelim(*it))
		{
			size_t dist = beg - ret.begin();
			ret.erase(beg,it+1);
			beg = it = ret.begin() + dist;
			continue;
		}
		else if(it == ret.end())
		{
			ret.erase(beg,it);
			return ret;
		}
		for(;(it!=ret.end())&&__string_utils_internal::isNewLineDelim(*it);it++);
		if(it == ret.end())
			break;
		beg = ++it;
		if(it == ret.end())
			break;
	}
	return ret;
}

EString clean_string(const EString& str)
{
	EString ret = "";
	EStringList lst = split_to_list(str,SPLIT_BY_NEWLINE);
	size_t sz = lst.size();
	for(unsigned i = 0;i < sz; i++)
	{
		ret += core::trim_leading_spaces(core::trim_tailing_spaces(lst[i]));
		if(i != sz -1)
			ret += EString("\n");
		//std::cout << "STR: " << core::trim_leading_spaces(core::trim_tailing_spaces(lst[i])) << std::endl;
	}
	return ret;
}


EStringList split_to_list(const EString& str,unsigned mode) //SplitMode enum or'ed
{
	if(str.length() == 0)
		return EStringList();
	bool (*split)(char c) = NULL;
	switch(mode)
	{
	case  SPLIT_BY_SPACES:
		split = __string_utils_internal::isWhiteSpace;
		break;

	case  SPLIT_BY_NEWLINE:
		split = __string_utils_internal::isNewLineDelim;
		break;

	case (SPLIT_BY_SPACES | SPLIT_BY_NEWLINE):
		split = __string_utils_internal::isDelim;
	break;
	}
	EString ret(str);
	EString::iterator it = ret.begin();
	EStringList lst;
	while(true)
	{
		while(true)
		{
			if(split(*it))
				if(!split(*(it+1)))
				{
					it++;
					break;
				}
			if(++it == ret.end())
			{
				lst.push_back(ret);
				return lst;
			}
		}
		//for(;it!=ret.end()&&!split(*it);it++);

		//std::cout << EString("DBG: ") <<  ret.substr(0,(it-ret.begin())) << " vs " << remove_empty_lines(ret.substr(0,(it-ret.begin()))) << std::endl;
		EString s = remove_empty_lines(ret.substr(0,(it-ret.begin())));
		if(s.length() > 0)
			lst.push_back(s);
		if(it == ret.end())
			break;
		ret.erase(ret.begin(),it);
		it = ret.begin();
	}
	return lst;
}

EString ident(unsigned n_of_tabs)
{
	return EString(n_of_tabs,'\t');
}

}
