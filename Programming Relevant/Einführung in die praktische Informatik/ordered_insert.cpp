#include <vector>
#include <iostream>

std::vector <int> sortint()
{
	std::vector <int> zahlen;
	for(int k = 0; k < 100; k++)
	{
		std::cout << "Bitte geben Sie eine Zahl.";
		int temp;
		std::cin >> temp;
		if (temp < 0)
			break;
		else if(k == 0)
		{
			zahlen.push_back(temp);
		}
		else
		{
			for(int i = 0; i < k; i++)
			{
				if(temp <= zahlen[i])
				{
					zahlen.insert(zahlen.begin() + i, temp);
					break;
				}
				else if(i == k - 1)
				{
					zahlen.push_back(temp);
				}
			}
		}
	}
	for(int i = 0; i < zahlen.size(); i++)
	{
		std::cout << zahlen[i] << " ";
	}
	return zahlen;
}

int main()
{
	sortint();
	return 0;
}