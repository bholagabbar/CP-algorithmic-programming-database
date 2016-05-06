/*input
3
ababab ab
aaaaa bbb
aafafaasf aaf
*/
//Shreyans Sheth [bholagabbar]

#include <bits/stdc++.h>
using namespace std;
#define readFile freopen("E:/Shreyans/Documents/Coding Workspace/STDINPUT.txt","v",stdin);
#define getPrecision(s,p) fixed<<setprecision(p)<<s
#define boostIO ios_base::sync_with_stdio(0), cin.tie(0)
#define CLR(s) memset(&s, 0, sizeof s)
#define hashset unordered_set
#define hashmap unordered_map
#define PB push_back
#define MP make_pair
#define N 100010
#define F first
#define S second
#define endl '\n'

typedef long long int ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll modPrime = 1e9 + 7;
const ll base = 257;
ll basePower[N];

void calculatePowers() {
	basePower[0] = 1;
	for (int i = 1 ; i < N; i++) {
		basePower[i] = (basePower[i-1] * base) % modPrime;
	}
}

ll getStringHash(string s) {
	int len = s.size(); 
	int powCnt = 1;
	ll hashValue = s[len - 1];
	for (int i = len - 2 ; i >= 0; i--) {
		hashValue += s[i] * basePower[powCnt];
		hashValue %= modPrime;
		powCnt++;
	}
	return hashValue;
}

int main() {
	boostIO;
	calculatePowers();
	int tc;
	cin >> tc;
	while (tc--) {
		string text, pattern;
		cin >> text >> pattern;
		int textLen = text.size(), patternLen = pattern.size();
		ll patternHash = getStringHash(pattern);
		ll currTextHash = getStringHash(text.substr(0, patternLen));
		vector<int> occurences;
		for (int i = patternLen; i < textLen; i++) {
			if (patternHash == currTextHash && pattern.compare(text.substr(i - patternLen, patternLen)) == 0) {
				occurences.PB(i - patternLen + 1);
			}
			currTextHash -= text[i - patternLen] * basePower[patternLen - 1];
			if (currTextHash < 0) {
				currTextHash += modPrime;
			}
			currTextHash *= base;
			currTextHash += text[i];
		}
		if (patternHash == currTextHash && pattern.compare(text.substr(textLen - patternLen, patternLen)) == 0) {
			occurences.PB(textLen - patternLen + 1);
		}
		if (occurences.size() > 0) {
			cout << occurences.size() << endl;
			for (int i : occurences) {
				cout << i << " ";
			}
		} else {
			cout << "Not Found";
		}
		cout << endl << endl;
	}
	return 0;
}