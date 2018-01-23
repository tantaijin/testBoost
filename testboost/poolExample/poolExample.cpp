#include "stdafx.h"
#include <vector>
#include "poolExample.h"
#include "boost\pool\pool.hpp"
#include "boost\pool\object_pool.hpp"
#include "boost\pool\pool_alloc.hpp"

/*
** object_pool test
*/
struct demo_class{
public:
	int a;
	int b;
	int c;
	demo_class(int x=1, int y=2, int z=3):a(x),b(y),c(z){}
};

void testpool()
{
	/*
	** pool 
	*/
	boost::pool<> pl(sizeof(int));
	int *p = (int*)pl.malloc();
	assert(pl.is_from(p));
	pl.free(p);

	for (int i = 0; i < 10; i++)
	{
		pl.ordered_malloc();
	}

	/*
	** object_pool
	*/
	boost::object_pool<demo_class> opl;
	demo_class* pdemo = opl.malloc();
	assert(opl.is_from(pdemo));
	assert(pdemo->a != 1);

	pdemo = opl.construct(7, 8, 9); // 不能多于3个参数，否则要走扩展
	assert(pdemo->a == 7);

	boost::object_pool<std::string> spl;
	for (int i = 0; i < 2; i++)
	{
		std::string *s = spl.construct("hello boject_pool");
		std::cout << s->c_str() << std::endl;
	}

	/*
	** boost::singleton_pool 接口与 pool 一样，只是都是静态的，并且是线程安全的
	*/
	std::vector<int, boost::pool_allocator<int>> v;
	v.emplace_back(1);
	std::cout << "pool_allocator test, size is " << v.size() << std::endl;
}