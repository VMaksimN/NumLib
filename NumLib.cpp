#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<cmath>
#include<thread>
#include<string>
#include<chrono>
#include<ctime>

using namespace std;

	vector<short int> Zero(1,0);
	vector<short int> One(1,1);
	vector<short int> Two(1,2);
	
	const long long max_rand = 100000000000;
	const long long int amount_of_tests = 10000;
	
	
	void TEST_from_to(int id);
	void TEST_Sum(int id);
	void TEST_Sub(int id);
	void TEST_Mul(int id);
	void TEST_Div(int id);
	void Log(string test_name, string log);
	void Super_TEST_Sum(int id);
	void Super_TEST_Sub(int id);
	void Super_TEST_Mul(int id);
	void Super_TEST_Div(int id);

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
		if(num-> size() == 0)
		{
			return;
		}
		int k = 0;
		
		if((*num)[k] != 0)
		{
			return;
		}
		k++;
		
		while( k < num->size() && (*num)[k] == 0)
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
		vector<short int> ans;
		vector<short int> mod(a.begin(), a.end());
		short int was_divided = a.size();
		
		vector<short int>* current_minuend = new vector<short int>(0);
		vector<short int>* current_subtrahend;
		
		short int minuend_len = 0;
		
		if(b == Zero)
		{
			throw "It is impossible to divide by zero";
		}
		else if(b == One)
		{
			return make_pair(a, Zero);
		}
		else if(a == b)
		{
			return make_pair(One, Zero);
		}
		
		for(long long int w = 0; w > -1; w++)
		{
			for(int i = 0; i < mod.size(); i++)
			{
				if(mod[i] != 0)
				{
					break;
				}
				was_divided--;
				ans.push_back(0);
			}
			RemoveLeadingZeros(&mod);
			RemoveLeadingZeros(current_minuend);
			
			if(w != 0)
			{	
				if(current_minuend->size() < mod.size())
				{
					current_minuend->push_back(mod[current_minuend->size()]);
					was_divided--;
				}
				else
				{
					delete current_minuend;
					delete current_subtrahend;
					return make_pair(ans, mod);
				}
			}
			
			short int flag = 0;
			while(true)
			{
				if(current_minuend->size() < b.size())
				{
					if(current_minuend->size() < mod.size())
					{
						current_minuend->push_back(mod[current_minuend->size()]);
						ans.push_back(0);
						was_divided--;
					}
					else
					{
						ans.push_back(0);
						delete current_minuend;
						delete current_subtrahend;
						return make_pair(ans, mod);
					}
					continue;
				}
				else if(current_minuend->size() == b.size())
				{
					for (unsigned int i = 0; i < current_minuend->size(); i++)
					{
						if((*current_minuend)[i] > b[i])
						{
							flag = 0;
							break;
						}
						else if((*current_minuend)[i] < b[i])
						{
							flag = 1;
							break;
						}
						else if(i == current_minuend->size() - 1)
						{
							flag = 2;
							break;
						}
					}
					if(flag == 1)
					{
						if(current_minuend->size() < mod.size())
						{
							current_minuend->push_back(mod[current_minuend->size()]);
							ans.push_back(0);
							was_divided--;
						}
						else
						{
							ans.push_back(0);
							delete current_minuend;
							delete current_subtrahend;
							return make_pair(ans, mod);
						}
					}
				}
				break;
			}
		
			minuend_len = current_minuend->size();
			current_subtrahend = new vector<short int>(b.begin(), b.end());
			
			for(vector<short int> i(1,1); i[0] < 11; i[0]++)
			{
				*current_subtrahend = Mul(b, i);

				if(current_subtrahend->size() > current_minuend->size())
				{
					i[0]--;
					ans.push_back(i[0]);
					*current_minuend = Sub(*current_minuend, Mul(b, i));
					break;
				}
				else if(current_subtrahend->size() == current_minuend->size())
				{
					for (unsigned int j = 0; j < current_minuend->size(); j++)
					{
						if((*current_minuend)[j] > (*current_subtrahend)[j])
						{
							flag = 0;
							break;
						}
						else if((*current_minuend)[j] < (*current_subtrahend)[j])
						{
							flag = 1;
							break;
						}
						else if(j == current_minuend->size() - 1)
						{
							flag = 2;
							break;
						}
					}
					if(flag == 1)
					{
						i[0]--;
						ans.push_back(i[0]);
						*current_minuend = Sub(*current_minuend, Mul(b, i));
						break;
					}
					else if(flag == 2)
					{
						ans.push_back(i[0]);
						current_minuend = new vector<short int>(1,0);
						break;
					}
				}
				
			}
			
			for(int i = 0; i < mod.size(); i++)
			{
				if(mod[i] == 0)
				{
					mod[i] = -1;
				}
			}
			for(int i = minuend_len - 1, j = current_minuend->size() - 1; i > -1; i--, j--)
			{
				if(j > -1)
				{
					mod[i] = (*current_minuend)[j];
					continue;
				}
				mod[i] = 0;
			}
			RemoveLeadingZeros(&mod);
			RemoveLeadingZeros(&ans);
			
			for(int i = 0; i < mod.size(); i++)
			{
				if(mod[i] == -1)
				{
					mod[i] = 0;
				}
			}
			
			if(mod.size() > b.size()) /////////////CHECK THIS
			{
				continue;
			}
			else if(mod.size() == b.size()) /////////////CHECK THIS
			{
				for (unsigned int i = 0; i < mod.size(); i++)
				{
					if(mod[i] > b[i])
					{
						break;
					}
					else if(mod[i] < b[i])
					{
						while(was_divided != 0)
						{	
							was_divided--;
							ans.push_back(0);
						}
						delete current_minuend;
						delete current_subtrahend;
						return make_pair(ans, mod);
					}
					else if(i == mod.size() - 1)
					{
						while(was_divided != 1)
						{	
							was_divided--;
							ans.push_back(0);
						}
						ans.push_back(1);
						delete current_minuend;
						delete current_subtrahend;
						return make_pair(ans, Zero);
					}
				}
				
				continue;
			}
			else if(mod.size() < b.size()) /////////////CHECK THIS
			{
				if(was_divided == 0)
				{
					delete current_minuend;
					delete current_subtrahend;
					return make_pair(ans, mod);
				}
				else
				{
					while(was_divided != 0)
					{
						was_divided--;
						ans.push_back(0);
					}
					delete current_minuend;
					delete current_subtrahend;
					return make_pair(ans, mod);
				}
			}
		}
	}

int main()
{	
	srand(time(NULL));
	
	string a;
	cout << rand();
	cin>>a;
	
	/*vector<thread> threads;
	
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
	
	for(int i = 21; i < 26; i++)
	{
		thread thr(TEST_Div, i);
		threads.emplace_back(move(thr));
	}
	
	for(auto& thr : threads) 
	{
        thr.join();
    }*/
    
    Super_TEST_Sum(1);
	Super_TEST_Sub(1);
	Super_TEST_Mul(1);
}


void TEST_from_to(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;

	for(int i = 0; i < amount_of_tests; i++)
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
		Log("FROM_TO", to_string(a) + to_string(b));
	}
}

void TEST_Sum(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_sum;

	for(int i = 0; i < amount_of_tests; i++)
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
		Log("SUM", to_string(a) + to_string(b));
	}
}

void TEST_Sub(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_sub;

	for(int i = 0; i < amount_of_tests; i++)
	{
		a = abs((rand() % max_rand) + 100000000);
		b = abs((rand() % 10000000) * 1);
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
		Log("SUB", to_string(a) + to_string(b));
	}
}

void TEST_Mul(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_mul;

	for(int i = 0; i < amount_of_tests; i++)
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
		Log("MUL", to_string(a) + to_string(b));
	}
}

void TEST_Div(int id)
{
	bool failed = false;
	long long a, b, c;
	vector<short int> super_a;
	vector<short int> super_b;
	vector<short int> super_div;

	for(int i = 0; i < amount_of_tests; i++)
	{
		a = abs((rand() % max_rand)) + 10000000;
		b = abs((rand() % 100000) * 1) + 1;
		//cin >> a;
		//cin >> b;
		cout << a << endl;
		cout << b << endl;
	
		super_a = long_long_to_super_long(a);
		super_b = long_long_to_super_long(b);
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_div = Div(super_a, super_b).first;
		print_super_long(super_div);
		
		if(a / b != super_long_to_long_long(super_div))
		{
			failed = true;
			break;
		}
	}
	
	if(failed)
	{
		Log("DIV", to_string(a) + to_string(b));
	}
}

void Log(string test_name, string log)
{
	ofstream fout(test_name + ".txt", ios::app);
	fout << log << "\n";
	fout.close();
}



void Super_TEST_Sum(int id)
{
	vector<short int> super_a(512);
	vector<short int> super_b(512);
	vector<short int> super_sum;
	auto begin = chrono::high_resolution_clock::now();    
    
	for(int i = 0; i < amount_of_tests; i++)
	{
		for(int j = 0; j < 512; j++)
		{
			super_a[j] = abs(rand() % 10);
			super_b[j] = abs(rand() % 10);
		}
			
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_sum = Sum(super_a, super_b);
		print_super_long(super_sum);
	}
	
	auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    
    cout << "SUM with 2048-bit numbers\t elapsed: " << ms << endl;
    
	Log("SUM", "SUM with 2048-bit numbers\t elapsed: " + to_string(ms));
}

void Super_TEST_Sub(int id)
{
	vector<short int> super_a(512);
	vector<short int> super_b(511);
	vector<short int> super_sub;
	auto begin = chrono::high_resolution_clock::now();    
    
	for(int i = 0; i < amount_of_tests; i++)
	{
		super_a[0] = abs(rand() % 10);
		for(int j = 1; j < 512; j++)
		{
			super_a[j] = abs(rand() % 10);
			super_b[j - 1] = abs(rand() % 10);
		}
			
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_sub = Sub(super_a, super_b);
		print_super_long(super_sub);
	}
	
	auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    
    cout << "SUB with 2048-bit numbers\t elapsed: " << ms << endl;
	
	Log("SUB", "SUB with 2048-bit numbers\t elapsed: " + to_string(ms));
}

void Super_TEST_Mul(int id)
{
	vector<short int> super_a(512);
	vector<short int> super_b(512);
	vector<short int> super_mul;
	auto begin = chrono::high_resolution_clock::now();    
    
	for(int i = 0; i < amount_of_tests; i++)
	{
		for(int j = 0; j < 512; j++)
		{
			super_a[j] = abs(rand() % 10);
			super_b[j] = abs(rand() % 10);
		}
			
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_mul = Mul(super_a, super_b);
		print_super_long(super_mul);
	}
	
	auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    
    cout << "MUL with 2048-bit numbers\t elapsed: " << ms << endl;
    
	Log("MUL", "SUM with 2048-bit numbers\t elapsed: " + to_string(ms));
}

void Super_TEST_Div(int id)
{
	/*int size_a = abs(rand() % 512 + 1);
	int size_b = abs(rand() % 255 + 1);
	vector<short int> super_a(size_a);
	vector<short int> super_b(size_b);
	vector<short int> super_div;
	auto begin = chrono::high_resolution_clock::now();    
    
	for(int i = 0; i < amount_of_tests; i++)
	{
		for(int j = 0; j < 512; j++)
		{
			super_a[j] = abs(rand() % 10);
			super_b[j] = abs(rand() % 10);
		}
			
		print_super_long(super_a);
		print_super_long(super_b);
		
		super_sum = Sum(super_a, super_b);
		print_super_long(super_sum);
	}
	
	auto end = chrono::high_resolution_clock::now();    
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    
    cout << "SUM with 2048-bit numbers\t elapsed: " << ms << endl;
    
	Log("SUM", "SUM with 2048-bit numbers\t elapsed: " + to_string(ms));*/
}







