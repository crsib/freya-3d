/* File         : FreyaReflectBinary: ReflectedElement.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include <boost/shared_ptr.hpp>
#include <string>

namespace base
{
	class ReflectedElement;
	class ReflectedScope;

#define static unsigned getClassID() { static unsigned int = -1}

	typedef boost::shared_ptr<ReflectedElement> reflected_element_ptr;

	class ReflectedElement
	{
		ReflectedElement(const ReflectedElement&);
		ReflectedElement& operator = (const ReflectedElement&);
	public:
		ReflectedElement(const std::string& name, ReflectedScope* parent = NULL) : m_Parent(parent), m_Name(name) {}
		virtual ~ReflectedElement() {}

		const std::string&          getElementName() const { return m_Name; }
		void                        setElementName(const std::string& name) { m_Name = name; }

		ReflectedScope*             getParent() { return m_Parent; }
		const ReflectedScope*       getParent() const { return m_Parent; }

		void                        setParent(ReflectedScope* parent) { m_Parent = parent; } 
	protected:
		ReflectedScope*           m_Parent;
		std::string				  m_Name;
	};

}