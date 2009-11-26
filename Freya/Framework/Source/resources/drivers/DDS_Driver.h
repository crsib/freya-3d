#ifndef DDS_DRIVER_H_
#define DDS_DRIVER_H_

#include <resources/ResourceManagerDriver.h>
#include <core/drivermodel/DriverID.h>

namespace resources {

	namespace drivers {

		template<typename _Tp>
		class  DDSDriverID : public core::drivermodel::DriverID
		{
		public:
			//could be created only if _Tp is DDSDriver9 or DDSDriver10
			inline DDSDriverID();
			virtual core::drivermodel::Driver* create() const {
				return new _Tp;
			}
			virtual EString id() const;
		};//class DDSDriverID

		//abstract DDS Driver class
		class DDSDriver : public resources::ResourceManagerDriver {
			virtual ~DDSDriver() = 0;
		public:
			virtual resources::Resource* loadSynchronous(const EString&);
			virtual resources::Resource* loadAsynchronous(const EString&);
			
			virtual EString id() const = 0;
			virtual bool unique() const = 0;
			virtual void destroy(Resource*) = 0;
		};//class DDSDriver

		//Driver used to load DirectX9 DDS file
		class DDSDriver9 : public DDSDriver {
			/*OpenGL dependencies :
			*/
			//DirectX dependencies : partial DirectX9 hardware support
			friend class DDSDriverID<DDSDriver9>;
			friend class resources::ResourceManager;

			DDSDriver9() { }
			virtual ~DDSDriver9() { }
		public :
			virtual resources::Resource* loadSynchronous(const EString&);
			virtual resources::Resource* loadAsynchronous(const EString&);
			
			virtual EString id() const;
			virtual bool unique() const {
				return true;
			}
			virtual void destroy(Resource*);
		};//class DDSDriver9

		//Driver used to load DirectX10 DDS file
		class DDSDriver10 : public DDSDriver {
			/*OpenGL dependencies :
			*/
			//DirectX dependencies : DirectX10 hardware support
			friend class DDSDriverID<DDSDriver10>;
			friend class resources::ResourceManager;
			DDSDriver10();
			virtual ~DDSDriver10();
		public :
			virtual resources::Resource* loadSynchronous(const EString&);
			virtual resources::Resource* loadAsynchronous(const EString&);

			virtual EString id() const;
			virtual bool unique() const {
				return true;
			}
			virtual void destroy(Resource*);
		};//class DDSDriver10

	} //namespace drivers

}//namespace resources

#endif//DDS_DRIVER_H_