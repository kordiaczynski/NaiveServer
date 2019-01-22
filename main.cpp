
#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>
std::function<void()> retFun()
{

int counter =0;
return	[&](){
	int internal = counter;
	std::cout << internal;
	internal++;
	std::cout << std::endl;
};
}



int main()
{

	std::vector<int> vec = { 1,2,3,5,6,7,8 };

	std::vector<int>::iterator post = std::remove_if(vec.begin(), vec.end(), [](int i) {
		if( i < 5 )
			return true;
			
			return false;
	});	
	for( std::vector<int>::iterator it = vec.begin(); it != post; ++ it)
	{
		std::cout << *post;
	}	

//	std::function<void()> counter1 = retFun();
//	std::function<void()> counter2 = retFun();

//	counter1();
//	counter1();
//	counter2();
	




return 0;
}
