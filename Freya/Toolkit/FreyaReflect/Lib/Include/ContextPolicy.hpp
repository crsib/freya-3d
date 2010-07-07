#ifndef ContextPolicy_h__
#define ContextPolicy_h__
#include <iostream>

class custom_directives_hooks
	:   public boost::wave::context_policies::default_preprocessing_hooks
{
public:
	template <typename ContextT, typename ContainerT>
	bool
		found_unknown_directive(ContextT const& ctx, ContainerT const& line, 
		ContainerT& pending)
	{
		//temp hook
		std::copy(line.begin(), line.end(), std::back_inserter(pending));
		return true;
	}
	template <typename ContextT>
	bool found_include_directive(ContextT const& ctx, 
		std::string const &filename, bool include_next)
	{
	//	std::cout << "Loading " << filename << std::endl;
		return false;
	}
};

#endif // ContextPolicy_h__