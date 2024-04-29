#include"myvector.h"
using namespace std;
int main()
{
	try {
		MyVector<int> myVector(5);
		myVector[3] = 42;  // 正确的访问
		
		// 试图访问越界的索引
		int value = myVector[10];
		std::cout << "Value: " << value << std::endl;
	} catch (const std::out_of_range& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	
	// 使用自定义的MyVector类
	MyVector<int> myVector;
	// 添加元素
	cout << "push_back" << endl;
	for (int i = 0; i < 15; ++i)
	{
		myVector.pushback(i);
		// b.push_back(i);
	}
	cout<<myVector.Size()<<endl;
	for (int i = 0; i < myVector.Size(); i++)
	{
		cout << myVector[i] << " ";
	}
	cout << endl
	<< endl;
	cout << "empty" << endl;
	cout << myVector.empty() << endl;
	cout << endl;
	//	b.clear();
	cout << "pop_back" << endl;
	myVector.pop_back();
	cout<<myVector.Size()<<endl;
	for (int i = 0; i < myVector.Size(); i++)
	{
		cout << myVector[i] << " ";
	}
	cout << endl
	<< endl;
	cout << "resize" << endl;
	myVector.resize(20, 5);
	//cout<<"size"<<
	for (int i = 0; i < myVector.Size(); i++)
	{
		cout << myVector[i] << " ";
	}
	cout << endl
	<< endl;
	cout << "front" << endl;
	cout << myVector.front() << endl;
	// myVector=myVector2;
	//  使用迭代器遍历元素
	cout << endl;
	cout<<"back"<<endl;
	cout<<myVector.back()<<endl<<endl;
	cout<<"size"<<endl;
	cout <<myVector.Size()<<endl<<endl;
	cout<<"modify"<<endl;
	myVector.modify(10,100);
	for(MyVector<int>::Iterator i=myVector.begin();i!=myVector.end();i++)
		cout<<*i<<" ";
	
	return 0;
}

