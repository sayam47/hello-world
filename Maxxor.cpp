#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define pll pair<ll,ll>
#define all(x) x.begin(),x.end()
#define sz(x) (ll)x.size() 

ll power(ll x,ll y,ll p) 
{ 
    ll res = 1;      

    x = x % p;  

    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x) % p; 
  
        y = y>>1; 
        x = (x*x) % p;   
    } 
    return res; 
} 
ll cnt[1<<21],a[1<<21],dp[1<<21];
int main()
{
    ios_base::sync_with_stdio(false);
	ll n,i,j,k,x,y,t,m;

	cin >> t;
	while(t--)
	{
		cin >> n;
		for(i=1;i<=n;i++)
		{
			cin >> a[i];
			cnt[a[i]]++;
		}


		for(i=0;i<(1<<20);i++)
			dp[i]=cnt[i];

		for(j=0;j<20;j++)
		{
			for(i=0;i<(1<<20);i++)
				if(i&(1<<j))dp[i]+=dp[i^(1<<j)];
		}

		ll ans=0;

		
		for(i=0;i<=1e6;i++)
		{
			ans+=(dp[i]-cnt[i])*cnt[i];
			ans+=((cnt[i]*(cnt[i]-1))/2);
		}
		
		cout<<ans<<endl;
		
		for(i=1;i<=n;i++)
			cnt[a[i]]--;
	}
}
