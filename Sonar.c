#include <list>
class Sonar
{

 public:
  int currentvalue;
  std::list<int> values;

  void in(int v)
  {
    currentvalue = v;
    values.push_back(v);
  }

  int state()
  {
    if(currentvalue<=20)
      {
	return 1;
	  }
    else
      {
	return 0;
	  }
  }

};
