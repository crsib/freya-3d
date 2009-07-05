#ifndef STRINUTILS_H_
#define STRINUTILS_H_
#include "core/EString.h"
#include "core/EStringList.h"
namespace core
{
//!Trim leading spaces from string
EString	trim_leading_spaces(const EString& str);
//!Trim tailing spaces from string
EString	trim_tailing_spaces(const EString& str);
//!Remove empty lines from string
EString remove_empty_lines(const EString& str);
//!Remove leading, tailing spaces and empty lines from string
EString clean_string(const EString& str);

//!Split mode for string splitting
enum SplitMode
{
	//!Split string by spaces
	SPLIT_BY_SPACES = 1,
	//!Split string by newline
	SPLIT_BY_NEWLINE = 2
};
//!Split the string to list using mode described by SplitMode
EStringList split_to_list(const EString& str,unsigned mode);
//!Returns a string of {n_of_tabs} tabs
EString ident(unsigned n_of_tabs);
}
#endif /*STRINGTRIM_H_*/
