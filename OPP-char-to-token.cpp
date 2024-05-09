//  Operator Precedence Code

// In this , all the characters are converted into tokens and then determined whether the string is valid or invalid

#include<bits/stdc++.h>
using namespace std;

void fillMapping(map<string,int> &charToToken)
{
	charToToken["t"]=1;
	charToToken["f"]=2;
	charToToken["&&"]=3;
	charToToken["||"]=4;
	charToToken["~"]=5;
	charToToken["("]=6;
	charToToken[")"]=7;
}

void fillProductions(map<vector<int>,int> &productions)
{
	productions[{100,3,100}]=100;
	productions[{100,4,100}]=100;
	productions[{5,100}]=100;
	productions[{6,100,7}]=100;
	productions[{1}]=100;
	productions[{2}]=100;
}

void fillTable(vector<vector<char>> &table)
{
	table={
	{'A','L','L','L','L','L','L','N'},
	{'G','N','N','G','G','G','N','G'},
	{'G','N','N','G','G','G','N','G'},
	{'G','L','L','G','G','L','L','G'},
	{'G','L','L','L','G','L','L','G'},
	{'G','L','L','G','G','L','L','G'},
	{'G','L','L','L','L','L','L','E'},
	{'G','N','N','G','G','N','N','G'}	
	};
}
void fillInputStream(vector<int> &inputStream,string inputString,map<string,int> charToTokenId)
{
	for(int i=0;i<inputString.size();i++)
	{
		if(i!=inputString.size()-1 && inputString[i]=='&' && inputString[i+1]=='&')
		{
			inputStream.push_back(3);
			i++;
		}
		else if(i!=inputString.size()-1 && inputString[i]=='|' && inputString[i+1]=='|')
		{
			inputStream.push_back(4);
			i++;
		}
		else if(charToTokenId.find(string(1,inputString[i]))!=charToTokenId.end())
		{
			inputStream.push_back(charToTokenId[string(1,inputString[i])]);
		}
		else {
			cout<<"error at "<<i;
		}
	}
}

bool parser(vector<int> inputStream, map<vector<int>, int> productions, vector<vector<char>> table, int &tracer)
{
	stack<int> s;
	s.push(0);
	int lastPushedToken = 0;
	while (tracer != inputStream.size())
	{
		
		if (table[lastPushedToken][inputStream[tracer]] == 'L' || table[lastPushedToken][inputStream[tracer]] == 'E')
		{
			s.push(inputStream[tracer]);
			lastPushedToken = inputStream[tracer];
			tracer++;
		}
		else if (table[lastPushedToken][inputStream[tracer]] == 'G')
		{
			int lastPoppedToken = -1;
			int topOfStackToken = lastPushedToken;
			vector<int> buffer;
			while (lastPoppedToken == -1 || table[topOfStackToken][lastPoppedToken] == 'G' ||
			table[topOfStackToken][lastPoppedToken] == 'E')
			{
				
				while (s.top() >= 100)
				{
					buffer.push_back(s.top());
					s.pop();
				}
				lastPoppedToken = s.top();
				buffer.push_back(lastPoppedToken);
				s.pop();
				while (s.top() >= 100)
				{
					buffer.push_back(s.top());
					s.pop();
				}
				topOfStackToken = s.top();
			}
			reverse(buffer.begin(), buffer.end());
			if (productions.find(buffer) == productions.end())
			{

				return false;
			}
			int toReplace = productions[buffer];
			lastPushedToken = topOfStackToken;
			s.push(toReplace);
		}
		else if (table[lastPushedToken][inputStream[tracer]] == 'A')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (s.empty())
	return true;
	return false;
}

int main()
{
	string inputString;
	map<string,int> charToTokenId;
	vector<int> inputStream;
	map<vector<int>, int> productions;
	vector<vector<char>> table;
	int tracer=0;
	fillMapping(charToTokenId);
	fillProductions(productions);
	fillTable(table);
	cout<<"enter the input string:";
	cin>>inputString;
	fillInputStream(inputStream,inputString,charToTokenId);
	inputStream.push_back(0);
	if(parser(inputStream,productions,table,tracer))
	{
		cout<<"parsed successfully";
	}
	else
	{
		cout<<"error parsing token number "<<tracer;
	}
	
	
	return 0;
}
