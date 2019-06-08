#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

//a)
template <typename ElementType, typename LessThanFunctor>
bool check_sorted(std::vector<ElementType> const & v, LessThanFunctor less_than){
  for (int k = 1; k<v.size(); ++k)
  {
    if(less_than(v[k], v[k-1]))       //verwende Funktor
      return false;
  }
  return true;
}

//b)
template <typename Iterator, typename LessThanFunctor>
bool check_sorted(Iterator begin, Iterator end, LessThanFunctor less_than){
  if (begin == end)
    return true;
  Iterator next = begin;
  ++next;
  for (; next != end; ++begin, ++next)
  {
    if (less_than(*next, *begin))
      return false;
  }
  return true;
}

//c)
// pass-by-reference, weil v verändert werden soll
template <typename ElementType, typename LessThanFunctor>
void insertion_sort(std::vector<ElementType> & v, LessThanFunctor less_than){
  for(int k=1; k<v.size(); ++k)
  {
    ElementType current = v[k]; // Element, das jetzt einsortiert wird
    int j = k;                  // Anfangsposition der Lücke
    while(j > 0)
    {
      if(less_than (current, v[j-1]))
        v[j] = v[j-1];          // Luecke eine Position nach links
      else
        break;                  // Luecke jetzt an richtiger Position
      --j;
    }
    v[j] = current;             // Element in die Luecke einfuegen
  }
}

//d)
template <typename Iterator, typename LessThanFunctor>
void insertion_sort(Iterator begin, Iterator end, LessThanFunctor less_than){
  if(begin == end)
    return; // leeres Array => nichts zu tun
  Iterator k = begin;
  ++k;
  for(; k != end; ++k)
  {
    auto current = *k;
    Iterator j = k;
    Iterator j_1 = k;    // soll j-1 darstellen, da *(j-1) nicht erlaubt ist
    --j_1;
    while(j != begin)
    {
      if(less_than (current, *(j_1)))
      {
        *j = *(j_1);
      }
      else
      {
        break;
      }
      --j_1;
      --j;
    }
    *j = current;
  }
}

int main(){
  std::vector<int> vec;
  for (int i=9; i>0; --i)
    vec.push_back(i);
  vec.push_back(9);

  std::sort(vec.begin(), vec.end(), [] (int a, int b){return a>b;});
  std::cout<<"sorted vector: "<<std::endl;
  for(auto const & temp : vec) std::cout<<temp<<" ";
  std::cout<<std::endl;

  //a)
  assert(check_sorted(vec, [](int a, int b){return a>b;}));
  std::random_shuffle(vec.begin(),vec.end());
  assert(!check_sorted(vec, [](int a, int b){return a>b;}));

  //b)
  std::sort(vec.begin(), vec.end(), [] (int a, int b){return a>b;});
  assert(check_sorted(vec.begin(), vec.end(), [](int a, int b){return a>b;}));
  std::random_shuffle(vec.begin(),vec.end());
  assert(!check_sorted(vec.begin(), vec.end(), [](int a, int b){return a>b;}));

  //c)
  insertion_sort(vec, [] (int a, int b){return a>b;});
  assert(check_sorted(vec.begin(), vec.end(), [](int a, int b){return a>b;}));
  std::random_shuffle(vec.begin(),vec.end());
  assert(!check_sorted(vec.begin(), vec.end(), [](int a, int b){return a>b;}));

  //d)
  insertion_sort(vec.begin(), vec.end(), [] (int a, int b){return a>b;});
  assert(check_sorted(vec.begin(), vec.end(), [](int a, int b){return a>b;}));
  std::random_shuffle(vec.begin(),vec.end());
  assert(!check_sorted(vec.begin(), vec.end(), [](int a, int b){return a>b;}));

  return 0;
}
