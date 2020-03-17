#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<thread>
#include<string>
#include<ctime>

using namespace std;

	vector<short int> Zero(1,0);
	vector<short int> One(1,1);
	vector<short int> Two(1,2);
	const long long max_rand = 100000000000;
	
	void TEST_from_to(int id);
	void TEST_Sum(int id);
	void TEST_Sub(int id);
	void TEST_Mul(int id);
	

	void print_super_long(vector<short int> super)
	{
		for(unsigned int i = 0; i < super.size(); i++)
		{
			cout << super[i];
		}
		cout << endl;
	}

	long long super_long_to_long_long(vector<short int> super)
	{
		long long multiplier = 1;
		long long num = 0;
		for(int i = super.size() - 1; i > -1; i--)
		{
			num += super[i] * multiplier;
			multiplier *= 10;
		}
		return num;
	}

	vector<short int> long_long_to_super_long(long long num)
	{
			vector<short int> super_long;
			
			while(num > 0)
			{
				super_long.push_back(num % 10);
				num /= 10;
			}
			reverse(super_long.begin(), super_long.end());
			
			return super_long;
	}

	void RemoveLeadingZeros(vector<short int>* num)
	{
		int k = 0;
		
		if((*num)[k] != 0)
		{
			return;
		}
		k++;
		
		while((*num)[k] == 0)
		{
			k++;
		}
		num->erase(num->begin(), num->begin() + k);
	}



	vector<short int> Sub(vector<short int> a, vector<short int> b)
	{
		vector<short int> ans(a.size(), 0);
		if(a.size() < b.size())
		{
			throw "The first can not be less than the second";
		}
		else if(a.size() == b.size())
		{
			for (unsigned int i = 0; i < a.size(); i++)
			{
				if(a[i] > b[i])
				{
					break;
				}
				else if(a[i] < b[i])
				{
					throw "The first can not be less than the second";
				}
				else if(i == a.size() - 1)
				{
					return Zero;
				}
			}
		}
		
		for(unsigned int i = 0; i < a.size(); i++)
		{
			ans[i] = a[i];
		}
		
		for(int i = a.size() - 1, j = b.size() - 1; j > - 1; i--, j--)
		{
			ans[i] -= b[j];
			if(ans[i] < 0)
			{
				ans[i] += 10;
				ans[i - 1]--;
				
				if(ans[i - 1] < 0 && j == 0)
				{
					ans[i - 2]--;
					ans[i - 1] += 10;
				}
			}
		}
		RemoveLeadingZeros(&ans);
		return ans;
	}

	vector<short int> Sum(vector<short int> a, vector<short int> b)
	{
		vector<short int> ans(max(a.size(), b.size()) + 1, 0);
		
		if(b.size() >= a.size())
		{
			for(unsigned int i = 0; i < b.size(); i++)
			{
				ans[i + 1] = b[i];
			}
			
			for(int i = a.size() - 1, j = b.size() - 1; i > -1; i--,j--)
			{
				ans[j + 1] += a[i];
				if(ans[j + 1] > 9)
				{
					ans[j]++;
					ans[j + 1] -= 10;
				}	
			}
		}
		else
		{
			for(unsigned int i = 0; i < a.size(); i++)
			{
				ans[i + 1] = a[i];
			}
			
			for(int i = b.size() - 1, j = a.size() - 1; i > -1; i--,j--)
			{
				ans[j + 1] += b[i];
				if(ans[j + 1] > 9)
				{
					ans[j]++;
					ans[j + 1] -= 10;
				}	
			}
		}
		
		RemoveLeadingZeros(&ans);

		return ans;
	}

	
	vector<short int> Mul(vector<short int> a, vector<short int> b)
	{
		if(a == Zero || b == Zero)
		{
			return Zero;
		}
		else if(a == One)
		{
			return b;
		}
		else if(b == One)
		{
			return a;
		}
		
		vector<short int> ans(a.size() + b.size(), 0);
		
		//short int mod = 0;
		
		if(a.size() >= b.size())
		{
			for(int l = 0; l < b.size(); l++)
			{
				for(int j = a.size() - 1, k = ans.size() - 1 - l; j > - 1; j--, k--)
				{
					ans[k] += a[j] * b[b.size() - l - 1];
					if(ans[k] > 9)
					{
						ans[k - 1] += ans[k] / 10;
						ans[k] %= 10; 
					}
				}
			}
		}
		else
		{
			for(int l = 0; l < a.size(); l++)
			{
				for(int j = b.size() - 1, k = ans.size() - 1 - l; j > - 1; j--, k--)
				{
					ans[k] += a[a.size() - 1 - l] * b[j];
					if(ans[k] > 9)
					{
						ans[k - 1] += ans[k] / 10;
						ans[k] %= 10; 
					}
				}
			}
		}
		
		RemoveLeadingZeros(&ans);
		return ans;
	}


	pair<vector<short int>, vector<short int>> Div(vector<short int> a, vector<short int> b)
	{
		vector<short int> ans(a.begin(), a.end());
		vector<short int> mod(a.begin(), a.end());
		
		
	}

int main()
{	
	srand(time(NULL));
	
	string a;
	cout << "12";
	cin>>a;
	
	vector<thread> threads;
	
	for(int i = 0; i < 5; i++)
	{
		thread thr(TEST_from_to, i);
		threads.emplace_back(move(thr));
	}
	
	for(int i = 5; i < 10; i++)
	{
		thread thr(TEST_Sum, i);
		threads.emplace_back(move(thr));
	}
	
	for(int i = 11; i < 16; i++)
	{
		thread thr(TEST_Sub, i);
		threads.emplace_back(move(thr));
	}
	
	for(int i = 16; i < 21; i++)
	{
		thread thr(TEST_Mul, i);
		threads.emplace_back(move(thr));
	}
	
	for(auto& thr : threads) 
	{
        thr.join();
    }
    
}


void TEST_from_to(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;

	for(int i = 0; i < 10000; i++)
	{
		a = abs((rand() % max_rand) * 1);
		b = abs((rand() % max_rand) * 1);
		cout << a << endl;
		cout << b << endl;
	
		super_a = long_long_to_super_long(a);
		super_b = long_long_to_super_long(b);
		print_super_long(super_a);
		print_super_long(super_b);
		
		if(a != super_long_to_long_long(super_a) || b != super_long_to_long_long(super_b))
		{
			failed = true;
			break;
		}
	}
		
	if(failed)
	{
		cout << "TEST from to";
		cin >> c;
	}
}

void TEST_Sum(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_sum;

	for(int i = 0; i < 10000; i++)
	{
		a = abs((rand() % max_rand) * 1);
		b = abs((rand() % max_rand) * 1);
		cout << a << endl;
		cout << b << endl;
	
		super_a = long_long_to_super_long(a);
		super_b = long_long_to_super_long(b);
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_sum = Sum(super_a, super_b);
		print_super_long(super_sum);
		
		if(a + b != super_long_to_long_long(super_sum))
		{
			failed = true;
			break;
		}
	}
	
	if(failed)
	{
		cout << "TEST Sum";
		cin >> c;
	}
}

void TEST_Sub(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_sub;

	for(int i = 0; i < 10000; i++)
	{
		a = abs((rand() % max_rand) + 1000000);
		b = abs((rand() % 1000000) * 1);
		cout << a << endl;
		cout << b << endl;
	
		super_a = long_long_to_super_long(a);
		super_b = long_long_to_super_long(b);
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_sub = Sub(super_a, super_b);
		print_super_long(super_sub);
		
		if(a - b != super_long_to_long_long(super_sub))
		{
			failed = true;
			break;
		}
	}
	
	if(failed)
	{
		cout << "TEST Sub";
		cin >> c;
	}
}

void TEST_Mul(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_mul;

	for(int i = 0; i < 10000; i++)
	{
		a = abs((rand() % 100000) + 1);
		b = abs((rand() % 100000) + 1);
		cout << a << endl;
		cout << b << endl;
	
		super_a = long_long_to_super_long(a);
		super_b = long_long_to_super_long(b);
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_mul = Mul(super_a, super_b);
		print_super_long(super_mul);
		
		if(a * b != super_long_to_long_long(super_mul))
		{
			failed = true;
			break;
		}
	}
	
	if(failed)
	{
		cout << "TEST Mul";
		cin >> c;
	}
}

