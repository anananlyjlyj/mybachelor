#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm> //transform
#include<string>
#include"format_numbers.php"

std::vector<int> vec_to_int (std::vector<double> v)
{
    std::vector<int> result(v.size(), 0);
    std::transform(v.begin(), v.end(), result.begin(),
        [](double d){
            return std::round(d);
        }
        );
    return result;
}

std::vector<double> vec_rounded (std::vector<double> v)
{
    std::vector<double> result(v.size(), 0.0);
    std::transform(v.begin(), v.end(), result.begin(),
        [](double d){
            return std::round(d * 100.0) / 100.0;
        }
        );
    return result;
}