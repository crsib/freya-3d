/* File		: FreyaSupport/Source/containers/policies/rehash/PrimeNumber.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "containers/policies/rehash/PrimeNumber.h"

namespace containers
{
	namespace policies
	{
		namespace rehash
		{
			// Taken from EASTL/src/hashtable.cpp
			static const uint32_t prime_numbers[] =
			{
				2u, 3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u,
				37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u, 79u,
				83u, 89u, 97u, 103u, 109u, 113u, 127u, 137u, 139u, 149u,
				157u, 167u, 179u, 193u, 199u, 211u, 227u, 241u, 257u,
				277u, 293u, 313u, 337u, 359u, 383u, 409u, 439u, 467u,
				503u, 541u, 577u, 619u, 661u, 709u, 761u, 823u, 887u,
				953u, 1031u, 1109u, 1193u, 1289u, 1381u, 1493u, 1613u,
				1741u, 1879u, 2029u, 2179u, 2357u, 2549u, 2753u, 2971u,
				3209u, 3469u, 3739u, 4027u, 4349u, 4703u, 5087u, 5503u,
				5953u, 6427u, 6949u, 7517u, 8123u, 8783u, 9497u, 10273u,
				11113u, 12011u, 12983u, 14033u, 15173u, 16411u, 17749u,
				19183u, 20753u, 22447u, 24281u, 26267u, 28411u, 30727u,
				33223u, 35933u, 38873u, 42043u, 45481u, 49201u, 53201u,
				57557u, 62233u, 67307u, 72817u, 78779u, 85229u, 92203u,
				99733u, 107897u, 116731u, 126271u, 136607u, 147793u,
				159871u, 172933u, 187091u, 202409u, 218971u, 236897u,
				256279u, 277261u, 299951u, 324503u, 351061u, 379787u,
				410857u, 444487u, 480881u, 520241u, 562841u, 608903u,
				658753u, 712697u, 771049u, 834181u, 902483u, 976369u,
				1056323u, 1142821u, 1236397u, 1337629u, 1447153u, 1565659u,
				1693859u, 1832561u, 1982627u, 2144977u, 2320627u, 2510653u,
				2716249u, 2938679u, 3179303u, 3439651u, 3721303u, 4026031u,
				4355707u, 4712381u, 5098259u, 5515729u, 5967347u, 6456007u,
				6984629u, 7556579u, 8175383u, 8844859u, 9569143u, 10352717u,
				11200489u, 12117689u, 13109983u, 14183539u, 15345007u,
				16601593u, 17961079u, 19431899u, 21023161u, 22744717u,
				24607243u, 26622317u, 28802401u, 31160981u, 33712729u,
				36473443u, 39460231u, 42691603u, 46187573u, 49969847u,
				54061849u, 58488943u, 63278561u, 68460391u, 74066549u,
				80131819u, 86693767u, 93793069u, 101473717u, 109783337u,
				118773397u, 128499677u, 139022417u, 150406843u, 162723577u,
				176048909u, 190465427u, 206062531u, 222936881u, 241193053u,
				260944219u, 282312799u, 305431229u, 330442829u, 357502601u,
				386778277u, 418451333u, 452718089u, 489790921u, 529899637u,
				573292817u, 620239453u, 671030513u, 725980837u, 785430967u,
				849749479u, 919334987u, 994618837u, 1076067617u, 1164186217u,
				1259520799u, 1362662261u, 1474249943u, 1594975441u,
				1725587117u, 1866894511u, 2019773507u, 2185171673u,
				2364114217u, 2557710269u, 2767159799u, 2993761039u,
				3238918481u, 3504151727u, 3791104843u, 4101556399u,
				4294967291u
			};

			inline uint32_t not_least_prime( uint32_t target )
			{
				static const uint32_t num_primes = sizeof( prime_numbers ) / sizeof ( uint32_t );

				int32_t d = num_primes;
				const uint32_t* first = prime_numbers;
				while(d > 0)
				{	
					const uint32_t* i = first;
					int32_t d2 = d >> 1;

					i += d2;

					if( *i < target )
					{
						first = ++i;
						d -= d2 + 1;
					}
					else
						d = d2;
				}

				return *(first);
			}

			uint32_t PrimeNumber::get_bucket_count( size_t elem, size_t bucket_count ) const
			{
				const uint32_t min_bucket_count = static_cast<uint32_t>(ceil(m_LoadFactor * elem));
				const uint32_t growth_factor_bucket_count = bucket_count * 2;

				uint32_t		desired_bucket_count 
					= min_bucket_count < growth_factor_bucket_count ? growth_factor_bucket_count : min_bucket_count;
				desired_bucket_count = not_least_prime(desired_bucket_count);
				m_NextRehashSize = static_cast<uint32_t>( m_LoadFactor * desired_bucket_count );
				return desired_bucket_count;
			}

		} // namespace rehash
	} // namespace policies
} // namespace containers