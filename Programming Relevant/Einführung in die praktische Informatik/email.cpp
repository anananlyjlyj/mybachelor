#include <string>
#include <cassert>

bool is_email(std::string s)
{
	int size = s.size();
	for(int i = 0; i < size; )
	{
		if(std::isalnum(s[i]) || s[i] == '.' || s[i] == '_' || s[i] == '-' || s[i] == '@')
		{
			i++;
		}
		else
			return false;
	}
	int m = s.find('@');
	int n = s.rfind('@');
	if(m == std::string::npos || m != n || m == 0)
	{
		return false;
	}
	int lastpkt = s.rfind('.');
	if(lastpkt == std::string::npos || lastpkt <= m + 1 || lastpkt == size - 1)
	{
		return false;
	}
	return true;
}

int main()
{
	assert(is_email("email@email.com"));
	assert(is_email("e-mail@e_mail.com"));
	assert(is_email("1mail@-0mail.com"));
	assert(is_email("stu.den.t@uni.hd.de"));
	assert(is_email(".stu-_@u.ni"));
	assert(is_email("69117@1386.2016"));
	assert(is_email("@i"));
	assert(is_email("@uni.de"));
	assert(is_email("uni@.de"));
	assert(is_email("uni@de."));
	assert(is_email("+a@uni.de"));
	assert(is_email("uni@hd@de"));
	return 0;
}