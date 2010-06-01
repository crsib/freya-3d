#ifndef ContextPolicy_h__
#define ContextPolicy_h__

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

	//Disable include directives
	template <typename ContextT>
	bool found_include_directive(ContextT const& ctx, 
		std::string const &filename, bool include_next)
	{
		return true;
	}
};

#endif // ContextPolicy_h__